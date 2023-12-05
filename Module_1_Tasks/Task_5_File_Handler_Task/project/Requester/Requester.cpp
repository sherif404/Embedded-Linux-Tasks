#include <iostream>
#include <string>
#include "Requester.h"
#include "SharedMemory.h"

void Requester::printFileContent(const std::string& filePath) {
    // Create the message to be sent through the shared memory
    std::string message = "cat " + filePath;

    // Write the message to the shared memory
    SharedMemory sharedMemory;
    sharedMemory.write(message);

    // Notify the FileHandler to process the message
    notifyFileHandler();
}

void Requester::listDirectory(const std::string& directoryPath) {
    // Create the message to be sent through the shared memory
    std::string message = "ls " + directoryPath;

    // Write the message to the shared memory
    SharedMemory sharedMemory;
    sharedMemory.write(message);

    // Notify the FileHandler to process the message
    notifyFileHandler();
}

void Requester::notifyFileHandler() {
    // Open the named pipe for writing
    FILE* pipe = fopen("/tmp/my_named_pipe", "w");

    // Send a notification to the FileHandler
    if (pipe) {
        fprintf(pipe, "1");
        fclose(pipe);
    } else {
        std::cerr << "Failed to open the named pipe for writing." << std::endl;
    }
}

int main() {
    Requester requester;

    // Perform the "cat" function to print file content
    requester.printFileContent("/path/to/file.txt");

    // Perform the "ls" function to list directory contents
    requester.listDirectory("/path/to/directory");

    return 0;
}
