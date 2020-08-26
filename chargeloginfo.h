#ifndef CHARGELOGINFO_H
#define CHARGELOGINFO_H

#include <QDateTime>
#include <QList>


class ChargeLogInfo
{
public:
    ChargeLogInfo(QString contentOneDay);
    ChargeLogInfo();
    ChargeLogInfo(QDateTime dateTime, int connectorID, QString SOC, QString stopReason,QString chargedTime, QString chargedPower);

private:
    QDateTime _dateTime;
    int _connectorID;
    QString _SOC;
    QString _stopReason;
    QString _chargedTime;
    QString _chargedPower;
    bool _dateChanged;

    QString _contentOneDay;

};

#endif // CHARGELOGINFO_H
