#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <semaphore.h>
#include <unistd.h>
#include <vector>
#include "MsgQueue_lib.hpp"
#include "boostLogger.h"
#include "MsgQueue_lib.hpp"

  
std::string logFileName = "/home/sherif/Desktop/MultiServicesApplication/logger_deamon/build/logfile.txt";
void ProcessMessagesAndLogToFile(const std::string& logFileName);

int main() {

  
    LOG_TRACE << "Logger start as a deamon..";
    const char* configFilePath = "/etc/ConfigFile.txt";
    std::ifstream configFile(configFilePath);

    if (!configFile) {
        std::cerr << "Error opening configuration file." << std::endl;
        return 1;
    }

    std::vector<std::string> appNames;
    std::string line;
    int appCounter = 1;
    // Define variables for app names
    std::string app1, app2, app3; 

    while (std::getline(configFile, line)) {
        if (appCounter > 10) {
            std::cerr << "Reached maximum number of applications (10)." << std::endl;
            break;
        }

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
        MessageQueReceiver sync_receiver1("math", 10);
    }

    if (app2 == "print_app") {
        MessageQueReceiver sync_receiver2("print", 20);
    }

    if (app3 == "count_app") {
        MessageQueReceiver sync_receiver3("count", 30);

    }
    
//call the function that count the log file || create another one in case Log File reach 1000 msg.
   ProcessMessagesAndLogToFile(logFileName);

   
 //---------------------------------------------------------------------------------------
 //---------------------Receiving Message Queue from the Applications---------------------
   while(true){

 //MATH APPLICATION

	// CREATE MessageQue and used as Receiver (instance with the same key with sender)
       MessageQueReceiver sync_receiver1("math", 10);
       sync_receiver1.ReadLogs();
    

//COUNT APPLICATION
   
	// CREATE MessageQue and used as Receiver (instance with the same key with sender)
       MessageQueReceiver sync_receiver2("print", 20);
       sync_receiver2.ReadLogs();
    
    
//Print APPLICATION
   
	// CREATE MessageQue and used as Receiver (instance with the same key with sender)
       MessageQueReceiver sync_receiver3("count", 30);
       sync_receiver3.ReadLogs();
       sleep(2);
}

 

   return 0;
   
}

void ProcessMessagesAndLogToFile(const std::string& logFileName) {
    LOG_TRACE << "ProcessMessagesAndLogToFile function is opened..";
    const int maxLinesPerFile = 1000;
    int currentLineCount = 0;
    int fileNumber = 1;
    std::string message;

    MessageQueReceiver sync_receiver1("math", 10);
    MessageQueReceiver sync_receiver2("print", 10);
    MessageQueReceiver sync_receiver3("count", 10);

    while (true) {
        // Receive messages from different receivers
        std::string mathMessage = sync_receiver1.ReadLogs();
        sync_receiver1.ReadLogs();
        std::string printMessage = sync_receiver2.ReadLogs();
        sync_receiver2.ReadLogs();
        std::string countMessage = sync_receiver3.ReadLogs();
        sync_receiver3.ReadLogs();
        // Append the received messages to the main message string
        message += mathMessage + "\n" + printMessage + "\n" + countMessage + "\n";

        // Check if any of the messages is "end" to exit the loop
        if (mathMessage == "end" || printMessage == "end" || countMessage == "end") {
            break;
        }

        LOG_TRACE << message;

        currentLineCount++;
        if (currentLineCount >= maxLinesPerFile) {
            // Open the current log file
            std::ofstream logFile(logFileName + std::to_string(fileNumber) + ".txt", std::ios::app);

            if (!logFile) {
                std::cerr << "Failed to open the log file." << std::endl;
                return;
            }

            logFile << message << std::endl;
            logFile.close(); // Close the current log file

            message.clear(); // Clear the message buffer
            currentLineCount = 0;
            fileNumber++;
        }

        // Sleep for 1 second before processing the next messages
        sleep(5);
    }

    LOG_TRACE << "ProcessMessagesAndLogToFile function has been ended.";
}

