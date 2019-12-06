#include "cfilemanager.h"

CFileManager::CFileManager() {
   _appDirPath      = QCoreApplication::applicationDirPath();
   _autostartPath   = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).at(0) + QLatin1String("/autostart");
   _appPath         = QCoreApplication::applicationFilePath();
}

CFileManager::~CFileManager() {}

/*!
 * \brief CFileManager::getTokenFromFile function will extract token from a ".conf" file.
 * \param token QString value where will be stored token string.
 * \return true if token exists in a ".conf" file, overwise false.
 */

bool CFileManager::getTokenFromFile(QString& token) {
    QFile file(_appDirPath + CONF);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
           QTextStream stream(&file);
           QString log;
           token = stream.readLine();
           if(token.length() < 33) {
               token = "";
               return false;
           }
           token = token.mid(DELIMETR.length(), token.length() - DELIMETR.length());
           file.close();
           return true;
    } else {
        createConfFile();
        return false;
    }
}

/*!
 * \brief CFileManager::_parseTimeString function splits string into hours and minutes.
 * \param strToParse input String, which has format "01:02", "01" stands for hours and "02" for minutes.
 * \return Pair of strings, first means hours, second - minutes.
 */

QPair<QString,QString> CFileManager::_parseTimeString(QString strToParse) {
    QPair<QString,QString> retPair;
    retPair.first = strToParse.mid(0, 2);
    retPair.second = strToParse.mid(3);
    return retPair;
}

/*!
 * \brief CFileManager::updateDesktopNames Updates ".conf" file with new or modified entries.
 *        (E.x. user has changed desktop's name manually and function updates it).
 * \param list List of pairs with Desktop's name and their time.
 */

void CFileManager::updateDesktopNames(QList<QPair<QString, QString> > list) {
    QFile file(_appDirPath + CONF);
    QFile tempFile(_appDirPath + TEMP);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    tempFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if(file.isOpen() && tempFile.isOpen()) {
        QTextStream org(&file);
        QTextStream tmp(&tempFile);
        QString line;
        line = org.readLine();
        tmp << line << endl;
        line = org.readLine();
        tmp << line << endl;
        line = org.readLine();
        tmp << line << endl;
        for(auto i : list) {
            tmp << i.first << DELIMETR << i.second << endl;
        }
        file.remove();
        tempFile.rename(_appDirPath + CONF);
        tempFile.close();
        }
    }

/*!
 * \brief CFileManager::tokenAvaliable finction decides if token is a good string or not.
 *        Requirements for a good string: - lenght should equals 35 (as 2 for delimiter, 32 for token and 1 for new line)
 * \return true if token seems to be a good string, false overwise.
 */

bool CFileManager::tokenAvaliable() {
    QFile file(_appDirPath + CONF);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(file.isOpen()) {
        QTextStream org(&file);
        QString line;
        line = org.readLine();
        if(line.length() != 34)
            return false;
    } else {
        return false;
    }
    file.close();
    return true;
}

/*!
 * \brief CFileManager::createConfFile function will create a ".conf" file with based structure"
 *        (1. line) %%
 *        (2. line) %%
 *        (3. line) %%
 */

void CFileManager::createConfFile() {
    QFile file(_appDirPath + CONF);
    if ( file.open(QIODevice::ReadWrite) )    {
        QTextStream stream( &file );
        stream << DELIMETR << endl;
        stream << DELIMETR << endl;
        stream << DELIMETR << endl;
    }
    file.close();
}


/*!
 * \brief getTokenFromResponse Function parses array from http response and extract token from it.
 * \param bytearray Array of QByteArray type - thhp response body.
 * \return Token string.
 */

QString getTokenFromResponse(QByteArray bytearray) {
    QByteArray api("api_token");
    int index = bytearray.indexOf(api);
    return bytearray.mid(index + 12, 32);
}


/*!
 * \brief CFileManager::uploadTokenToFile will extract token from response array and store to a file.
 *        If token already exists in a file, function will replace with new one.
 * \param bytearray Array of format QByteArray taken from http response.
 */

void CFileManager::uploadTokenToFile(QByteArray bytearray) {
    QFile file(_appDirPath + CONF);
    QFile fileTemp(_appDirPath + TEMP);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileTemp.open(QIODevice::WriteOnly | QIODevice::Text);
    if (file.isOpen() && fileTemp.isOpen()){
           QTextStream stream(&file);
           QTextStream tmp(&fileTemp);
           QString line = stream.readLine();
                   line = stream.readLine();
           tmp << DELIMETR << getTokenFromResponse(bytearray) << endl;
           tmp << line << endl;
           tmp << DELIMETR << endl;
           line = stream.readLine();
           while(true) {
               line = stream.readLine();
               if(line.length() == 0)
                   break;
               tmp << line << endl;
           }
    }
    file.remove();
    fileTemp.rename(_appDirPath + CONF);
    fileTemp.close();
}

