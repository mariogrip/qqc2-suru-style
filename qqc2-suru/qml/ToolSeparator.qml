import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

import "suru_helpers.js" as Helpers

T.ToolSeparator {
    id: control

    implicitWidth: Helpers.calculate_implicit_width(control)
    implicitHeight: Helpers.calculate_implicit_height(control)

    leftPadding: vertical ? control.Suru.units.PaddingLarge : control.Suru.units.PaddingMedium
    rightPadding: vertical ? control.Suru.units.PaddingLarge : control.Suru.units.PaddingMedium
    topPadding: vertical ? control.Suru.units.PaddingMedium : control.Suru.units.PaddingLarge
    bottomPadding: vertical ? control.Suru.units.PaddingMedium : control.Suru.units.PaddingLarge

    contentItem: Rectangle {
        implicitWidth: vertical ? control.Suru.units.dp(1) : control.Suru.units.gu(4)
        implicitHeight: vertical ? control.Suru.units.gu(4) : control.Suru.units.dp(1)
        color: control.Suru.dividerColor
    }
}
