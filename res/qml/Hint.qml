import QtQuick 2.0

MessageView {
    id: root
    property int imageSize: Math.min(body.width, body.height) / 1.25
    message: ""
    buttonText: qsTr("Shuffle")

    Text {
        id: title
        anchors {
            top: body.top
            topMargin: 10
            horizontalCenter: body.horizontalCenter
        }
        text: qsTr("Winning combo")
        font.family: "Helvetica"
        font.pointSize: 20
        font.weight: Font.DemiBold
        color: "yellow"
    }

    Image {
        id: combo
        anchors {
            top: title.bottom
            horizontalCenter: root.horizontalCenter
            topMargin: 5
        }
        width: imageSize
        height: imageSize
        source: "/res/img/win_combo.png"
    }
}
