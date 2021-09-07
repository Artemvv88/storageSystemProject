#include "rack.h"

QVector<Product *> Rack::products() const
{
    return _products;
}

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

void Rack::addProduct(Product *product)
{
    _products.push_back(product);
}

Product *Rack::getProductById(ProductID productId)
{
    for (auto product : _products) {
        if (product->id() == productId) {
            return product;
        }
    }

    return nullptr;
}

void Rack::removeProductById(ProductID productId)
{
    auto product = getProductById(productId);
    if (product != nullptr) {
        _products.removeOne(product);
    }
}
