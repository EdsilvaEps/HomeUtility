#include "cheapestprices.h"
#include "ui_cheapestprices.h"
#include "cheappriceitemlist.h"

cheapestPrices::cheapestPrices(QWidget *parent) :
    QDialog(parent), // will probably return this to QWidget(parent) when we're ready to embed
    ui(new Ui::cheapestPrices)
{
    ui->setupUi(this);

    auto dataHandler = std::make_unique<JsonHandler>();

    // get a unique pointer to a vector of HourPrice structs representing the cheapest times and prices for the day(s)
    auto EHourPrices = dataHandler->getElectricityHourPrices(true);

    if(!EHourPrices->empty()){

        try {

           // iterate through the list of Hour/Prices and populate our listItemWidget with elements
           for(EHourPrice ehp : *EHourPrices){
               auto listWidgetItem = new QListWidgetItem(ui->listWidget); // using keyword new cuz im sure how to pass ownership to ui::ListWidget
               ui->listWidget->addItem(listWidgetItem);

               auto cheapPriceItem = new CheapPriceItemList(ui->listWidget, &ehp);
               listWidgetItem->setSizeHint(cheapPriceItem->sizeHint());
               ui->listWidget->setItemWidget(listWidgetItem, cheapPriceItem); // encapsulate our custom item into a generic list item element
           }


        }

        catch (std::exception const& e) {
            qDebug() << "error populating list: " << e.what();
        }

    }
}

cheapestPrices::~cheapestPrices()
{
    delete ui;
}
