import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.Suru 2.1
import QtQuick.Templates 2.1 as T

import "suru_helpers.js" as Helpers

T.RadioButton {
    id: control

    implicitWidth: Helpers.calculate_implicit_width(control)
    implicitHeight: Helpers.calculate_implicit_height(control)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: control.Suru.units.PaddingMedium
    spacing: control.Suru.units.SpacingMedium

    indicator: RadioIndicator {
        x: text ? (control.mirrored ? control.width - width - control.rightPadding : control.leftPadding) : control.leftPadding + (control.availableWidth - width) / 2
        y: control.topPadding + (control.availableHeight - height) / 2
        control: control
    }

    contentItem: Label {
        leftPadding: control.indicator && !control.mirrored ? control.indicator.width + control.spacing : 0
        rightPadding: control.indicator && control.mirrored ? control.indicator.width + control.spacing : 0

        text: control.text
        color: control.down ? control.Suru.tertiaryTextColor : control.Suru.primaryTextColor
        elide: Text.ElideRight
        visible: control.text
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }
}
