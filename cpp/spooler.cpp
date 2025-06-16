#include "spooler.h"
Spooler *Spooler::printSpooler = nullptr;

Spooler *Spooler::getInstance() {
    if (!printSpooler)
        printSpooler = new Spooler();
    return printSpooler;
}

void Spooler::addPrinter(const std::string &name) {
    printers.push_back(Printer(name));
}

void Spooler::removePrinter(const std::string& printerName) {
    printers.erase(std::remove_if(printers.begin(), printers.end(),
                                    [&printerName](const Printer& p) { return p.getName() == printerName; }),
                                    printers.end());
}

bool Spooler::addToPrintQueue(const std::string& document, const std::string& printerName) {
    for (auto& printer : printers) {
        if (printer.getName() == printerName) {
            return printer.addToQueue(document);
        }
    }
    return false; // Printer not found
}
