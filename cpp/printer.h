#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include <vector>
#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>

#include "job.h"
#include "options.h"
#include "spooler.h"

class Printer {
private:
    int id;
    std::string name;
    Spooler *spooler = nullptr;
    bool verbose = false;
    std::atomic<bool> stopFlag;

public:
    Printer(const std::string& name);
    const std::string& getName() { return name; }
    void print();
    void stop();
};

#endif // PRINTER_H
