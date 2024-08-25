#include "electricitygraph.h"
#include "ui_electricitygraph.h"
#include "jsonhandler.h"
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QChart>
#include <QLegend>
#include <QValueAxis>

#include <QChart>
#include <QChartView>

ElectricityGraph::ElectricityGraph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ElectricityGraph)
{
    ui->setupUi(this);
    auto jsonHandler = std::make_unique<JsonHandler>();
    // get regular electricity price/hour
    hourPrices = jsonHandler->getElectricityHourPrices(false);

    //![1] set X-Axis labels and their data

    QBarSeries *series = new QBarSeries;
    auto pricesBarSet = new QBarSet("electricyPrices");
    QStringList cats;

    for(const EHourPrice &e : *hourPrices){
        *pricesBarSet << e.price;
        cats.append(e.hour);
    }

    series->append(pricesBarSet); // append the created sets to the QBarSeries

    //![2]

    //![3]
    auto chart = new QChart;
    chart->setTheme(QChart::ChartThemeBlueNcs);
    chart->addSeries(series);
    series->setBarWidth(0.5);
    chart->setTitle("Simple Bar Chart");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    //![3]

    //![4]
    auto axisX = new QBarCategoryAxis;
    axisX->append(cats);
    axisX->setRange("00h", "05h+");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto axisY = new QValueAxis;
    auto range = getFloorCeiling();
    axisY->setRange(range[0],range[1]);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //![4]

    //![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //![5]
    //!
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->fitInView(chartView->chart()->plotArea(), Qt::KeepAspectRatio);
    ui->gridLayout->addWidget(chartView, 1,0);




}

ElectricityGraph::~ElectricityGraph()
{
    delete ui;
}

vector<int> ElectricityGraph::getFloorCeiling()
{
    vector<int> range = {0,0};
    double highest = 0;
    double lowest = 0;
    if(!hourPrices->empty()){
        for(EHourPrice e : *hourPrices){
            e.price > highest ? highest = e.price : highest ;
            e.price < lowest ? lowest = e.price : lowest;
            if(e.hour == "05h+") break;
        }
    }

    if(lowest < 0){
        range[0] = (int)lowest - 1;
    }
    range[1] = (int)highest + 1;
    qDebug() << "range: (" << range[0] << "," << range[1] << ")";
    return range;
}
