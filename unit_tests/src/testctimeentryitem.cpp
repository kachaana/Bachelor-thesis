#include "testctimeentryitem.h"

TestCTimeEntryItem::TestCTimeEntryItem(QObject *parent) : QObject(parent) {

}

void TestCTimeEntryItem::testTimeEntryToJSON() {
    QString desc = "Serials";
    CTimeEntryItem item(desc, "true");
    QString compareString = "";
            compareString += "{\"time_entry\":{";
            compareString += "\"description\":\"";
            compareString += desc + "\",";
            compareString += "\"created_with\":\"toggl_client_desk\"," ;
            compareString += "\"duronly\":";
            compareString += "true";
            compareString += "}}";
    QCOMPARE(item.timeEntryToJSON(), compareString);
}

void TestCTimeEntryItem::testGetTimeEntryIDFromResponse() {
    CTimeEntryItem item;

    /*** Case 1 positive scenario ***/

    QByteArray byteArray =  "{"
                            "\"data\":"
                             "{\"id\":436694100,"
                             "\"pid\":123,"
                             "\"wid\":777,"
                             "\"billable\":false,"
                             "\"start\":\"2013-03-05T07:58:58.000Z\","
                             "\"duration\":-1362470338,"
                             "\"description\":\"Meeting with possible clients\","
                             "\"tags\":[\"billed\"]}}";
    QCOMPARE(item.getTimeEntryIDFromResponse(byteArray), 436694100);

     /*** Case 2 negative scenario ***/

    byteArray =              "{"
                             "\"data\":"
                             "\"pid\":123,"
                             "\"wid\":777,"
                             "\"billable\":false,"
                             "\"start\":\"2013-03-05T07:58:58.000Z\","
                             "\"duration\":-1362470338,"
                             "\"description\":\"Meeting with possible clients\","
                             "\"tags\":[\"billed\"]}}";
    QCOMPARE(item.getTimeEntryIDFromResponse(byteArray), -1);
}
