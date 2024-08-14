#ifndef ELECTRICITYGRAPH_H
#define ELECTRICITYGRAPH_H

#include <QWidget>
#include <QDialog>
#include "jsonhandler.h"


namespace Ui {
class ElectricityGraph;
}

class ElectricityGraph : public QDialog
{
    Q_OBJECT

public:
    explicit ElectricityGraph(QWidget *parent = nullptr);
    ~ElectricityGraph();

private:
    Ui::ElectricityGraph *ui;
    std::unique_ptr<vector<EHourPrice>> hourPrices;
    vector<int> getFloorCeiling(); // return a vector containing lowest and highest price values (indexes 0 and 1 respectively)
};

#endif // ELECTRICITYGRAPH_H
