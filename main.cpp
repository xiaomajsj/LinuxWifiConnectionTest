#include "settingwifi.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SettingWifi w;
    w.show();
    return a.exec();
}
