import QtQuick 2.0
import QtQuick.Controls 2.2
import assets 1.0
import CM 1.0
import components 1.0

Item {
    property Client newClient: masterController.ui_newClient

    Rectangle {
        anchors.fill: parent
        color: Style.colourBackground
    }

    Column {
        spacing: Style.sizeScreenMargin
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: Style.sizeScreenMargin
        }
        Panel {
            headerText: "Client Details"
            contentComponent:
                Column {
                spacing: Style.sizeControlSpacing
                StringEditorSingleLine {
                    stringDecorator: newClient.ui_reference
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                }
                StringEditorSingleLine {
                    stringDecorator: newClient.ui_name
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                }
            }
        }
        AddressEditor {
            address: newClient.ui_supplyAddress
            headerText: "Supply Address"
        }
        AddressEditor {
            address: newClient.ui_billingAddress
            headerText: "Billing Address"
        }
    }

    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_createClientViewContextCommands
    }
}
