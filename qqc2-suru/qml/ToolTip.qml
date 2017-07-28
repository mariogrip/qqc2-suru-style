import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

import "suru_helpers.js" as Helpers

T.ToolTip {
    id: control

    x: parent ? (parent.width - implicitWidth) / 2 : 0
    y: -implicitHeight - control.Suru.units.SpacingLarge

    implicitWidth: Helpers.calculate_implicit_width(control)
    implicitHeight: Helpers.calculate_implicit_height(control)

    margins: control.Suru.units.SpacingMedium
    padding: control.Suru.units.SpacingMedium

    closePolicy: T.Popup.CloseOnEscape | T.Popup.CloseOnPressOutsideParent | T.Popup.CloseOnReleaseOutsideParent

    contentItem: Label {
        text: control.text
        font: control.font

        // ToolTip background uses inverted color.
        Suru.theme: control.Suru.theme == Suru.Light ? Suru.Dark : Suru.Light
    }

    enter: Transition {
        NumberAnimation {
            property: "opacity"
            from: 0.0; to: 1.0
            //easing.type: control.Suru.animation.StandardEasing
            duration: control.Suru.animation.BriskDuration
        }
    }

    exit: Transition {
        NumberAnimation {
            property: "opacity"
            from: 1.0; to: 0.0
            //easing.type: control.Suru.animation.StandardEasing
            duration: control.Suru.animation.BriskDuration
        }
    }

    background: Rectangle {
        color: control.Suru.tooltipColor
        radius: control.Suru.units.RadiusMedium
        border.color: control.Suru.dividerColor
        border.width: control.Suru.units.dp(1)
        opacity: 0.6    // Match opacity of overlayColor
    }
}
