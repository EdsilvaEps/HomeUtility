#include "cheapestprices.h"
#include "ui_cheapestprices.h"

cheapestPrices::cheapestPrices(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cheapestPrices)
{
    ui->setupUi(this);
}

cheapestPrices::~cheapestPrices()
{
    delete ui;
}
