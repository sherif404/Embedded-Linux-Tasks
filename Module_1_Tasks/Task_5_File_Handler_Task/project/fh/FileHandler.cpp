#include "FileHandler.h"
#include <boost/log/trivial.hpp>
#include <sstream>
#include "SharedMemory.h"

void FileHandler::run() {
    namedPipe_.create();
    BOOST_LOG_TRIVIAL(info) << "[FileHandler] Started.";

    handleRequests();

    namedPipe_.close();
    BOOST_LOG_TRIVIAL(info) << "[FileHandler] Stopped.";
}

void FileHandler::handleRequests() {
    std::string request;
    while ((request = namedPipe_.read()) != "EXIT") {
        BOOST_LOG_TRIVIAL(info) << "[FileHandler] Received request: " << request;

        if (request == "LIST_FILES") {
            // Simulating file list retrieval
            std::string fileList = "file1.txt\nfile2.txt\nfile3.txt";
            sharedMemory_.write(fileList);
        } else if (request.find("GET_CONTENT:") == 0) {
            std::string filename = request.substr(12);
            // Simulating file content retrieval
            std::string fileContent = "Content of " + filename;
            sharedMemory_.write(fileContent);
        }
    }
}


int main() {



  FileHandler fileHandler;
    fileHandler.run();

    return 0;
}


