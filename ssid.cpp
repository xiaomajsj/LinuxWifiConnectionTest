#include "ssid.h"



SSID::SSID(QString ssid, QString password, QString psk)
{
    _ssid=ssid;
    _password=password;
    _psk=psk;
    _haspassword=true;
    _hasSSID=true;
    _hasPSK=true;
    _inputting=false;
}

SSID::~SSID()
{


}

SSID::SSID()
{
    _haspassword=false;
    _hasSSID=false;
    _hasPSK=false;
    _inputting=false;
}

void SSID::Clear()
{
    _ssid="";
    _password="";
    _haspassword=false;
    _hasSSID=false;
    _hasPSK=false;
    _inputting=false;
}
