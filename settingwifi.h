#ifndef SETTINGWIFI_H
#define SETTINGWIFI_H

#include <QMainWindow>
#include <QProcess>
#include <QFile>
#include <QMutex>
#include <QMutexLocker>
#include <QTextStream>
#include <QDebug>
#include <QTime>
#include <QDateTime>
#include <QTimer>
#include <QTimeZone>
#include <QList>
#include <QMessageBox>
#include <QDir>

#include <QPainter>
#include <QtCore>
#include <QtGui>

#include "blankpage.h"

//static const QString WifiSettingPath = "/etc/network/interfaces";
static const QString CommandList[]={
    "e:/QT Project/LinuxWifiSetting/TestFile.txt",
    "/home/root/PC-LCD/networkMode.sh wifiMode",
    "",
    "/home/root/PC-LCD/LocalUpdate.sh",
    "/home/root/PC-LCD/networkMode.sh simMode",
};

static const QString CountryList[]={
 "UTC",
 "Netherlands/Amsterdam",
 "Germany/Berlin",
 "United Kingdom/London",
 "China/Peking",
 "America/New York",
 "Australis/Sydney",
};

enum Country{
    UTC=0,
    Netherlands,
    Germany,
    England,
    China,
    America,
    Australia,
};


enum ListType{
    WifiSetting=0,
    BeginConnect,
    WifiSetting2,
    Update,
    FourGConnect,
};

QT_BEGIN_NAMESPACE
namespace Ui { class SettingWifi; }
QT_END_NAMESPACE

class SettingWifi : public QMainWindow
{
    Q_OBJECT

public:
    SettingWifi(QWidget *parent = nullptr);
    ~SettingWifi();

    void WriteSetting();
    void ConnectWifi();
    void SettingCommand();

    void ShowTime();
    void InitialClock();
    void GetTimeZone();

protected:
    void paintEvent(QPaintEvent *e) override;
private slots:
    void on_Connect_clicked();

    void on_Clean_clicked();

    void on_Cancel_clicked();

    void on_OK_clicked();

    void on_TimeZoneCombo_currentIndexChanged(int index);

    void on_Update_clicked();

    void ReadOutputData();

    void on_LastPage_clicked();

    void on_connect4G_clicked();

    void on_Test_clicked();

    void on_BeginConnect_clicked();

private:
    Ui::SettingWifi *ui;
    QString _ssid;
    QString _password;
    QMutex *mutex;
    QTimer *ClockTimer;
    QTime timeNow;
    QTimeZone timezone;
    QDateTime zoneTime;
    QList<QByteArray> timezoneList;
    QProcess updateProcess;

    QMessageBox msgboxUpdate;

    BlankPage *_blankpage;

};
#endif // SETTINGWIFI_H
