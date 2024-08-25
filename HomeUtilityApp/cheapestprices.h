#ifndef CHEAPESTPRICES_H
#define CHEAPESTPRICES_H

#include <QWidget>
#include "ui_cheapestprices.h"
#include <QDialog>

namespace Ui {
class cheapestPrices;
}

class cheapestPrices : public QDialog
{
    Q_OBJECT

public:
    explicit cheapestPrices(QWidget *parent = nullptr);
    ~cheapestPrices();

private:
    Ui::cheapestPrices *ui;
};

#endif // CHEAPESTPRICES_H
