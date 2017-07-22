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

.pragma library

// Functions content is from QtQuick Controls 2.

function calculate_implicit_width(control) {
    return Math.max(control.background ? control.background.implicitWidth : 0,
        control.contentItem.implicitWidth + control.leftPadding + control.rightPadding)
}

function calculate_implicit_width_2(control, thirdControl) {
    return Math.max(control.background ? control.background.implicitWidth : 0,
                   Math.max(control.contentItem.implicitWidth, thirdControl ? thirdControl.implicitWidth : 0) + control.topPadding + control.bottomPadding)
}

function calculate_implicit_width_3(control) {
    return Math.max(control.background ? control.background.implicitWidth : 0,
                                 Math.max(control.contentWidth,
                                          control.header && control.header.visible ? control.header.implicitWidth : 0,
                                          control.footer && control.footer.visible ? control.footer.implicitWidth : 0) + control.leftPadding + control.rightPadding)
}

function calculate_implicit_height(control) {
    return Math.max(control.background ? control.background.implicitHeight : 0,
        control.contentItem.implicitHeight + control.topPadding + control.bottomPadding)
}

function calculate_implicit_height_2(control, thirdControl) {
    return Math.max(control.background ? control.background.implicitHeight : 0,
                   Math.max(control.contentItem.implicitHeight, thirdControl ? thirdControl.implicitHeight : 0) + control.topPadding + control.bottomPadding)
}

function calculate_implicit_height_3(control) {
    return Math.max(control.background ? control.background.implicitHeight : 0,
                                 control.contentHeight + control.topPadding + control.bottomPadding
                                 + (control.header && control.header.visible ? control.header.implicitHeight + control.spacing : 0)
                                 + (control.footer && control.footer.visible ? control.footer.implicitHeight + control.spacing : 0))

}
