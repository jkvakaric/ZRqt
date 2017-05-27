#include "readingtemperatureonewire.h"
#include <QFile>
#include <QDebug>

ReadingTemperatureOneWire::ReadingTemperatureOneWire(QObject *parent) : Reading(parent) { }

void ReadingTemperatureOneWire::measure(QString dataFilepath)
{
    QFile file(dataFilepath);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << file.errorString();
        qDebug() << "WARNING - sensor reading source file (" + dataFilepath + ") not found or unreadable";
        return;
    }

    QTextStream in(&file);
    QString read = in.readAll();
    QString readValue = read.section("t=", 1, 1, QString::SectionSkipEmpty).trimmed();
    readValue.insert(readValue.size() - 3, '.');

    readValue_ = readValue;

    file.close();
}
