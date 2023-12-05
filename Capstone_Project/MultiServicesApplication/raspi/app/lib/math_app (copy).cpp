#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include "MsgQueue_lib.hpp"   // add Message Queue library
#include "boostLogger.h"        // add boost logger library	

void printHelp() {
    std::cout << "Usage: math_app <operand1> <operator> <operand2>" << std::endl;
    std::cout << "Supported operators: +, -, *, /" << std::endl;
}

int main(int argc, char* argv[]) {

 // Create a MessageQueSender instance with a unique key
    MessageQueSender sender("math", 10);
 // Send a message using MessageQueue:WriteLogs function
    sender.WriteLogs("Math Application: math application is started.. ");
    
    if (argc == 2 && std::string(argv[1]) == "--help") {
        printHelp();
        return 0;
    }

    if (argc != 4) {
    	//check the entered arguments: 
        std::cerr << "Invalid usage. Use --help for usage instructions." << std::endl;
        return 1;
    }

    double operand1 = std::stod(argv[1]);
    char oper = argv[2][0];
    double operand2 = std::stod(argv[3]);
    double result = 0.0;

    switch (oper) {
        case '+':       //add operation 
            result = operand1 + operand2;
            break;
        case '-':	//sub operation 
            result = operand1 - operand2;
            break;
        case '*':	//mul operation 
            result = operand1 * operand2;
            break;
        case '/':	//dev operation 
            if (operand2 != 0) {
                result = operand1 / operand2;
            } else {
                std::cerr << "Division by zero is not allowed." << std::endl;
                return 1;
            }
            break;
        default:
            std::cerr << "Unsupported operator: " << oper << std::endl;
            return 1;
    }
 // printing the result of the mathematical operation
    std::cout << "Result: " << result << std::endl;

 // Send a message using MessageQueue:WriteLogs function
    sender.WriteLogs("Math Application: Math Application has been closed.. Goodbye..!");

    return 0;
}


