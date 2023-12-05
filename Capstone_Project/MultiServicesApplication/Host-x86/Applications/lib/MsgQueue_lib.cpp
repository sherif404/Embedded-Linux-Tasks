#include "MsgQueue_lib.hpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

//Declaration of timeStamp function
std::string GetTimestamp() {
    // Get the current time
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the time to a struct tm
    struct std::tm timeInfo;
    localtime_r(&currentTime, &timeInfo);

    // Create a string stream to format the timestamp
    std::ostringstream timestampStream;
    timestampStream << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S");
    return timestampStream.str();
}
    std::string timestamp = GetTimestamp();



MessageQueSender::MessageQueSender(const char* filePath, int id) {
    std::string timestamp = GetTimestamp();

    key = ftok(filePath, id);
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;
}

MessageQueSender::~MessageQueSender() {
    msgctl(msgid, IPC_RMID, nullptr);
}

void MessageQueSender::WriteLogs(const char* data) {
    strncpy(message.mesg_text, data, sizeof(message.mesg_text));
    msgsnd(msgid, &message, sizeof(message), 0);
  //  std::cout << "Data sent is : " << message.mesg_text << std::endl;
    std::cout << timestamp << ": " << message.mesg_text << std::endl;
}

MessageQueReceiver::MessageQueReceiver(const char* filePath, int id) {
    key = ftok(filePath, id);
    msgid = msgget(key, 0666 | IPC_CREAT);
}

MessageQueReceiver::~MessageQueReceiver() {
    msgctl(msgid, IPC_RMID, nullptr);
}

void MessageQueReceiver::ReadLogs() {

    msgrcv(msgid, &message, sizeof(message), 1, 0);    
    std::cout << timestamp << ": " << message.mesg_text << std::endl;

//    std::cout << "Data Received is : " << message.mesg_text << std::endl;
}



