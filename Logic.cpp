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
        : moveCount(0)
    {
        mix();
    }

    bool isSolvable();
    bool gameOver();
    void mix();
    int findIndexToMove(int fromIndex);

    int moveCount;
    QList<int> items;
};

bool Logic::Impl::isSolvable()
{
    int parity = 0;
    int row = 0;
    int blankRow = 0;
    bool isSolvable = false;

    for (int i = 0; i < items.size(); ++i)
    {
        if (i % ITEMS_IN_ROW == 0) {
            row++;
        }

        if (items[i] == 0) {
            blankRow = row;
            continue;
        }

        for (int j = i + 1; j < items.size(); ++j)
        {
            if (items[i] > items[j] && items[j] != 0)
            {
                parity++;
            }
        }
    }

    if (blankRow % 2 == 0) {
        isSolvable = parity % 2 == 0;
    } else {
        isSolvable = parity % 2 != 0;
    }

    return isSolvable;
}

bool Logic::Impl::gameOver()
{
    int prevValue = items[0];
    for (int i = 1; i < items.size(); ++i) {
        if (prevValue > items[i] && prevValue != 0 && items[i] != 0) {
            return false;
        }
        prevValue = items[i];
    }
    return true;
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

    if (!isSolvable()) {
        mix();
    }
}

int Logic::Impl::findIndexToMove(int fromIndex)
{
    int index = fromIndex + 1;
    if (index < items.size() && !items[index] && index / 4 == fromIndex / 4) {
        return index;
    }

    index = fromIndex - 1;
    if (index >= 0 && !items[index] && index / ITEMS_IN_ROW == fromIndex / ITEMS_IN_ROW) {
        return index;
    }

    index = fromIndex + ITEMS_IN_ROW;
    if (index < items.size() && !items[index] && index % ITEMS_IN_ROW == fromIndex % ITEMS_IN_ROW) {
        return index;
    }

    index = fromIndex - ITEMS_IN_ROW;
    if (index >= 0 && !items[index] && index % ITEMS_IN_ROW == fromIndex % ITEMS_IN_ROW) {
        return index;
    }

    return -1;
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

int Logic::moveCounter() const
{
    return impl->moveCount;
}

void Logic::move(int fromIndex)
{
    if (fromIndex < 0 || fromIndex >= impl->items.size() || impl->items[fromIndex] == 0) {
        return;
    }

    int toIndex = impl->findIndexToMove(fromIndex);
    if (toIndex == -1) {
        return;
    }

    beginMoveRows(QModelIndex(), fromIndex, fromIndex, QModelIndex(), toIndex + (fromIndex < toIndex ? 1 : 0));
    impl->items.swap(fromIndex, toIndex);
    endMoveRows();

    impl->moveCount++;
    emit moveCounterChanged();

    int lowest  = qMin(fromIndex, toIndex);
    int highest = qMax(fromIndex, toIndex);
    QModelIndex topLeft = createIndex(lowest, 0);
    QModelIndex bottomRight = createIndex(highest, 0);
    emit dataChanged(topLeft, bottomRight);

    if (impl->items.first() == 0 || impl->items.last() == 0) {
        if (impl->gameOver()) {
            emit gameOver();
        }
    }
}

void Logic::shuffle()
{
    beginResetModel();
    impl->mix();
    endResetModel();

    impl->moveCount = 0;
    emit moveCounterChanged();
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

