#ifndef CHEAPPRICEITEMLIST_H
#define CHEAPPRICEITEMLIST_H

#include <QWidget>

namespace Ui {
class CheapPriceItemList;
}

class CheapPriceItemList : public QWidget
{
    Q_OBJECT

public:
    explicit CheapPriceItemList(QWidget *parent = nullptr, const QString price="", const QString time="");
    ~CheapPriceItemList();

private:
    Ui::CheapPriceItemList *ui;
    QString price, time;
};

#endif // CHEAPPRICEITEMLIST_H
