#include "tablemodel.h"

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

void TableModel::populateData(const QList<QList<QVariant>> &table_data)
{
    tm_data.clear();
    tm_data = table_data;
    return;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return tm_data[0].length();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return tm_data.length();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
            return tm_data[index.column()][index.row()];
        else
            return QVariant();

}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
//    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
//        if (section == 0) {
//            return QString("Name");
//        } else if (section == 1) {
//            return QString("Phone");
//        }
//    }
    return QVariant();
}
