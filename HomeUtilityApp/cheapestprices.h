#ifndef CHEAPESTPRICES_H
#define CHEAPESTPRICES_H

#include <QWidget>
#include "jsonhandler.h"
#include "ui_cheapestprices.h"

namespace Ui {
class cheapestPrices;
}

class cheapestPrices : public QWidget
{
    Q_OBJECT

public:
    explicit cheapestPrices(QWidget *parent = nullptr);
    ~cheapestPrices();

private:
    Ui::cheapestPrices *ui;
};

#endif // CHEAPESTPRICES_H
