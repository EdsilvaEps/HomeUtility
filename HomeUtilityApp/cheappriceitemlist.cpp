#include "cheappriceitemlist.h"
#include "ui_cheappriceitemlist.h"

CheapPriceItemList::CheapPriceItemList(QWidget *parent, EHourPrice *eHP) :
    QWidget(parent),
    ui(new Ui::CheapPriceItemList)
{
    ui->setupUi(this);

    if(!(eHP == nullptr)){
        QString p = QString::number(eHP->price, 'f', 2); // limit the decimal numbers
        this->_price = p + " c/Kwh"; // stupid concat but i dont wanna go looking for another way
        this->_time= eHP->hour;
    }

    ui->price->setText(this->_price);
    ui->time->setText(this->_time);


}


CheapPriceItemList::~CheapPriceItemList()
{
    delete ui;
}

void CheapPriceItemList::setPriceTime(QString price, QString time)
{
    this->_price=price + " c/Kwh";
    this->_time=time;
    ui->price->setText(price);
    ui->time->setText(time);

}
