/*
 * Copyright 2013-2016 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QQUICKSURUANIMATION_P_H
#define QQUICKSURUANIMATION_P_H

#include <QtCore/QEasingCurve>
#include <QtCore/QObject>

class QQuickSuruAnimation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int SnapDuration READ SnapDuration CONSTANT)
    Q_PROPERTY(int FastDuration READ FastDuration CONSTANT)
    Q_PROPERTY(int BriskDuration READ BriskDuration CONSTANT)
    Q_PROPERTY(int SlowDuration READ SlowDuration CONSTANT)
    Q_PROPERTY(int SleepyDuration READ SleepyDuration CONSTANT)

    Q_PROPERTY(QEasingCurve StandardEasing READ StandardEasing CONSTANT)
    Q_PROPERTY(QEasingCurve StandardEasingReverse READ StandardEasingReverse CONSTANT)

public:
    int SnapDuration() const { return 100; }
    int FastDuration() const { return 165; }
    int BriskDuration() const { return 333; }
    int SlowDuration() const { return 500; }
    int SleepyDuration() const { return 1000; }

    const QEasingCurve& StandardEasing() const {
        return QEasingCurve::OutQuad;
    }

    const QEasingCurve& StandardEasingReverse() const {
        return QEasingCurve::InQuad;
    }
};

#endif // QQUICKSURUANIMATION_P_H
