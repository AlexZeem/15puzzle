import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    id: root
    readonly property int squareSize: 70
    visible: true
    width: 320
    height: 480
    title: qsTr("15 puzzle")

    Image {
        anchors.fill: parent
        source: "/img/board.png"
    }

    GridView {
        id: board
        width: logic.itemsInRow * squareSize
        height: logic.itemsInRow * squareSize

        anchors.centerIn: parent

        cellWidth: squareSize
        cellHeight: squareSize

        model: logic

        delegate: Tile {
            width: squareSize
            height: squareSize
        }

        move: Transition {
            NumberAnimation { properties: "x,y"; duration: 500 }
        }
    }
}
