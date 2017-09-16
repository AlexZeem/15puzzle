import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    id: root
    visible: true
    minimumWidth: 320
    minimumHeight: minimumWidth * 1.1
    maximumWidth: maximumHeight / 1.1
    maximumHeight: 720
    title: qsTr("15 puzzle")

    readonly property int widthMargin: 20
    readonly property int heightMargin: 40
    property int squareWidth: (root.width - widthMargin) / logic.itemsInRow
    property int squareHeight: (root.height - heightMargin) / logic.itemsInRow

    Image {
        anchors.fill: parent
        source: "/res/img/board.png"
    }

    Text {
        id: moveCountText
        anchors {
            bottom: board.top
            horizontalCenter: board.horizontalCenter
        }
        text: logic.moveCounter ? logic.moveCounter + qsTr(" moves") : ""
        font.family: "Helvetica"
        font.pointSize: 10
        font.weight: Font.DemiBold
        color: "white"
    }

    GridView {
        id: board
        width: logic.itemsInRow * squareWidth
        height: logic.itemsInRow * squareHeight

        anchors.centerIn: parent

        cellWidth: squareWidth
        cellHeight: squareHeight

        model: logic

        delegate: Tile {
            width: squareWidth
            height: squareHeight
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
        width: board.width + widthMargin
        height: board.height + heightMargin
        anchors.centerIn: board
    }

    MessageView {
        id: message
        visible: false
        width: board.width + widthMargin
        height: board.height + heightMargin
        anchors.centerIn: board
    }

    Item {
        anchors.fill: parent
        focus: true
        onFocusChanged: {
            if (!focus) {
                focus = true;
            }
        }

        Keys.onPressed: {
            if (event.key === Qt.Key_H) {
                event.accepted = true;
                hint.visible = !hint.visible;
            }
        }
    }

    Connections {
        target: logic
        onGameOver: {
            message.visible = !message.visible;
        }
    }
}
