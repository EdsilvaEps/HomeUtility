#include "jsonhandler.h"

JsonHandler::JsonHandler(const QString &ePricesPath, const QString &weatherDataPath)
{
    this->_ePricesPath = ePricesPath;
    this->_weatherDataPath = weatherDataPath;
}

JsonHandler::JsonHandler()
{

}

std::unique_ptr<vector<EHourPrice>>
JsonHandler::getElectricityHourPrices(bool onlyCheapest = false)
{
    QString key = "hour_price";
    if(onlyCheapest) key = "cheapest_times";

    std::unique_ptr<QJsonObject> jsonHourPrices;
    auto eHourPrices = std::make_unique<vector<EHourPrice>>();

    try {
        jsonHourPrices = std::make_unique<QJsonObject>(parseJson(this->_ePricesPath));

    } catch (const std::ios_base::failure &e) {
        qWarning() << "Json file failure: " << e.what();
        return eHourPrices;
    }

    bool nextDay = false; // this flag will identify the next day hour/prices
    if (jsonHourPrices->contains(key) && jsonHourPrices->value(key).isArray()) {
            QJsonArray hour_prices_arr = jsonHourPrices->value(key).toArray();
            for (const QJsonValue &value : hour_prices_arr) {
                //qDebug() << "hour_price:" << value.toString();
                EHourPrice eHP = {"", 0.0}; // initialize a struct object of type EHourPrice
                QJsonObject obj = value.toObject();

                if (obj.contains("hour") && obj["hour"].isString()) {
                    eHP.hour = obj["hour"].toString() + "h";
                    if(nextDay) eHP.hour += "+";
                }

                if (obj.contains("price") && obj["price"].isDouble()) {
                    eHP.price = obj["price"].toDouble();
                }

                if(eHP.hour == "23h") nextDay = true;

                eHourPrices->push_back(eHP);
            }
        }

    return eHourPrices;

}

bool JsonHandler::ePricesAvailable()
{
    QFile file(this->_ePricesPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    return true;
}

bool JsonHandler::weatherDataAvailable()
{
    QFile file(this->_weatherDataPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    return true;
}

QJsonObject JsonHandler::parseJson(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Couldn't open the file.";
        throw std::ios_base::failure("json file could not be opened");
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    if (jsonDoc.isNull()) {
        qWarning() << "Failed to create JSON doc.";
        throw std::ios_base::failure("json could not be created");
    }
    if (!jsonDoc.isObject()) {
        qWarning() << "JSON is not an object.";
        throw std::ios_base::failure("json is not an object");
    }

    QJsonObject jsonObj = jsonDoc.object();
    qDebug() << "JSON Object:" << jsonObj;
    return jsonObj;

}

