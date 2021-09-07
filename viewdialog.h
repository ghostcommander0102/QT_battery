#ifndef VIEWDIALOG_H
#define VIEWDIALOG_H

#include <QDialog>
#include <qtableview.h>
#include <iostream>
#include <qdebug.h>
#include <QVariant>
using namespace std;

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

QXLSX_USE_NAMESPACE
namespace Ui {
class ViewDialog;
}

class ViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewDialog(QWidget *parent = nullptr);
    ~ViewDialog();
    void setFileName(QString);
    void initTable();
    void initUI();
    void setSelectedCell();
private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_nextButton_clicked();

    void on_prevButton_clicked();

private:
    Ui::ViewDialog *ui;
    QList<QList<QVariant>> table_data;
    QTableView *view;
    QString filename;
    int tablecount;
    int rowindex;
    int columnindex;
    double vol_high,resi_high,rel_high,vol_possible,vol_impossible;
};

#endif // VIEWDIALOG_H
