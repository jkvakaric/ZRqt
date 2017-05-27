#ifndef RTID_H
#define RTID_H

#include <QMap>

enum RTID
{
    TemperatureOneWire
};

struct RTIDMap
{
    static QMap<QString, int> map;
};

#endif // RTID_H
