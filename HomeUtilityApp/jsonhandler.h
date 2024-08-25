#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

using namespace std;
using multitype = variant<double, QString>;

struct EHourPrice {
    QString hour;
    double price;
};

struct WeatherHour {
    QString hour;
    float temp;
    float rainChance;
};

class JsonHandler
{
public:
    JsonHandler(const QString &ePricesPath, const QString &weatherDataPath);
    JsonHandler();

    std::unique_ptr<vector<EHourPrice>> getElectricityHourPrices(bool onlyCheapest);
    int getAverageElectricityPrice(); // TODO: make this a local calculation


private:
    QString _ePricesPath = "/home/edson/Documents/HomeUtility/HomeUtilityScripts/prices.json";
    QString _weatherDataPath = "";

    bool ePricesAvailable() noexcept;
    bool weatherDataAvailable() noexcept;
    QJsonObject parseJson(const QString &file);
};

#endif // JSONHANDLER_H
