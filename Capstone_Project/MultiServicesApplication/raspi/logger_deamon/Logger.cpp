#include <iostream>
#include <fstream>
#include <string>
#include <filesystem> 
#include <cstdlib>               // For system() function
#include <semaphore.h>
#include <unistd.h>
#include "MsgQueue_lib.hpp"     // add message queue library
#include "boostLogger.h"        // add boost logger library	

int main() {

    MessageQueReceiver receiverone("math", 10);
    MessageQueReceiver receivertwo("count", 20);
    MessageQueReceiver receiverthree("print", 30);

    // Provide the full path to the configuration file
 const char* configFilePath = "/etc/ConfigFile.txt"; // Path to the config file
    std::ifstream configFile(configFilePath);
    
    if (!configFile) {
        std::cerr << "Error opening configuration file." << std::endl;
        return 1;
    }

    std::vector<std::string> appNames;
    std::string line;
    int appCounter = 1;

    while (std::getline(configFile, line)) {
        if (appCounter > 10) {
            std::cerr << "Reached maximum number of applications (10)." << std::endl;
            break;
        }
        
        std::string varName = "app" + std::to_string(appCounter);
        std::string varValue = line;
        
        // Output the variable assignment
        std::cout << "std::string " << varName << " = \"" << varValue << "\";" << std::endl;
        
        appNames.push_back(varName);
        appCounter++;
    }

    configFile.close();


 //---------------------------------------------------------------------------------------
 //---------------------Receiving Message Queue from the Applications---------------------



 //MATH APPLICATION
   	sleep(2);
	// CREATE MessageQue and used as Receiver (instance with the same key with sender)
//    MessageQueReceiver receiver("math", 10);
	// Receive and read a message using the ReadLogs function
    receiverone.ReadLogs();
    

//COUNT APPLICATION
   
	// CREATE MessageQue and used as Receiver (instance with the same key with sender)
//    MessageQueReceiver receivertwo("count", 20);
	// Receive and read a message using the ReadLogs function
    receivertwo.ReadLogs();
    
    
//Print APPLICATION
   
	// CREATE MessageQue and used as Receiver (instance with the same key with sender)
//    MessageQueReceiver receiverthree("print", 30);
	// Receive and read a message using the ReadLogs function
    receiverthree.ReadLogs();



    return 0;
}
/*
  LOG_TRACE << "this is a trace message";
  LOG_DEBUG << "this is a debug message";
  LOG_WARNING << "this is a warning message: 
  LOG_ERROR << "this is an error message";
  LOG_FATAL << "this is a fatal error message";
*/  
    
