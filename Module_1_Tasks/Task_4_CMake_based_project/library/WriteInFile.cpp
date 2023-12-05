#include "WriteInFile.h"
#include <fstream>

void WriteInFile::writeHelloWorldToFile() {
    std::ofstream file("helloWorld.txt");
    if (file.is_open()) {
        file << "helloWorld" << std::endl;
        file.close();
    }
}
