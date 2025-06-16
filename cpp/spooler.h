#ifndef SPOOLER_H
#define SPOOLER_H

#include <string>
#include <vector>
#include <queue>

#include "job.h"

// forware declaration
class Printer;

class Spooler {
private:
    std::vector<Printer*> printers;
    // make the constructor private to make it Singleton
    Spooler() {}
    static Spooler *printSpooler;

public:
    // mutex to control the concurrent access to the print jobs
    std::mutex mtx;
    std::condition_variable cond;
    std::queue<PrintJob> printJobs;

    static Spooler *getInstance();
    void addPrinter(const std::string& name);
    void removePrinter(const std::string& printerName);
    void addJob(const PrintJob& job);
};

#endif // SPOOLER_H
