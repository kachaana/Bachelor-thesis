#include "mock_ctablemodel.h"

Mock_CTableModel::Mock_CTableModel() {}

QList<QPair<QString, QString>>  Mock_CTableModel::getList( void ) const {
    QPair<QString,QString> pair;
    pair.first = TEST_STRING;
    pair.second = TEST_STRING;
    QList<QPair<QString, QString>> ret_list;
    ret_list.push_back(pair);
    return ret_list;
}

int Mock_CTableModel::rowCount(const QModelIndex&) const {
    return TEST_INT;
}

int Mock_CTableModel::columnCount(const QModelIndex&) const {
    return TEST_INT;
}

QVariant Mock_CTableModel::data(const QModelIndex&, int) const {
    QVariant dummyVariant;
    return dummyVariant;
}

QVariant Mock_CTableModel::headerData(int, Qt::Orientation, int) const {
    QVariant dummyVariant;
    return dummyVariant;
}

Qt::ItemFlags Mock_CTableModel::flags(const QModelIndex&) const {
    return Qt::ItemFlag::NoItemFlags;
}

bool Mock_CTableModel::setData(const QModelIndex &, const QVariant &, int) {
    return RET_TRUE_FALSE;
}

bool Mock_CTableModel::insertRows(int, int, const QModelIndex&) {
    return RET_TRUE_FALSE;
}

bool Mock_CTableModel::removeRows(int, int, const QModelIndex&) {
    return RET_TRUE_FALSE;
}
