import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

T.Frame {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0, contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0, contentHeight + topPadding + bottomPadding)

    contentWidth: contentItem.implicitWidth || (contentChildren.length === 1 ? contentChildren[0].implicitWidth : 0)
    contentHeight: contentItem.implicitHeight || (contentChildren.length === 1 ? contentChildren[0].implicitHeight : 0)

    padding: control.Suru.units.spacingMedium
    spacing: control.Suru.units.spacingLarge

    background: Rectangle {
        radius: control.Suru.units.dp(4)
        color: control.Suru.frameColor
        border.width: control.Suru.units.dp(1)
        border.color: control.Suru.dividerColor
    }
}
