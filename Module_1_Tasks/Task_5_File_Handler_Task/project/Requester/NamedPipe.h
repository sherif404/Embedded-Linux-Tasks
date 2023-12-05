#ifndef NAMED_PIPE_H
#define NAMED_PIPE_H

#include <string>

class NamedPipe {
public:
    NamedPipe();
    ~NamedPipe();
    void create();
    void close();
    std::string read();
    void write(const std::string& message);

private:
    std::string pipeName_;
    int pipeDescriptor_;
};

#endif  // NAMED_PIPE_H
