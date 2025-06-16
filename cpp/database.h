#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>

#include "spooler.h"

struct PrinterData {
    int id;
    std::string name;
    std::string status;
};

struct PrintJobData {
    int id;
    std::string filename;
    std::string status;
};

// FIXME: make this class as singleton
class DatabaseHandler {
    sqlite3 *db = nullptr;
    DatabaseHandler(sqlite3 *db) : db(db) {}
    ~DatabaseHandler() {
        sqlite3_close(db);
    }
    bool initialize();
public:
    // "print_spooler.db"
    static std::string dbFilename;
    static DatabaseHandler* Get();

    std::vector<PrinterData> getPrinters();
    bool addPrinter(std::string name);
    bool addPrintJob(std::string filename);
};

#endif // DATABASE_H
