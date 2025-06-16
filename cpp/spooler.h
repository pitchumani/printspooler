#ifndef SPOOLER_H
#define SPOOLER_H

#include <string>
#include <vector>

class PrintJob {
    int id;
    std::string fileName;
    enum class STATUS { NONE, DONE, INPROGRESS, WAITING };
    STATUS status;
public:
    PrintJob(const std::string &filename) : fileName(filename) {}
};

class Printer {
private:
    int id;
    std::string name;
    std::vector<PrintJob> printQueue;
public:
    Printer(const std::string& name) : name(name) {}
    Printer(const int id, const std::string &name) : id(id), name(name) {}

    const std::string& getName() const {
        return name;
    }

    bool addToQueue(const std::string& document) {
        // Here we would normally check if the document exists and is accessible
        printQueue.push_back(PrintJob(document));
        return true; // Assume the job was added successfully
    }
};

class Spooler {
private:
    std::vector<Printer> printers;
    std::vector<PrintJob> printJobs;
    // make the constructor private to make it Singleton
    Spooler() {}
    static Spooler *printSpooler;
public:
    Spooler *getInstance();
    void addPrinter(const std::string& name);
    void removePrinter(const std::string& printerName);
    bool addToPrintQueue(const std::string& document, const std::string& printerName);
};

#endif // SPOOLER_H
