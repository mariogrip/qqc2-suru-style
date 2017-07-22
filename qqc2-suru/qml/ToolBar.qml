import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

import "suru_helpers.js" as Helpers

T.ToolBar {
    id: control

    implicitWidth: Helpers.calculate_implicit_width(control)
    implicitHeight: Helpers.calculate_implicit_height(control)

    contentWidth: contentItem.implicitWidth || (contentChildren.length === 1 ? contentChildren[0].implicitWidth : 0)
    contentHeight: contentItem.implicitHeight || (contentChildren.length === 1 ? contentChildren[0].implicitHeight : 0)

    background: Rectangle {
        implicitHeight: control.Suru.units.gu(6)
        color: control.Suru.toolBarColor

        Rectangle {
            anchors { left: parent.left; right: parent.right }
            anchors.bottom: control.position == T.ToolBar.Header ? parent.bottom : undefined
            anchors.top: control.position == T.ToolBar.Footer ? parent.top : undefined
            height: control.Suru.units.dp(1)
            color: control.Suru.dividerColor
            visible: control.position == T.ToolBar.Header || control.position == T.ToolBar.Footer
        }
    }
}
