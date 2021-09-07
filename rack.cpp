#include "rack.h"

Rack::Rack()
{

}

RackID Rack::id() const
{
    return _id;
}

quint32 Rack::storagePosition() const
{
    return _storagePosition;
}

void Rack::setStoragePosition(const quint32 &storagePosition)
{
    _storagePosition = storagePosition;
}

quint32 Rack::capacity() const
{
    return _capacity;
}

void Rack::setCapacity(const quint32 &capacity)
{
    _capacity = capacity;
}
