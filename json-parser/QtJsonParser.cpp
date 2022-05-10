
#include "QtJsonParser.h"

#include <sstream>
#include <iostream>
#include <vector>

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

auto QtJsonParser::parseJson(const std::string& jsonFilePath,
        JsonData& jsonData) -> void
{
    QFile file;
    QString filePath = QString::fromUtf8(jsonFilePath.c_str());
    file.setFileName(filePath);

    auto fileOpen = file.open(QIODevice::ReadOnly | QIODevice::Text);
    
    if (!fileOpen) {
        std::stringstream err;
        err << "Fail to parse the JSON file " << jsonFilePath;
        err << file.errorString().toUtf8().data();
        throw JsonParseException(err.str());
    }

    QString byteArray = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray.toUtf8());

    if (jsonDoc.isNull()) {
        file.close();
        throw JsonParseException("Null json document received !");
    }

    QJsonObject jsonObj = jsonDoc.object();

    if (jsonObj.isEmpty()) {
        file.close();
        throw JsonParseException("Empty Json object received !");
    }

    QJsonValue jsonValues = jsonObj["data"];
    if (!jsonValues.isObject()) {
        file.close();
        throw JsonParseException("Invalid data present in JSON !");
    }

    foreach (const QString& key, jsonValues.toObject().keys()) {
        QJsonValue jsonV = jsonValues.toObject().value(key);
        std::vector<std::string> values;
        std::string intent = key.toUtf8().data();
        QJsonArray jsonArr = jsonV.toArray();

        for(auto v : jsonArr) {
            values.push_back(v.toString().toUtf8().data());
        }

        jsonData[key.toUtf8().data()] = values;
    }

    file.close();
}