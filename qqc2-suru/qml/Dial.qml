import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1
import QtGraphicalEffects 1.0

T.Dial {
    id: control

    implicitWidth: control.Suru.units.gu(24)
    implicitHeight: control.Suru.units.gu(24)

    opacity: control.enabled ? 1.0 : 0.3

    background: Rectangle {
        x: control.width / 2 - width / 2
        y: control.height / 2 - height / 2

        width: Math.max(control.Suru.units.gu(24), Math.min(control.width, control.height))
        height: width; radius: width / 2

        color: "transparent"
        border.color: control.Suru.dividerColor
        border.width: control.Suru.units.dp(2)

        // http://stackoverflow.com/questions/22873550/how-to-create-a-circular-progress-bar-in-pure-qmljs
        ConicalGradient {
            source: control.background
            anchors.fill: parent
            antialiasing: true

            // Get ConicalGradient starting from the right position
            angle: -140

            gradient: control.position == 1.0 ? pos100Gradient : stdGradient
            Gradient {
                id: stdGradient
                GradientStop { position: 0.00; color: control.Suru.accentColor }
                GradientStop { position: control.position * 280 / 360; color: control.Suru.accentColor }
                GradientStop { position: control.position * 280 / 360 + 0.0000000000001; color: "transparent" }
                GradientStop { position: 1.00 * 280 / 360; color: "transparent" }
            }

            Gradient {
                id: pos100Gradient
                GradientStop { position: 0.00; color: control.Suru.accentColor }
                GradientStop { position: control.position * 280 / 360; color: control.Suru.accentColor }
                GradientStop { position: control.position * 280 / 360 + 0.0000000000001; color: "transparent" }
                GradientStop { position: 1.00; color: "transparent" }
            }
        }
    }

    handle: Rectangle {
        implicitWidth: control.Suru.units.gu(2)
        implicitHeight: control.Suru.units.gu(2)
        radius: width * 0.5

        x: background.x + background.width / 2 - handle.width / 2
        y: background.y + background.height / 2 - handle.height / 2

        color: control.pressed ? control.Suru.accentColor :
               control.hovered ? control.Suru.foregroundColor : control.Suru.baseColor

        transform: [
            Translate {
                y: -Math.min(background.width, background.height) * 0.4 + handle.height / 2
            },
            Rotation {
                angle: control.angle
                origin.x: handle.width / 2
                origin.y: handle.height / 2
            }
        ]
    }
}
