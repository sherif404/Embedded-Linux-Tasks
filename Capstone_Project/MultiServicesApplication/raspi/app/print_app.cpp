#include <iostream>
#include "MsgQueue_lib.hpp"   // add Message Queue library
#include "boostLogger.h"        // add boost logger library	



int main(int argc, char* argv[]) {

   // Create a MessageQueSender instance with a unique key
    MessageQueSender sender("print", 30);
    // Send a message using MessageQueue:WriteLogs function
    sender.WriteLogs("Print Application: Print application is started :) ");


    // Check if there's at least one command-line argument (excluding the program name)
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <string_to_print>" << std::endl;
        return 1; // Return with an error code
    }

    // Print the entered string
    std::cout << "Entered string: " << argv[1] << std::endl;

    // Send a message using MessageQueue:WriteLogs function
    sender.WriteLogs("Print Application: Print Application has been closed.. Goodbye ");
    
    
    return 0; 
}
