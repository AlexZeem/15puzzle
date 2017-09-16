#pragma once
#include <memory>
#include <QAbstractItemModel>

class Logic : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int itemsInRow READ itemsInRow CONSTANT)
    Q_PROPERTY(int moveCounter READ moveCounter NOTIFY moveCounterChanged)

public:
    explicit Logic(QObject *parent = 0);
    ~Logic();

    int itemsInRow() const;
    int moveCounter() const;

    Q_INVOKABLE void move(int fromIndex);
    Q_INVOKABLE void shuffle();

signals:
    void moveCounterChanged();
    void gameOver();

protected:
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex & parent) const override;
    QVariant data(const QModelIndex & modelIndex, int role = Qt::DisplayRole) const override;

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
