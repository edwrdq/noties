#include "main.h"

void runNodeScript(const std::string& filePath) {
    
    std::string command = "node index.js" + filePath;

    int result = std::system(command.c_str());

    if (result == 0) {
        std::cout << "node.js executed succesfully" << std::endl;
    } else {
        std::cerr << "node.js error executing" << std::endl;
    }
}



int main() {
    std::string noteFilePath = "filepath"
    int charCount = 0;
    int cycleCount = 0;
    auto startTime = std::chrono::system_clock::now();
    while (true) {
        std::getline(std::cin, input);
        charCount = input.length();

        auto elapsedTime = std::chrono::system_clock::now();
        std::chrono::duration<double> duration = elapsedTime - startTime;
        auto seconds = duration.count();

        if (charCount >= 20) {
            charCount -= 20*cycleCount;
            cycleCount += 1;
            notifyNode();
        } else if (seconds >= 30) {
            notifyNode();
            startTime = std::chrono::system_clock::now();
        }
    }

    return 0;
}