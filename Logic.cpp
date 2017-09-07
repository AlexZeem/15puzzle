#include <QDateTime>
#include <QSet>
#include <QDebug>
#include "Logic.h"

const int ITEMS_IN_ROW = 4;
const int MODEL_LENGTH = 16;

enum Roles {
    Value = Qt::UserRole,
    PositionX,
    PositionY,
};

struct Tile
{
    int value;
    int x;
    int y;
};

struct Logic::Impl
{
    Impl()
        : onlySolvable(true)
    {
        mix();
    }

    bool isSolvable();
    QPair<int, int> randomPosition();
    void randomize(int value, QSet<QPair<int, int> > &filledSquares);
    void mix();

    bool onlySolvable;
    QList<Tile> items;
};

bool Logic::Impl::isSolvable()
{
    int n = 0;
    int prevValue = items[0].value;
    if (prevValue == 0) {
        n = items[0].y + 1;
    }

    for (int i = 1; i < items.size(); ++i) {
        if (items[i].value == 0) {
            n += items[i].y + 1;
        } else if (prevValue > items[i].value) {
            n += 1;
        }

        prevValue = items[i].value;
    }

    qDebug() << "isSolvable" << n << (n % 2 == 0);
    return (n % 2 == 0);
}

QPair<int, int> Logic::Impl::randomPosition()
{
    QPair<int, int> position;

    position.first = qrand() % 4;
    position.second = qrand() % 4;

    return position;
}

void Logic::Impl::randomize(int value, QSet<QPair<int, int>>& filledSquares)
{
    QPair<int, int> position = randomPosition();

    if (!filledSquares.contains(position)) {
        items << Tile { value, position.first, position.second };
        filledSquares << position;
    } else {
        randomize(value, filledSquares);
    }
}

void Logic::Impl::mix()
{
    items.clear();
    QSet<QPair<int, int>> filledSquares;
    qsrand (QDateTime::currentMSecsSinceEpoch());

    for (int i = 0; i < MODEL_LENGTH; ++i) {
        randomize(i, filledSquares);
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
    names.insert(Roles::Value     , "value");
    names.insert(Roles::PositionX , "positionX");
    names.insert(Roles::PositionY , "positionY");
    return names;
}

int Logic::rowCount(const QModelIndex & ) const
{
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

    Tile & tile = impl->items[index];

    switch (role) {
    case Roles::Value    : return tile.value;
    case Roles::PositionX: return tile.x;
    case Roles::PositionY: return tile.y;
    }
    return QVariant();
}

