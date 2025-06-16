#include "options.h"

Options& getOptions() {
    static Options optHandler;
    return optHandler;
}

bool Options::handleArgs(int argc, char *argv[]) {
    // Store command line arguments
    for (int i = 0; i < argc; ++i) {
        args.push_back(argv[i]);
    }

    if (args.size() < 2) {
        std::cerr << "Error: Not enough arguments provided." << std::endl;
        printUsage();
        return false;
    }

    for (size_t index = 1; index < args.size(); ++index) {
        const auto& arg = args[index];
        if (arg == "--help") {
            printUsage();
            return true;
        } else if (arg == "--print") {
            if (index + 1 < args.size()) {
                print = true;
                printDocuments.push_back(args[index + 1]);
                index += 1;
            } else {
                std::cerr << "Error: No document specified for printing." << std::endl;
                return false;
            }
        } else if (arg == "--cancel") {
            if (index + 1 < args.size()) {
                cancel = true;
                cancelJobId = args[index + 1];
                index += 1;
            } else {
                std::cerr << "Error: No job ID specified for cancellation." << std::endl;
                return false;
            }
        } else if (arg == "--status") {
            status = true;
            index++;
        } else if (arg == "--list") {
            if (index + 1 < args.size()) {
                list = true;
                if (args[index + 1] == "jobs") {
                    listType = ListType::Jobs;
                } else if (args[index + 1] == "printers") {
                    listType = ListType::Printers;
                } else {
                    std::cerr << "Error: Invalid type specified for listing." << std::endl;
                    return false;
                }
                index += 1;
            } else {
                std::cerr << "Error: No type specified for listing." << std::endl;
                return false;
            }
        } else if (arg == "--add") {
            if (index + 1 < args.size()) {
                addPrinter = true;
                auto name = args[index + 1];
                bool is_valid = std::regex_match(name, std::regex("^[A-Za-z_][A-Za-z_0-9]*"));
                if (!is_valid) {
                    std::cerr << "Error: Invalid printer name." << std::endl;
                    return false;
                }
                printersToAdd.push_back(name);
                index += 1;
            } else {
                std::cerr << "Error: Printer name is not specified." << std::endl;
                return false;
            }
        } else if (arg == "--verbose") {
            verbose = true;
        } else {
            std::cerr << "Error: Unknown command '" << arg << "'." << std::endl;
            printUsage();
            return false;
        }
    }
    return true;
}

void Options::printUsage() const {
    std::cout << "Usage: " << args[0] << " [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --print <document>      Print the specified document" << std::endl;
    std::cout << "  --cancel <job_id>       Cancel the specified print job" << std::endl;
    std::cout << "  --status                Check the status of the print spooler" << std::endl;
    std::cout << "  --list <jobs|printers>  List all print jobs or printers" << std::endl;
    std::cout << "  --help                  Show this help message" << std::endl;
    std::cout << "  --add <printer>         Add the printer to the list" << std::endl;
    std::cout << "  --verbose               Enable verbose outputs" << std::endl;
}

