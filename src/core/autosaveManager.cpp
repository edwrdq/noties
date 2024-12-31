#include "main.h"

main::AutosaveManager(NotesManager* notesManager) : notesManager(notesManager), running(false) {}

main::AutosaveManager() {
    stopAutosave();
}

void main::startAutosave() {
    running = true;
    autosaveThread = std::thread([this](){
        while (running) {
            notesManager->syncAllNotesToCloud();
            std::this_thread::sleep_for(std::chrono::seconds(30));
        }
    });
}

void main::stopAutosave() {
    running = false;
    if (autosaveThread.joinable()) {
        autosaveThread.join();
    }
}