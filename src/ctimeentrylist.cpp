#include "ctimeentrylist.h"
#include "ui_ctimeentrylist.h"
#include <QModelIndex>
#include <cstdlib>
#include <cstring>

CTimeEntryList::CTimeEntryList() : _ui(new Ui::CTimeEntryList),
                                   _isStart(false) {
    _ui->setupUi(this);
    server = new CHTTPReceiver();
    timer = new QTimer(this);
    timer->start(TIMER_DESK_DET);
    _timeEntryItem = new CTimeEntryItem();
    _dateEvaluate = QDate::currentDate();
    _fileManager = new CFileManager();
    tableModel = new CTableModel();
    _ui->tableView->setModel(tableModel);
    _initializeList();
    _ui->tableView->horizontalHeader()->setStretchLastSection(true);
    _ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    _ui->tableView->setDragEnabled(true);
    _ui->tableView->setDropIndicatorShown(true);
    _ui->tableView->setAcceptDrops(true);
    _ui->tableView->viewport()->setAcceptDrops(true);
    _ui->tableView->setDefaultDropAction(Qt::MoveAction);
    _ui->tableView->setDragDropMode(QTableView::InternalMove);
    _ui->tableView->setDragDropOverwriteMode(false);
    _ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    _ui->tableView->setColumnWidth(0, this->width()/5 * 3);
    _ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    _ui->tableView->setDragEnabled(true);
    _ui->tableView->setAcceptDrops(true);
    _ui->tableView->setDropIndicatorShown(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(detectDesktopsProperty()));
    connect(tableModel, SIGNAL(wasMerged()), this, SLOT(decrementTotalDesktopsNumber()));
    _currentDisplay = getCurrentDesktop();
}

CTimeEntryList::~CTimeEntryList(){
    delete _ui;
    _fileManager->updateDesktopNames(tableModel->getList());
}

/*!
 * \brief CTimeEntryList::_initializeList will load entries from ".conf" file if exist.
 *        If not, will detect them from system.
 */

void CTimeEntryList::_initializeList() {
    list_init list_i;
    list_i = _fileManager->loadEntriesFromFile();
    if(!list_i.first) {
        _totalNumberOfDesktops = getNumberOfDesktops();
    for(int i = 0; i < _totalNumberOfDesktops; i++) {
        int numb = getNumberOfDesktops();
        QModelIndex in = tableModel->index(i,0);
        tableModel->insertRow(numb, in);
        QModelIndex index = tableModel->index(i, 0, QModelIndex());
        QString desktopName = _fileManager->getDesktopNameByNumber(i);
        tableModel->setData(index, desktopName, Qt::EditRole);
        index = tableModel->index(i, 1, QModelIndex());
        tableModel->setData(index, "00:00", Qt::DisplayRole);
        QPair<int,int> pair;
        pair.first = 0;
        pair.second = 0;
        vectorTime.push_back(pair);
    }
    _fileManager->updateDesktopNames(tableModel->getList());
    } else {
        int i = 0;
        _totalNumberOfDesktops = list_i.second.size();
        for(auto e : list_i.second) {
            QModelIndex in = tableModel->index(i,0);
            tableModel->insertRow(i, in);
            QModelIndex index = tableModel->index(i, 0, QModelIndex());
            tableModel->setData(index, e.first, Qt::EditRole);
            index = tableModel->index(i, 1, QModelIndex());
            tableModel->setData(index, e.second, Qt::DisplayRole);
            QPair<int,int> pair;
            pair.first = e.second.mid(0, 2).toInt();
            pair.second = e.second.mid(3).toInt();
            vectorTime.push_back(pair);
            i++;
        }
        _fileManager->updateDesktopNames(tableModel->getList());
    }
}

/*!
 * \brief CTimeEntryList::get_property exported from XLib manual.
 * \param disp
 * \param win
 * \param xa_prop_type
 * \param prop_name
 * \param size
 * \return
 */

char * CTimeEntryList::get_property (Display *disp, Window win, Atom xa_prop_type, char *prop_name, unsigned long *size){
    Atom xa_prop_name;
    Atom xa_ret_type;
    int ret_format;
    unsigned long ret_nitems;
    unsigned long ret_bytes_after;
    unsigned long tmp_size;
    unsigned char *ret_prop;
    char* ret;
    xa_prop_name = XInternAtom(disp, prop_name, False);
    if (XGetWindowProperty(disp, win, xa_prop_name, 0, MAX_PROPERTY_VALUE_LEN / 4, False,
            xa_prop_type, &xa_ret_type, &ret_format,
            &ret_nitems, &ret_bytes_after, &ret_prop) != Success) {
        return nullptr;
    }
    if (xa_ret_type != xa_prop_type) {
        XFree(ret_prop);
        return nullptr;
    }
    tmp_size = (static_cast<unsigned long>(ret_format) / 8) * ret_nitems;
    ret = new char[tmp_size + 1];
    memcpy(ret, ret_prop, tmp_size);
    ret[tmp_size] = '\0';
    if (size) {
        *size = tmp_size;
    }
    XFree(ret_prop);
    return ret;
}

