#include "main.h"

main::notesManager(const std::string& notesDirectory) : notesDirectory(notesDirectory) {
    if (!fs::exists(notesDirectory)) {
        fs::create_directories(notesDirectory);
    }
}


void main::saveNoteToDevice(const Note& note) {
    std::string filePath = notesDirectory + "/" + note.title + ".md";
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << note.content;
        file.close();

        notesCache[note.title] = note;
        notesCache[note.title].filePath = filePath;
        notesCache[note.title].lastModified = std::to_string(std::time(nullptr));
    }
}

void main::saveNoteToCloud(const Note& note) {
    json noteData = {
        {"title", note.title},
        {"content", note.content},
        {"lastModified", note.lastModified}
    };


    //network logic
}


void main::loadNoteFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    Note note;
    if (file.is_open()) {
        std::getline(file, note.content, "\0");
        note.title = fs::path(filePath).stem().string();
        note.filePath = filePath;
        note.lastModified = std::to_string(fs::last_write_time(filePath).time_since_epoch().count());
        file.close();
    }
    return note;
}

std::vector<Note> main::getAllNotes() {
    std::vector<Note> notes;
    for (const auto& entry : fs::directory_iterator(notesDirectory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".md") {
            notes.push_back(loadNoteFromFile(entry.path().string()));
        }
    }
    return notes;
}

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