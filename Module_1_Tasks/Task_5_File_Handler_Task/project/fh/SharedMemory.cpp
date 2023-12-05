#include "SharedMemory.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>


SharedMemory::SharedMemory() : sharedMemoryId_(-1), sharedMemoryKey_("/tmp/my_shared_memory_key") {}

SharedMemory::~SharedMemory() {
    if (sharedMemoryId_ != -1) {
        shmctl(sharedMemoryId_, IPC_RMID, nullptr);
        sharedMemoryId_ = -1;
    }
}

void SharedMemory::write(const std::string& message) {
    key_t key = ftok(sharedMemoryKey_.c_str(), 1);
    sharedMemoryId_ = shmget(key, message.length(), IPC_CREAT | 0666);

    char* sharedMemory = static_cast<char*>(shmat(sharedMemoryId_, nullptr, 0));
    std::strcpy(sharedMemory, message.c_str());
    shmdt(sharedMemory);
}

std::string SharedMemory::read() {
    key_t key = ftok(sharedMemoryKey_.c_str(), 1);
   

    sharedMemoryId_ = shmget(key, 1024, 0666);
    char* sharedMemory = static_cast<char*>(shmat(sharedMemoryId_, nullptr, 0));
    std::string message = sharedMemory;
    shmdt(sharedMemory);
    return message;
}
