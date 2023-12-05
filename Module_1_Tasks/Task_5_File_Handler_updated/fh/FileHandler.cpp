#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "simpleLogger.h"  // >> add logger library 

// Define the path to the named pipe
	const char* NAMED_PIPE_PATH = "/home/sherif/Desktop/FileHandler/my_named_pipe";  
// Define the key for shared memory
	const char* SHARED_MEMORY_KEY = "/home/sherif/Desktop/FileHandler/my_shared_memory_key";  

void executeCommandProcess() {
 // Open the named pipe for reading
    int pipeFd = open(NAMED_PIPE_PATH, O_RDONLY);  
    if (pipeFd == -1) {
        perror("Failed to open the named pipe for reading"); 
        return;
    }

    while (true) {
     // Create a buffer to read data from the named pipe
        char buffer[256];  
     // Read data from the named pipe
        ssize_t bytesRead = read(pipeFd, buffer, sizeof(buffer) - 1);  

     // Log each entered command
        LOG_INFO << "received command: " <<  bytesRead;

        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';

            std::string command = buffer;
            std::cout << "Received command: " << command << std::endl;

            size_t spacePos = command.find(' ');
            std::string cmd, path;
            if (spacePos != std::string::npos) {
                cmd = command.substr(0, spacePos);
                path = command.substr(spacePos + 1);
            } else {
                cmd = command;
            }

            if (cmd == "ls") {
                std::string lsCommand = "ls " + path;
                std::cout << "Executing: " << lsCommand << std::endl;
                system(lsCommand.c_str());
            } else if (cmd == "cat") {
                std::string catCommand = "cat " + path;
                std::cout << "Executing: " << catCommand << std::endl;
                system(catCommand.c_str());
            } else {
                std::cerr << "Invalid command received: " << command << std::endl;
            }
        }
    }

    close(pipeFd);
    sleep(1);
}

void sharedMemoryProcess() {
    int pipeFd = open(NAMED_PIPE_PATH, O_RDONLY);  // Open the named pipe for reading
    if (pipeFd == -1) {
        perror("Failed to open the named pipe for reading");  // Print an error message if opening the named pipe fails
        return;
    }

    while (true) {
        char buffer[256];  // Create a buffer to read data from the named pipe
        ssize_t bytesRead = read(pipeFd, buffer, sizeof(buffer) - 1);  // Read data from the named pipe

        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';

            std::string commandAndPath = buffer;
            std::cout << "Received command and path: " << commandAndPath << std::endl;

            size_t spacePos = commandAndPath.find(' ');
            std::string cmd, path;
            if (spacePos != std::string::npos) {
                cmd = commandAndPath.substr(0, spacePos);
                path = commandAndPath.substr(spacePos + 1);
            } else {
                cmd = commandAndPath;
            }

            if (cmd == "ls" || cmd == "cat") {
                std::string fullCommand = cmd + " " + path;
                std::cout << "Executing: " << fullCommand << std::endl;

			 // Execute the command and get the output
                FILE* commandOutput = popen(fullCommand.c_str(), "r");  
                if (commandOutput) {
                    std::string content;
                    char outputBuffer[1024];
                    while (fgets(outputBuffer, sizeof(outputBuffer), commandOutput)) {
                        content += outputBuffer;
                    }
                    pclose(commandOutput);
                    

                 // Generate a key for the shared memory
                    key_t shmKey = ftok(SHARED_MEMORY_KEY, 1);  
                    
                 // Create or access the shared memory segment
                    int sharedMemoryId = shmget(shmKey, content.size(), IPC_CREAT | 0666);

                    if (sharedMemoryId == -1) {
                     // Print an error message if creating or accessing shared memory fails
                        perror("Error creating/shared memory");  
                        return;
                    }
			     // Attach to the shared memory segment
                    char* sharedMemory = static_cast<char*>(shmat(sharedMemoryId, nullptr, 0));  
                    if (sharedMemory == reinterpret_cast<void*>(-1)) {
                     // Print an error message if attaching to shared memory fails
                        perror("Error attaching to shared memory");  
                        return;
                    }
                 // Copy the content to the shared memory
                    std::strcpy(sharedMemory, content.c_str());  
                 // Detach from the shared memory segment
                    shmdt(sharedMemory);  
                    sleep(1);  
                    std::cout << "Copied content to shared memory: " << content << std::endl;
                } else {
                    std::cerr << "Error executing command" << std::endl;
                }
            } else {
                std::cerr << "Invalid command received: " << cmd << std::endl;
            }
        }
    }

    close(pipeFd);  
}

int main() {

// Fork the process to create a child process
    pid_t pid = fork();  

    if (pid < 0) {
     // Print an error message if forking fails
        perror("Fork failed");  
        return 1;
    } 
    else if (pid == 0) {
     // Child process executes the executeCommandProcess function
        executeCommandProcess();
    } else {
     // Fork another process to create a second child process
        pid_t pid2 = fork();
	sleep(2);
        if (pid2 < 0) {
         // Print an error message if forking fails
            perror("Fork failed");  
            return 1;
        } else if (pid2 == 0) {
         // Second child process executes the sharedMemoryProcess function
            sharedMemoryProcess();
        }
    }

    return 0;
}
