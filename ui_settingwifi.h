/********************************************************************************
** Form generated from reading UI file 'settingwifi.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGWIFI_H
#define UI_SETTINGWIFI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingWifi
{
public:
    QWidget *centralwidget;
    QWidget *InputWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *Password;
    QLineEdit *PasswordInput;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *SSID;
    QLineEdit *SSIDInput;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *OK;
    QPushButton *Cancel;
    QLabel *label;
    QPushButton *LastPage;
    QPushButton *NextPage;
    QLineEdit *TestText;
    QPushButton *Test;
    QGroupBox *groupBox;
    QRadioButton *wifiButton;
    QRadioButton *SIMButton;
    QGroupBox *groupBox_2;
    QPushButton *AddSSID;
    QPushButton *Clean;
    QListWidget *SSIDList;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *DeleteSSID;
    QTextEdit *SSIDContent;
    QPushButton *SaveSSID;
    QGroupBox *groupBox_3;
    QComboBox *TimeZoneCombo;
    QLCDNumber *Clock;
    QGroupBox *groupBox_4;
    QPushButton *Update;
    QLabel *UpdateLabel;
    QGroupBox *groupBox_5;
    QPushButton *AddAPN;
    QPushButton *CleanAPN;
    QLineEdit *APNContent;
    QPushButton *saveAPN;
    QPushButton *DeleteAPN;
    QPushButton *BeginConnect;
    QPushButton *connectSIM;
    QGroupBox *groupBox_6;
    QTextEdit *LogContent;
    QPushButton *DeleteLOG;
    QListWidget *LogList;
    QLabel *label_2;
    QLabel *label_3;
    QTextEdit *TestBox;
    QTextEdit *TestBox2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SettingWifi)
    {
        if (SettingWifi->objectName().isEmpty())
            SettingWifi->setObjectName(QString::fromUtf8("SettingWifi"));
        SettingWifi->resize(810, 762);
        centralwidget = new QWidget(SettingWifi);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        InputWidget = new QWidget(centralwidget);
        InputWidget->setObjectName(QString::fromUtf8("InputWidget"));
        InputWidget->setGeometry(QRect(510, 460, 281, 151));
        layoutWidget = new QWidget(InputWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 70, 261, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(20);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 29, 0);
        Password = new QLabel(layoutWidget);
        Password->setObjectName(QString::fromUtf8("Password"));

        horizontalLayout_2->addWidget(Password);

        PasswordInput = new QLineEdit(layoutWidget);
        PasswordInput->setObjectName(QString::fromUtf8("PasswordInput"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PasswordInput->sizePolicy().hasHeightForWidth());
        PasswordInput->setSizePolicy(sizePolicy);
        PasswordInput->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(PasswordInput);

        layoutWidget1 = new QWidget(InputWidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 261, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 29, 0);
        SSID = new QLabel(layoutWidget1);
        SSID->setObjectName(QString::fromUtf8("SSID"));

        horizontalLayout->addWidget(SSID);

        SSIDInput = new QLineEdit(layoutWidget1);
        SSIDInput->setObjectName(QString::fromUtf8("SSIDInput"));
        sizePolicy.setHeightForWidth(SSIDInput->sizePolicy().hasHeightForWidth());
        SSIDInput->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(SSIDInput);

        layoutWidget2 = new QWidget(InputWidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 120, 261, 25));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        OK = new QPushButton(layoutWidget2);
        OK->setObjectName(QString::fromUtf8("OK"));

        horizontalLayout_3->addWidget(OK);

        Cancel = new QPushButton(layoutWidget2);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));

        horizontalLayout_3->addWidget(Cancel);

        label = new QLabel(InputWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(-20, -20, 81, 31));
        LastPage = new QPushButton(centralwidget);
        LastPage->setObjectName(QString::fromUtf8("LastPage"));
        LastPage->setGeometry(QRect(600, 0, 71, 31));
        NextPage = new QPushButton(centralwidget);
        NextPage->setObjectName(QString::fromUtf8("NextPage"));
        NextPage->setGeometry(QRect(690, 0, 71, 31));
        TestText = new QLineEdit(centralwidget);
        TestText->setObjectName(QString::fromUtf8("TestText"));
        TestText->setGeometry(QRect(510, 50, 291, 41));
        Test = new QPushButton(centralwidget);
        Test->setObjectName(QString::fromUtf8("Test"));
        Test->setGeometry(QRect(710, 100, 91, 31));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 231, 61));
        wifiButton = new QRadioButton(groupBox);
        wifiButton->setObjectName(QString::fromUtf8("wifiButton"));
        wifiButton->setGeometry(QRect(10, 30, 82, 17));
        SIMButton = new QRadioButton(groupBox);
        SIMButton->setObjectName(QString::fromUtf8("SIMButton"));
        SIMButton->setGeometry(QRect(110, 30, 82, 17));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 150, 231, 301));
        AddSSID = new QPushButton(groupBox_2);
        AddSSID->setObjectName(QString::fromUtf8("AddSSID"));
        AddSSID->setEnabled(true);
        AddSSID->setGeometry(QRect(15, 250, 41, 41));
        Clean = new QPushButton(groupBox_2);
        Clean->setObjectName(QString::fromUtf8("Clean"));
        Clean->setGeometry(QRect(175, 250, 41, 41));
        SSIDList = new QListWidget(groupBox_2);
        SSIDList->setObjectName(QString::fromUtf8("SSIDList"));
        SSIDList->setGeometry(QRect(10, 40, 211, 81));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(85, 20, 61, 16));
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(90, 130, 47, 13));
        label_5->setAlignment(Qt::AlignCenter);
        DeleteSSID = new QPushButton(groupBox_2);
        DeleteSSID->setObjectName(QString::fromUtf8("DeleteSSID"));
        DeleteSSID->setGeometry(QRect(70, 250, 41, 41));
        SSIDContent = new QTextEdit(groupBox_2);
        SSIDContent->setObjectName(QString::fromUtf8("SSIDContent"));
        SSIDContent->setGeometry(QRect(10, 150, 211, 81));
        SSIDContent->setReadOnly(false);
        SaveSSID = new QPushButton(groupBox_2);
        SaveSSID->setObjectName(QString::fromUtf8("SaveSSID"));
        SaveSSID->setGeometry(QRect(125, 250, 41, 41));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(260, 20, 231, 111));
        TimeZoneCombo = new QComboBox(groupBox_3);
        TimeZoneCombo->setObjectName(QString::fromUtf8("TimeZoneCombo"));
        TimeZoneCombo->setGeometry(QRect(10, 20, 211, 31));
        Clock = new QLCDNumber(groupBox_3);
        Clock->setObjectName(QString::fromUtf8("Clock"));
        Clock->setGeometry(QRect(10, 60, 211, 41));
        Clock->setDigitCount(8);
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(260, 150, 231, 80));
        Update = new QPushButton(groupBox_4);
        Update->setObjectName(QString::fromUtf8("Update"));
        Update->setGeometry(QRect(10, 30, 101, 31));
        UpdateLabel = new QLabel(groupBox_4);
        UpdateLabel->setObjectName(QString::fromUtf8("UpdateLabel"));
        UpdateLabel->setGeometry(QRect(120, 30, 101, 31));
        UpdateLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(140, 140, 140);"));
        UpdateLabel->setAlignment(Qt::AlignCenter);
        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(20, 470, 231, 251));
        AddAPN = new QPushButton(groupBox_5);
        AddAPN->setObjectName(QString::fromUtf8("AddAPN"));
        AddAPN->setGeometry(QRect(15, 200, 41, 41));
        CleanAPN = new QPushButton(groupBox_5);
        CleanAPN->setObjectName(QString::fromUtf8("CleanAPN"));
        CleanAPN->setGeometry(QRect(175, 200, 41, 41));
        APNContent = new QLineEdit(groupBox_5);
        APNContent->setObjectName(QString::fromUtf8("APNContent"));
        APNContent->setGeometry(QRect(10, 20, 211, 171));
        APNContent->setReadOnly(true);
        saveAPN = new QPushButton(groupBox_5);
        saveAPN->setObjectName(QString::fromUtf8("saveAPN"));
        saveAPN->setGeometry(QRect(125, 200, 41, 41));
        DeleteAPN = new QPushButton(groupBox_5);
        DeleteAPN->setObjectName(QString::fromUtf8("DeleteAPN"));
        DeleteAPN->setGeometry(QRect(70, 200, 41, 41));
        BeginConnect = new QPushButton(centralwidget);
        BeginConnect->setObjectName(QString::fromUtf8("BeginConnect"));
        BeginConnect->setGeometry(QRect(30, 100, 81, 31));
        connectSIM = new QPushButton(centralwidget);
        connectSIM->setObjectName(QString::fromUtf8("connectSIM"));
        connectSIM->setGeometry(QRect(150, 100, 91, 31));
        groupBox_6 = new QGroupBox(centralwidget);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(260, 240, 231, 481));
        LogContent = new QTextEdit(groupBox_6);
        LogContent->setObjectName(QString::fromUtf8("LogContent"));
        LogContent->setGeometry(QRect(10, 150, 211, 271));
        LogContent->setReadOnly(true);
        DeleteLOG = new QPushButton(groupBox_6);
        DeleteLOG->setObjectName(QString::fromUtf8("DeleteLOG"));
        DeleteLOG->setGeometry(QRect(175, 430, 41, 41));
        LogList = new QListWidget(groupBox_6);
        LogList->setObjectName(QString::fromUtf8("LogList"));
        LogList->setGeometry(QRect(10, 40, 211, 81));
        label_2 = new QLabel(groupBox_6);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 20, 47, 13));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(groupBox_6);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 130, 47, 13));
        label_3->setAlignment(Qt::AlignCenter);
        TestBox = new QTextEdit(centralwidget);
        TestBox->setObjectName(QString::fromUtf8("TestBox"));
        TestBox->setGeometry(QRect(510, 140, 291, 141));
        TestBox2 = new QTextEdit(centralwidget);
        TestBox2->setObjectName(QString::fromUtf8("TestBox2"));
        TestBox2->setGeometry(QRect(510, 300, 291, 141));
        SettingWifi->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(SettingWifi);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SettingWifi->setStatusBar(statusbar);

        retranslateUi(SettingWifi);

        QMetaObject::connectSlotsByName(SettingWifi);
    } // setupUi

    void retranslateUi(QMainWindow *SettingWifi)
    {
        SettingWifi->setWindowTitle(QCoreApplication::translate("SettingWifi", "SettingWifi", nullptr));
        Password->setText(QCoreApplication::translate("SettingWifi", "Password:", nullptr));
        SSID->setText(QCoreApplication::translate("SettingWifi", "Ssid:", nullptr));
        OK->setText(QCoreApplication::translate("SettingWifi", "OK", nullptr));
        Cancel->setText(QCoreApplication::translate("SettingWifi", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("SettingWifi", "TextLabel", nullptr));
        LastPage->setText(QCoreApplication::translate("SettingWifi", "last page", nullptr));
        NextPage->setText(QCoreApplication::translate("SettingWifi", "next page", nullptr));
        Test->setText(QCoreApplication::translate("SettingWifi", "Test", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SettingWifi", "Default network connection mode: ", nullptr));
        wifiButton->setText(QCoreApplication::translate("SettingWifi", "Wifi", nullptr));
        SIMButton->setText(QCoreApplication::translate("SettingWifi", "SIM Card", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SettingWifi", "Existing WIFI SSID and password: ", nullptr));
        AddSSID->setText(QCoreApplication::translate("SettingWifi", "Add \n"
"SSID", nullptr));
        Clean->setText(QCoreApplication::translate("SettingWifi", "Delele\n"
"All", nullptr));
        label_4->setText(QCoreApplication::translate("SettingWifi", "SSID List", nullptr));
        label_5->setText(QCoreApplication::translate("SettingWifi", "Content", nullptr));
        DeleteSSID->setText(QCoreApplication::translate("SettingWifi", "Delete\n"
" SSID", nullptr));
        SaveSSID->setText(QCoreApplication::translate("SettingWifi", "Save", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("SettingWifi", "Timezone", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("SettingWifi", "Software Update", nullptr));
        Update->setText(QCoreApplication::translate("SettingWifi", "Update", nullptr));
        UpdateLabel->setText(QString());
        groupBox_5->setTitle(QCoreApplication::translate("SettingWifi", "Existing SIM APN", nullptr));
        AddAPN->setText(QCoreApplication::translate("SettingWifi", "Add \n"
"APN", nullptr));
        CleanAPN->setText(QCoreApplication::translate("SettingWifi", "Delele \n"
"All", nullptr));
        saveAPN->setText(QCoreApplication::translate("SettingWifi", "Save", nullptr));
        DeleteAPN->setText(QCoreApplication::translate("SettingWifi", "Delete \n"
"APN", nullptr));
        BeginConnect->setText(QCoreApplication::translate("SettingWifi", "Connect WIFI", nullptr));
        connectSIM->setText(QCoreApplication::translate("SettingWifi", "Connect SIM", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("SettingWifi", "Charge Log", nullptr));
        DeleteLOG->setText(QCoreApplication::translate("SettingWifi", "Delete", nullptr));
        label_2->setText(QCoreApplication::translate("SettingWifi", "Log List", nullptr));
        label_3->setText(QCoreApplication::translate("SettingWifi", "Content", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingWifi: public Ui_SettingWifi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGWIFI_H
