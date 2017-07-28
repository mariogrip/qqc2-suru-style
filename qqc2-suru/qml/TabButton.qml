import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

import "suru_helpers.js" as Helpers

T.TabButton {
    id: control

    implicitWidth: Helpers.calculate_implicit_width(control)
    implicitHeight: Helpers.calculate_implicit_height(control)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: control.Suru.units.PaddingLarge

    contentItem: Label {
        text: control.text
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        opacity: control.checked || control.down || control.hovered ? 1.0 : 0.3
        color: control.hovered ? control.Suru.secondaryTextColor : control.Suru.primaryTextColor
    }
}
