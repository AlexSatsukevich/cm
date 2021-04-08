pragma Singleton
import QtQuick 2.0

Item {
    readonly property  color colourBackground: "#efefef"
    property alias fontAwesome: fontAwesomeLoader.name

    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/assets/fontawesome.tff"
    }
}
