import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.2

import assets 1.0

Item {
    property alias iconCharacter: textIcon.text
    property alias description: textDescription.text

    property color hoverColour: Style.colourNavigationBarBackground

    width: Style.widthNavigationButton
    height: Style.heightNavigationButton

    signal navigationButtonClicked()

    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.colourNavigationBarBackground

        Row {
            Text {
                id: textIcon
                width: Style.widthNavigationButtonIcon
                height: Style.heightNavigationButtonIcon
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font {
                    family: Style.fontAwesome
                    pixelSize: Style.pixelSizeNavigationBarIcon
                }
                color: Style.colourNavigationBarFont
                text: "\uf11a"
            }
            Text {
                id: textDescription
                width: Style.widthNavigationButtonDescription
                height: Style.heightNavigationButtonDescription
                verticalAlignment: Text.AlignVCenter
                color: Style.colourNavigationBarFont
                font.pixelSize: Style.pixelSizeNavigationBarText
                text: "SET ME!!"
            }

        }

        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: background
                    color: hoverColour
                }
            }
        ]

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state = ""
            onClicked: navigationButtonClicked()
        }
    }
}
