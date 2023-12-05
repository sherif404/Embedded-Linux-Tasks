#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "simpleLogger.h"   // >> add logger library 

const char* NAMED_PIPE_PATH = "/home/sherif/Desktop/FileHandler/my_named_pipe";
const char* SHARED_MEMORY_KEY = "/home/sherif/Desktop/FileHandler/my_shared_memory_key";

int main(int argc, char* argv[]) {

 

	//using boost to logger to generate information message 
      LOG_INFO << "Requester application has been started ..";
  
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <command> <path>" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    std::string path = argv[2];

    // Open the named pipe for writing
    int pipeFd = open(NAMED_PIPE_PATH, O_WRONLY);

    if (pipeFd == -1) {
        perror("Failed to open the named pipe for writing");
        return 1;
    } 
    LOG_INFO << "Open NamedPipe to receive data, and send data to shared memory..";
    std::string message = command + " " + path;

    // Write the message to the named pipe
    ssize_t bytesWritten = write(pipeFd, message.c_str(), message.size());

    if (bytesWritten == -1) {
        perror("Error writing to the named pipe");
        close(pipeFd);
        return 1;
    }

    close(pipeFd);

//--------------------------------------------------
// Open shared memory
	sleep(2);
    key_t shmKey = ftok(SHARED_MEMORY_KEY, 1);
    int sharedMemoryId = shmget(shmKey, 0, 0);
    
    if (sharedMemoryId == -1) {
        perror("Error getting shared memory ");
        return 1;
    }
      LOG_INFO << "Extracting data from shared memory..";

    // Attach to shared memory
    char* sharedMemory = static_cast<char*>(shmat(sharedMemoryId, nullptr, 0));
    if (sharedMemory == reinterpret_cast<void*>(-1)) {
        perror("Error attaching to shared memory");
        return 1;
    }

    // Read from shared memory
    std::string content(sharedMemory);
    
    // Detach from shared memory
    if (shmdt(sharedMemory) == -1) {
        perror("Error detaching from shared memory");
        return 1;
    }
      LOG_INFO << "Shared memory is closed ..";
    std::cout << "Received content from shared memory:\n" << content << std::endl;

    return 0;

}

