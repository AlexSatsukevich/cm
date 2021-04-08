import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.2

import assets 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Client Management")

    Component.onCompleted: contentFrame.replace("qrc:/views/DashboardView.qml")

    Rectangle {
        id: navigationBar
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }
        width: 100
        color: "#000000"

        Column {
            Row {
                Text {
                    font {
                        family: Style.fontAwesome
                        pixelSize: 42
                    }
                    color: "#ffffff"
                    text: "\uf0c9"
                }
            }
            Row {
                Text {
                    font {
                        family: Style.fontAwesome
                        pixelSize: 42
                    }
                    color: "#ffffff"
                    text: "\uf015"
                }
                Text {
                    color: "#ffffff"
                    text: "Dashboard"
                }
            }
            Row {
                Text {
                    font {
                        family: Style.fontAwesome
                        pixelSize: 42
                    }
                    color: "#ffffff"
                    text: "\uf234"
                }
                Text {
                    color: "#ffffff"
                    text: "New Client"
                }

            }
            Row {
                Text {
                    font {
                        family: Style.fontAwesome
                        pixelSize: 42
                    }
                    color: "#ffffff"
                    text: "\uf002"
                }
                Text {
                    color: "#ffffff"
                    text: "Find Client"
                }

            }
        }
    }

    StackView {
        id: contentFrame
        clip: true
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: navigationBar.right
        }
        initialItem: Qt.resolvedUrl("qrc:/views/SplashView.qml")
    }

    Connections {
        target: masterController.ui_navigationController
        function onGoCreateClientView() { contentFrame.replace("qrc:/views/CreateClientView.qml") }
        function onGoDashboardView() { contentFrame.replace("qrc:/views/DashboardView.qml") }
        function onGoEditClientView(client) { contentFrame.replace("qrc:/views/EditClientView.qml", { selectedClient: client}) }
        function onGoFindClientView() { contentFrame.replace("qrc:/views/FindClientView.qml") }
    }
}
