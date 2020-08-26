#include "chargeloginfo.h"

ChargeLogInfo::ChargeLogInfo()
{
_dateChanged=false;
}
ChargeLogInfo::ChargeLogInfo(QString contentOneDay)
{
_dateChanged=false;
_contentOneDay=contentOneDay;
}


ChargeLogInfo::ChargeLogInfo(QDateTime dateTime, int connectorID, QString SOC, QString stopReason,QString chargedTime, QString chargedPower)
{
_dateTime=dateTime;
_connectorID=connectorID;
_SOC=SOC;
_stopReason=stopReason;
_chargedTime=chargedTime;
_chargedPower=chargedPower;

_dateChanged=false;
}
