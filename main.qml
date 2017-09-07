import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    property int squareSize: 70
    visible: true
    width: logic.itemsInRow * squareSize
    height: logic.itemsInRow * squareSize
    title: qsTr("15 puzzle")

    Repeater {
        model: logic
        Rectangle {
            width: squareSize
            height: squareSize
            x: positionX * squareSize
            y: positionY * squareSize

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
