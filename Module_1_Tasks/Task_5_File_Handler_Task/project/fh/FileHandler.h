#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "NamedPipe.h"
#include "SharedMemory.h"

class FileHandler {
public:
    void run();

private:
    void handleRequests();

    NamedPipe namedPipe_;
    SharedMemory sharedMemory_;
};

#endif  // FILE_HANDLER_H

