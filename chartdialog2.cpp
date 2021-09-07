
#include "chartdialog2.h"
#include "ui_chartdialog2.h"
#include <qdebug.h>
ChartDialog2::ChartDialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartDialog2)
{
    ui->setupUi(this);
    m_chart = new QChart();
    axisX = new QBarCategoryAxis();
    axisY = new QValueAxis();
    m_series = new QBarSeries();
    m_chartView = new QChartView(m_chart, ui->widget_2);
}

ChartDialog2::~ChartDialog2()
{
    delete ui;
}

void ChartDialog2::setTableData(QList<QList<QVariant>> data, int count) {
    table_data = data;
    tablecount = count;
    chartindex = 1;

    createSeries();
}

void ChartDialog2::createSeries() {
    qDebug()<<chartindex;
    m_barSet.clear();
    axisX->clear();
    m_series->clear();


    for(int i=1;i<=tablecount;i++){
        QBarSet *set = new QBarSet(QString::number(i));
        m_barSet.append(set);
    }

    for(int j=0;j<tablecount;j++){
        for(int i=0;i<24;i++){
            *m_barSet.at(j) << table_data[chartindex + j * 4][4 + i].toDouble();
        }
        m_series->append(m_barSet.at(j));
    }
    m_chart->addSeries(m_series);
    QStringList categories;
    for(int i=1;i<=24;i++){
        categories << QString::number(i);
    }

    axisX->append(categories);

    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_series->attachAxis(axisX);


    axisY->setRange(0,15);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_series->attachAxis(axisY);

    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);
    m_chart->legend()->update();
    m_chartView->setGeometry(0,0,1100, 420);
    m_chartView->setRenderHint(QPainter::Antialiasing);
}

void ChartDialog2::on_pushButton_2_clicked()
{
    if(chartindex != 3) {
        chartindex ++;
        createSeries();
    }
}


void ChartDialog2::on_pushButton_clicked()
{
    if(chartindex != 1) {
        chartindex --;
        createSeries();
    }
}

