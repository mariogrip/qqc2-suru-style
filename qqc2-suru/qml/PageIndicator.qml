import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

import "suru_helpers.js" as Helpers

T.PageIndicator {
    id: control

    implicitWidth: Helpers.calculate_implicit_width(control)
    implicitHeight: Helpers.calculate_implicit_height(control)

    padding: control.Suru.units.SpacingSmall
    spacing: control.Suru.units.SpacingSmall

    delegate: Rectangle {
        implicitWidth: control.Suru.units.gu(1)
        implicitHeight: control.Suru.units.gu(1)

        radius: width / 2

        color: index == control.currentIndex
               ? control.Suru.accentColor
               : pressed ? control.Suru.baseColor : "transparent"

        border {
            width: index == control.currentIndex ? 0 : control.Suru.units.dp(1)
            color: index == control.currentIndex ? control.Suru.accentColor : control.Suru.baseColor
        }
    }

    contentItem: Row {
        spacing: control.spacing

        Repeater {
            model: control.count
            delegate: control.delegate
        }
    }
}