/*!
 * \brief CFileManager::getDesktopNameByNumber Funcion looks into a file and searches for a desktop's name by given order number.
 * \param number Order number of desktop.
 * \return Name of finded desktop.
 */

QString CFileManager::getDesktopNameByNumber(int number) {
    int counterRow = 0;
    QFile file(_appDirPath + CONF);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (file.isOpen()){
        QTextStream stream(&file);
        QString line = stream.readLine(); //token
                line = stream.readLine(); //name
                line = stream.readLine(); //del
        while(true) {
             line = stream.readLine();
             if(line.length() == 0) {
                 file.close();
                 return "Desktop_" + QString::number(number);
             }
             if(number == counterRow) {
                 file.close();
                 return _getDesktopName(line);
             }
             counterRow++;
        }
    }
    file.close();
    return "";
}

/*!
 * \brief CFileManager::saveNameToFile Function will save user's name to a ".conf" file.
 * \param name User's name.
 */

void CFileManager::saveNameToFile(QByteArray name) {
    QFile file(_appDirPath + CONF);
    QFile fileTemp(_appDirPath + TEMP);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileTemp.open(QIODevice::WriteOnly | QIODevice::Text);
    if (file.isOpen() && fileTemp.isOpen()){
           QTextStream stream(&file);
           QTextStream tmp(&fileTemp);
           QString line = stream.readLine();
           tmp << line << endl;
           line = stream.readLine();
           tmp << DELIMETR << name << endl;
           line = stream.readLine();
           tmp << DELIMETR << endl;
           while(true) {
               line = stream.readLine();
               if(line.length() == 0)
                   break;
               tmp << line << endl;
           }
    }
    file.remove();
    fileTemp.rename(_appDirPath + CONF);
    fileTemp.close();
}

/*!
 * \brief CFileManager::getNameFromFile Function will extract user's name from a ".conf" file.
 * \return User's name.
 */

QString CFileManager::getNameFromFile() {
    QString retName;
    QFile file(_appDirPath + CONF);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
           QTextStream stream(&file);
           QString log;
           retName = stream.readLine();
           if(retName.length() < 3)
               return DEFAULT_USER_NAME;
           retName = stream.readLine();
           retName = retName.mid(DELIMETR.length(), retName.length() - DELIMETR.length());
           file.close();
           return retName;
    } else {
        createConfFile();
        return DEFAULT_USER_NAME;
    }
}

/*!
 * \brief CFileManager::_getDesktopName Parses string and extract Desktop's name from it.
 * \param line Input string for parsing.
 * \return Desktop's name.
 */

QString CFileManager::_getDesktopName(QString line) {
    int index = line.indexOf(DELIMETR);
    return line.mid(0, index);
}

/*!
 * \brief CFileManager::loadEntriesFromFile Function will extract all desktop's entries from a ".conf" file.
 * \return list_init type -> QPair<bool,QList<QPair<QString, QString>>>:
 *                           first - true, if entries are available, false if doesn't.
 *                           second - empty list, if first pair value is false.
 *                                    List with entries (desktop's name, time), if firts pair value is true.
 *
 */

list_init CFileManager::loadEntriesFromFile() {
    list_init list;
    QList<QPair<QString,QString>> list_i;
    QFile file(_appDirPath + CONF);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (file.isOpen()){
        QTextStream stream(&file);
        QString line = stream.readLine();
        int fileSize = (line.length() == 0) ? 0 : line.length() + 1; //token
        line = stream.readLine();
        fileSize += (line.length() == 0) ? 0 : line.length() + 1;   //name
        line = stream.readLine();
        fileSize += (line.length() == 0) ? 0 : line.length() + 1;   //del
        if(file.size() == fileSize) {
            list.first = false;
            list.second = list_i;
            file.close();
            return list;
        } else {
            while(true) {
                line = stream.readLine();
                if(line.length() == 0)
                    break;
                QPair<QString,QString> pair;
                pair.first = _getDesktopName(line);
                int indexDEL = line.indexOf(DELIMETR);
                pair.second = line.mid(indexDEL + 2);
                list_i.append(pair);
            }
            list.first = true;
            list.second = list_i;
            file.close();
            return list;
        }
    }
    createConfFile();
    list.first = false;
    list.second = list_i;
    return list;
}

/*!
 * \brief CFileManager::checkAutorunDirExistance Function will check existance of directory for autostart applications.
 *        Will create this directory if doesn't exist.
 */

void CFileManager::checkAutorunDirExistance() {
    QDir autorunDir(_autostartPath);
    if(!autorunDir.exists())
        autorunDir.mkpath(_autostartPath);
}

