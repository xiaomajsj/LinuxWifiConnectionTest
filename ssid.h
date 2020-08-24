#ifndef SSID_H
#define SSID_H

#include <QString>

class SSID
{
public:
    SSID(QString ssid, QString password, QString psk);
    SSID();
    ~SSID();

    QString getSSID(){return _ssid;}
    QString getPassword(){return _password;}
    QString getPSK(){return _psk;}

    void SetSSID(QString ssid){_ssid=ssid;}
    void SetPassword(QString pass){_password=pass;}
    void SetPSK(QString psk){_psk=psk;}
    void Clear();

private:
    QString _ssid;
    QString _password;
    QString _psk;
    bool _haspassword;
    bool _hasSSID;
    bool _hasPSK;
    bool _inputting;


    friend class SettingWifi;

};
#endif // SSID_H
