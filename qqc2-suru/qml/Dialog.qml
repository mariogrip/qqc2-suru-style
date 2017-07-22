import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.Suru 2.1
import QtQuick.Templates 2.1 as T

import "suru_helpers.js" as Helpers

T.Dialog {
    id: control

    implicitWidth: Helpers.calculate_implicit_width_3(control)
    implicitHeight: Helpers.calculate_implicit_height_3(control)

    contentWidth: contentItem.implicitWidth || (contentChildren.length === 1 ? contentChildren[0].implicitWidth : 0)
    contentHeight: contentItem.implicitHeight || (contentChildren.length === 1 ? contentChildren[0].implicitHeight : 0)

    leftPadding: control.Suru.units.SpacingLarge
    rightPadding: control.Suru.units.SpacingLarge
    topPadding: control.Suru.units.SpacingXLarge
    bottomPadding: control.Suru.units.SpacingXLarge

    background: Rectangle {
        color: control.Suru.backgroundColor
        radius: control.Suru.units.dp(4)
        border.width: control.Suru.units.dp(1)
        border.color: control.Suru.dividerColor
    }

    header: Label {
        text: control.title
        visible: control.title
        elide: Label.ElideRight
        topPadding: control.Suru.units.SpacingLarge
        leftPadding: control.Suru.units.SpacingLarge
        rightPadding: control.Suru.units.SpacingLarge

        font.pixelSize: control.Suru.units.FontLarge
    }

    footer: DialogButtonBox {
        visible: count > 0
    }
}
