#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <vector>
#include <iostream>
#include <regex>

class Options {
private:
    std::vector<std::string> args;
    Options() {}
    static Options *instance;

public:
    static Options* Get();
    bool print = false;
    std::vector<std::string> printDocuments;
    bool cancel = false;
    std::string cancelJobId;
    bool status = false;
    bool list = false;
    enum class ListType { None, Jobs, Printers } listType = ListType::None;
    bool addPrinter = false;
    std::vector<std::string> printersToAdd;
    bool verbose = false;

    bool handleArgs(int argc, char *argv[]);
    void printUsage() const;
};

#endif // OPTIONS_H
