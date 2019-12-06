#ifndef MOCK_CTABLEMODEL_H
#define MOCK_CTABLEMODEL_H
#include "../../src/ia_ctablemodel.h"
#include "test_data.h"

class Mock_CTableModel : public IA_CTableModel {
public:
    Mock_CTableModel();
    QList<QPair<QString, QString>>  getList( void ) const override;
    int                             rowCount(const QModelIndex&) const override;
    int                             columnCount(const QModelIndex&) const override;
    QVariant                        data(const QModelIndex&, int) const override;
    QVariant                        headerData(int, Qt::Orientation, int) const override;
    Qt::ItemFlags                   flags(const QModelIndex&) const override;
    bool                            setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole) override;
    bool                            insertRows(int, int, const QModelIndex&) override;
    bool                            removeRows(int, int, const QModelIndex&) override;
};

#endif // MOCK_CTABLEMODEL_H
