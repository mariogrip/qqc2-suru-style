import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

import "suru_helpers.js" as Helpers

T.ToolButton {
    id: control

    implicitWidth: Helpers.calculate_implicit_width(control)
    implicitHeight: Helpers.calculate_implicit_height(control)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: control.Suru.units.PaddingSmall
    property bool useSystemFocusVisuals: true

    contentItem: Label {
        text: control.text
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        implicitWidth: control.Suru.units.gu(4)
        implicitHeight: control.Suru.units.gu(6)

        color: control.enabled && (control.highlighted || control.checked) ? control.Suru.accentColor : "transparent"

        Rectangle {
            width: parent.width
            height: parent.height
            visible: control.down || control.hovered
            color: control.down ? control.Suru.baseColor : control.Suru.foregroundColor
        }
    }
}
