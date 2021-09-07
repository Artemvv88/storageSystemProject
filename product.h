#ifndef PRODUCT_H
#define PRODUCT_H

#include <QtGlobal>
#include <QString>
#include <QVector>


typedef quint32 ProductID;

class Product
{
private:
    ProductID _id;
    QString _title;
    QString _info;
    QVector<int> _flow;

public:
    Product();

    ProductID id() const;
    QString title() const;
    void setTitle(const QString &title);
    QString info() const;
    void setInfo(const QString &info);
    QVector<int> flow() const;
    void addFlowItem(int flowAmount);

    friend class Database;
};

#endif // PRODUCT_H
