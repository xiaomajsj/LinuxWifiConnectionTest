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

     ReadNetworkLog();
    if(_currentMode=="Wifi"){ui->wifiButton->setChecked(true);
    ConnectWifi();
    }
    else if(_currentMode=="SIM_Card"){ui->SIMButton->setChecked(true);
    ConnectSIMCard();
    }


    GetAllSSID();
    ui->UpdateLabel->setStyleSheet("QLabel{background-color:white;}");

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
//    for(QByteArray &id : timezoneList)
//     {
//         ui->TimeZoneCombo->addItem(id);
//     }

//    ui->TimeZoneCombo->addItem("Europe/Amsterdam");
//    ui->TimeZoneCombo->addItem("Europe/Berlin");
//    ui->TimeZoneCombo->addItem("Europe/London");
//    ui->TimeZoneCombo->addItem("Asia/Shanghai");
//    ui->TimeZoneCombo->addItem("America/New_York");
//    ui->TimeZoneCombo->addItem("Australia/Sydney");
        ui->TimeZoneCombo->addItem(CountryList[Country::UTC]);
        ui->TimeZoneCombo->addItem(CountryList[Country::Netherlands]);
        ui->TimeZoneCombo->addItem(CountryList[Country::Germany]);
        ui->TimeZoneCombo->addItem(CountryList[Country::England]);
        ui->TimeZoneCombo->addItem(CountryList[Country::China]);
        ui->TimeZoneCombo->addItem(CountryList[Country::America]);
        ui->TimeZoneCombo->addItem(CountryList[Country::Australia]);
    //ShowTime();
}


void SettingWifi::GetAllSSID()
{

SSIDList.clear();
SSIDItem.clear();

QDir SSIDDocPath(filePath[0]);
QFile SSIDDoc(SSIDDocPath.filePath("TestSSID.txt"));
if(!SSIDDoc.open(QIODevice::ReadWrite | QIODevice::Text))
{qDebug("fail to open");
    msgboxUpdate.setText("failed to open SSID Setting file");
    msgboxUpdate.exec();
    return;
}
QTextStream in(&SSIDDoc);
QString allText=in.readAll();
in.seek(0);
QString line;
QString key;
QString value;
QString _SSID;
QString _password;

//parsing each line and get all SSIDs
do
{
    line=in.readLine();
    line.replace(QString("="),QString(" "));
    line.replace(QString("\""),QString(""));
    line.replace(QString(":"),QString(" "));
    QTextStream linestream(&line);
    linestream>>key>>value;
    qDebug()<<line;
    if(key=="network")
    {
      currentSSID._inputting=true;
      qDebug()<<currentSSID._inputting;
    }
    if(key=="ssid")
    {
       if(currentSSID._inputting)
       {currentSSID.SetSSID(value);
        currentSSID._hasSSID=true;
       }
    }
    if(key=="#psk")
    {
       if(currentSSID._inputting)
       {currentSSID.SetPassword(value);
        currentSSID._haspassword=true;
       }
    }
    if(key=="psk")
    {
        if(currentSSID._inputting)
        {currentSSID.SetPSK(value);
         currentSSID._hasPSK=true;
        }
    }
    if(key=="}")
    {
       if(currentSSID._inputting)
       {
           SSIDList.append(currentSSID);
           currentSSID.Clear();
       }
    }
}while(!line.isNull());

SSIDDoc.close();

//add all ssid to the list
    for(auto &a : SSIDList)
    {
    QListWidgetItem item(a.getSSID());
    SSIDItem.append(item);
    }
    for (auto &a : SSIDItem)
    {
     a.setSizeHint(QSize(20,20));
     ui->SSIDList->addItem(&a);
    }

}

void SettingWifi::GetSSIDItemFromList(QList<SSID> list)
{
    SSIDItem.clear();
    for(auto &a : list)
    {
    QListWidgetItem item(a.getSSID());
    SSIDItem.append(item);
    }
    for (auto &a : SSIDItem)
    {
     a.setSizeHint(QSize(20,20));
     ui->SSIDList->addItem(&a);
    }
}

