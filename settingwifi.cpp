#include "settingwifi.h"
#include "ui_settingwifi.h"

SettingWifi::SettingWifi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SettingWifi)
{
    ui->setupUi(this);
    ui->InputWidget->hide();
    mutex=new QMutex;
    InitialClock();

    _blankpage= new BlankPage;

}

SettingWifi::~SettingWifi()
{
    delete ui;
    delete mutex;
    delete _blankpage;
}

void SettingWifi::InitialClock()
{
    ClockTimer=new QTimer(this);
    ClockTimer->setInterval(50);
    connect(ClockTimer,&QTimer::timeout,this,&SettingWifi::ShowTime);


//    timezoneList=QTimeZone::availableTimeZoneIds(QLocale::UnitedKingdom);
//    timezoneList.append(QTimeZone::availableTimeZoneIds(QLocale::Germany));

//    timezoneList.append(QTimeZone::availableTimeZoneIds(QLocale::China));
//    timezoneList.append(QTimeZone::availableTimeZoneIds(QLocale::UnitedStates));
//    timezoneList.append(QTimeZone::availableTimeZoneIds(QLocale::Australia));
//    for(QByteArray &id : timezoneList)
//     {
//         ui->TimeZoneCombo->addItem(id);
//     }

    ui->TimeZoneCombo->addItem("Europe/Amsterdam");
    ui->TimeZoneCombo->addItem("Europe/Berlin");
    ui->TimeZoneCombo->addItem("Europe/London");
    ui->TimeZoneCombo->addItem("Asia/Shanghai");
    ui->TimeZoneCombo->addItem("America/New_York");
    ui->TimeZoneCombo->addItem("Australia/Sydney");
    //ShowTime();
}



void SettingWifi::WriteSetting()
{
QFile file(CommandList[ListType::WifiSetting]);
file.resize(0);
QMutexLocker mutexLocker(mutex);
if(file.open(QIODevice::Append | QIODevice::Text))
{
QTextStream stream(&file);
//stream << "auto wlan0\niface wlan inet dhcp\n"<<
//          "wpa-ssid {"<<_ssid<<"}\nwpa-psk {"<<_password<<"}";
stream<<"wpa_passphrase "<<"\""<<_ssid<<"\" \""<<_password<<"\""<<">>/etc/wpa_supplicant.conf";
file.close();
qDebug("Writing finished");
}
}

void SettingWifi::SettingCommand()
{
    QString command="wpa_passphrase \""+_ssid+"\" \""+_password+"\">>/etc/wpa_supplicant.conf";
    qDebug()<< command;
    ui->TestText->setText(command);
    QProcess process;
    QMutexLocker mutexLocker(mutex);
    process.start(command);
    process.waitForFinished();
    qDebug("setting finished");
    qDebug()<<process.error();
    qDebug()<<process.exitStatus();

    system(command.toLocal8Bit());
    qDebug("System code start");
}

void SettingWifi::ConnectWifi()
{
QString command=CommandList[ListType::BeginConnect];
QProcess process;
QMutexLocker mutexLocker(mutex);
process.start(command);
process.waitForFinished();
qDebug("connect WIFI successfully");
qDebug()<<process.error();
qDebug()<<process.exitStatus();

system(command.toLocal8Bit());
qDebug("System code start");
}

void SettingWifi::on_Connect_clicked()
{
    ui->InputWidget->show();
    ui->SSIDInput->setText("");
    ui->PasswordInput->setText("");
}
void SettingWifi::on_connect4G_clicked()
{
    QString command=CommandList[ListType::FourGConnect];
    QProcess process;
    QMutexLocker mutexLocker(mutex);
    process.start(command);
    process.waitForFinished();
    qDebug("connect 4G successfully");
    qDebug()<<process.error();
    qDebug()<<process.exitStatus();

}
void SettingWifi::on_BeginConnect_clicked()
{
    ConnectWifi();
}

void SettingWifi::on_Clean_clicked()
{
    QFile file(CommandList[ListType::WifiSetting]);
    file.resize(0);
    qDebug("clean file finished");
}

void SettingWifi::on_Cancel_clicked()
{
    ui->InputWidget->hide();
}

void SettingWifi::on_OK_clicked()
{
    if(ui->SSIDInput->text()=="" || ui->PasswordInput->text()=="")
    {
        QMessageBox msgbox;
        msgbox.setText("please enter SSID and Password");
        msgbox.exec();
        return;
    }
    _ssid=ui->SSIDInput->text();
    _password=ui->PasswordInput->text();
    ui->InputWidget->hide();
    //WriteSetting();
    SettingCommand();
}

void SettingWifi::on_Update_clicked()
{
QString updateCommand=CommandList[ListType::Update];
connect (&updateProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(ReadOutputData()));
updateProcess.start(updateCommand);
updateProcess.waitForFinished();
}

void SettingWifi::ReadOutputData()
{
    QTextStream StdoutStream(updateProcess.readAllStandardOutput());
    QString line;

    do {
        line = StdoutStream.readLine();
        qDebug()<<line;
        if ( line.contains("completed"))
        {
            QMessageBox msgbox;
            msgbox.setText("updating completed, please restart the software");
            msgbox.exec();
        }

    } while (!line.isNull());

}

void SettingWifi::ShowTime()
{
    zoneTime=QDateTime(QDate::currentDate(),QTime::currentTime(),QTimeZone(Qt::UTC));
    //zoneTime=QDateTime(QDate::currentDate(),QTime::currentTime(),QTimeZone("Europe/Berlin"));

    QByteArray id=ui->TimeZoneCombo->currentText().toLatin1();
    timezone=QTimeZone(id);

    timeNow=(zoneTime.toTimeZone(timezone)).time();
    QString text = timeNow.toString("hh:mm:ss");
    if(timeNow.second()%2==0){text[2]=' ';
    text[5]=' ';}
    ui->Clock->QLCDNumber::display(text);


}


void SettingWifi::on_TimeZoneCombo_currentIndexChanged(int index)
{
    ShowTime();
    ClockTimer->start();
    QByteArray id=ui->TimeZoneCombo->currentText().toLatin1();
    qDebug()<<ui->TimeZoneCombo->currentText();
    qDebug()<<id;
    qDebug()<<timezone<<":  "<<timeNow;
}


void SettingWifi::on_LastPage_clicked()
{
    _blankpage->show();
}



void SettingWifi::on_Test_clicked()
{
    QDir dir;
    if(!dir.exists("Test/"))
    {dir.mkpath("Test/");}
    if(!dir.mkpath("Test/"))
      return;
    QDateTime nowDateTime(QDate::currentDate(),QTime::currentTime());
    QString fileNameWithTime=nowDateTime.currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
    fileNameWithTime+=".txt";

    QMutexLocker locker(mutex);
    QFile file("Test/"+fileNameWithTime);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {qDebug("failed to open");
        return;}
    {
    QTextStream out(&file);
    out<<"This is a test text"<<"\n"<<"second paragraph"<<"\n"<<fileNameWithTime<<endl;
    }
    file.close();

}


