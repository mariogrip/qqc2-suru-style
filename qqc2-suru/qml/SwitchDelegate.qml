import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

import "suru_helpers.js" as Helpers

T.CheckDelegate {
    id: control

    implicitWidth: Helpers.calculate_implicit_width(control)
    implicitHeight: Helpers.calculate_implicit_height_2(control, control.indicator)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: control.Suru.units.PaddingLarge
    spacing: control.Suru.units.SpacingLarge

    indicator: SwitchIndicator {
        x: text ? (control.mirrored ? control.leftPadding : control.width - width - control.rightPadding) : control.leftPadding + (control.availableWidth - width) / 2
        y: control.topPadding + (control.availableHeight - height) / 2
        control: control
    }

    contentItem: Label {
        leftPadding: !control.mirrored ? 0 : control.indicator.width + control.spacing
        rightPadding: control.mirrored ? 0 : control.indicator.width + control.spacing

        text: control.text
        font: control.font
        elide: Text.ElideRight
        visible: control.text
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        visible: control.down || control.highlighted || control.visualFocus || control.hovered
        color: control.down ? control.Suru.baseColor :
               control.hovered ? control.Suru.foregroundColor : control.Suru.backgroundColor

        Rectangle {
            width: parent.width
            height: parent.height
            visible: control.visualFocus || control.highlighted
            color: control.Suru.accent
            opacity: 0.5
        }
    }
}
