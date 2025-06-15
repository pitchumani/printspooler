#include <iostream>
#include <vector>
#include <string>

#include "options.h"

int main(int argc, char* argv[]) {
    Options options(argc, argv);

    bool status = options.handleArgs();
    if (!status) {
        return 1;
    }
    
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