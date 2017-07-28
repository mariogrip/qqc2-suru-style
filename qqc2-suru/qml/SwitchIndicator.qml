import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

Item {
    property Item control

    implicitWidth: control.Suru.units.gu(5)
    implicitHeight: control.Suru.units.gu(2.5)

    opacity: control.enabled ? 1.0 : 0.3

    Rectangle {
        width: parent.width
        height: parent.height

        radius: control.Suru.units.RadiusMedium
        color: control.pressed
            ? control.Suru.baseColor
            : control.checked ? control.Suru.positiveColor : control.Suru.baseColor

        border.width: control.Suru.units.dp(1)
        border.color: control.checked && !control.pressed
                      ? control.Suru.positiveColor
                      : control.Suru.foregroundColor

        Behavior on color {
            ColorAnimation { duration: control.Suru.animation.BriskDuration }
        }

        Behavior on border.color {
            ColorAnimation { duration: control.Suru.animation.BriskDuration }
        }
    }

    Rectangle {
        width: control.Suru.units.gu(2.5)
        height: control.Suru.units.gu(2.5)
        radius: control.Suru.units.RadiusMedium

        color: control.Suru.backgroundColor

        border.width: control.Suru.units.dp(1)
        border.color: control.Suru.foregroundColor

        x: Math.max(0, Math.min(parent.width - width,
                                control.visualPosition * parent.width - (width / 2)))
        y: (parent.height - height) / 2

        Behavior on x {
            enabled: !control.pressed
            NumberAnimation { duration: control.Suru.animation.SnapDuration }
        }
    }
}
