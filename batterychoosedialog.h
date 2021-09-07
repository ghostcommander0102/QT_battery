#ifndef BATTERYCHOOSEDIALOG_H
#define BATTERYCHOOSEDIALOG_H

#include <QDialog>
#include <qdir.h>
#include <QComboBox>
#include <iostream>
#include <qdebug.h>
using namespace std;

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

QXLSX_USE_NAMESPACE
namespace Ui {
class BatteryChooseDialog;
}

class BatteryChooseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BatteryChooseDialog(QWidget *parent = nullptr);
    ~BatteryChooseDialog();
    void initDB();
    void getDataFromExcel(QString);
private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    QComboBox *combo;
    Ui::BatteryChooseDialog *ui;
    QString filename;
};

#endif // BATTERYCHOOSEDIALOG_H
