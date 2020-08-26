/********************************************************************************
** Form generated from reading UI file 'blankpage.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLANKPAGE_H
#define UI_BLANKPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BlankPage
{
public:
    QPushButton *LastPage;
    QPushButton *NextPage;

    void setupUi(QWidget *BlankPage)
    {
        if (BlankPage->objectName().isEmpty())
            BlankPage->setObjectName(QString::fromUtf8("BlankPage"));
        BlankPage->resize(800, 600);
        BlankPage->setStyleSheet(QString::fromUtf8(""));
        LastPage = new QPushButton(BlankPage);
        LastPage->setObjectName(QString::fromUtf8("LastPage"));
        LastPage->setGeometry(QRect(600, 10, 71, 31));
        NextPage = new QPushButton(BlankPage);
        NextPage->setObjectName(QString::fromUtf8("NextPage"));
        NextPage->setGeometry(QRect(690, 10, 71, 31));

        retranslateUi(BlankPage);

        QMetaObject::connectSlotsByName(BlankPage);
    } // setupUi

    void retranslateUi(QWidget *BlankPage)
    {
        BlankPage->setWindowTitle(QCoreApplication::translate("BlankPage", "Form", nullptr));
        LastPage->setText(QCoreApplication::translate("BlankPage", "last page", nullptr));
        NextPage->setText(QCoreApplication::translate("BlankPage", "next page", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BlankPage: public Ui_BlankPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLANKPAGE_H
