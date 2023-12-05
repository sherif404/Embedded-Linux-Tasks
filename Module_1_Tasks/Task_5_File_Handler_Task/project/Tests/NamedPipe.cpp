#include "NamedPipe.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

NamedPipe::NamedPipe() : pipeName_("/tmp/my_named_pipe"), pipeDescriptor_(-1) {}

NamedPipe::~NamedPipe() {
    close();
}

void NamedPipe::create() {
    mkfifo(pipeName_.c_str(), 0666);
    pipeDescriptor_ = open(pipeName_.c_str(), O_RDWR);
}

void NamedPipe::close() {
    if (pipeDescriptor_ != -1) {
        ::close(pipeDescriptor_);
        ::unlink(pipeName_.c_str());
        pipeDescriptor_ = -1;
    }
}

std::string NamedPipe::read() {
    const int bufferSize = 1024;
    char buffer[bufferSize];
    std::string message;

    ssize_t bytesRead = ::read(pipeDescriptor_, buffer, bufferSize - 1);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        message = buffer;
    }

    return message;
}

void NamedPipe::write(const std::string& message) {
    ::write(pipeDescriptor_, message.c_str(), message.length());
}
