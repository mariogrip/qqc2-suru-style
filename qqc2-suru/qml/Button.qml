import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1
import QtQuick.Controls.Material.impl 2.1 as Material	// drop shadows

import "suru_helpers.js" as Helpers

T.Button {
    id: control

    implicitWidth: Helpers.calculate_implicit_width(control)
    implicitHeight: Helpers.calculate_implicit_height(control)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    leftPadding: control.Suru.units.PaddingXLarge
    rightPadding: control.Suru.units.PaddingXLarge
    topPadding: control.Suru.units.PaddingMedium
    bottomPadding: control.Suru.units.PaddingMedium

    property bool useSystemFocusVisuals: true

    contentItem: Label {
        text: control.text
        font: control.font
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        color: control.flat && control.highlighted
                 ? control.Suru.accentColor
                 : control.highlighted ? control.Suru.primaryHighlightedTextColor : control.Suru.primaryTextColor
    }

    background: Rectangle {
        visible: !control.flat

        color: control.down
               ? control.Suru.baseColor
               : control.enabled && (control.highlighted || control.checked)
                 ? control.Suru.accentColor
                 : control.Suru.foregroundColor

        radius: control.Suru.units.RadiusMedium
        //border.width: control.Suru.units.dp(1)
        //border.color: control.Suru.dividerColor

        // TODO: Use our own implementation of drop shadows
        layer.enabled: control.enabled && !control.flat
        layer.effect: Material.ElevationEffect {
            elevation: 1
        }
    }
}
