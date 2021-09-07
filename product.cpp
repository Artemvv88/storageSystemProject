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

QVector<int> Product::flow() const
{
    return _flow;
}

void Product::addFlowItem(int flowAmount)
{
    _flow.append(flowAmount);
}
