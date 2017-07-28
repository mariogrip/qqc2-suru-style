import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.Suru 2.1
import QtQuick.Templates 2.1 as T

import "suru_helpers.js" as Helpers

T.RadioDelegate {
    id: control

    implicitWidth: Helpers.calculate_implicit_width(control)
    implicitHeight: Helpers.calculate_implicit_height_2(control, control.indicator)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: control.Suru.units.PaddingLarge
    spacing: control.Suru.units.SpacingLarge

    contentItem: Label {
        leftPadding: control.mirrored ? control.indicator.width + control.spacing : 0
        rightPadding: !control.mirrored ? control.indicator.width + control.spacing : 0

        text: control.text
        elide: Text.ElideRight
        visible: control.text
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    indicator: RadioIndicator {
        x: control.mirrored ? control.leftPadding : control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight - height) / 2

        control: control
    }

    background:  Rectangle {
        visible: control.down || control.highlighted || control.visualFocus || control.hovered
        color: control.down ? control.Suru.baseColor :
               control.hovered ? control.Suru.foregroundColor : control.Suru.backgroundColor

        Rectangle {
            width: parent.width
            height: parent.height
            visible: control.visualFocus || control.highlighted
            color: control.Suru.accent
            opacity: control.Suru.theme === Suru.Light ? 0.4 : 0.6
        }
    }
}
