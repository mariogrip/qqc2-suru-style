import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.Suru 2.1

Rectangle {
    implicitWidth: control.Suru.units.gu(2.5)
    implicitHeight: control.Suru.units.gu(2.5)

    property Item control

    opacity: enabled ? 1 : 0.3

    radius: width / 2
    color: control.checked
        ? control.Suru.positiveColor
        : control.Suru.foregroundColor

    border.color: control.down
        ? control.Suru.positiveColor
        : control.checked ? control.Suru.foregroundColor : control.Suru.dividerColor

    border.width: control.Suru.units.dp(1)

    Behavior on color {
        ColorAnimation { duration: control.Suru.animation.FastDuration }
    }

    Behavior on border.color {
        ColorAnimation { duration: control.Suru.animation.FastDuration }
    }

    Rectangle {
        anchors.centerIn: parent
        width: control.Suru.units.gu(1); height: width
        radius: width * 0.5
        color: control.Suru.backgroundColor
        visible: control.checked
        opacity: visible ? 1.0 : 0.0

        Behavior on opacity {
            NumberAnimation { duration: control.Suru.animation.FastDuration }
        }
    }
}
