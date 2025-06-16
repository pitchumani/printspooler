#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include <vector>
#include <mutex>
#include <iostream>

#include "job.h"
#include "options.h"
#include "spooler.h"

class Printer {
private:
    int id;
    std::string name;
    Spooler *spooler = nullptr;
    bool verbose = false;
public:
    Printer(const std::string& name) : name(name) {
        spooler = Spooler::getInstance();
        verbose = getOptions().verbose;
    }
    const std::string& getName() { return name; }
    void print();
};

#endif // PRINTER_H