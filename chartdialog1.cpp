#include "chartdialog1.h"
#include "ui_chartdialog1.h"

ChartDialog1::ChartDialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartDialog1)
{
    ui->setupUi(this);
    m_chart = new QChart();
    axisX = new QBarCategoryAxis();
    axisY = new QValueAxis();
    m_series = new QBarSeries();
    m_chartView = new QChartView(m_chart, ui->widget_2);
}

ChartDialog1::~ChartDialog1()
{
    delete ui;
}

void ChartDialog1::setTableData(QList<QList<QVariant>> data, int index) {
    table_data = data;
    columnindex = index;
    createSeries();
}

void ChartDialog1::createSeries(){
    m_barSet.clear();
    axisX->clear();
    m_series->clear();


    for(int i=1;i<=3;i++){
        QBarSet *set = new QBarSet(QString::number(i));
        m_barSet.append(set);
    }

    for(int j=0;j<3;j++){
        for(int i=0;i<24;i++){
            *m_barSet.at(j) << table_data[columnindex + j][4 + i].toDouble();
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
