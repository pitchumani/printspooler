#include <iostream>
#include <vector>
#include <string>

#include "database.h"
#include "options.h"
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
    if (options.print) {
        std::cout << "Printing documents:" << std::endl;
        for (const auto& doc : options.printDocuments) {
            std::cout << "  - adding " << doc << " to print queue." << std::endl;
            // TODO: Implement actual printing logic
            // Check if the document exists, is accessible, etc.
        }
    }
    return 0;
}
