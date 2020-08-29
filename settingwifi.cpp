#include "settingwifi.h"
#include "ui_settingwifi.h"

SettingWifi::SettingWifi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SettingWifi)
{
    ui->setupUi(this);
    ui->InputWidget->hide();
    ui->InputWidget->setWindowFlags(Qt::Popup);
    mutex=new QMutex;
    _resize=Resize();

    ResizeAllObjects();

    //Start the time display clock
    InitialClock();

    //read networklog to connect the internet through default setting
    ReadNetworkLog();
    if(_currentMode=="Wifi")
    {
        ui->wifiButton->setChecked(true);
        ConnectWifi();
    }
    else if(_currentMode=="SIM_Card")
    {
        ui->SIMButton->setChecked(true);
        ConnectSIMCard();
    }


    GetAllSSID();
    GetAllLog();

    ui->UpdateLabel->setStyleSheet("QLabel{background-color:white;}");

    _blankpage= new BlankPage;

}

SettingWifi::~SettingWifi()
{
    delete ui;
    delete mutex;
    delete _blankpage;
}


void SettingWifi::ResizeAllObjects()
{
    //get screen geometry, and resize all objects
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    double _screenWidth;
    double _screenHeight;
    _screenWidth = screenGeometry.width();
    _screenHeight = screenGeometry.height();



    resizeParameterW=(double)_screenWidth/this->width();
    resizeParameterH=(double)_screenHeight/this->height();

    this->resize(_screenWidth,_screenHeight);



    _resize.ObjectResize(ui->groupBox,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->wifiButton,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->SIMButton,resizeParameterW,resizeParameterH);

    _resize.ObjectResize(ui->groupBox_2,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->SSIDList,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->SSIDContent,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->label_4,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->label_5,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->AddSSID,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->DeleteSSID,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->SaveSSID,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->Clean,resizeParameterW,resizeParameterH);

    _resize.ObjectResize(ui->groupBox_5,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->APNList,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->APNLabel,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->APNContent,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->AddAPN,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->DeleteAPN,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->saveAPN,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->CleanAPN,resizeParameterW,resizeParameterH);

    _resize.ObjectResize(ui->groupBox_3,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->TimeZoneCombo,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->Clock,resizeParameterW,resizeParameterH);

    _resize.ObjectResize(ui->groupBox_4,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->Update,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->UpdateLabel,resizeParameterW,resizeParameterH);

    _resize.ObjectResize(ui->groupBox_6,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->LogContent,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->LogList,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->DeleteLOG,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->label_2,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->label_3,resizeParameterW,resizeParameterH);

    _resize.ObjectResize(ui->LastPage,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->NextPage,resizeParameterW,resizeParameterH);

    _resize.ObjectResize(ui->SSIDInput,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->InputWidget,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->PasswordInput,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->OK,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->Cancel,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->SSID,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->Password,resizeParameterW,resizeParameterH);

    _resize.ObjectResize(ui->Test,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->TestBox,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->TestBox2,resizeParameterW,resizeParameterH);
    _resize.ObjectResize(ui->TestText,resizeParameterW,resizeParameterH);

    SSIDInputX=ui->InputWidget->x();
    SSIDInputY=ui->InputWidget->y();



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

    //go to path:/etc
    QDir SSIDDocPath(QDir::rootPath());
    SSIDDocPath.cd(filePath[1]);
    qDebug()<<"wpa supplicant file path now is "<<SSIDDocPath.absolutePath();

    //open the SSID Config file wpa_supplicant.conf
    QFile SSIDDoc(SSIDDocPath.filePath(fileList[fileNameType::SSIDConfig]));
    if(!SSIDDoc.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug("fail to open");
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

    //parsing each line and get all SSIDs, store them as Class SSID. And then append them all into
    //QList<SSID>
    do
    {
        line=in.readLine();
        line.replace(QString("="),QString(" "));
        line.replace(QString("\""),QString(""));
        line.replace(QString(":"),QString(" "));
        QTextStream linestream(&line);
        linestream>>key>>value;
        if(key=="network")
        {
          currentSSID._inputting=true;
        }
        if(key=="ssid")
        {
           if(currentSSID._inputting)
           {
               currentSSID.SetSSID(value);
               currentSSID._hasSSID=true;
           }
        }
        if(key=="#psk")
        {
           if(currentSSID._inputting)
           {
               currentSSID.SetPassword(value);
               currentSSID._haspassword=true;
           }
        }
        if(key=="psk")
        {
            if(currentSSID._inputting)
            {
                currentSSID.SetPSK(value);
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

    //extract all the SSID from SSIDList and put them into SSIDItem
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
    //Extract all the items in SSIDItem and put them into QListWidget
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
    //When clicking item in the QListWidget:SSIDList, the content window will show its SSID and password.
    int index=ui->SSIDList->currentRow();
    QStringList content;
    //content<<"SSID: "<<SSIDList[index].getSSID()<<"\n"<<"Password: "<<SSIDList[index].getPassword()<<"\n"<<"PSK: "<<SSIDList[index].getPSK();
    content<<"SSID: "<<SSIDList[index].getSSID()<<"\n"<<"Password: "<<SSIDList[index].getPassword();
    ui->SSIDContent->setText(content.join(""));
}

void SettingWifi::on_DeleteSSID_clicked()
{

    //Messagebox popup
    msgboxUpdate.setText("Are you sure to delete this SSID?");
    msgboxUpdate.setStandardButtons(QMessageBox::Yes);
    msgboxUpdate.addButton(QMessageBox::No);
    msgboxUpdate.setDefaultButton(QMessageBox::No);
    if (msgboxUpdate.exec()==QMessageBox::Yes){BeginDeleteSSID();}
    else {return;}

}

void SettingWifi::BeginDeleteSSID()
{
    //make sure that the chossen SSID is valid. If no item is choosen, return
    QModelIndex index=ui->SSIDList->currentIndex();
    if(index.isValid())
    {
        QString AllWPA;
        int index=ui->SSIDList->currentRow();
        //check the deleted part in debugging text box
        QString deletedPart=GetWPAFormat(SSIDList[index]);
        ui->TestBox->setText(deletedPart);


        //first remove the choosen item in the SSIDList
        if((index+1)<=SSIDList.size()){SSIDList.removeAt(index);}
        else
        {
            qDebug("selected SSID dont exist!");
            msgboxUpdate.setText("selected SSID dont exist!");
            msgboxUpdate.exec();
        }

        //Then get the complete WPA_supplicant formatting from SSIDList
        for(auto &a : SSIDList)
        {
            AllWPA+=GetWPAFormat(a);
        }
        //*****here insert the function to write the file WPA to remove SSID*****//
        //Write the complete formatting back to the wpa_supplicant.conf
        WriteWPA(AllWPA);
        //debugging
        ui->TestBox2->setText(AllWPA);
        //**********///


        // Refresh the SSID in the ListWidget
        GetAllSSID();
    }
    else
    {
        qDebug()<<"please selected a valid object!";
        msgboxUpdate.setText("please selected a valid object!");
        msgboxUpdate.exec();
        return;
    }
}

QString SettingWifi::GetWPAFormat(SSID ssid)
{
    //Return the string of the wpa_supplicant format for each SSID
    QStringList content;
    content<<"network={\n\t"<<"ssid=\""<<ssid.getSSID()<<"\"\n\t"<<"#psk=\""<<ssid.getPassword()<<"\"\n\t"
        <<"psk="<<ssid.getPSK()<<"\n}\n";
    return content.join("");
}


void SettingWifi::WriteWPA(QString content)
{

    //Go to the path /etc
    QDir SSIDDocPath(QDir::rootPath());
    SSIDDocPath.cd(filePath[1]);

    //Open file wpa_supplicant.conf
    QFile SSIDDoc(SSIDDocPath.filePath(fileList[fileNameType::SSIDConfig]));
    if(!SSIDDoc.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug("fail to open");
        msgboxUpdate.setText("failed to open SSID Setting file");
        msgboxUpdate.exec();
        return;
    }

    //Write the QString content to the file
    QMutexLocker WPALocker(mutex);
    qDebug()<<"operating wpa supplicant file in "<<SSIDDocPath.absolutePath();
    SSIDDoc.resize(0);
    QTextStream out(&SSIDDoc);
    out<<content;
    SSIDDoc.close();
}

void SettingWifi::on_Clean_clicked()
{
    //Messagebox before deleting
    msgboxUpdate.setText("Are you sure to delete all the SSID?");
    msgboxUpdate.setStandardButtons(QMessageBox::Yes);
    msgboxUpdate.addButton(QMessageBox::No);
    msgboxUpdate.setDefaultButton(QMessageBox::No);
    if (msgboxUpdate.exec()==QMessageBox::Yes){DeleteAllSSID();}
    else {return;}
}

void SettingWifi::DeleteAllSSID()
{
    //Go to the path /etc
    QDir SSIDDocPath(QDir::rootPath());
    SSIDDocPath.cd(filePath[1]);


    //Open wpa_supplicant.conf file
    QFile SSIDDoc(SSIDDocPath.filePath(fileList[fileNameType::SSIDConfig]));
    if(!SSIDDoc.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug("fail to open");
        msgboxUpdate.setText("failed to open SSID Setting file");
        msgboxUpdate.exec();
        return;
    }
    QMutexLocker WPALocker(mutex);

    //Delete all contents
    SSIDDoc.resize(0);
    SSIDDoc.close();

    //Refresh SSID
    GetAllSSID();
}
void SettingWifi::on_SaveSSID_clicked()
{
    //save the changed content of SSID
    QString content=ui->SSIDContent->toPlainText();
    int SelectedRow=ui->SSIDList->currentRow();
    QTextStream contentStream(&content);
    QString line;
    QString newSSID;
    QString newPassword;
    QString newPSK;
    QString key;
    QString value;

    newPSK=SSIDList[SelectedRow].getPSK();


    //Read the text in the content window and store them in a new SSID.
    do
    {
        line=contentStream.readLine();
        QTextStream linestream(&line);
        linestream>>key>>value;
        if(key=="SSID:"){newSSID=value;}
        if(key=="Password:"){newPassword=value;}
        if(key=="PSK:"){newPSK=value;}
     }while(!line.isNull());

    //return if formatting is not correct
    if(newSSID=="" || newPassword=="" || newPSK=="")
    {
        qDebug("incorrect format. Please check the contents");
        return;
    }

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


void SettingWifi::GetAllLog()
{
    //Go to path current->LOG/
    QDir LOGDir(QDir::current());
    LOGDir.cd(filePath[0]);

    ChargeLogItem.clear();
    ChargeLogList.clear();

    //Get all the log files with the text "PC_Charge.log" in the application directory
    QStringList ChargeLogList=LOGDir.entryList(QStringList()<<"*PC_Charge.log",QDir::Files);
    qDebug()<<ChargeLogList;
    for(auto &a : ChargeLogList)
    {
        QListWidgetItem LogItem(a);
        ChargeLogItem.append(LogItem);
    }

    //Extract them to the Charge log ListWidget
    for(auto &a : ChargeLogItem)
    {
        a.setSizeHint(QSize(20,20));
        ui->LogList->addItem(&a);
    }

}


void SettingWifi::on_DeleteLOG_clicked()
{

    QDir LOGDir(QDir::current());
    LOGDir.cd(filePath[0]);

    msgboxUpdate.setText("Are you sure to delete this LOG?");
    msgboxUpdate.setStandardButtons(QMessageBox::Yes);
    msgboxUpdate.addButton(QMessageBox::No);
    msgboxUpdate.setDefaultButton(QMessageBox::No);
    if (msgboxUpdate.exec()==QMessageBox::Yes)
    {
        QModelIndex index=ui->LogList->currentIndex();
        if(index.isValid())
        {
            QString filename=ui->LogList->currentItem()->text();
            ui->LogList->takeItem(ui->LogList->currentRow());
            QFile LogFile(LOGDir.filePath(filename));
            LogFile.remove();
            GetAllLog();
        }
        else
        {
           qDebug("File dont exist!");
        }
    }
    else {return;}

}


void SettingWifi::on_LogList_itemClicked(QListWidgetItem *item)
{

    QDir LOGDir(QDir::current());
    LOGDir.cd(filePath[0]);
    QModelIndex index=ui->LogList->currentIndex();
    if(index.isValid())
    {
       QString fileName=ui->LogList->currentItem()->text();
       QFile LogFile(LOGDir.filePath(fileName));
       if(!LogFile.open(QIODevice::ReadWrite | QIODevice::Text))
       {
           qDebug("Can not open Charge Log File");
           msgboxUpdate.setText("Can not open Charge Log File");
           msgboxUpdate.exec();
           return;
       }
       else
       {
           QTextStream in(&LogFile);
           QString content=in.readAll();
           ui->LogContent->setText(content);
       }
    }

}


void SettingWifi::WriteSetting()
{
    //debugging
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

    //run the command in terminal to add new SSID


    QString command="wpa_passphrase \""+_ssid+"\" \""+_password+"\">>/etc/wpa_supplicant.conf";
    qDebug()<< command;
    ui->TestText->setText(command);
    //*******QProcess has no effect,need to be tested later***********
//    SSIDSetting.setProcessEnvironment(QProcessEnvironment::systemEnvironment());

//    SSIDSetting.setWorkingDirectory(QDir::rootPath());
//    SSIDSetting.start(command.toLocal8Bit());
//    SSIDSetting.waitForStarted();
//    SSIDSetting.waitForFinished();
//    qDebug("setting finished");
//    qDebug()<<SSIDSetting.error();
//    qDebug()<<SSIDSetting.exitStatus();

    system(command.toLocal8Bit());
    qDebug("System code start");
}

void SettingWifi::ConnectWifi()
{
    //run the command in terminal to connect WIFI
    QString command=CommandList[ListType::BeginConnect];
    //WifiConnect.setProcessEnvironment(QProcessEnvironment::systemEnvironment());
    //WifiConnect.start(command);
    //WifiConnect.waitForFinished();
    //qDebug("connect WIFI successfully");
    //qDebug()<<"ConnectWIFI error Code: "<<WifiConnect.error();
    //qDebug()<<"ConnectWIFI exit Status: "<<WifiConnect.exitStatus();

    system(command.toLocal8Bit());
    qDebug("System code start");
}


void SettingWifi::ConnectSIMCard()
{
    //run the command in terminal to connect Sim card
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

    //Centering the AddSSID input window
    QScreen *scr=QGuiApplication::primaryScreen();
    QRect rec=scr->geometry();
    QSize size=ui->InputWidget->size();
    QPoint topLeft = QPoint((rec.width() / 2) - (size.width() / 2), (rec.height() / 2) - (size.height() / 2));
    ui->InputWidget->setGeometry(QRect(topLeft, size));

}

void SettingWifi::on_Cancel_clicked()
{
    ui->InputWidget->hide();
    QSize size=ui->InputWidget->size();
    QPoint Back = QPoint(SSIDInputX,SSIDInputY);
    ui->InputWidget->setGeometry(QRect(Back, size));
}

void SettingWifi::on_OK_clicked()
{

    if(ui->SSIDInput->text()=="" || ui->PasswordInput->text()=="" || ui->SSIDInput->text().length()<=6)
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

    //Exceute the setting command
    SettingCommand();
    GetAllSSID();

    QSize size=ui->InputWidget->size();
    QPoint Back = QPoint(SSIDInputX,SSIDInputY);
    ui->InputWidget->setGeometry(QRect(Back, size));
}


void SettingWifi::on_Update_clicked()
{
    QString updateCommand=CommandList[ListType::Update];

    //Connect to slots to read terminal output, and to get the process completion flag
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

    qDebug()<<"Updating Process return code is "<<code;

    qDebug()<<"Updating Process return status is "<<status;

    if(!updateResult.isNull()){ui->UpdateLabel->setText(updateResult);}
}


void SettingWifi::ReadOutputData()
{
    QTextStream StdoutStream(updateProcess.readAllStandardOutput());
    QString line;

    //Read the terminal output to display the status
    do
    {
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
            ui->UpdateLabel->setText(updateResult);

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
        else if (line.contains("Network is unreachable"))
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

    //Set the timezone accoring to the combobox index
    if(true){
    //if(zoneTime.isDaylightTime()){
        switch(id)
        {
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
    //Change the timezone when the timezone combobox changes
    ClockTimer->stop();
    ShowTime();
    ClockTimer->start();

    //debugging
    const char* s = "2020-08-15T03:54:00";
    QDateTime d1 = QDateTime::fromString(s, Qt::ISODate);
    qDebug()<<d1<<d1.isDaylightTime();
    QDateTime d2 = QDateTime::fromString(s, Qt::ISODate).toLocalTime();
//    qDebug()<<d2<<d2.isDaylightTime();

//    qDebug()<<zoneTime.timeSpec();
//    qDebug()<<zoneTime<<zoneTime.isDaylightTime();

//    qDebug()<<zoneTime.toLocalTime()<<zoneTime.toLocalTime().isDaylightTime();
//    qDebug()<<zoneTime.timeSpec();

//    qDebug()<<zoneTime<<zoneTime.isDaylightTime();
//    qDebug()<<zoneTime.timeSpec();

//    zoneTime.setTimeSpec(Qt::UTC);
//    qDebug()<<zoneTime<<zoneTime.isDaylightTime();
//    qDebug()<<zoneTime.timeSpec();

//    zoneTime.setTimeSpec(Qt::TimeZone);
//    qDebug()<<zoneTime<<zoneTime.isDaylightTime();
//    qDebug()<<zoneTime.timeSpec();

}


void SettingWifi::on_LastPage_clicked()
{
    _blankpage->show();
}



void SettingWifi::on_Test_clicked()
{
//    QDir dir;
//    if(!dir.exists("Test/"))
//    {
//        dir.mkpath("Test/");
//    }
//    if(!dir.mkpath("Test/"))
//    {
//        return;
//    }
//    QDateTime nowDateTime(QDate::currentDate(),QTime::currentTime());
//    QString fileNameWithTime=nowDateTime.currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
//    fileNameWithTime+=".txt";

//    QMutexLocker locker(mutex);
//    QFile file("Test/"+fileNameWithTime);
//    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
//    {
//        qDebug("failed to open");
//        return;
//    }
//    {
//        QTextStream out(&file);
//        out<<"This is a test text"<<"\n"<<"second paragraph"<<"\n"<<fileNameWithTime<<endl;
//    }
//    file.close();

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
   //Change the default connection mode to wifi / Connect to Wifi
   if(checked==true)
   {
        _networkMode="Wifi";
        ReadNetworkLog();
        ConnectWifi();
        if(_networkMode==_currentMode){return;}
        else
        {
            _currentMode=_networkMode;
            RewriteNetworkLog();
        }
   }
   else
   {
        return;
   }
}

void SettingWifi::on_SIMButton_toggled(bool checked)
{
    //Change the default connection mode to SIM Card / Connect to SIM Card
    if(checked==true)
    {
        _networkMode="SIM_Card";
        ReadNetworkLog();
        ConnectSIMCard();
        if(_networkMode==_currentMode){return;}
        else
        {
            _currentMode=_networkMode;
            RewriteNetworkLog();
        }
    }
    else
    {
        return;
    }
}

void SettingWifi::ReadNetworkLog()
{
    //Go to current application path, search LOG folder. If there is none, create one
    QDir dir(QDir::current());
    if(!dir.exists("LOG/"))
    {
        dir.mkpath("LOG/");
    }
    if(!dir.mkpath("LOG/"))
    {
        return;
    }
    QString fileName;
    fileName="NetworkMode.txt";

    QMutexLocker locker(mutex);
    QFile file("LOG/"+fileName);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug("failed to open");
        msgboxUpdate.setText("failed to open setting file");
        msgboxUpdate.exec();
        return;
    }

    QString line;
    QTextStream in(&file);
    QString allText=in.readAll();
    in.seek(0);


    //If the setting file is empty, set the default connection mode "Wifi"
    if(allText=="")
    {
        file.close();
        _currentMode="Wifi";
        locker.unlock();
        RewriteNetworkLog();
        return;
    }


    //Read the setting file and get the connection mode
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
\
    //Go to current->LOG/
    QDir dir(QDir::current());
    dir.cd("LOG/");

    QString fileName;
    fileName="NetworkMode.txt";
    QFile file(dir.filePath(fileName));
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug("fail to open");
        msgboxUpdate.setText("failed to open setting file");
        msgboxUpdate.exec();
        return;
    }

    //Rewrite the default connection setting file
    file.resize(0);
    QMutexLocker inputLocker(mutex);
    QTextStream out(&file);
    out<<"NetworkMode: "<<_currentMode;
    file.close();
}









