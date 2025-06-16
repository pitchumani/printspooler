
#include "printer.h"
#include "options.h"

void Printer::print() {
    if (verbose) std::cout << "Started Printer::print thread!\n";
    while(true) {
    // get the lock for spooler's mutex
    std::unique_lock<std::mutex> lock(spooler->mtx);
    // wait for the job or till jobs queue is empty
    spooler->cond.wait(lock, [this]{ return !this->spooler->printJobs.empty(); });
    // get the job from the queue
    PrintJob job = spooler->printJobs.front();
    spooler->printJobs.pop();
    // unlock the lock
    lock.unlock();
    // simulate the print job
    for (int i = 0; i < 10000; ++i) {}
    if (verbose) std::cout << "- Printing task (doc: " << job.filename << ") completed!" << std::endl;
    }
}