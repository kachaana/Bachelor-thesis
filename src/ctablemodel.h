#ifndef CTABLEMODEL_H
#define CTABLEMODEL_H
#include <QAbstractItemModel>
#include <QTableView>
#include <QItemDelegate>
#include <QMimeData>
#include <QSize>
#include <QList>
#include <QPair>
#include <QDebug>
#include "cfilemanager.h"
#include "ia_ctablemodel.h"


class CTableModel : public IA_CTableModel {
    Q_OBJECT
public:
    CTableModel();
    CTableModel(QList<QPair<QString, QString> > listofPairs);
    ~CTableModel() override;

    int                             rowCount(const QModelIndex&) const override;
    int                             columnCount(const QModelIndex&) const override;
    QVariant                        data(const QModelIndex&, int) const override;
    QVariant                        headerData(int, Qt::Orientation, int) const override;
    Qt::ItemFlags                   flags(const QModelIndex&) const override;
    bool                            setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole) override;
    bool                            insertRows(int, int, const QModelIndex&) override;
    bool                            removeRows(int, int, const QModelIndex&) override;
    QList<QPair<QString, QString>>  getList( void ) const override;
    Qt::DropActions                 supportedDropActions() const override;
    bool                            dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                                                 int column, const QModelIndex &parent) override;
    QMimeData *                     mimeData(const QModelIndexList &indexes) const override;
    QStringList                     mimeTypes() const override;

    void setMerged(bool status) {
        isMerged = status;
        emit wasMerged();
    }

signals:
    void wasMerged();

private:
    QList<QPair<QString, QString> > _listOfPairs;
    CFileManager                   *_fileManager;
    bool isMerged;
};



#endif // CTABLEMODEL_H
