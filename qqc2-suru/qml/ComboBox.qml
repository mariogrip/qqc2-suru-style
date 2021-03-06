/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls 2 module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

import "suru_helpers.js" as Helpers

T.ComboBox {
    id: control

    implicitWidth: Helpers.calculate_implicit_width(control)
    implicitHeight: Helpers.calculate_implicit_height_2(control, control.indicator)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    spacing: control.Suru.SpacingLarge
    padding: control.Suru.PaddingMedium

    opacity: enabled ? 1.0 : 0.3

    delegate: ItemDelegate {
        width: control.popup.width
        text: control.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
        highlighted: control.highlightedIndex === index
        hoverEnabled: control.hoverEnabled
    }

    indicator: Image {
        x: control.mirrored ? control.leftPadding : control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight - height) / 2

        width: control.Suru.units.gu(2)
        height: control.Suru.units.gu(2)

        source: "image://suru/down/" + control.Suru.iconColor
        sourceSize.width: width
        sourceSize.height: height
    }

    contentItem: Label {
        leftPadding: control.mirrored && control.indicator ? control.indicator.width + control.spacing : 0
        rightPadding: !control.mirrored && control.indicator ? control.indicator.width + control.spacing : 0

        text: control.displayText
        font: control.font
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight

        color: control.Suru.primaryTextColor
    }

    background: Rectangle {
        implicitWidth: control.Suru.units.gu(20)
        implicitHeight: control.Suru.units.gu(4)

        radius: control.Suru.units.RadiusMedium

        border.width: control.flat ? 0 : control.Suru.units.dp(1)

        border.color: control.pressed || popup.visible
                      ? control.Suru.accentColor
                      : control.Suru.dividerColor

        color: control.pressed || popup.visible
               ? control.Suru.baseColor
               : control.hovered ? control.Suru.foregroundColor : control.Suru.backgroundColor

        visible: !control.flat || control.pressed || control.hovered || control.visualFocus
    }

    popup: T.Popup {
        width: control.width
        implicitHeight: Math.min(control.Suru.units.gu(50), contentItem.implicitHeight)
        topMargin: control.Suru.units.SpacingMedium
        bottomMargin: control.Suru.units.SpacingMedium

        Suru.theme: control.Suru.theme
        Suru.accent: control.Suru.accent

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex
            highlightRangeMode: ListView.ApplyRange
            highlightMoveDuration: 0

            T.ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            color: control.Suru.foregroundColor
            border.color: control.Suru.dividerColor
            border.width: control.Suru.units.dp(1)
            radius: control.Suru.units.RadiusMedium
        }
    }
}