/*!
 * \brief CFileManager::createAutorunFile Function will create Autostart file.
 */

void CFileManager::createAutorunFile() {
    checkAutorunDirExistance();
    QFile autorunFile(_autostartPath + DESKTOP);
    if(!autorunFile.exists()){
        if(autorunFile.open(QFile::WriteOnly)){
            QString autorunContent("[Desktop Entry]\n"
                                   "Type=Application\n"
                                   "Exec=" + _appPath + "\n"
                                   "Hidden=false\n"
                                   "NoDisplay=false\n"
                                   "X-GNOME-Autostart-enabled=true\n"
                                   "Name[en_GB]=AutorunLinux\n"
                                   "Name=AutorunLinux\n"
                                   "Comment[en_GB]=AutorunLinux\n"
                                   "Comment=AutorunLinux\n");
            QTextStream outStream(&autorunFile);
            outStream << autorunContent;
            autorunFile.setPermissions(QFileDevice::ExeUser|QFileDevice::ExeOwner|QFileDevice::ExeOther|QFileDevice::ExeGroup|
                                   QFileDevice::WriteUser|QFileDevice::ReadUser);
            autorunFile.close();
        }
    }
}

/*!
 * \brief CFileManager::removeAutostartFile Function will remove file for autostart application.
 */

void CFileManager::removeAutostartFile() {
    QFile autorunFile(_autostartPath + DESKTOP);
    if(autorunFile.exists())
        autorunFile.remove();
}

/*!
 * \brief CFileManager::getSettings Function will load setting from a ".confsettings" file.
 * \return vec_set type with:
 *                      - first: true if ".confsettings" file is availavle. False if is empty.
 *                      - second: empty QVector if first pair value is false. Vector with setting's values if first value is true.
 */

vec_set CFileManager::getSettings() {
    vec_set ret;
    QVector<int> vec;
    QFile setconfFile(_appDirPath + SETTINGS);
    if(setconfFile.open(QFile::ReadWrite)) {
        QTextStream stream(&setconfFile);
        if(setconfFile.size() == 0) {
            stream << 0 << endl;
            stream << 0 << endl;
            stream << 0 << endl;
            stream << 10 << endl;
            ret.first = false;
            ret.second = vec;
            return ret;
        }
        QString line;
        while(true) {
            line = stream.readLine();
            if(line.length() == 0)
                break;
            vec.push_back(line.toInt());
        }
        ret.first = true;
        ret.second = vec;
        setconfFile.close();
        return ret;
    }
    ret.first = false;
    ret.second = vec;
    setconfFile.close();
    return ret;
}

/*!
 * \brief CFileManager::loadSettingChanges function will store changes to a ".cobfsettings" file for specified setting's item.
 * \param set_id Setting's item id.
 * \param value Value to set in setting's item.
 */

void CFileManager::loadSettingChanges(int set_id, int value) {
    QFile setconfFile(_appDirPath + SETTINGS);
    QFile tempFile(_appDirPath + TEMP);
    setconfFile.open(QIODevice::ReadOnly | QIODevice::Text);
    tempFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if(setconfFile.isOpen() && tempFile.isOpen()) {
        QTextStream org(&setconfFile);
        QTextStream tmp(&tempFile);
        QString line;
        int counterRow = 0;
        while(true) {
            line = org.readLine();
            if(line.length() == 0)
                break;
            if(counterRow == set_id)
                tmp << value << endl;
            else {
                tmp << line << endl;
            }
            counterRow++;
        }
        setconfFile.remove();
        tempFile.rename(_appDirPath + SETTINGS);
        tempFile.close();
        }
}

/*!
 * \brief CFileManager::removeAllConfFiles Function remove all configuration files.
 */

void CFileManager::removeAllConfFiles() {
    QFile conf(_appDirPath + CONF);
    conf.remove();
    QFile set(_appDirPath + SETTINGS);
    set.remove();
    QFile autorun(_autostartPath + DESKTOP);
    autorun.remove();
}

/*!
 * \brief CFileManager::deleteLastDesktop After user deletes desktop, function delete it too from a ".conf" file/
 * \param desktopsNumber Actual desktops count.
 */

void CFileManager::deleteLastDesktop(int desktopsNumber) {
    int counter = 0;
    QFile file(_appDirPath + CONF);
    QFile fileTemp(_appDirPath + TEMP);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileTemp.open(QIODevice::WriteOnly | QIODevice::Text);
    QString line;
    if (file.isOpen() && fileTemp.isOpen()){
        QTextStream stream(&file);
        QTextStream tmp(&fileTemp);
        while(true){
            line = stream.readLine();
            if(counter == desktopsNumber + 3)
                break;
            tmp << line << endl;
            counter++;
        }
    }
    file.remove();
    fileTemp.rename(_appDirPath + CONF);
    fileTemp.close();
}
