#pragma once
#include <memory>
#include <QAbstractItemModel>

class Logic : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int itemsInRow READ itemsInRow CONSTANT)

public:
    explicit Logic(QObject *parent = 0);
    ~Logic();

    int itemsInRow() const;

protected:
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex & parent) const override;
    QVariant data(const QModelIndex & modelIndex, int role = Qt::DisplayRole) const override;

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
