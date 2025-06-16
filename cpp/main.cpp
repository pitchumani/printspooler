#include <iostream>
#include <vector>
#include <string>
#include <thread>

#include "database.h"
#include "options.h"
#include "printer.h"
#include "spooler.h"

int main(int argc, char* argv[]) {
    auto options = getOptions();
    if (!options.handleArgs(argc, argv)) return 1;

    DatabaseHandler *dbHandler = nullptr;
    try {
        dbHandler = DatabaseHandler::Get();
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // TODO: move dbhandling and print jobs to spooler functions
    // User - producer of PrintJob objects and add it to the queue in the Spooler
    // Printer - consumer of PrintJob objects, takes the jobs from queue in the Spooler

    Spooler *printSpooler = Spooler::getInstance();
    Printer printer1("Printer1");
    if (options.status) {
        std::cout << "Status of print jobs:" << std::endl;
        std::cout << "  - To be implemented: Job status details." << std::endl;
        std::cout << "Status of Printers:" << std::endl;
        std::cout << "  - To be implemented: Printer status details." << std::endl;
    }
    if (options.list) {
        if (options.listType == Options::ListType::Jobs) {
            std::cout << "Listing all print jobs:" << std::endl;
        } else if (options.listType == Options::ListType::Printers) {
            std::cout << "Listing all printers:" << std::endl;
            auto printers = dbHandler->getPrinters();
        }
    }
    if (options.addPrinter) {
        std::cout << "Adding a printer" << std::endl;
        for (auto &p : options.printersToAdd) {
            dbHandler->addPrinter(p);
        }
    }
    auto printFunc = [&printer1]() {
        std::cout << "Starting print thread!\n";
        printer1.print();
    };
    std::thread printThread(printFunc);
    if (options.print) {
        std::cout << "Printing documents:" << std::endl;
        for (const auto& doc : options.printDocuments) {
            printSpooler->addJob(PrintJob(doc));
            // TODO: Implement actual printing logic
            // Check if the document exists, is accessible, etc.
        }
    }
    printThread.join();
    return 0;
}
