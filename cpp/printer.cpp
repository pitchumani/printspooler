
#include "printer.h"
#include "options.h"

Printer::Printer(const std::string &name) : name(name) {
        spooler = Spooler::getInstance();
        stopFlag = false;
        verbose = Options::Get()->verbose;
    }

void Printer::print() {
    if (verbose) std::cout << "[" << name << "] Started Printer::print thread!\n";
    while(!stopFlag) {
        // get the lock for spooler's mutex
        std::unique_lock<std::mutex> lock(spooler->mtx);

        // wait for the job or for stopFlag to be set
        spooler->cond.wait(lock, [this]{
            return !this->spooler->printJobs.empty() || this->stopFlag;
        });
        // after wakeup, check if stopFlag is set
        if (stopFlag) {
            if (verbose) std::cout << "[" << name << "] stop flag detected, exiting.\n";
            break;
        }
        // job queue is not empty and stopFlag is not set
        // get the job from the queue
        PrintJob job = spooler->printJobs.front();
        spooler->printJobs.pop();
        // unlock the lock
        lock.unlock();
        // simulate the print job
        if (verbose) {
            std::cout << "[" << name << "] Printing task (doc: "
                << job.filename << ") started...\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
        if (verbose) {
             std::cout << "[" << name << "] Printing task (doc: " << job.filename
                 << ") completed!" << std::endl;
        }
    }
}

void Printer::stop() {
    stopFlag = true;
    // IMPORTANT: notify the condition variable to wake up the waiting threads
    spooler->cond.notify_all();
    // notify_one is to wake up a specific thread
}
