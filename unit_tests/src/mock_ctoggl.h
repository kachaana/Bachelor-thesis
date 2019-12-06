#ifndef MOCK_CTOGGL_H
#define MOCK_CTOGGL_H
#include "../../src/ia_ctoggl.h"
#include "test_data.h"


class Mock_CToggl : public IA_CToggl {
public:
    Mock_CToggl();

    void                    setUsername();
    void                    setIconStopStart(QSystemTrayIcon * icon);
    void                    setAction(QAction * action);
    bool                    getIsStart() const ;
    void                    on_ButtonStart_clicked();
    void                    on_ButtonDes_clicked();
    void                    on_ButtonSettings_clicked();
    void                    updateTable();
    void                    calculate();
};

#endif // MOCK_CTOGGL_H
