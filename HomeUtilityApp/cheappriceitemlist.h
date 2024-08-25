#ifndef CHEAPPRICEITEMLIST_H
#define CHEAPPRICEITEMLIST_H

#include <QWidget>
#include "jsonhandler.h"

namespace Ui {
class CheapPriceItemList;
}

class CheapPriceItemList : public QWidget
{
    Q_OBJECT

public:
    explicit CheapPriceItemList(QWidget *parent = nullptr,  EHourPrice *eHp = nullptr);
    ~CheapPriceItemList();

    void setPriceTime(QString price, QString time);

private:
    Ui::CheapPriceItemList *ui;
    QString _price = "NaN";
    QString _time = "NaN";
};

#endif // CHEAPPRICEITEMLIST_H