void SettingWifi::on_SSIDList_itemClicked(QListWidgetItem *item)
{
int index=ui->SSIDList->currentRow();
QStringList content;
content<<"SSID: "<<SSIDList[index].getSSID()<<"\n"<<"Password: "<<SSIDList[index].getPassword()<<"\n"<<"PSK: "<<SSIDList[index].getPSK();
ui->SSIDContent->setText(content.join(""));
}

void SettingWifi::on_DeleteSSID_clicked()
{

    msgboxUpdate.setText("Are you sure to delete this SSID?");
    msgboxUpdate.setStandardButtons(QMessageBox::Yes);
    msgboxUpdate.addButton(QMessageBox::No);
    msgboxUpdate.setDefaultButton(QMessageBox::No);
    if (msgboxUpdate.exec()==QMessageBox::Yes){BeginDeleteSSID();}
    else {return;}

}

void SettingWifi::BeginDeleteSSID()
{
    QModelIndex index=ui->SSIDList->currentIndex();
    if(index.isValid())
        {
            QString AllWPA;
            int index=ui->SSIDList->currentRow();
            QString deletedPart=GetWPAFormat(SSIDList[index]);
            ui->TestBox->setText(deletedPart);

            if((index+1)<=SSIDList.size()){SSIDList.removeAt(index);}
            else{qDebug("selected SSID dont exist!");
                msgboxUpdate.setText("selected SSID dont exist!");
                msgboxUpdate.exec();}

            for(auto &a : SSIDList)
            {
                AllWPA+=GetWPAFormat(a);

            }
            //*****here insert the function to write the file WPA to remove SSID*****//
            WriteWPA(AllWPA);
            ui->TestBox2->setText(AllWPA);
             //**********///
            GetAllSSID();
        }
    else{
            qDebug()<<"please selected a valid object!";
            msgboxUpdate.setText("please selected a valid object!");
            msgboxUpdate.exec();
            return;
        }
}

QString SettingWifi::GetWPAFormat(SSID ssid)
{
QStringList content;
content<<"network={\n\t"<<"ssid=\""<<ssid.getSSID()<<"\"\n\t"<<"#psk=\""<<ssid.getPassword()<<"\"\n\t"
      <<"psk="<<ssid.getPSK()<<"\n}\n";
return content.join("");
}


void SettingWifi::WriteWPA(QString content)
{

    QDir SSIDDocPath(filePath[0]);
    QFile SSIDDoc(SSIDDocPath.filePath("TestSSID.txt"));
    if(!SSIDDoc.open(QIODevice::ReadWrite | QIODevice::Text))
    {qDebug("fail to open");
        msgboxUpdate.setText("failed to open SSID Setting file");
        msgboxUpdate.exec();
        return;
    }
    QMutexLocker WPALocker(mutex);
    SSIDDoc.resize(0);
    QTextStream out(&SSIDDoc);
    out<<content;
    SSIDDoc.close();
}

void SettingWifi::on_Clean_clicked()
{
    msgboxUpdate.setText("Are you sure to delete all the SSID?");
    msgboxUpdate.setStandardButtons(QMessageBox::Yes);
    msgboxUpdate.addButton(QMessageBox::No);
    msgboxUpdate.setDefaultButton(QMessageBox::No);
    if (msgboxUpdate.exec()==QMessageBox::Yes){DeleteAllSSID();}
    else {return;}
}
void SettingWifi::DeleteAllSSID()
{
    QDir SSIDDocPath(filePath[0]);
    QFile SSIDDoc(SSIDDocPath.filePath("TestSSID.txt"));
    if(!SSIDDoc.open(QIODevice::ReadWrite | QIODevice::Text))
    {qDebug("fail to open");
        msgboxUpdate.setText("failed to open SSID Setting file");
        msgboxUpdate.exec();
        return;
    }
    QMutexLocker WPALocker(mutex);
    SSIDDoc.resize(0);
    SSIDDoc.close();

    GetAllSSID();
}
void SettingWifi::on_SaveSSID_clicked()
{
    QString content=ui->SSIDContent->toPlainText();
    int SelectedRow=ui->SSIDList->currentRow();
    QTextStream contentStream(&content);
    QString line;
    QString newSSID;
    QString newPassword;
    QString newPSK;
    QString key;
    QString value;

    do{
    line=contentStream.readLine();
    QTextStream linestream(&line);
    linestream>>key>>value;
    if(key=="SSID:"){newSSID=value;}
    if(key=="Password:"){newPassword=value;}
    if(key=="PSK:"){newPSK=value;}

    }while(!line.isNull());

    //return if formatting is not correct
    if(newSSID=="" || newPassword=="" || newPSK==""){qDebug("incorrect format. Please check the contents");
    return;}

    //operating SSIDList
    SSIDList.removeAt(SelectedRow);
    SSID newItem(newSSID,newPassword,newPSK);
    SSIDList.insert(SelectedRow,newItem);

    //write new SSID information to setting file
    QString AllWPA;
    for(auto &a : SSIDList)
    {
        AllWPA+=GetWPAFormat(a);
    }
    WriteWPA(AllWPA);
    ui->TestBox2->setText(AllWPA);
    GetSSIDItemFromList(SSIDList);

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
process.setProcessEnvironment(QProcessEnvironment::systemEnvironment());
process.start(command);
process.waitForFinished();
qDebug("connect WIFI successfully");
qDebug()<<"ConnectWIFI error Code: "<<process.error();
qDebug()<<"ConnectWIFI exit Status: "<<process.exitStatus();

//system(command.toLocal8Bit());
//qDebug("System code start");
}


