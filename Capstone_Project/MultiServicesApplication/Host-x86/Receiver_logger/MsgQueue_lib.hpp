#ifndef MSGQUEUE_LIB_HPP
#define MSGQUEUE_LIB_HPP

#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>

class  MessageQueSender {
private:
    struct mesg_buffer {
        long mesg_type;
        char mesg_text[100];
    } message;

    key_t key;
    int msgid;

public:
    MessageQueSender(const char* filePath, int id);
    ~MessageQueSender();

    void WriteLogs(const char* data);
};

class MessageQueReceiver {
private:
    struct mesg_buffer {
        long mesg_type;
        char mesg_text[100];
    } message;

    key_t key;
    int msgid;

public:
    MessageQueReceiver(const char* filePath, int id);
    ~MessageQueReceiver();

    void ReadLogs();
};

#endif // MSGQUEUE_LIB_HPP

