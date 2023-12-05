#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <string>

class SharedMemory {
public:
    SharedMemory();
    ~SharedMemory();
    void write(const std::string& message);
    std::string read();

private:
    int sharedMemoryId_;
    std::string sharedMemoryKey_;
};

#endif  // SHARED_MEMORY_H
