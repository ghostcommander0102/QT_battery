#ifndef CHARTDIALOG1_H
#define CHARTDIALOG1_H

#include <QDialog>
#include <QVariant>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class ChartDialog1;
}

class ChartDialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit ChartDialog1(QWidget *parent = nullptr);
    ~ChartDialog1();
    void setTableData(QList<QList<QVariant>>, int);
    void createSeries();
private:
    Ui::ChartDialog1 *ui;
    QList<QList<QVariant>> table_data;
    int columnindex;
    QChart *m_chart;
    QChartView *m_chartView;
    QBarCategoryAxis *axisX;
    QValueAxis *axisY;
    QBarSeries *m_series;
    QList<QBarSet*> m_barSet;

};

#endif // CHARTDIALOG1_H
