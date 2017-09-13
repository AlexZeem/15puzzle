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
            width: board.squareWidth
            height: board.squareHeight

            border.color: "black"

            Text {
                anchors.centerIn: parent
                text: value ? value : ""
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Item clicked:", value)
                }
            }
        }
    }
}
