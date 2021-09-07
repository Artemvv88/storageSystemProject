#ifndef RACK_H
#define RACK_H

#include <QtGlobal>
#include <QString>
#include <QVector>


typedef quint32 RackID;

class Rack
{
private:
    RackID _id;
    quint32 _storagePosition;
    quint32 _capacity;

public:
    Rack();

    RackID id() const;
    quint32 storagePosition() const;
    void setStoragePosition(const quint32 &storagePosition);
    quint32 capacity() const;
    void setCapacity(const quint32 &capacity);
};

#endif // RACK_H
