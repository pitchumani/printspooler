#include "database.h"

#include "options.h"

DatabaseHandler* DatabaseHandler::instance = nullptr;

// initialize the dbfilename static member
std::string DatabaseHandler::dbFilename = "print_spooler.db";

DatabaseHandler* DatabaseHandler::Get() {
    // create instance if not exists
    if (!instance) {
        sqlite3 *db = nullptr;
        int ret = sqlite3_open(DatabaseHandler::dbFilename.c_str(), &db);
        if (ret) {
            std::stringstream ss;
            ss << "Can't open database: " << sqlite3_errmsg(db);
            if (db) sqlite3_close(db);
            throw std::runtime_error(ss.str());
        }
        if (Options::Get()->verbose)
            std::cout << "Opened the database successfully!" << std::endl;

        instance = new DatabaseHandler(db);
        instance->initialize();
    }
    return instance;
}

// A callback function for SQLite to execute for each row of a result set
// This function will be called by sqlite3_exec for each row returned by the SELECT query
static int callbackPrinters(void* data, int argc, char** argv, char** azColName) {
    // Cast the 'data' pointer back to the type we expect (a vector of PrintJob)
    std::vector<PrinterData>* printers = static_cast<std::vector<PrinterData>*>(data);

    PrinterData printerData;
    // argc is the number of columns in the row
    // argv is an array of strings representing the data for each column
    // azColName is an array of strings representing the name of each column
    for (int i = 0; i < argc; i++) {
        std::string colName = azColName[i];
        if (colName == "ID") {
            printerData.id = argv[i] ? std::stoi(argv[i]) : -1;
        } else if (colName == "NAME") {
            printerData.name = argv[i] ? argv[i] : "NULL";
        } else if (colName == "STATUS") {
            printerData.status = argv[i] ? argv[i] : "NULL";
        }
    }
    printers->push_back(printerData);
    return 0; // Return 0 to continue processing rows
}

static int callbackPrintJobs(void* data, int argc, char** argv, char** azColName) {
    // Cast the 'data' pointer back to the type we expect (a vector of PrintJob)
    std::vector<PrintJobData>* jobs = static_cast<std::vector<PrintJobData>*>(data);

    PrintJobData job;
    // argc is the number of columns in the row
    // argv is an array of strings representing the data for each column
    // azColName is an array of strings representing the name of each column
    for (int i = 0; i < argc; i++) {
        std::string colName = azColName[i];
        if (colName == "ID") {
            job.id = argv[i] ? std::stoi(argv[i]) : -1;
        } else if (colName == "FILE_NAME") {
            job.filename = argv[i] ? argv[i] : "NULL";
        } else if (colName == "STATUS") {
            job.status = argv[i] ? argv[i] : "NULL";
        }
    }
    jobs->push_back(job);
    return 0; // Return 0 to continue processing rows
}

bool DatabaseHandler::addPrinter(std::string name) {
    std::stringstream ss;
    ss << "INSERT INTO PRINTERS (NAME,STATUS) VALUES ('"  << name << "', 'Waiting');";
    // Execute insert statements
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, ss.str().c_str(), callbackPrinters, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::stringstream ss;
        ss << "SQL INSERT error: " << zErrMsg;
        throw std::runtime_error(ss.str());
        return false;
    } else {
        if (Options::Get()->verbose)
            std::cout << "Records inserted successfully" << std::endl;
    }
    return true;
}

std::vector<PrinterData> DatabaseHandler::getPrinters() {
    const char* sqlSelect = "SELECT * FROM PRINTERS;";
    std::vector<PrinterData> printers; // Vector to store the results
    char *zErrMsg = 0;

    // Execute the select statement, passing our 'jobs' vector to the callback
    int rc = sqlite3_exec(db, sqlSelect, callbackPrinters, &printers, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::stringstream ss;
        ss << "SQL error: " << zErrMsg;
        throw std::runtime_error(ss.str());
    } else {
        std::cout << "DB Retrieval info:\n";
        for (const auto& printer : printers) {
            std::cout << "ID: " << printer.id << ", File: " << printer.name << ", Status: " << printer.status << std::endl;
        }
    }
    return printers;
}

bool DatabaseHandler::addPrintJob(std::string filename) {
    /*
    // 3. Insert some data into the table
    const char* sqlInsert1 = "INSERT INTO PRINT_JOBS (FILE_NAME,STATUS) VALUES ('document1.pdf', 'Waiting');";
    const char* sqlInsert2 = "INSERT INTO PRINT_JOBS (FILE_NAME,STATUS) VALUES ('image.png', 'Waiting');";
    const char* sqlInsert3 = "INSERT INTO PRINT_JOBS (FILE_NAME,STATUS) VALUES ('report_final.docx', 'Waiting');";

    // Execute insert statements
    rc = sqlite3_exec(db, sqlInsert1, callback, 0, &zErrMsg);
    rc = sqlite3_exec(db, sqlInsert2, callback, 0, &zErrMsg);
    rc = sqlite3_exec(db, sqlInsert3, callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error during INSERT: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Records inserted successfully" << std::endl;
    }
    */
    return true;
}




bool DatabaseHandler::initialize() {
    const char *sqlCreateTablePrinters = "CREATE TABLE IF NOT EXISTS PRINTERS("
                                            "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                            "NAME TEXT NOT NULL,"
                                            "STATUS TEXT NOT NULL);";
    char *errMsg = 0;
    int ret = sqlite3_exec(db, sqlCreateTablePrinters, 0, 0, &errMsg);
    if (ret != SQLITE_OK) {
        std::stringstream ss;
        ss << "SQLError: " << errMsg;
        throw std::runtime_error(ss.str());
    } else {
        if (Options::Get()->verbose)
            std::cout << "PRINTERS table created successfully or already exists" << std::endl;
    }

    const char* sqlCreateTablePrintJobs = "CREATE TABLE IF NOT EXISTS PRINT_JOBS("
                                            "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                            "FILE_NAME TEXT NOT NULL,"
                                            "STATUS TEXT NOT NULL);";
    // Execute the SQL statement
    char *errMsg2 = 0;
    int ret2 = sqlite3_exec(db, sqlCreateTablePrintJobs, callbackPrintJobs, 0, &errMsg2);
    if (ret2 != SQLITE_OK) {
        std::stringstream ss;
        ss << "SQLError: " << errMsg2;
        throw std::runtime_error(ss.str());
    } else {
        if (Options::Get()->verbose)
            std::cout << "Table created successfully or already exists" << std::endl;
    }

    return true;
}