void SettingWifi::ConnectSIMCard()
{
    QString command=CommandList[ListType::FourGConnect];
    QProcess process;
    QMutexLocker mutexLocker(mutex);
    process.setProcessEnvironment(QProcessEnvironment::systemEnvironment());
    process.start(command);
    process.waitForFinished();
    qDebug("connect 4G successfully");
    qDebug()<<"Connect Sim Card error Code: "<<process.error();
    qDebug()<<"Connect Sim Card exit Status: "<<process.exitStatus();

}

void SettingWifi::on_AddSSID_clicked()
{
    ui->InputWidget->show();
    ui->SSIDInput->setText("");
    ui->PasswordInput->setText("");
}
void SettingWifi::on_connectSIM_clicked()
{
   ConnectSIMCard();

}
void SettingWifi::on_BeginConnect_clicked()
{
    ConnectWifi();
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
    GetAllSSID();
}


void SettingWifi::on_Update_clicked()
{
QString updateCommand=CommandList[ListType::Update];
connect (&updateProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(ReadOutputData()));
connect (&updateProcess,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(UpdateFinished(int, QProcess::ExitStatus)));

//lambda function
//connect(&updateProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
//    [=](int exitCode, QProcess::ExitStatus exitStatus)
//{
//    qDebug("Updating ended");
//    qDebug()<<updateProcess.error();
//    qDebug()<<updateProcess.errorString();

//    QString exitStat="Updating finished, exiting code is: ";
//    exitStat.append(exitCode);
//    exitStat.append(". Exiting status is: ");
//    exitStat.append(exitStatus);

//    msgboxUpdate.setText(exitStat);
//    msgboxUpdate.exec();
//}
//);

//process initialize
updateProcess.setWorkingDirectory("/home/root/PC-LCD");
updateProcess.setProcessEnvironment(QProcessEnvironment::systemEnvironment());
QStringList enviroment =QProcess::systemEnvironment();
updateProcess.start(updateCommand);

//start
updateProcess.waitForStarted();
ui->UpdateLabel->setStyleSheet("QLabel{background-color:red;}");
ui->UpdateLabel->setText("updating, please wait");
qDebug("Updating start");
qDebug()<<updateProcess.error();
qDebug()<<updateProcess.errorString();
msgboxUpdate.setText("Updating start, please wait");
msgboxUpdate.exec();
}


void SettingWifi::UpdateFinished(int code, QProcess::ExitStatus status)
{
        qDebug("Updating ended");
        qDebug()<<updateProcess.error();
        qDebug()<<updateProcess.errorString();

        qDebug()<<"Process return code is "<<code;

        qDebug()<<"Process return status is "<<status;

        ui->UpdateLabel->setText(updateResult);
}


