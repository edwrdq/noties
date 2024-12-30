#include "main.h"

bool checkFlag() {
    std::ifstream flagFile("flag.txt")
    bool flag = false;

    if (flagFile.is_open()) {
        std::string value;
        flagFile >> value;
        flagFile.close();
    }

    if (value == "true") {
        flag = true;
    } else if (value == false) {
        flag = false;
    }

    return flag;
}

void notifyNode() {
    std::cout << "NOTIFY_NODE" << std::endl;   
}

int main() {
    std::string input;
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