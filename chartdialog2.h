#ifndef CHARTDIALOG2_H
#define CHARTDIALOG2_H

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
class ChartDialog2;
}

class ChartDialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit ChartDialog2(QWidget *parent = nullptr);
    ~ChartDialog2();
    void setTableData(QList<QList<QVariant>>, int);
    void createSeries();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ChartDialog2 *ui;
    QList<QList<QVariant>> table_data;
    QChart *m_chart;
    QChartView *m_chartView;
    QBarCategoryAxis *axisX;
    QValueAxis *axisY;
    QBarSeries *m_series;
    QList<QBarSet*> m_barSet;
    int tablecount;
    int chartindex;
};

#endif // CHARTDIALOG2_H
