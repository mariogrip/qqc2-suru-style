import QtQuick 2.8
import QtQuick.Controls.Suru 2.1

Item {
    implicitWidth: control.Suru.units.gu(2.5)
    implicitHeight: control.Suru.units.gu(2.5)

    property Item control

    opacity: enabled ? 1.0 : 0.3

    Rectangle {
        anchors.fill: parent
        color: control.checked ? control.Suru.positiveColor : control.Suru.foregroundColor
        border.color: control.down
            ? control.Suru.positiveColor
            : control.checked ? control.Suru.foregroundColor : control.Suru.dividerColor

        border.width: control.Suru.units.dp(1)
        radius: control.Suru.units.RadiusMedium

        Behavior on color {
            ColorAnimation { duration: control.Suru.animation.FastDuration }
        }

        Behavior on border.color {
            ColorAnimation { duration: control.Suru.animation.FastDuration }
        }
    }

    Image {
        anchors { fill: parent; margins: control.Suru.units.dp(2) }

        // FIXME: Shouldn't be hard-coded
        source: control.checkState == Qt.PartiallyChecked
                ? "image://suru/checkmark-undefined/#FFFFFF"    // FIXME: Hard-coded
                : "image://suru/checkmark/#FFFFFF"    // FIXME: Hard-coded

        sourceSize.width: width
        sourceSize.height: height

        visible: control.checkState != Qt.Unchecked
    }
}
