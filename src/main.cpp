#include "csingleton.h"
#include "cwindowapplication.h"

int main(int argc, char *argv[]) {
   CSingleton::setQuitOnLastWindowClosed(false);
   CSingleton::setApplicationName(TITLE);
   CSingleton app(argc, argv);
   my_argc = argc;
   my_argv = argv;
   if (app.isRunning()) {
        return 0;
    }
   app.setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + TOGGL_ICON));
   CWindowApplication window;
   window.setWindowTitle(TITLE);
   app.widget = &window;
   window.run();
   app.widget->show();
   return app.exec();
}
