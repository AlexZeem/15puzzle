import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    readonly property int squareMinSize: 70
    visible: true
    width: logic.itemsInRow * squareMinSize
    height: logic.itemsInRow * squareMinSize
    title: qsTr("15 puzzle")

    GridView {
        id: board
        property int squareWidth: parent.width / logic.itemsInRow
        property int squareHeight: parent.height / logic.itemsInRow

        anchors.fill: parent

        cellWidth: board.squareWidth
        cellHeight: board.squareHeight

        model: logic

        delegate: Rectangle {
            id: tile
            width: board.squareWidth
            height: board.squareHeight

            border.color: "black"
            opacity: value ? 1.0 : 0.1

            Text {
                anchors.centerIn: parent
                text: value ? value : ""
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Item clicked:", index, value)
                    logic.move(index)
                }
            }
        }

        move: Transition {
                NumberAnimation { properties: "x,y"; duration: 500 }
            }
    }
}
