#ifndef READINGTEMPERATUREONEWIRE_H
#define READINGTEMPERATUREONEWIRE_H

#include "reading.h"
#include <QObject>

class ReadingTemperatureOneWire : public Reading
{
    Q_OBJECT

public:
    explicit ReadingTemperatureOneWire(QObject *parent = 0);
    virtual void measure(QString dataFilepath);

};

#endif // READINGTEMPERATUREONEWIRE_H
