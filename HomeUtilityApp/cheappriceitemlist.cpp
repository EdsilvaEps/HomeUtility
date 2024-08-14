#include "cheappriceitemlist.h"
#include "ui_cheappriceitemlist.h"

CheapPriceItemList::CheapPriceItemList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheapPriceItemList)
{
    ui->setupUi(this);
}

CheapPriceItemList::~CheapPriceItemList()
{
    delete ui;
}
