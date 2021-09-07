#ifndef PRODUCT_H
#define PRODUCT_H

#include <QtGlobal>
#include <QString>
#include <QVector>
#include <QPair>
#include <QDate>


typedef quint32 ProductID;
typedef QPair<QDateTime, int> FlowItem;

class Product
{
private:
    ProductID _id;
    QString _title;
    QString _info;
    QVector<FlowItem> _flow;
    quint32 _size = 0;

public:
    Product();

    ProductID id() const;
    QString title() const;
    void setTitle(const QString &title);
    QString info() const;
    void setInfo(const QString &info);
    QVector<FlowItem> flow() const;
    void addFlowItem(int flowAmount);
    void removeFlowItemAt(int index);
    quint32 size() const;
    void setSize(const quint32 &size);

    friend class Database;
    friend class NewProductDialog;
};

#endif // PRODUCT_H
