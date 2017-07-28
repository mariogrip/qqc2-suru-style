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
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

T.Slider {
    id: control

    readonly property bool horizontal: control.orientation === Qt.Horizontal

    implicitWidth: horizontal ? control.Suru.units.gu(38) : control.Suru.units.gu(5)
    implicitHeight: horizontal ? control.Suru.units.gu(5) : control.Suru.units.gu(38)

    padding: control.Suru.units.PaddingMedium
    opacity: control.enabled ? 1.0 : 0.3

    property bool useSystemFocusVisuals: true

    handle: Rectangle {
        implicitHeight: control.Suru.units.gu(2)
        implicitWidth: control.Suru.units.gu(2)

        readonly property bool horizontal: control.orientation === Qt.Horizontal

        x: control.leftPadding + (horizontal ? control.visualPosition * (control.availableWidth - width) : (control.availableWidth - width) / 2)
        y: control.topPadding + (horizontal ? (control.availableHeight - height) / 2 : control.visualPosition * (control.availableHeight - height))

        border.width: control.Suru.units.dp(1)
        border.color: control.Suru.dividerColor
        radius: control.Suru.units.RadiusMedium
        color: control.pressed
               ? control.Suru.baseColor
               : control.hovered ? control.Suru.foregroundColor : control.Suru.backgroundColor
        opacity: control.enabled ? 1.0 : 0.3
    }

    background: Item {
        implicitWidth: horizontal ? control.Suru.units.gu(25) : control.Suru.units.gu(2)
        implicitHeight: horizontal ? control.Suru.units.gu(2) : control.Suru.units.gu(25)

        readonly property bool horizontal: control.orientation === Qt.Horizontal

        x: control.leftPadding + (horizontal ? 0 : (control.availableWidth - width) / 2)
        y: control.topPadding + (horizontal ? (control.availableHeight - height) / 2 : 0)
        width: horizontal ? control.availableWidth : implicitWidth
        height: horizontal ? implicitHeight : control.availableHeight

        scale: horizontal && control.mirrored ? -1 : 1

        Rectangle {
            x: parent.horizontal ? 0 : (parent.width - width) / 2
            y: parent.horizontal ? (parent.height - height) / 2 : 0
            width: parent.horizontal ? parent.width : 2
            height: !parent.horizontal ? parent.height : 2

            color: control.Suru.baseColor
        }

        Rectangle {
            x: parent.horizontal ? 0 : (parent.width - width) / 2
            y: parent.horizontal ? (parent.height - height) / 2 : control.visualPosition * parent.height
            width: parent.horizontal ? control.position * parent.width : 2
            height: !parent.horizontal ? control.position * parent.height : 2

            color: control.Suru.accentColor
        }
    }
}
