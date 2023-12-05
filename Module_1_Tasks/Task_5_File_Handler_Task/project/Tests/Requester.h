#ifndef REQUESTER_H
#define REQUESTER_H

#include "NamedPipe.h"
#include "SharedMemory.h"


class Requester {
public:
    void run();
    void printFileContent(const std::string& filePath);
    void listDirectory(const std::string& directoryPath);
    void notifyFileHandler();

private:
    NamedPipe namedPipe_;
    SharedMemory sharedMemory_;
};

#endif  // REQUESTER_H
