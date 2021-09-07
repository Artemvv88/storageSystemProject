#include "product.h"

Product::Product()
{
    
}

ProductID Product::id() const
{
    return _id;
}

QString Product::title() const
{
    return _title;
}

void Product::setTitle(const QString &title)
{
    _title = title;
}

QString Product::info() const
{
    return _info;
}

void Product::setInfo(const QString &info)
{
    _info = info;
}

QVector<FlowItem> Product::flow() const
{
    return _flow;
}

void Product::addFlowItem(int flowAmount)
{
    _flow.append(FlowItem(QDateTime::currentDateTime(), flowAmount));
}

void Product::removeFlowItemAt(int index)
{
    if (index >= 0 && index < _flow.length()){
        _flow.removeAt(index);
    }
}

quint32 Product::size() const
{
    return _size;
}

void Product::setSize(const quint32 &size)
{
    _size = size;
}
