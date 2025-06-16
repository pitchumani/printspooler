#include "spooler.h"
#include "printer.h"
#include "options.h"

Spooler *Spooler::printSpooler = nullptr;

Spooler *Spooler::getInstance() {
    if (!printSpooler)
        printSpooler = new Spooler();
    return printSpooler;
}

void Spooler::addPrinter(const std::string &name) {
    printers.push_back(new Printer(name));
}

void Spooler::removePrinter(const std::string& printerName) {
    printers.erase(std::remove_if(printers.begin(), printers.end(),
                                    [&printerName](Printer *p) { return p->getName() == printerName; }),
                                    printers.end());
}

void Spooler::addJob(const PrintJob &job) {
    std::unique_lock<std::mutex> lock(mtx);
    printJobs.push(job);
    lock.unlock();
    cond.notify_one();
    if (Options::Get()->verbose) {
        std::cout << "- Added print job (doc: " << job.filename << ")" << std::endl;
    }
}

