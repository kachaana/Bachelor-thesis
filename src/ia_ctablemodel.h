#ifndef IA_CTABLEMODEL_H
#define IA_CTABLEMODEL_H
#include <QAbstractTableModel>
#include <QColor>

class IA_CTableModel : public QAbstractTableModel
{
public:
    IA_CTableModel();

    virtual QList<QPair<QString, QString>>  getList( void ) const = 0;
};

#endif // IA_CTABLEMODEL_H
