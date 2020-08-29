#ifndef SETTINGWIFI_H
#define SETTINGWIFI_H

#include <QMainWindow>
#include <QProcess>
#include <QFile>
#include <QMutex>
#include <QMutexLocker>
#include <QTextStream>
#include <QListWidgetItem>
#include <QListWidget>
#include <QStringList>
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
#include "ssid.h"
#include "chargeloginfo.h"
#include "resize.h"

//static const QString WifiSettingPath = "/etc/network/interfaces";
static const QString CommandList[]={
    "e:/QT Project/LinuxWifiSetting/TestFile.txt",
    "/home/root/PC-LCD/networkMode.sh wifiMode",
    "",
    "/home/root/PC-LCD/LocalUpdate.sh",
    "/home/root/PC-LCD/networkMode.sh simMode",
};


//***************careful:the filepath is defined relative, its absolute path depends on the terminal path!!!!!*********************

static const QString filePath[]=
{
    "LOG/",
    "etc/"
};

static const QString fileList[]=
{
    "wpa_supplicant.conf",
    " ",
    "TestSSID.txt",
};


static const QString CountryList[]=
{
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

enum fileNameType{
    SSIDConfig=0,
    DefaultNetWorkMode,
    TestFile,
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

    void ResizeAllObjects();

    void GetAllSSID();
    void BeginDeleteSSID();
    void DeleteAllSSID();
    QString GetWPAFormat(SSID ssid);
    void WriteWPA(QString content);
    void GetSSIDItemFromList(QList<SSID> list);

    void GetAllLog();

    void WriteSetting();
    void ConnectWifi();
    void ConnectSIMCard();
    void SettingCommand();


    void RewriteNetworkLog();
    void ReadNetworkLog();

    void ShowTime();
    void InitialClock();
    void GetTimeZone();


protected:
    void paintEvent(QPaintEvent *e) override;
private slots:
    void on_AddSSID_clicked();

    void on_Clean_clicked();

    void on_Cancel_clicked();

    void on_OK_clicked();

    void on_TimeZoneCombo_currentIndexChanged(int index);

    void on_Update_clicked();

    void ReadOutputData();

    void on_LastPage_clicked();

    void on_Test_clicked();

    void UpdateFinished(int code, QProcess::ExitStatus status);

    void on_wifiButton_toggled(bool checked);

    void on_SIMButton_toggled(bool checked);

    void on_SSIDList_itemClicked(QListWidgetItem *item);

    void on_DeleteSSID_clicked();

    //void on_SSIDList_itemSelectionChanged();

    void on_SaveSSID_clicked();

    void on_LogList_itemClicked(QListWidgetItem *item);

    void on_DeleteLOG_clicked();

private:
    Ui::SettingWifi *ui;
    Resize _resize;
    double resizeParameterW;
    double resizeParameterH;

    ChargeLogInfo currentLog;
    QDir RootDir;
    QList<ChargeLogInfo> ChargeLogList;
    QList<QListWidgetItem> ChargeLogItem;

    SSID currentSSID;
    QList<SSID> SSIDList;
    QList<QListWidgetItem> SSIDItem;
    int SSIDInputX;
    int SSIDInputY;


    QString _ssid;
    QString _password;
    QString _networkMode;
    QString _currentMode;

    QMutex *mutex;

    QTimer *ClockTimer;
    QTime timeNow;
    QTimeZone timezone;
    QDateTime zoneTime;
    QList<QByteArray> timezoneList;

    QProcess updateProcess;
    QString updateResult;
    QProcess SSIDSetting;
    QProcess WifiConnect;

    QMessageBox msgboxUpdate;

    BlankPage *_blankpage;


};


#endif // SETTINGWIFI_H