void SettingWifi::ReadOutputData()
{
    QTextStream StdoutStream(updateProcess.readAllStandardOutput());
    QString line;

    do {
        line = StdoutStream.readLine();
        if ( line.contains("updated"))
        {
            qDebug()<<line;
            msgboxUpdate.done(QDialog::Accepted);

            updateResult="finished!";
            ui->UpdateLabel->setStyleSheet("QLabel{background-color:green;}");

            msgboxUpdate.setText("updating completed, please restart the software");
            msgboxUpdate.exec();
        }
        else if ( line.contains("no new version found"))
        {
            qDebug()<<line;
            msgboxUpdate.done(QDialog::Accepted);
            msgboxUpdate.setText("no new version found, the current software is the newest version");
            msgboxUpdate.exec();

            ui->UpdateLabel->setStyleSheet("QLabel{background-color:green;}");
            updateResult="finished!";

        }
        else if (line.contains("no network"))
        {
            qDebug()<<line;
            msgboxUpdate.setText("No network, please check the network connection");
            msgboxUpdate.exec();

            updateResult="no network";
            ui->UpdateLabel->setStyleSheet("QLabel{background-color:red;}");
            ui->UpdateLabel->setText(updateResult);
            break;
        }
        else if (line.contains("connected"))
        {
            qDebug()<<line;
            qDebug("Network connection successfully, the updating start");
        }

    } while (!line.isNull());

}

void SettingWifi::ShowTime()
{
    zoneTime=QDateTime(QDate::currentDate(),QTime::currentTime(),Qt::TimeZone);
    //zoneTime=QDateTime(QDate::currentDate(),QTime::currentTime(),QTimeZone("Europe/Berlin"));
//   QByteArray id=ui->TimeZoneCombo->currentText().toLatin1();
//   timezone=QTimeZone(id);

    GetTimeZone();

    timeNow=(zoneTime.toTimeZone(timezone)).time();
    QString text = timeNow.toString("hh:mm:ss");
    if(timeNow.second()%2==0){text[2]=' ';
    text[5]=' ';}
    ui->Clock->QLCDNumber::display(text);


}
void SettingWifi::GetTimeZone()
{
    int id=ui->TimeZoneCombo->currentIndex();
    QString timezoneString;
    QByteArray timezoneID;
    if(true){
    //if(zoneTime.isDaylightTime()){
    switch(id){
    case Country::UTC:
        timezoneString="UTC";
        timezoneID=timezoneString.toLatin1();
        timezone=QTimeZone(timezoneID);
        break;
    case Country::China:
        timezoneString="UTC+08:00";
        timezoneID=timezoneString.toLatin1();
        timezone=QTimeZone(timezoneID);
        break;
    case Country::America:
        timezoneString="UTC-05:00";
        timezoneID=timezoneString.toLatin1();
        timezone=QTimeZone(timezoneID);
        break;
    case Country::England:
        timezoneString="UTC+01:00";
        timezoneID=timezoneString.toLatin1();
        timezone=QTimeZone(timezoneID);
        break;
    case Country::Germany:
        timezoneString="UTC+02:00";
        timezoneID=timezoneString.toLatin1();
        timezone=QTimeZone(timezoneID);
        break;
    case Country::Netherlands:
        timezoneString="UTC+02:00";
        timezoneID=timezoneString.toLatin1();
        timezone=QTimeZone(timezoneID);
        break;
    case Country::Australia:
        timezoneString="UTC+10:00";
        timezoneID=timezoneString.toLatin1();
        timezone=QTimeZone(timezoneID);
        break;
    default:
        break;
     }
    }
//  else if((!zoneTime.isDaylightTime())){
//        switch(id){
//        case Country::UTC:
//            timezoneString="UTC";
//            timezoneID=timezoneString.toLatin1();
//            timezone=QTimeZone(timezoneID);
//            break;
//        case Country::China:
//            timezoneString="UTC+08:00";
//            timezoneID=timezoneString.toLatin1();
//            timezone=QTimeZone(timezoneID);
//            break;
//        case Country::America:
//            timezoneString="UTC-05:00";
//            timezoneID=timezoneString.toLatin1();
//            timezone=QTimeZone(timezoneID);
//            break;
//        case Country::England:
//            timezoneString="UTC+00:00";
//            timezoneID=timezoneString.toLatin1();
//            timezone=QTimeZone(timezoneID);
//            break;
//        case Country::Germany:
//            timezoneString="UTC+01:00";
//            timezoneID=timezoneString.toLatin1();
//            timezone=QTimeZone(timezoneID);
//            break;
//        case Country::Netherlands:
//            timezoneString="UTC+01:00";
//            timezoneID=timezoneString.toLatin1();
//            timezone=QTimeZone(timezoneID);
//            break;
//        case Country::Australia:
//            timezoneString="UTC+10:00";
//            timezoneID=timezoneString.toLatin1();
//            timezone=QTimeZone(timezoneID);
//            break;
//        default:
//            break;

//        }
//    }

}

