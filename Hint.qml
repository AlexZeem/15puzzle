import QtQuick 2.0
import QtQuick.Controls 1.04
import QtQuick.Controls.Styles 1.4

Item {
    id: root
    property int imageSize: 140

    Image {
        anchors.fill: parent
        source: "/img/board.png"
    }

    Rectangle {
        id: background
        anchors.fill: parent
        opacity: 0.6
        border.color: "grey"
        radius: 10
    }

    Text {
        id: title
        anchors {
            top: background.top
            topMargin: 10
            horizontalCenter: background.horizontalCenter
        }
        text: qsTr("Winning combo")
        font.family: "Helvetica"
        font.pointSize: 20
        font.weight: Font.DemiBold
        color: "yellow"
    }

    Image {
        anchors {
            top: title.bottom
            left: background.left
            topMargin: 5
            leftMargin: 10
        }
        width: imageSize
        height: imageSize
        source: "/img/win_combo1.png"
    }

    Image {
        anchors {
            top: title.bottom
            right: background.right
            topMargin: 5
            rightMargin: 10
        }
        width: imageSize
        height: imageSize
        source: "/img/win_combo2.png"
    }

    Button {
        anchors {
            bottom: background.bottom
            bottomMargin: 10
            horizontalCenter: background.horizontalCenter
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
            anchors.centerIn: parent
            text: qsTr("Shuffle")
            font.family: "Helvetica"
            font.pointSize: 14
            font.weight: Font.DemiBold
            color: "yellow"
        }
    }
}
