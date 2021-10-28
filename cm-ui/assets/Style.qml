pragma Singleton
import QtQuick 2.0

Item {
    readonly property real widthWindow: 1920
    readonly property real heightWindow: 1080

    readonly property color colourNavigationBarBackground: "#000000"
    readonly property color colourNavigationBarFont: "#ffffff"
    readonly property int pixelSizeNavigationBarIcon: 42

    readonly property real widthNavigationButtonIcon: 80
    readonly property real heightNavigationButtonIcon: widthNavigationButtonIcon
    readonly property real widthNavigationButtonDescription: 160
    readonly property real heightNavigationButtonDescription: heightNavigationButtonIcon
    readonly property real widthNavigationButton: widthNavigationButtonIcon + widthNavigationButtonDescription
    readonly property real heightNavigationButton: Math.max(heightNavigationButtonIcon, heightNavigationButtonDescription)

    readonly property real widthNavigationBarCollapsed: widthNavigationButtonIcon
    readonly property real heightNavigationBarExpanded: widthNavigationButton

    readonly property  color colourBackground: "#efefef"
    property alias fontAwesome: fontAwesomeLoader.name
    readonly property int pixelSizeNavigationBarText: 22

    readonly property color colourCommandBarBackground: "#cecece"
    readonly property color colourCommandBarFont: "#131313"
    readonly property color colourCommandBarFontDisabled: "#636363"
    readonly property real heightCommandBar: heightCommandButton
    readonly property int pixelSizeCommandBarIcon: 32
    readonly property int pixelSizeCommandBarText: 12
    readonly property real widthCommandButton: 80
    readonly property real heightCommandButton: widthCommandButton

    readonly property real sizeScreenMargin: tscale(20)
    readonly property color colourDataControlsBackground: "#ffffff"
    readonly property color colourDataControlsFont: "#131313"
    readonly property int pixelSizeDataControls: 18
    readonly property real widthDataControls: 400
    readonly property real heightDataControls: 40

    readonly property real sizeControlSpacing: 10
    readonly property color colourPanelBackground: "#ffffff"
    readonly property color colourPanelBackgroundHover: "#ececec"
    readonly property color colourPanelHeaderBackground: "#131313"
    readonly property color colourPanelHeaderFont: "#ffffff"
    readonly property color colourPanelFont: "#131313"
    readonly property int pixelSizePanelHeader: 18
    readonly property real heightPanelHeader: 40
    readonly property real sizeShadowOffset: 5
    readonly property color colourShadow: "#dedede"

    readonly property color colourItemBackground: "#fefefe"
    readonly property color colourItemBackgroundHover: "#efefef"
    readonly property color colorItemBorder: "#efefef"
    readonly property color colorItemDateFont: "#636363"
    readonly property color colorItemTitleFont: "#131313"
    readonly property real sizeItemMargin: 5

    readonly property real widthWindowReference: 1920
    readonly property real heightWindowReference: 1080

    readonly property color colourDashboardBackground: "#f36f24"
    readonly property color colourDashboardFont: "#ffffff"
    readonly property int pixelSizeDashboard: tscale(36)
    readonly property real sizeDashboardLogo: tscale(500)

    readonly property color colourDataSelectorBackground: "#131313"
    readonly property color colourDataControlsBackgroundSelected: "#f36f24"
    readonly property color colourDataSelectorFont: "#ffffff"
    readonly property int sizeDataControlsRadius: tscale(5)

    function hscale(size) {
        return Math.round(size * (widthWindow / widthWindowReference))
    }
    function vscale(size) {
        return Math.round(size * (heightWindow / heightWindowReference))
    }
    function tscale(size) {
        return Math.round((hscale(size) + vscale(size)) / 2)
    }

    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/assets/fontawesome.tff"
    }
}