void SettingWifi::on_TimeZoneCombo_currentIndexChanged(int index)
{
    ShowTime();
    ClockTimer->start();
    const char* s = "2020-08-15T03:54:00";
    QDateTime d1 = QDateTime::fromString(s, Qt::ISODate);
    qDebug()<<d1<<d1.isDaylightTime();
    QDateTime d2 = QDateTime::fromString(s, Qt::ISODate).toLocalTime();
    qDebug()<<d2<<d2.isDaylightTime();

    qDebug()<<zoneTime.timeSpec();
    qDebug()<<zoneTime<<zoneTime.isDaylightTime();

    qDebug()<<zoneTime.toLocalTime()<<zoneTime.toLocalTime().isDaylightTime();
    qDebug()<<zoneTime.timeSpec();

    qDebug()<<zoneTime<<zoneTime.isDaylightTime();
    qDebug()<<zoneTime.timeSpec();

    zoneTime.setTimeSpec(Qt::UTC);
    qDebug()<<zoneTime<<zoneTime.isDaylightTime();
    qDebug()<<zoneTime.timeSpec();

    zoneTime.setTimeSpec(Qt::TimeZone);
    qDebug()<<zoneTime<<zoneTime.isDaylightTime();
    qDebug()<<zoneTime.timeSpec();

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

void SettingWifi::paintEvent(QPaintEvent *e)
{

//    QPainter painter(this);
//    QPen paintpen(Qt::green);
//    paintpen.setWidth(20);
//    painter.setPen(paintpen);
//    painter.drawLine(0,0,100,100);
}



void SettingWifi::on_wifiButton_toggled(bool checked)
{
   if(checked==true)
   {
     _networkMode="Wifi";
     ReadNetworkLog();
     if(_networkMode==_currentMode){return;}
     else{
         _currentMode=_networkMode;
         RewriteNetworkLog();}
   }
   else
   {
     return;
   }
}

void SettingWifi::on_SIMButton_toggled(bool checked)
{
    if(checked==true)
    {
      _networkMode="SIM_Card";
      ReadNetworkLog();
      if(_networkMode==_currentMode){return;}
      else{
          _currentMode=_networkMode;
          RewriteNetworkLog();}
    }
    else
    {
      return;
    }
}

void SettingWifi::ReadNetworkLog()
{
    QDir dir;
    if(!dir.exists("LOG/"))
    {dir.mkpath("LOG/");}
    if(!dir.mkpath("LOG/"))
      return;
    QString fileName;
    fileName="NetworkMode.txt";

    QMutexLocker locker(mutex);
    QFile file("LOG/"+fileName);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {qDebug("failed to open");
        msgboxUpdate.setText("failed to open setting file");
        msgboxUpdate.exec();
        return;}

    QString line;
    QTextStream in(&file);
    QString allText=in.readAll();
    in.seek(0);


    if(allText=="")
    {
      file.close();
      _currentMode="Wifi";
      locker.unlock();
      RewriteNetworkLog();
      return;
    }


    do
     {
        line=in.readLine();
        QTextStream linestream(&line);
        QString key;
        QString Mode;
        linestream>>key>>Mode;

        if(key=="NetworkMode:"){_currentMode=Mode;}

     } while(!line.isNull());



    file.close();

}

void SettingWifi::RewriteNetworkLog()
{

    QDir dir("LOG/");
    QString fileName;
    fileName="NetworkMode.txt";
    QFile file(dir.filePath(fileName));
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {qDebug("fail to open");
        msgboxUpdate.setText("failed to open setting file");
        msgboxUpdate.exec();
        return;
    }
    file.resize(0);
    QMutexLocker inputLocker(mutex);
    QTextStream out(&file);
    out<<"NetworkMode: "<<_currentMode;
    file.close();
}






