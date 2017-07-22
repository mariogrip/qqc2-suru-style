import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

T.BusyIndicator {
    id: control

    implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding
    implicitHeight: contentItem.implicitHeight + topPadding + bottomPadding

    contentItem: Image {
        width: control.Suru.units.gu(12)
        height: control.Suru.units.gu(12)

        source: "image://suru/spinner/" + control.Suru.accentColor
        opacity: enabled ? 1.0 : 0.3

        RotationAnimator on rotation {
            running: control.visible && control.running
            from: 0
            to: 360
            loops: Animation.Infinite
            duration: control.Suru.animation.SleepyDuration
        }
    }
}
