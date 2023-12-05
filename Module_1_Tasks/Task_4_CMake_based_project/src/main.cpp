#include "Print.h"
#include "WriteInFile.h"
#include <string>

int main(int argc, char** argv) {
    if (argc > 1 && std::string(argv[1]) == "-c") {
        Print p;
        p.printHelloWorld();
    } else if (argc > 1 && std::string(argv[1]) == "-f") {
        WriteInFile w;
        w.writeHelloWorldToFile();
    }
    return 0;
}
