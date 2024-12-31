#include "main.h"
#include <QDebug>

main::NetworkUtils(QObject* parent)
    : QObject(parent) {
        connect(&networkManager, &QNetworkAccessManager::finished, this, &NetworkUtils::handleReply);
}

void main::postRequest(const QUrl& url, const QByteArray& data) {
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkManager.post(request, data);
}

void main::getRequest(const QUrl& url) {
    QNetworkRequest request(url);
    networkManager.get(request);
}

void main::handleReply(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        emit requestFinished(reply->readAll());
    } else {
        emit requestError(reply->errorString());
    }
    reply->deleteLater();
}

//almost