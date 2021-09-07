#include "batterychoosedialog.h"
#include "ui_batterychoosedialog.h"
#include "viewdialog.h"
BatteryChooseDialog::BatteryChooseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BatteryChooseDialog)
{
    ui->setupUi(this);
    combo = ui->comboBox;
    initDB();

}

BatteryChooseDialog::~BatteryChooseDialog()
{
    delete ui;
}

void BatteryChooseDialog::initDB() {
    QString rootDir = qApp->applicationDirPath();
    QString data = "/list";
    qDebug()<<rootDir;
    QDir test(rootDir+data);
    QStringList testlist = test.entryList();
    for(int i=0;i<testlist.length();i++){
        if(testlist[i].endsWith(".xlsx")) {
            combo->addItem(testlist[i].split(".xlsx")[0]);
        }
    }
    getDataFromExcel(combo->currentText());
}

void BatteryChooseDialog::getDataFromExcel(QString fileName) {

    filename = fileName;
    qDebug() << fileName;
    QXlsx::Document xlsx(qApp->applicationDirPath() + "/list/" + fileName + ".xlsx");
    if (!xlsx.isLoadPackage())
    {
        qDebug() << "[ReadExcel.xlsx] failed to load package";

    }
    ui->ForkliftMaker_lbl->setText(xlsx.read("U4").toString());
    ui->ForkliftModel_lbl->setText(xlsx.read("H4").toString());
    ui->ForkliftModelYear_lbl->setText(xlsx.read("U5").toString());
    ui->BatteryModel_lbl->setText(xlsx.read("H5").toString());
    ui->BatteryYear_lbl->setText(xlsx.read("U3").toString());
    ui->BatterySerialNumber_lbl->setText(xlsx.read("H6").toString());
    QPixmap pix(qApp->applicationDirPath() + "/list/" + fileName + "1.png");

    ui->Battery_img->setPixmap(QPixmap(pix.scaled( ui->Battery_img->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
}

void BatteryChooseDialog::on_pushButton_clicked()
{
    ViewDialog *dlg = new ViewDialog();
    dlg->setFileName(filename);
    dlg->show();
    this->close();
}


void BatteryChooseDialog::on_comboBox_currentTextChanged(const QString &arg1)
{
    getDataFromExcel(combo->currentText());
    qDebug() << arg1;
}

