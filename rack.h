#ifndef RACK_H
#define RACK_H

#include <QtGlobal>
#include <QString>
#include <QVector>

#include "product.h"


typedef quint32 RackID;

class Rack
{
private:
    RackID _id = -1;
    quint32 _storagePosition;
    quint32 _capacity;
    QVector<Product*> _products;

public:
    Rack();

    RackID id() const;
    quint32 storagePosition() const;
    void setStoragePosition(const quint32 &storagePosition);
    quint32 capacity() const;
    void setCapacity(const quint32 &capacity);
    QVector<Product *> products() const;

    friend class Database;
    friend class NewRackDialog;
};

#endif // RACK_H
