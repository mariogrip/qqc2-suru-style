import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

T.ApplicationWindow {
    id: window

    color: window.Suru.backgroundColor

    overlay.modal: Rectangle {
        color: window.Suru.overlayColor
    }

    overlay.modeless: Rectangle {
        color: window.Suru.overlayColor
    }

    Rectangle {
        parent: window.activeFocusControl
        width: parent ? parent.width : 0
        height: parent ? parent.height : 0
        visible: parent && !!parent.useSystemFocusVisuals && !!parent.visualFocus

        color: "transparent"
        border {
            width: window.Suru.units.dp(2)
            color: window.Suru.accentColor
        }
    }
}