/*!
 * \brief CTimeEntryList::getNumberOfDesktops Function uses Xlib interface to get know the amount of virtual desktops.
 * \return Number of actual existing desktops.
 */

int CTimeEntryList::getNumberOfDesktops() {
    Window root = DefaultRootWindow(QX11Info::display());
    char * num_desktops = nullptr;
    if(!(num_desktops = get_property(QX11Info::display(), root,
            XA_CARDINAL, NET_NUMBER_OF_DESKTOPS.toLocal8Bit().data(), nullptr))) {
        if(!(num_desktops = get_property(QX11Info::display(), root,
                XA_CARDINAL, WIN_WORKSPACE_COUNT.toLocal8Bit().data(), nullptr))) {
       qDebug() << "Error" ;
        }
    }
    return static_cast<int>(*num_desktops);
}

/*!
 * \brief CTimeEntryList::getCurrentDesktop Function uses Xlib interface to get know the order number of current in use virtual desktops.
 * \return Order number of active desktop.
 */


int CTimeEntryList::getCurrentDesktop() {
    Window root = DefaultRootWindow(QX11Info::display());
    char *cur_desktop = nullptr;
    if(!(cur_desktop = get_property(QX11Info::display(), root,
            XA_CARDINAL, NET_CURRENT_DESKTOP.toLocal8Bit().data(), nullptr))) {
        if(!(cur_desktop = get_property(QX11Info::display(), root,
                XA_CARDINAL, WIN_WORKSPACE.toLocal8Bit().data(), nullptr))) {
            qDebug() << "Error" ;
        }
    }
    return static_cast<int>(*cur_desktop);
}

void CTimeEntryList::decrementTotalDesktopsNumber() {
    _totalNumberOfDesktops--;
}

/*!
 * \brief CTimeEntryList::detectDesktopsProperty Function detects ever change about desktops status that was happend.
 *
 */

void CTimeEntryList::detectDesktopsProperty() {
    int actualDesktopNumberNew = getNumberOfDesktops();
    QDate dateActual = QDate::currentDate();
    if(_dateEvaluate < dateActual) {
        _dateEvaluate = QDate::currentDate();
        QPair<int,int> pairNull;
        pairNull.first = 0;
        pairNull.second = 0;
        for(int i = 0; i < actualDesktopNumberNew; i++) {
            vectorTime.replace(i, pairNull);
        }
    }
    int checkActualDesktop =  getCurrentDesktop();
    if(checkActualDesktop != _currentDisplay) {
        if(_isStart) {
            _currentDisplay = checkActualDesktop;
            emit valueChanged();
            _fileManager->updateDesktopNames(tableModel->getList());
        }
    }
    if(actualDesktopNumberNew > _totalNumberOfDesktops) {
        _totalNumberOfDesktops = actualDesktopNumberNew;
        emit valueChanged();
        QModelIndex in = tableModel->index(actualDesktopNumberNew - 1,0);
        tableModel->insertRow(actualDesktopNumberNew, in);
        QModelIndex index = tableModel->index(actualDesktopNumberNew - 1, 0, QModelIndex());
        QString desktopName = DEFAULT_DES_NAME + QString::number(actualDesktopNumberNew - 1);
        tableModel->setData(index, desktopName, Qt::EditRole);
        index = tableModel->index(actualDesktopNumberNew - 1, 1, QModelIndex());
        tableModel->setData(index, "00:00", Qt::DisplayRole);
        QPair<int,int> pair;
        pair.first = 0;
        pair.second = 0;
        vectorTime.push_back(pair);
    } else if (actualDesktopNumberNew < _totalNumberOfDesktops) {
        _totalNumberOfDesktops = actualDesktopNumberNew;
        emit valueChanged();
        QModelIndex in = tableModel->index(actualDesktopNumberNew - 1,0);
        tableModel->removeRow(actualDesktopNumberNew, in);
        _fileManager->deleteLastDesktop(_totalNumberOfDesktops);
        vectorTime.removeLast();
    }
}


