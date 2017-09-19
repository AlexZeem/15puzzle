import QtQuick 2.0

Item {
    id: root

    Rectangle {
        id: tile
        anchors.fill: parent
        border.color: "grey"
        opacity: value ? 0.5 : 0
        radius: 10

        MouseArea {
            anchors.fill: parent
            onClicked: {
                logic.move(index)
            }
        }
    }

    Text {
        anchors.centerIn: tile
        text: value ? value : ""
        font.family: "Helvetica"
        font.pointSize: root.height / 3
        font.weight: Font.DemiBold
        color: value % 2 ? "white" : "yellow"
    }
}
