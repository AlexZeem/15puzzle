#include <QDateTime>
#include <QSet>
#include <QDebug>
#include "Logic.h"

const int ITEMS_IN_ROW = 4;
const int MODEL_LENGTH = 16;

enum Roles {
    Value = Qt::UserRole
};

struct Logic::Impl
{
    Impl()
        : onlySolvable(true)
    {
        mix();
    }

    bool isSolvable();
    void mix();

    bool onlySolvable;
    QList<int> items;
};

bool Logic::Impl::isSolvable()
{
    int n = 0;
    int prevValue = items[0];
    if (prevValue == 0) {
        n = 1;
    }

    for (int i = 1; i < items.size(); ++i) {
        if (items[i] == 0) {
            n += i % ITEMS_IN_ROW + 1;
        } else if (prevValue > items[i]) {
            n += 1;
        }

        prevValue = items[i];
    }

    qDebug() << "isSolvable" << n << (n % 2 == 0);
    return (n % 2 == 0);
}

void Logic::Impl::mix()
{
    items.clear();
    qsrand (QDateTime::currentMSecsSinceEpoch());

    QSet<int> filledSquares;
    while (items.size() <= MODEL_LENGTH - 1) {
       int item = qrand() % 16;
       if (!filledSquares.contains(item)) {
           items << item;
           filledSquares << item;
       } else {
           continue;
       }
    }

    if (!isSolvable() && onlySolvable) {
        mix();
    }
}

Logic::Logic(QObject *parent)
    : QAbstractListModel(parent)
    , impl(new Impl())
{ }

Logic::~Logic()
{}

int Logic::itemsInRow() const
{
    return ITEMS_IN_ROW;
}

bool Logic::onlySolvable() const
{
    return impl->onlySolvable;
}

void Logic::setOnlySolvable(bool value)
{
    if (value != impl->onlySolvable) {
        impl->onlySolvable = value;
        emit onlySolvableChanged();
    }
}

QHash<int, QByteArray> Logic::roleNames() const
{
    QHash<int, QByteArray> names;
    names.insert(Roles::Value   , "value");
    return names;
}

int Logic::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return impl->items.size();
}

QVariant Logic::data(const QModelIndex & modelIndex, int role) const
{
    if (!modelIndex.isValid()) {
        return QVariant();
    }

    int index = static_cast<int>(modelIndex.row());

    if (index >= impl->items.size() || index < 0) {
        return QVariant();
    }

    if (role == Roles::Value) {
        return impl->items[index];
    }

    return QVariant();
}

