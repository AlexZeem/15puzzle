import QtQuick 2.0
import QtQuick.Controls 1.04
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: root
    radius: 10

    property alias body: body
    property alias message: message.text
    property alias buttonText: buttonText.text

    Image {
        anchors.fill: parent
        source: "/res/img/board.png"
    }

    Rectangle {
        id: background
        anchors.fill: parent
        opacity: 0.6
        radius: 10
        border.color: "grey"
    }

    Item {
        id: body
        anchors.centerIn: parent
        width: root.width / 1.25
        height: root.height / 1.25

        Text {
            id: message
            anchors.centerIn: parent
            text: qsTr("Game over\nWell done!")
            horizontalAlignment: Text.AlignHCenter
            font.family: "Helvetica"
            font.pointSize: 20
            font.weight: Font.DemiBold
            color: "yellow"
        }
    }

    Button {
        anchors {
            top: body.bottom
            horizontalCenter: body.horizontalCenter
        }

        onClicked: {
            logic.shuffle();
            root.visible = false;
        }

        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 25
                border.width: control.activeFocus ? 2 : 1
                border.color: "grey"
                radius: 5
                gradient: Gradient {
                    GradientStop { position: 0 ; color: control.pressed ? "#D1C8C1" : "#CFC6BF" }
                    GradientStop { position: 1 ; color: control.pressed ? "#D6CDC6" : "#D1C8C1" }
                }
            }
        }

        Text {
            id: buttonText
            anchors.centerIn: parent
            text: qsTr("New game")
            font.family: "Helvetica"
            font.pointSize: 14
            font.weight: Font.DemiBold
            color: "yellow"
        }
    }
}
