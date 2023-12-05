#include <iostream>
#include <string>
#include "Requester.h"
#include "FileHandler.h"
#include "SharedMemory.h"


int main(int argc, char* argv[]);

int main() {

    FileHandler fileHandler;
    fileHandler.run();
    Requester requester;
    requester.run();

    return 0;
}



int main(int argc, char* argv[]) {
    if (argc < 3) {
        // Print an error message indicating correct usage
        std::cerr << "Usage: " << argv[0] << " <command> <path>" << std::endl;
        return 1;
    }

    // Extract the command and path from command-line arguments

    std::string command = argv[1];
    std::string path = argv[2];

    Requester requester;


// If the command is "cat", print the content of the specified file

    if (command == "cat") {
        requester.printFileContent(path);
    } 
// If the command is "ls", list the contents of the specified directory

    else if (command == "ls") {
        requester.listDirectory(path);
    } 
    
// If an invalid command is provided, print an error message
    
    else {
        std::cerr << "Invalid command: " << command << std::endl;
        return 1;
    }

    return 0;
}
