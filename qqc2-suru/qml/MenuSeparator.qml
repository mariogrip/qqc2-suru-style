import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

T.MenuSeparator {
    id: control

    implicitWidth: Helpers.calculate_implicit_width(control)
    implicitHeight: Helpers.calculate_implicit_height(control)

    topPadding: control.Suru.units.SpacingMedium
    bottomPadding: control.Suru.units.SpacingMedium

    contentItem: Rectangle {
        implicitWidth: control.Suru.units.gu(24)
        implicitHeight: control.Suru.units.dp(1)
        color: control.Suru.dividerColor
    }
}
