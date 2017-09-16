import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    id: root
    readonly property int squareSize: 70
    visible: true
    minimumWidth: 320
    minimumHeight: 480
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
            NumberAnimation { properties: "x,y"; duration: 500; }
        }
    }

    Text {
        id: hintText
        anchors {
            top: board.bottom
            left: board.left
        }
        text: qsTr("* press H for hint")
        font.family: "Helvetica"
        font.pointSize: 10
        font.weight: Font.DemiBold
        color: "yellow"
    }

    Hint {
        id: hint
        visible: false
        width: board.width + 20
        height: board.height + 20
        anchors.centerIn: board
    }

    Item {
        anchors.fill: parent
        focus: true
        onFocusChanged: {
            if (!focus) focus = true;
        }

        Keys.onPressed: {
            if (event.key === Qt.Key_H) {
                event.accepted = true;
                hint.visible = !hint.visible;
            }
        }
    }
}
