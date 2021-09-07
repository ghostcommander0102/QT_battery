#include "viewdialog.h"
#include "ui_viewdialog.h"
#include "tablemodel.h"
#include "chartdialog1.h"
#include "chartdialog2.h"

ViewDialog::ViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    ui->setupUi(this);
    view = ui->tableView;
    initUI();
}

ViewDialog::~ViewDialog()
{
    delete ui;
}

void ViewDialog::initUI () {
    rowindex = 4; columnindex = 1;
    vol_high = 2.14, vol_possible = 1.9, vol_impossible = 1.4;
    resi_high = 0.77;
    rel_high = 1.28;
    ui->volhigh_lbl->setText(QString::number(vol_high) + "V");
    ui->resihigh_lbl->setText(QString::number(resi_high) + "Ω");
    ui->relhigh_lbl->setText(QString::number(rel_high));

}

void ViewDialog::setFileName(QString name) {
    filename = name;
    initTable();
}


void ViewDialog::initTable() {
    tablecount = 0;
    QXlsx::Document xlsx(qApp->applicationDirPath() + "/list/" + filename + ".xlsx");

    if (!xlsx.isLoadPackage())
    {
        qDebug() << "[ReadExcel.xlsx] failed to load package";

    }

    for(int i=2;;i++){
        if(xlsx.read(9, i).toString() != "") {
            tablecount++;
            i+=7;
        }else{
            break;
        }
    }

    view->setStyleSheet("QHeaderView {background-color: transparent;}");

    QList<QVariant> first_column;
    first_column.append(QVariant(""));
    first_column.append(QVariant(""));
    first_column.append(QVariant("備考"));
    first_column.append(QVariant("セル"));
    for(int i=1;i<=24;i++){
        first_column.append(QVariant(i));
    }
    first_column.append("選択比較");
    first_column.append("");
    table_data.append(first_column);
    for(int i=0;i<tablecount * 4;i++){
        QList<QVariant> t_data;
        if(i % 4 == 0) {
            t_data.append(QVariant("測定日 " + xlsx.read(10, 6 + i * 2).toString()));
            t_data.append(QVariant("アワーメーター"));

        }else if(i%4==2){
            t_data.append(QVariant(""));

            t_data.append(QVariant(xlsx.read(12, 2 + (i-2) * 8)));
        }else{
            t_data.append(QVariant(""));
            t_data.append(QVariant(""));

        }
        t_data.append(QVariant(""));
        if(i%4==0){
            t_data.append(QVariant("電圧"));
        }else if(i%4==1){
            t_data.append(QVariant("抵抗"));
        }else if(i%4==2){
            t_data.append(QVariant("比重"));
        }else{
            t_data.append(QVariant("液温"));
        }
        for(int j=0;j<24;j++){
            t_data.append(QVariant(xlsx.read(14 + j, 2 + (i % 4) * 2 + (i - i % 4) / 4 * 8)));
        }
        t_data.append("");
        t_data.append("");
        table_data.append(t_data);
    }
    TableModel *PhoneBookModel = new TableModel(this);
    PhoneBookModel->populateData(table_data);
    view->setModel(PhoneBookModel);
    view->horizontalHeader()->setSectionResizeMode (QHeaderView::ResizeMode::Interactive);
    for(int i=1;i<table_data.length();i++) {
        view->setColumnWidth(i, 30);
    }
    view->setSpan(28, 0, 2, 1);
    view->setColumnWidth(0, 8);
    for(int i=0;i<tablecount;i++){
        view->setSpan(0, 1 + i * 4, 1, 4);
        view->setSpan(1, 1 + i * 4, 1, 2);
        view->setSpan(1, 3 + i * 4, 1, 2);
        view->setSpan(2, 1 + i * 4, 1, 4);
        view->setSpan(28, 1 + i * 4, 2, 4);
    }

    QHeaderView *verticalHeader = view->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(700.0 / 30);
    view->show();
    setSelectedCell();
}

void ViewDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    qDebug() << index.row() << ":" << index.column();
    if(index.row() == 28 && index.column() % 4 == 1) {
        ChartDialog1 *dlg = new ChartDialog1();
        dlg->setTableData(table_data, index.column());
        dlg->show();
    }
    if(index.row() == 2 && index.column() % 4 == 1) {
        ChartDialog2 *dlg = new ChartDialog2();
        dlg->setTableData(table_data, tablecount);
        dlg->show();
    }
    if(index.column() % 4 != 0 && index.row() >= 4 && index.row() <= 27) {
        columnindex = index.column() - index.column() % 4 + 1;
        rowindex = index.row();
        setSelectedCell();
    }
}

void ViewDialog::setSelectedCell(){
    double vol_value = table_data[columnindex][rowindex].toDouble();
    double resi_value = table_data[columnindex + 1][rowindex].toDouble();
    double rel_value = table_data[columnindex + 2][rowindex].toDouble();
    if(vol_value >= vol_high) {
        vol_value = vol_high;
    }
    if(resi_value >= resi_high){
        resi_value = resi_high;
    }
    if(rel_value >= rel_high) {
        rel_value = rel_high;
    }
    ui->vol_lbl->setText(QString::number(vol_value) + "V");
    ui->resi_lbl->setText(QString::number(resi_value) + "Ω");
    ui->rel_lbl->setText(QString::number(rel_value));
    ui->volValue_widget->setMinimumHeight(375 * vol_value / vol_high);
    ui->volGrid_widget->setMinimumHeight(375 * (vol_high - vol_value) / vol_high);

    ui->resiValue_widget->setMinimumHeight(375 * resi_value / resi_high);
    ui->resiGrid_widget->setMinimumHeight(375 * (resi_high - resi_value) / resi_high);

    ui->relValue_widget->setMinimumHeight(375 * rel_value / rel_high);
    ui->relGrid_widget->setMinimumHeight(375 * (rel_high - rel_value) / rel_high);

    ui->cellNumber_lbl->setText(QString::number(rowindex - 3) + "番");
    ui->cellDate_lbl->setText(table_data[1][0].toString());
    ui->cellHour_lbl->setText(table_data[1][1].toString() + " " + table_data[3][1].toString());
}

void ViewDialog::on_nextButton_clicked()
{
    if(rowindex != 27) {
        rowindex ++;
        setSelectedCell();
    }
}


void ViewDialog::on_prevButton_clicked()
{
    if(rowindex != 4) {
        rowindex --;
        setSelectedCell();
    }
}

