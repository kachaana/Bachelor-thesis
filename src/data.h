#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>

const QString SETTINGS                      = "/.confsettings";
const QString TEMP                          = "/.temp";
const QString CONF                          = "/.conf";

const QString DELIMETR                      = "%%";
const QString DESKTOP                       = "/toggl.desktop";

const QString API_TOKEN                     = "api_token";

const QString REGISTRATION_LINK             = "<a href=\"https://toggl.com/signup\">Registration here</a>";

const QString AUTH_URL                      = "https://www.toggl.com/api/v8/me";
const QString TIME_ENTRY_DETAILS_URL        = "https://www.toggl.com/api/v8/time_entries";
const QString START_ENTRY                   = "/start";
const QString CLIENT_DETAILS                = "https://www.toggl.com/api/v8/clients/";

const QString DESTOP_ICON                   = "/../src/images/desktop.png";
const QString SETTINGS_ICON                 = "/../src/images/settings.png";
const QString START_ICON                    = "/../src/images/start.png";
const QString STOP_ICON                     = "/../src/images/stop.png";
const QString OFFLINE_ICON                  = "/../src/images/toggl_offline.png";
const QString TOGGL_ICON                    = "/../src/images/toggl.png";

const QString START_ACTION                  = "Start...";
const QString STOP_ACTION                   = "Stop...";
const QString EXIT_ACTION                   = "Exit";
const QString LOGOUT_ACTION                 = "Log out";
const QString OPEN_ACTION                   = "Open Toggl";
const QString WEB_ACTION                    = "Go to website";

const QString TOGGL_WEB_URL                 = "https://www.toggl.com";

const int     REMINDER_TIME                 = 10;
const int     MILLISECONDS                  = 60000;
const QString REMINDER_MESSAGE              = "Don't forget to track your time!";
const QString TITLE                         = "Toggl";

extern bool   OFFLINE_MODE;

const int     MAX_PROPERTY_VALUE_LEN        = 4096;

const int     SIZE_ICON                     = 60;

const int     TIMER_DESK_DET                = 2000;
extern int    TIMER_M_SEC;

const QString NET_DESKTOP_NAMES             = "_NET_DESKTOP_NAMES";
const QString UTF8_STRING                   = "UTF8_STRING";
const QString WIN_WORKSPACE_NAMES           = "_WIN_WORKSPACE_NAMES";
const QString NET_NUMBER_OF_DESKTOPS        = "_NET_NUMBER_OF_DESKTOPS";
const QString WIN_WORKSPACE_COUNT           = "_WIN_WORKSPACE_COUNT";
const QString NET_CURRENT_DESKTOP           = "_NET_CURRENT_DESKTOP";
const QString WIN_WORKSPACE                 = "_WIN_WORKSPACE";

const QString DEFAULT_DES_NAME              = "Desktop_";
const QString DEFAULT_USER_NAME             = "Unknow user";

const int     COLUMN_TABLE_NUMBER           = 2;
const QString COLUMN_DES_NAME               = "DESKTOP";
const QString COLUMN_TIME_NAME              = "Time today (HH:MM)";

const int     TIMEOUT_MS                    = 500;

const int     CHECK_BOX_NUMBER              = 3;

const QString LOGIN_MESSAGE_FAIL            = "Login Failed!\nTry again.";

const QString NEW_LINE                      ="\n";

const int     HTTP_OK                       = 200;
const int     HTTP_BAD_RQ                   = 400;
const int     HTTP_UNAUTH                   = 401;

//* needed for test cases*//

extern int my_argc;
extern char** my_argv;

#endif // CONSTANTS_H
