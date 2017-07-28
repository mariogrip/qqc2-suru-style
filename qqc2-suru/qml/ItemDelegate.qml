import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

import "suru_helpers.js" as Helpers

T.ItemDelegate {
    id: control

    implicitWidth: Helpers.calculate_implicit_width(control)
    implicitHeight: Helpers.calculate_implicit_height_2(control, control.indicator)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    spacing: control.Suru.units.SpacingLarge
    padding: control.Suru.units.PaddingLarge

    contentItem: Label {
        leftPadding: !control.mirrored ? (control.indicator ? control.indicator.width : 0) + control.spacing : 0
        rightPadding: control.mirrored ? (control.indicator ? control.indicator.width : 0) + control.spacing : 0

        text: control.text
        font: control.font
        elide: Text.ElideRight
        visible: control.text
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    background: Item {
        Rectangle {
            anchors.fill: parent
            visible: control.down || control.hovered
            color: control.down ? control.Suru.baseColor : control.Suru.foregroundColor
        }

        Rectangle {
            anchors.fill: parent
            visible: control.visualFocus || control.highlighted
            color: control.Suru.accentColor
            opacity: 0.5
        }
    }
}
