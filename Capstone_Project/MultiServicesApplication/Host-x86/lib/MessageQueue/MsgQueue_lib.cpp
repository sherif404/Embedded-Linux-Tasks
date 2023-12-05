#include "MsgQueue_lib.hpp"
#include <iostream>

MessageQueSender::MessageQueSender(const char* filePath, int id) {
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
    std::cout << "Data sent is : " << message.mesg_text << std::endl;
}

MessageQueReceiver::MessageQueReceiver(const char* filePath, int id) {
    key = ftok(filePath, id);
    msgid = msgget(key, 0666 | IPC_CREAT);
}

MessageQueReceiver::~MessageQueReceiver() {
   // msgctl(msgid, IPC_RMID, nullptr);
}

void MessageQueReceiver::ReadLogs() {

    msgrcv(msgid, &message, sizeof(message), 1, 0);
    std::cout << message.mesg_text << std::endl;
    //std::cout << "Data Received is : " << message.mesg_text << std::endl;
}

