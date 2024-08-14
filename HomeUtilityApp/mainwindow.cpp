#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>
#include <QDebug>
#include "jsonhandler.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // open bar graph (experimental)
    //     EventEdit * dialog = new EventEdit(this);
    auto jsonHandler = std::make_unique<JsonHandler>();
    auto eData = jsonHandler->getElectricityHourPrices(false);
    for(EHourPrice e : *eData){
        qDebug() << "Hour " << e.hour;
    }


    auto eGraph = std::make_unique<ElectricityGraph>(this);

    //     dialog->exec();
    eGraph->exec();
    qDebug() << "electricity graph";



}

