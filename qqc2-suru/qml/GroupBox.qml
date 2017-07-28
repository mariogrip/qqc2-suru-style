import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.Suru 2.1
import QtQuick.Templates 2.1 as T

T.GroupBox {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            label ? label.implicitWidth + leftPadding + rightPadding : 0,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0, contentHeight + topPadding + bottomPadding)

    contentWidth: contentItem.implicitWidth || (contentChildren.length === 1 ? contentChildren[0].implicitWidth : 0)
    contentHeight: contentItem.implicitHeight || (contentChildren.length === 1 ? contentChildren[0].implicitHeight : 0)

    spacing: control.Suru.units.SpacingMedium
    padding: control.Suru.units.SpacingLarge
    topPadding: padding + (label && label.paintedWidth > 0 ? label.paintedHeight + spacing : 0)

    label: Label {
        x: control.leftPadding
        width: control.availableWidth
        text: control.title
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        y: control.topPadding - control.padding
        width: parent.width
        height: parent.height - control.topPadding + control.padding

        radius: control.Suru.units.RadiusMedium
        color: control.Suru.foregroundColor
        border.color: control.Suru.dividerColor
        border.width: control.Suru.units.dp(1)
    }
}
