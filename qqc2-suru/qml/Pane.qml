import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

import "suru_helpers.js" as Helpers

T.Pane {
    id: control

    implicitWidth: Helpers.calculate_implicit_width(control)
    implicitHeight: Helpers.calculate_implicit_height(control)

    contentWidth: contentItem.implicitWidth || (contentChildren.length === 1 ? contentChildren[0].implicitWidth : 0)
    contentHeight: contentItem.implicitHeight || (contentChildren.length === 1 ? contentChildren[0].implicitHeight : 0)

    padding: control.Suru.units.PaddingLarge

    background: Rectangle {
        color: control.Suru.backgroundColor
    }
}
