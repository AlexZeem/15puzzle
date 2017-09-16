#pragma once
#include <memory>
#include <QAbstractItemModel>

class Logic : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int itemsInRow READ itemsInRow CONSTANT)
    Q_PROPERTY(bool onlySolvable READ onlySolvable WRITE setOnlySolvable NOTIFY onlySolvableChanged)

public:
    explicit Logic(QObject *parent = 0);
    ~Logic();

    int itemsInRow() const;
    bool onlySolvable() const;
    void setOnlySolvable(bool value);

    Q_INVOKABLE void move(int fromIndex);
    Q_INVOKABLE void shuffle();

signals:
    void onlySolvableChanged();

protected:
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex & parent) const override;
    QVariant data(const QModelIndex & modelIndex, int role = Qt::DisplayRole) const override;

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
