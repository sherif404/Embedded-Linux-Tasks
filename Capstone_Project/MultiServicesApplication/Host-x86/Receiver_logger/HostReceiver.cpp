#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <semaphore.h>
#include <unistd.h>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "MsgQueue_lib.hpp"
#include "boostLogger.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    // Assign the path of the configuration file
    const char* configFilePath = "/etc/ConfigFile.txt";
    std::ifstream configFile(configFilePath);
    // Check opening configuration file
    if (!configFile) {
        std::cerr << "Error opening configuration file." << std::endl;
        return 1;
    }

    // Define variables for the content of each line in the conf. file.
    std::vector<std::string> appNames;
    std::string line;
    int appCounter = 1;
    std::string app1, app2, app3;

    while (std::getline(configFile, line)) {
        // Assign a limit for the accessible applications.
        if (appCounter > 10) {
            std::cerr << "Reached the maximum number of applications (10)." << std::endl;
            break;
        }
        // Assign the variables to the content of lines in the conf file.
        std::string varName = "app" + std::to_string(appCounter);
        std::string varValue = line;

        std::cout << "std::string " << varName << " = \"" << varValue << "\";" << std::endl;

        appNames.push_back(varName);

        // Assign app names based on the appCounter
        if (appCounter == 1) {
            app1 = varValue;
        } else if (appCounter == 2) {
            app2 = varValue;
        } else if (appCounter == 3) {
            app3 = varValue;
        }

        appCounter++;
    }

    configFile.close();

    // Create MessageQueReceiver objects based on the app names
    if (app1 == "math_app") {
        MessageQueReceiver receiverone("math", 10);
    }

    if (app2 == "print_app") {
        MessageQueReceiver receivertwo("print", 20);
    }

    if (app3 == "count_app") {
        MessageQueReceiver receiverthree("count", 30);
    }

//---------------------------------------------------------------------------------------
//---------------------Receiving Message Queue from the Applications---------------------


    while (true) {
// MATH APPLICATION
      // CREATE MessageQue and used as Receiver (instance with the same key with sender)
        MessageQueReceiver receiverone("math", 10);
      // Receive and read a message using the ReadLogs function
        receiverone.ReadLogs();

// COUNT APPLICATION
      // CREATE MessageQue and used as Receiver (instance with the same key with sender)
        MessageQueReceiver receivertwo("print", 20);
      // Receive and read a message using the ReadLogs function
        receivertwo.ReadLogs();

// Print APPLICATION
      // CREATE MessageQue and used as Receiver (instance with the same key with sender)
        MessageQueReceiver receiverthree("count", 30);
      // Receive and read a message using the ReadLogs function
        receiverthree.ReadLogs();
        
     // Establish a socket connection and receive data
     std::string serverIP = "127.0.0.1"; 
    int serverPort = 8080;
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("Error creating socket");
            return 1;
        }

        struct sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(serverPort);
        if (inet_pton(AF_INET, serverIP.c_str(), &(serverAddress.sin_addr)) <= 0) {
            perror("Invalid address/Address not supported");
            return 1;
        }

        if (connect(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
            perror("Connection failed");
            return 1;
        }
	// Set an appropriate buffer size
        const int bufferSize = 1024; 
        char buffer[bufferSize];
        memset(buffer, 0, bufferSize);

        ssize_t bytesRead;
        while ((bytesRead = recv(sockfd, buffer, bufferSize - 1, 0)) > 0) {
            // Process the received data as needed
            std::cout << "Received: " << buffer << std::endl;

            memset(buffer, 0, bufferSize);
        }

        if (bytesRead < 0) {
            perror("Error receiving data");
        }

        close(sockfd);
    }

    return 0;
}
