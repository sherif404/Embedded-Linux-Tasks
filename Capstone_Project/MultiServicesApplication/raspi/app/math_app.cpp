#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void printHelp() {
    std::cout << "Usage: math_app <operand1> <operator> <operand2>" << std::endl;
    std::cout << "Supported operators: +, -, *, /" << std::endl;
}

int main(int argc, char* argv[]) {
 // Create a MessageQueSender instance with a unique key
    MessageQueSender sender("math", 10);

 // Send a message using MessageQueue:WriteLogs function
    sender.WriteLogs("Math Application: math application is started..");

    if (argc == 2 && std::string(argv[1]) == "--help") {
        printHelp();
        return 0;
    }

    if (argc != 4) {
        std::cerr << "Invalid usage. Use --help for usage instructions." << std::endl;
        return 1;
    }

    double operand1 = std::stod(argv[1]);
    char oper = argv[2][0];
    double operand2 = std::stod(argv[3]);
    double result = 0.0;

    switch (oper) {
        case '+':       // Add operation
            result = operand1 + operand2;
            break;
        case '-':       // Subtract operation
            result = operand1 - operand2;
            break;
        case '*':       // Multiply operation
            result = operand1 * operand2;
            break;
        case '/':       // Divide operation
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

 // Print the result of the mathematical operation
    std::cout << "Result: " << result << std::endl;

 // Establish a socket connection and send the output message
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

    std::string outputMessage = "Math Application Result: " + std::to_string(result);

    ssize_t bytesSent = send(sockfd, outputMessage.c_str(), outputMessage.length(), 0);
    if (bytesSent < 0) {
        perror("Error sending data");
    }

    close(sockfd);

    // Send a message using MessageQueue:WriteLogs function
    sender.WriteLogs("Math Application: Math Application has been closed.. Goodbye..!");

    return 0;
}
