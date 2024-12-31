#ifndef MAIN_H
#define MAIN_H



#include ".\md4c\src\entity.h"
#include ".\md4c\src\md4c-html.h"
#include ".\md4c\src\md4c.h"
#include <QApplication>
#include <QMainWindow>
#include "ui_mainwindow.h"
#include "json\single_include\nlohmann\json.hpp"
#include <iostream>
#include <thread>
#include <string>
#include <ctsdlib>
#include <fstream>
#include <map>
#include <vector>
#include <atomic>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QObject>

struct Note {
    std::string Title;
    std::string Content;
    std::string lastModified;
    std::string filePath;
};

class NotesManager{
public:
    NotesManager(const std::string& notesDirectory);
    void saveNoteToDevice(const Note& note);
    void saveNoteToCloud(const Note& note);
    void syncAllNotesToCloud();
    Note loadNoteFromFile(const std::string& filePath);
    std::vector<Note> getAllNotes();

private:
    std::string notesDirectory;
    std::map<std::string, Note> notesCache;
};

class AutoSaveManager {
public:
    AutosaveManager(NotesManager * notesManager);
    ~AutosaveManager();
    void startAutosave();
    void stopAutosave();

private:
    NotesManager * notesManager;
    std::thread autosaveThread;
    std::atomic<bool> running;
};

class NetworkUtils : public QObject {
    Q_OBJECT

public:
    explicit NetworkUtils(QObject* parent = nullptr);
    void postRequest(const QUrl& url, const QByteArray& data);
    void getRequest(const QUrl& url);

signals:
    void requestFinished(const QString& response);
    void requestError(const QString& error);

private slots:
    void handleReply(QNetworkReply* reply);

private:
    QNetworkAccessManager networkManager;

};

#endif MAIN_H

