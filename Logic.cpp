#include <QDebug>
#include "Logic.h"

const int ITEMS_IN_ROW = 4;

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
    {
        for (int i = 0; i < ITEMS_IN_ROW; ++i) {
            for (int j = 0; j < ITEMS_IN_ROW; ++j) {
                items << Tile { i * ITEMS_IN_ROW + j, j, i };
            }
        }

        mix();
    }

    bool isSolvable();
    void mix();

    QList<Tile> items;
};

bool Logic::Impl::isSolvable()
{
    return true;
}

void Logic::Impl::mix()
{

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

