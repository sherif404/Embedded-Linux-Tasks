#include <iostream>
#include "MsgQueue_lib.hpp"   // add Message Queue library
#include "boostLogger.h"        // add boost logger library	

int main() {


   // Create a MessageQueSender instance with a unique key
    MessageQueSender sender("count", 20);
    // Send a message using MessageQueue:WriteLogs function
    sender.WriteLogs("Count Application: Count application is started  :) ");
    
    //simple count application, counting from 1 to 5 :) ..
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << std::endl;
    }


    // Send a message using MessageQueue:WriteLogs function
    sender.WriteLogs("Count Application: Count Application has been closed.. Goodbye..!");

    return 0;
}
