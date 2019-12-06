
#include "ctablemodel.h"




CTableModel::CTableModel() : isMerged(false){
    _fileManager = new CFileManager();
}

CTableModel::CTableModel(QList<QPair<QString, QString> > pairs) {
    _listOfPairs = pairs;
    _fileManager = new CFileManager();
}

CTableModel::~CTableModel() {
    if(_fileManager) delete _fileManager;
}

int CTableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return _listOfPairs.size();
}

int CTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return COLUMN_TABLE_NUMBER;
}

QVariant CTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    if (index.row() >= _listOfPairs.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::TextAlignmentRole && index.column() == 1) {
        return Qt::AlignCenter;
    }

    if (role == Qt::EditRole || role == Qt::DisplayRole) {
        QPair<QString, QString> pair = _listOfPairs.at(index.row());
        if(index.column() == 0)
            return pair.first;
    }

    if (role == Qt::DisplayRole) {
        QPair<QString, QString> pair = _listOfPairs.at(index.row());
        if(index.column() == 1)
            return pair.second;
    }

    return QVariant();
}

QVariant CTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr(qPrintable(COLUMN_DES_NAME));
            case 1:
                return tr(qPrintable(COLUMN_TIME_NAME));
            default:
                return QVariant();
        }
    }
    return QVariant();
}

bool CTableModel::insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) {
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; ++row) {
        QPair<QString, QString> pair(" ", " ");
        _listOfPairs.insert(position, pair);
    }
    endInsertRows();
    return true;
}

bool CTableModel::removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) {
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; ++row) {
        _listOfPairs.removeAt(position);
    }
    endRemoveRows();
    return true;
}

bool CTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid()) {
        int row = index.row();
        QPair<QString, QString> p = _listOfPairs.value(row);
        if (index.column() == 0 and role == Qt::EditRole){
            p.first = value.toString();
            _fileManager->updateDesktopNames(_listOfPairs);
        }
        else if (index.column() == 1 and role == Qt::DisplayRole) {
            p.second = value.toString();
        }
        else {
            return false;
        }
        _listOfPairs.replace(row, p);
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags CTableModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsDropEnabled;
    if (index.column() == 1)
        return QAbstractTableModel::flags(index) | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

QList<QPair<QString, QString>> CTableModel::getList() const {
    return _listOfPairs;
}

Qt::DropActions CTableModel::supportedDropActions() const {
    return Qt::MoveAction | Qt::CopyAction;
}

QPair<int,int> getHoursMinutes(QString time) {
    QPair<int,int> retPair;
    retPair.first = time.mid(0, 2).toInt();
    retPair.second = time.mid(3).toInt();
    return retPair;
}

QString mergeTimes(QString firstTime, QString secondTime) {
       QString retStr;
       QPair<int,int> firstT = getHoursMinutes(firstTime);
       QPair<int,int> secondT = getHoursMinutes(secondTime);
       int hours = 0, minutes = 0;
       if(firstT.second + secondT.second > 59) {
           hours++;
       } else {
           minutes = firstT.second + secondT.second;
       }
       hours += firstT.first;
       hours += secondT.first;
       if(hours < 10) {
         retStr += "0" + QString::number(hours);
       } else
           retStr += QString::number(hours);
       retStr += ":";
       if(minutes < 10) {
         retStr += "0" + QString::number(minutes);
       } else
           retStr += QString::number(minutes);
       return retStr;
}

bool CTableModel::dropMimeData(const QMimeData *data,
     Qt::DropAction action, int row, int column, const QModelIndex &parent) {
     if (action == Qt::IgnoreAction)
         return true;
     if (!data->hasFormat("application/vnd.text.list"))  {
         return false;
     }
     if (column > 0){
         return false;
     }
     int beginRow;
     if (row != -1){
         beginRow = row;
     }
     else if (parent.isValid()) {
         beginRow = parent.row();
     }
     else {
        beginRow = rowCount(QModelIndex());
     }
     int rows = 0;
     QByteArray encodedData = data->data("application/vnd.text.list");
     QDataStream stream(&encodedData, QIODevice::ReadOnly);
     QStringList newItems;
     while (!stream.atEnd()) {
         QString text;
         stream >> text;
         newItems << text;
         ++rows;
     }
     QModelIndex idxToName = index(beginRow, 0, QModelIndex());
     QModelIndex idxToTime = index(beginRow, 1, QModelIndex());
     QString newName = "Merge_" + idxToName.data().toString() + "_" + newItems.at(0);
     QString newTime = mergeTimes(idxToTime.data().toString(), newItems.at(1));
        int rowToDel = newItems.at(2).toInt();


         for(int i = 0; i < _listOfPairs.size(); i++) {
             if( i == rowToDel)
                 continue;
             if( i == beginRow) {
                  setData(idxToName, newName, Qt::EditRole);
                  setData(idxToTime, newTime, Qt::DisplayRole);
             } else {
             QModelIndex idxToName = index(i, 0, QModelIndex());
             setData(idxToName, _listOfPairs.at(i).first, Qt::EditRole);
             idxToName = index(i, 1, QModelIndex());
             setData(idxToName, _listOfPairs.at(i).second, Qt::DisplayRole);
             }
         }
         setMerged(true);
         return true;
}

QStringList CTableModel::mimeTypes() const {
    QStringList types;
    types << "application/vnd.text.list";
    return types;
}


QMimeData * CTableModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (QModelIndex index, indexes) {
        if (index.isValid()) {
            QString text = data(index, Qt::DisplayRole).toString();
            stream << text;

        }
    }
    stream << QString::number(indexes.at(0).row());
    mimeData->setData("application/vnd.text.list", encodedData);
    return mimeData;
}

