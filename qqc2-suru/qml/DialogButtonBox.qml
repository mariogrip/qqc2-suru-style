import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls 2.1
import QtQuick.Controls.Suru 2.1

import "suru_helpers.js" as Helpers

T.DialogButtonBox {
    id: control

    implicitWidth: Helpers.calculate_implicit_width(control)
    implicitHeight: Helpers.calculate_implicit_height(control)

    spacing: control.Suru.units.SpacingMedium
    padding: control.Suru.units.PaddingXLarge

    topPadding: position === T.DialogButtonBox.Footer ? control.Suru.units.SpacingMedium : control.Suru.units.SpacingXLarge
    bottomPadding: position === T.DialogButtonBox.Header ? control.Suru.units.SpacingMedium : control.Suru.units.SpacingXLarge

    alignment: count === 1 ? Qt.AlignRight : undefined

    delegate: Button {
        width: control.count === 1 ? control.availableWidth / 2 : undefined
    }

    contentItem: ListView {
        implicitWidth: contentWidth
        implicitHeight: control.Suru.units.gu(4)

        model: control.contentModel
        spacing: control.spacing
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        snapMode: ListView.SnapToItem
    }
}
