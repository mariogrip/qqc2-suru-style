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

#include "qquicksurustyle_p.h"
#include "qquicksuruunits.h"
#include "qquicksuruanimation_p.h"

#include <QtCore/qdebug.h>
#include <QtCore/qsettings.h>
#include <QtQml/qqmlinfo.h>
#include <QtQuickControls2/private/qquickstyleattached_p.h>

QT_BEGIN_NAMESPACE

static QRgb qquicksuru_color(QQuickSuruStyle::Color colorRole)
{  
    static const QRgb colors[] = {
        0xFFFFFFFF, // White
        0xFFF7F7F7, // Porcelain
        0xFFCDCDCD, // Silk
        0xFF888888, // Ash

        0xFF111111, // Jet
        0xFF3B3B3B, // Inkstone
        0xFF5D5D5D, // Slate
        0xFF666666, // Graphite

        0xFF19B6EE, // Blue
        0xFF3EB34F, // Green
        0xFFEF9928, // Yellow
        0xFFE95420, // Orange
        0xFFED3146, // Red
        0xFF762572  // Purple
    };
    return colors[colorRole];
}

// If no value was inherited from a parent or explicitly set, the "global" values are used.
// The initial, default values of the globals are hard-coded here, but the environment
// variables and .conf file override them if specified.
static QQuickSuruStyle::Theme GlobalTheme = QQuickSuruStyle::Light;
static QRgb GlobalAccent = qquicksuru_color(QQuickSuruStyle::Blue);
static QRgb GlobalPositive = qquicksuru_color(QQuickSuruStyle::Green);
static QRgb GlobalNegative = qquicksuru_color(QQuickSuruStyle::Red);
static QRgb GlobalForeground = qquicksuru_color(QQuickSuruStyle::Porcelain);
static QRgb GlobalBackground = qquicksuru_color(QQuickSuruStyle::White);
static QRgb GlobalBase = qquicksuru_color(QQuickSuruStyle::Silk);
// These represent whether a global foreground/background was set.
// Each style's m_hasForeground/m_hasBackground are initialized to these values.
static bool HasGlobalForeground = false;
static bool HasGlobalBackground = false;
static bool HasGlobalBase = false;
// These represent whether or not the global color value was specified as one of the
// values that QColor accepts, as opposed to one of the pre-defined colors like Red.
static bool GlobalAccentCustom = false;
static bool GlobalPositiveCustom = false;
static bool GlobalNegativeCustom = false;
static bool GlobalForegroundCustom = false;
static bool GlobalBackgroundCustom = true;
static bool GlobalBaseCustom = false;

static const QRgb backgroundColorLight = qquicksuru_color(QQuickSuruStyle::White);
static const QRgb backgroundColorDark = qquicksuru_color(QQuickSuruStyle::Jet);

static const QRgb foregroundColorLight = qquicksuru_color(QQuickSuruStyle::Porcelain);
static const QRgb foregroundColorDark = qquicksuru_color(QQuickSuruStyle::Inkstone);

static const QRgb baseColorLight = qquicksuru_color(QQuickSuruStyle::Silk);
static const QRgb baseColorDark = qquicksuru_color(QQuickSuruStyle::Graphite);

static const QRgb primaryTextColorLight = qquicksuru_color(QQuickSuruStyle::Jet);
static const QRgb primaryTextColorDark = qquicksuru_color(QQuickSuruStyle::White);

static const QRgb secondaryTextColorLight = qquicksuru_color(QQuickSuruStyle::Inkstone);
static const QRgb secondaryTextColorDark = qquicksuru_color(QQuickSuruStyle::Silk);

static const QRgb hintTextColorLight = qquicksuru_color(QQuickSuruStyle::Graphite);
static const QRgb hintTextColorDark = qquicksuru_color(QQuickSuruStyle::Ash);

static const QRgb dividerColorLight = qquicksuru_color(QQuickSuruStyle::Silk);
static const QRgb dividerColorDark = qquicksuru_color(QQuickSuruStyle::Graphite);

static const QRgb iconColorLight = qquicksuru_color(QQuickSuruStyle::Ash);
static const QRgb iconColorDark = qquicksuru_color(QQuickSuruStyle::Graphite);

static const QRgb dialogColorLight = qquicksuru_color(QQuickSuruStyle::White);
static const QRgb dialogColorDark = qquicksuru_color(QQuickSuruStyle::Jet);

static const QRgb iconDisabledColorLight = 0x42000000;
static const QRgb iconDisabledColorDark = 0x4CFFFFFF;

static const QRgb raisedButtonColorLight = 0xFFD6D7D7;
static const QRgb raisedButtonColorDark = 0x3FCCCCCC;

static const QRgb raisedButtonDisabledColorLight = dividerColorLight;
static const QRgb raisedButtonDisabledColorDark = dividerColorDark;

static const QRgb frameColorLight = hintTextColorLight;
static const QRgb frameColorDark = hintTextColorDark;

static const QRgb rippleColorLight = 0x10000000;
static const QRgb rippleColorDark = 0x20FFFFFF;

static const QRgb spinBoxDisabledIconColorLight = 0xFFCCCCCC;
static const QRgb spinBoxDisabledIconColorDark = 0xFF666666;

extern bool qt_is_dark_system_theme();

static QQuickSuruStyle::Theme qquicksuru_effective_theme(QQuickSuruStyle::Theme theme)
{
    if (theme == QQuickSuruStyle::System)
        theme = qt_is_dark_system_theme() ? QQuickSuruStyle::Dark : QQuickSuruStyle::Light;
    return theme;
}

QQuickSuruStyle::QQuickSuruStyle(QObject *parent) : QQuickStyleAttached(parent),
    m_explicitTheme(false),
    m_explicitAccent(false),
    m_explicitPositive(false),
    m_explicitNegative(false),
    m_explicitForeground(false),
    m_explicitBackground(false),
    m_explicitBase(false),

    m_customAccent(GlobalAccentCustom),
    m_customPositive(GlobalPositiveCustom),
    m_customNegative(GlobalNegativeCustom),
    m_customForeground(GlobalForegroundCustom),
    m_customBackground(GlobalBackgroundCustom),
    m_customBase(GlobalBaseCustom),

    m_hasForeground(HasGlobalForeground),
    m_hasBackground(HasGlobalBackground),
    m_hasBase(HasGlobalBase),

    m_theme(GlobalTheme),
    m_accent(GlobalAccent),
    m_positive(GlobalPositive),
    m_negative(GlobalNegative),
    m_foreground(GlobalForeground),
    m_background(GlobalBackground),
    m_base(GlobalBase),

    m_units(new QQuickSuruUnits()),
    m_animation(new QQuickSuruAnimation())
{
    init();
}

QQuickSuruStyle *QQuickSuruStyle::qmlAttachedProperties(QObject *object)
{
    return new QQuickSuruStyle(object);
}

QQuickSuruStyle::Theme QQuickSuruStyle::theme() const
{
    return m_theme;
}

void QQuickSuruStyle::setTheme(Theme theme)
{
    if (theme == System)
        theme = qt_is_dark_system_theme() ? Dark : Light;

    m_explicitTheme = true;
    if (m_theme == theme)
        return;

    m_theme = theme;
    propagateTheme();
    emit themeChanged();
    emit paletteChanged();
    if (!m_customAccent)
        emit accentChanged();
    if (!m_customPositive)
        emit positiveChanged();
    if (!m_customNegative)
        emit negativeChanged();
    if (!m_hasBackground)
        emit backgroundChanged();
    if (!m_hasForeground)
        emit foregroundChanged();
    if (!m_hasBase)
        emit baseChanged();
}

void QQuickSuruStyle::inheritTheme(Theme theme)
{
    if (m_explicitTheme || m_theme == theme)
        return;

    m_theme = theme;
    propagateTheme();
    emit themeChanged();
    emit paletteChanged();
    if (!m_customAccent)
        emit accentChanged();
    if (!m_customPositive)
        emit positiveChanged();
    if (!m_customNegative)
        emit negativeChanged();
    if (!m_hasBackground)
        emit backgroundChanged();
    if (!m_hasForeground)
        emit foregroundChanged();
    if (!m_hasBase)
        emit baseChanged();
}

void QQuickSuruStyle::propagateTheme()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritTheme(m_theme);
    }
}

void QQuickSuruStyle::resetTheme()
{
    if (!m_explicitTheme)
        return;

    m_explicitTheme = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    inheritTheme(suru ? suru->theme() : GlobalTheme);
}

QVariant QQuickSuruStyle::accent() const
{
    return QColor::fromRgba(m_accent);
}

void QQuickSuruStyle::setAccent(const QVariant &var)
{
    QRgb accent = 0;
    bool custom = false;
    if (!variantToRgba(var, "accent", &accent, &custom))
        return;

    m_explicitAccent = true;
    if (m_accent == accent)
        return;

    m_customAccent = custom;
    m_accent = accent;
    propagateAccent();
    emit accentChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritAccent(QRgb accent, bool custom)
{
    if (m_explicitAccent || m_accent == accent)
        return;

    m_customAccent = custom;
    m_accent = accent;
    propagateAccent();
    emit accentChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateAccent()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritAccent(m_accent, m_customAccent);
    }
}

void QQuickSuruStyle::resetAccent()
{
    if (!m_explicitAccent)
        return;

    m_customAccent = false;
    m_explicitAccent = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritAccent(suru->m_accent, suru->m_customAccent);
    else
        inheritAccent(GlobalAccent, false);
}

QVariant QQuickSuruStyle::positive() const
{
    return QColor::fromRgba(m_positive);
}

void QQuickSuruStyle::setPositive(const QVariant &var)
{
    QRgb positive = 0;
    bool custom = false;
    if (!variantToRgba(var, "positive", &positive, &custom))
        return;

    m_explicitPositive = true;
    if (m_positive == positive)
        return;

    m_customPositive = custom;
    m_positive = positive;
    propagatePositive();
    emit positiveChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritPositive(QRgb positive, bool custom)
{
    if (m_explicitPositive || m_positive == positive)
        return;

    m_customPositive = custom;
    m_positive = positive;
    propagatePositive();
    emit positiveChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagatePositive()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritPositive(m_positive, m_customPositive);
    }
}

void QQuickSuruStyle::resetPositive()
{
    if (!m_explicitPositive)
        return;

    m_explicitPositive = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritPositive(suru->m_positive, suru->m_customPositive);
    else
        inheritPositive(GlobalPositive, false);
}

QVariant QQuickSuruStyle::negative() const
{
    return QColor::fromRgba(m_negative);
}

void QQuickSuruStyle::setNegative(const QVariant &var)
{
    QRgb negative = 0;
    bool custom = false;
    if (!variantToRgba(var, "negative", &negative, &custom))
        return;

    m_explicitNegative = true;
    if (m_negative == negative)
        return;

    m_customNegative = custom;
    m_negative = negative;
    propagateNegative();
    emit negativeChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritNegative(QRgb negative, bool custom)
{
    if (m_explicitNegative || m_negative == negative)
        return;

    m_customNegative = custom;
    m_negative = negative;
    propagateNegative();
    emit negativeChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateNegative()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritNegative(m_negative, m_customNegative);
    }
}

void QQuickSuruStyle::resetNegative()
{
    if (!m_explicitNegative)
        return;

    m_explicitNegative = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    if (suru)
        inheritNegative(suru->m_negative, suru->m_customNegative);
    else
        inheritNegative(GlobalNegative, false);
}

QVariant QQuickSuruStyle::foreground() const
{
    if (!m_hasForeground)
        return QColor::fromRgba(m_theme == Light ? foregroundColorLight : foregroundColorDark);

    //if (m_customForeground)
        return QColor::fromRgba(m_foreground);

    //return QColor();
}

void QQuickSuruStyle::setForeground(const QVariant &var)
{
    QRgb foreground = 0;
    bool custom = false;
    if (!variantToRgba(var, "foreground", &foreground, &custom))
        return;

    m_hasForeground = true;
    m_explicitForeground = true;
    if (m_foreground == foreground)
        return;

    m_customForeground = custom;
    m_foreground = foreground;
    propagateForeground();
    emit foregroundChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritForeground(QRgb foreground, bool custom, bool has)
{
    if (m_explicitForeground || m_foreground == foreground)
        return;

    m_hasForeground = has;
    m_customForeground = custom;
    m_foreground = foreground;
    propagateForeground();
    emit foregroundChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateForeground()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritForeground(m_foreground, m_customForeground, m_hasForeground);
    }
}

void QQuickSuruStyle::resetForeground()
{
    if (!m_explicitForeground)
        return;

    m_hasForeground = false;
    m_customForeground = false;
    m_explicitForeground = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    inheritForeground(suru ? suru->m_foreground : GlobalForeground, true, suru ? suru->m_hasForeground : false);
}

QVariant QQuickSuruStyle::background() const
{
    if (!m_hasBackground)
        return QColor::fromRgba(m_theme == Light ? backgroundColorLight : backgroundColorDark);

    //if (m_customBackground)
        return QColor::fromRgba(m_background);

    //return QColor();
}

void QQuickSuruStyle::setBackground(const QVariant &var)
{
    QRgb background = 0;
    bool custom = false;
    if (!variantToRgba(var, "background", &background, &custom))
        return;

    m_hasBackground = true;
    m_explicitBackground = true;
    if (m_background == background)
        return;

    m_customBackground = custom;
    m_background = background;
    propagateBackground();
    emit backgroundChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritBackground(QRgb background, bool custom, bool has)
{
    if (m_explicitBackground || m_background == background)
        return;

    m_hasBackground = has;
    m_customBackground = custom;
    m_background = background;
    propagateBackground();
    emit backgroundChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateBackground()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritBackground(m_background, m_customBackground, m_hasBackground);
    }
}

void QQuickSuruStyle::resetBackground()
{
    if (!m_explicitBackground)
        return;

    m_hasBackground = false;
    m_customBackground = false;
    m_explicitBackground = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    inheritBackground(suru ? suru->m_background : GlobalBackground, true, suru ? suru->m_hasBackground : false);
}

QVariant QQuickSuruStyle::base() const
{
    if (!m_hasBase)
        return QColor::fromRgba(m_theme == Light ? baseColorLight : baseColorDark);

    //if (m_customBase)
        return QColor::fromRgba(m_base);

    //return QColor();
}

void QQuickSuruStyle::setBase(const QVariant &var)
{
    QRgb base = 0;
    bool custom = false;
    if (!variantToRgba(var, "base", &base, &custom))
        return;

    m_hasBase = true;
    m_explicitBase = true;
    if (m_base == base)
        return;

    m_customBase = custom;
    m_base = base;
    propagateBase();
    emit baseChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::inheritBase(QRgb base, bool custom, bool has)
{
    if (m_explicitBase || m_base == base)
        return;

    m_hasBase = has;
    m_customBase = custom;
    m_base = base;
    propagateBase();
    emit baseChanged();
    emit paletteChanged();
}

void QQuickSuruStyle::propagateBase()
{
    const auto styles = childStyles();
    for (QQuickStyleAttached *child : styles) {
        QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(child);
        if (suru)
            suru->inheritBase(m_base, m_customBase, m_hasBase);
    }
}

void QQuickSuruStyle::resetBase()
{
    if (!m_explicitBase)
        return;

    m_hasBase = false;
    m_customBase = false;
    m_explicitBase = false;
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(parentStyle());
    inheritBackground(suru ? suru->m_base : GlobalBase, true, suru ? suru->m_hasBase : false);
}

QColor QQuickSuruStyle::color(Color color) const
{
    return qquicksuru_color(color);
}

QColor QQuickSuruStyle::accentColor() const
{
    return QColor::fromRgba(m_accent);
}

QColor QQuickSuruStyle::positiveColor() const
{
    return QColor::fromRgba(m_positive);
}

QColor QQuickSuruStyle::negativeColor() const
{
    return QColor::fromRgba(m_negative);
}

QColor QQuickSuruStyle::backgroundColor() const
{
    if (!m_hasBackground)
        return QColor::fromRgba(m_theme == Light ? backgroundColorLight : backgroundColorDark);

    if (m_customBackground)
        return QColor::fromRgba(m_background);

    Q_UNREACHABLE();
    return QColor();
}

QColor QQuickSuruStyle::foregroundColor() const
{
    if (!m_hasForeground)
        return QColor::fromRgba(m_theme == Light ? foregroundColorLight : foregroundColorDark);

    if (m_customForeground)
        return QColor::fromRgba(m_foreground);

    Q_UNREACHABLE();
    return QColor();
}

QColor QQuickSuruStyle::baseColor() const
{
    if (!m_hasBase)
        return QColor::fromRgba(m_theme == Light ? baseColorLight : baseColorDark);

    if (m_customBase)
        return QColor::fromRgba(m_base);

    Q_UNREACHABLE();
    return QColor();
}

QColor QQuickSuruStyle::primaryTextColor() const
{
    return QColor::fromRgba(m_theme == Light ? primaryTextColorLight : primaryTextColorDark);
}

QColor QQuickSuruStyle::primaryHighlightedTextColor() const
{
    if (m_explicitForeground)
        return primaryTextColor();
    return QColor::fromRgba(primaryTextColorDark);
}

QColor QQuickSuruStyle::secondaryTextColor() const
{
    return QColor::fromRgba(m_theme == Light ? secondaryTextColorLight : secondaryTextColorDark);
}

QColor QQuickSuruStyle::hintTextColor() const
{
    return QColor::fromRgba(m_theme == Light ? hintTextColorLight : hintTextColorDark);
}

QColor QQuickSuruStyle::textSelectionColor() const
{
    QColor color = accentColor();
    color.setAlphaF(0.2);
    return color;
}

QColor QQuickSuruStyle::dropShadowColor() const
{
    // TODO: Check this value (comes from Material)
    return QColor::fromRgba(0x40000000);
}

QColor QQuickSuruStyle::dividerColor() const
{
    return QColor::fromRgba(m_theme == Light ? dividerColorLight : dividerColorDark);
}

QColor QQuickSuruStyle::iconColor() const
{
    return QColor::fromRgba(m_theme == Light ? iconColorLight : iconColorDark);
}

QColor QQuickSuruStyle::iconDisabledColor() const
{
    return QColor::fromRgba(m_theme == Light ? iconDisabledColorLight : iconDisabledColorDark);
}

QColor QQuickSuruStyle::buttonColor(bool isFlat) const
{
    QColor color = Qt::transparent;

    if (m_explicitBackground) {
        color = backgroundColor();
    } else if (!isFlat) {
        color = QColor::fromRgba(m_theme == Light ? raisedButtonColorLight
                                                  : raisedButtonColorDark);
    }

    return color;
}

QColor QQuickSuruStyle::buttonDisabledColor(bool isFlat) const
{
    if (!isFlat) {
        return QColor::fromRgba(m_theme == Light ? raisedButtonDisabledColorLight
                                                 : raisedButtonDisabledColorDark);
    } else {
        return Qt::transparent;
    }
}

QColor QQuickSuruStyle::highlightedButtonColor(bool isFlat) const
{
    Q_UNUSED(isFlat)

    QColor color = Qt::transparent;

    if (m_explicitBackground) {
        color = backgroundColor();
    } else {
        color = accentColor();
    }

    return color;
}

QColor QQuickSuruStyle::frameColor() const
{
    return QColor::fromRgba(m_theme == Light ? frameColorLight : frameColorDark);
}

QColor QQuickSuruStyle::rippleColor() const
{
    return QColor::fromRgba(m_theme == Light ? rippleColorLight : rippleColorDark);
}

QColor QQuickSuruStyle::highlightedRippleColor() const
{
    QColor pressColor = accentColor();
    pressColor.setAlpha(m_theme == Light ? 30 : 50);
    return pressColor;
}

QColor QQuickSuruStyle::scrollBarColor() const
{
    return m_theme == Light ? qquicksuru_color(QQuickSuruStyle::Slate) : qquicksuru_color(QQuickSuruStyle::Silk);
}

QColor QQuickSuruStyle::scrollBarHoveredColor() const
{
    return m_theme == Light ? qquicksuru_color(QQuickSuruStyle::Inkstone) : qquicksuru_color(QQuickSuruStyle::Porcelain);
}

QColor QQuickSuruStyle::scrollBarPressedColor() const
{
    return m_theme == Light ? qquicksuru_color(QQuickSuruStyle::Jet) : qquicksuru_color(QQuickSuruStyle::White);
}

QColor QQuickSuruStyle::dialogColor() const
{
    if (m_hasBackground)
        return backgroundColor();

    return QColor::fromRgba(m_theme == Light ? dialogColorLight : dialogColorDark);
}

QColor QQuickSuruStyle::overlayColor() const
{
    QColor color = qquicksuru_color(QQuickSuruStyle::Jet);
    color.setAlphaF(0.6);

    return color;
}

QColor QQuickSuruStyle::listHighlightColor() const
{
    return foregroundColor();
}

QColor QQuickSuruStyle::tooltipColor() const
{
    if (m_explicitBackground)
        return backgroundColor();

    return m_theme == Light ? qquicksuru_color(QQuickSuruStyle::Jet) : qquicksuru_color(QQuickSuruStyle::White);
}

QColor QQuickSuruStyle::toolBarColor() const
{
    if (m_explicitBackground)
        return backgroundColor();

    // TODO: FIXME: We'd need to support three different Suru styles for toolbar.
    // 1) Toolbar bg color = bg color
    // 2) Toolbar bg color = white && bg color = darker white
    // 3) Toolbar bg color = accent color
    return backgroundColor();
}

QColor QQuickSuruStyle::toolTextColor() const
{
    if (toolBarColor().lightnessF() < 0.5)  // is dark background
        return iconColorDark;   // dark palette
    else
        return iconColorLight;  // light palette
}

QColor QQuickSuruStyle::spinBoxDisabledIconColor() const
{
    return QColor::fromRgba(m_theme == Light ? spinBoxDisabledIconColorLight : spinBoxDisabledIconColorDark);
}

void QQuickSuruStyle::parentStyleChange(QQuickStyleAttached *newParent, QQuickStyleAttached *oldParent)
{
    Q_UNUSED(oldParent);
    QQuickSuruStyle *suru = qobject_cast<QQuickSuruStyle *>(newParent);
    if (suru) {
        inheritTheme(suru->theme());
        inheritAccent(suru->m_accent, suru->m_customAccent);
        inheritPositive(suru->m_positive, suru->m_customPositive);
        inheritNegative(suru->m_negative, suru->m_customNegative);
        inheritForeground(suru->m_foreground, suru->m_customForeground, suru->m_hasForeground);
        inheritBackground(suru->m_background, suru->m_customBackground, suru->m_hasBackground);
        inheritBase(suru->m_base, suru->m_customBase, suru->m_hasBase);
    }
}

template <typename Enum>
static Enum toEnumValue(const QByteArray &value, bool *ok)
{
    QMetaEnum enumeration = QMetaEnum::fromType<Enum>();
    return static_cast<Enum>(enumeration.keyToValue(value, ok));
}

static QByteArray resolveSetting(const QByteArray &env, const QSharedPointer<QSettings> &settings, const QString &name)
{
    QByteArray value = qgetenv(env);
    if (value.isNull() && !settings.isNull())
        value = settings->value(name).toByteArray();
    return value;
}

void QQuickSuruStyle::init()
{
    static bool globalsInitialized = false;
    if (!globalsInitialized) {
        QSharedPointer<QSettings> settings = QQuickStyleAttached::settings(QStringLiteral("Suru"));

        bool ok = false;
        QByteArray themeValue = resolveSetting("QT_QUICK_CONTROLS_SURU_THEME", settings, QStringLiteral("Theme"));
        Theme themeEnum = toEnumValue<Theme>(themeValue, &ok);
        if (ok)
            GlobalTheme = m_theme = qquicksuru_effective_theme(themeEnum);
        else if (!themeValue.isEmpty())
            qWarning().nospace().noquote() << "Suru: unknown theme value: " << themeValue;

        QByteArray accentValue = resolveSetting("QT_QUICK_CONTROLS_SURU_ACCENT", settings, QStringLiteral("Accent"));
        Color accentEnum = toEnumValue<Color>(accentValue, &ok);
        if (ok) {
            GlobalAccentCustom = m_customAccent = false;
            GlobalAccent = m_accent = qquicksuru_color(accentEnum);
        } else if (!accentValue.isEmpty()) {
            QColor color(accentValue.constData());
            if (color.isValid()) {
                GlobalAccentCustom = m_customAccent = false;
                GlobalAccent = m_accent = color.rgba();
            } else {
                qWarning().nospace().noquote() << "Suru: unknown accent value: " << accentValue;
            }
        }

        QByteArray positiveValue = resolveSetting("QT_QUICK_CONTROLS_SURU_POSITIVE", settings, QStringLiteral("Positive"));
        Color positiveEnum = toEnumValue<Color>(positiveValue, &ok);
        if (ok) {
            GlobalPositiveCustom = m_customPositive = false;
            GlobalPositive = m_positive = qquicksuru_color(positiveEnum);
        } else if (!positiveValue.isEmpty()) {
            QColor color(positiveValue.constData());
            if (color.isValid()) {
                GlobalPositiveCustom = m_customPositive = false;
                GlobalPositive = m_positive = color.rgba();
            } else {
                qWarning().nospace().noquote() << "Suru: unknown positive value: " << positiveValue;
            }
        }

        QByteArray negativeValue = resolveSetting("QT_QUICK_CONTROLS_SURU_NEGATIVE", settings, QStringLiteral("Negative"));
        Color negativeEnum = toEnumValue<Color>(negativeValue, &ok);
        if (ok) {
            GlobalNegativeCustom = m_customNegative = false;
            GlobalNegative = m_negative = qquicksuru_color(negativeEnum);
        } else if (!negativeValue.isEmpty()) {
            QColor color(negativeValue.constData());
            if (color.isValid()) {
                GlobalNegativeCustom = m_customNegative = false;
                GlobalNegative = m_negative = color.rgba();
            } else {
                qWarning().nospace().noquote() << "Suru: unknown negative value: " << negativeValue;
            }
        }

        QByteArray foregroundValue = resolveSetting("QT_QUICK_CONTROLS_SURU_FOREGROUND", settings, QStringLiteral("Foreground"));
        Color foregroundEnum = toEnumValue<Color>(foregroundValue, &ok);
        if (ok) {
            GlobalForegroundCustom = m_customForeground = false;
            GlobalForeground = m_foreground = qquicksuru_color(foregroundEnum);
            HasGlobalForeground = m_hasForeground = true;
        } else if (!foregroundValue.isEmpty()) {
            QColor color(foregroundValue.constData());
            if (color.isValid()) {
                GlobalForegroundCustom = m_customForeground = false;
                GlobalForeground = m_foreground = color.rgba();
                HasGlobalForeground = m_hasForeground = true;
            } else {
                qWarning().nospace().noquote() << "Suru: unknown foreground value: " << foregroundValue;
            }
        }

        QByteArray backgroundValue = resolveSetting("QT_QUICK_CONTROLS_SURU_BACKGROUND", settings, QStringLiteral("Background"));
        Color backgroundEnum = toEnumValue<Color>(backgroundValue, &ok);
        if (ok) {
            GlobalBackgroundCustom = m_customBackground = false;
            GlobalBackground = m_background = qquicksuru_color(backgroundEnum);
            HasGlobalBackground = m_hasBackground = true;
        } else if (!backgroundValue.isEmpty()) {
            QColor color(backgroundValue.constData());
            if (color.isValid()) {
                GlobalBackgroundCustom = m_customBackground = false;
                GlobalBackground = m_background = color.rgba();
                HasGlobalBackground = m_hasBackground = true;
            } else {
                qWarning().nospace().noquote() << "Suru: unknown background value: " << backgroundValue;
            }
        }

        QByteArray baseValue = resolveSetting("QT_QUICK_CONTROLS_SURU_BASE", settings, QStringLiteral("Base"));
        Color baseEnum = toEnumValue<Color>(baseValue, &ok);
        if (ok) {
            GlobalBaseCustom = m_customBase = false;
            GlobalBase = m_base = qquicksuru_color(baseEnum);
            HasGlobalBase = m_hasBase = true;
        } else if (!baseValue.isEmpty()) {
            QColor color(baseValue.constData());
            if (color.isValid()) {
                GlobalBaseCustom = m_customBase = false;
                GlobalBase = m_base = color.rgba();
                HasGlobalBase = m_hasBase = true;
            } else {
                qWarning().nospace().noquote() << "Suru: unknown base value: " << baseValue;
            }
        }

        globalsInitialized = true;
    }

    QQuickStyleAttached::init(); // TODO: lazy init?
}

bool QQuickSuruStyle::variantToRgba(const QVariant &var, const char *name, QRgb *rgba, bool *custom) const
{
    *custom = false;
    if (var.type() == QVariant::Int) {
        int val = var.toInt();
        if (val < White || val > Purple) {
            qmlInfo(parent()) << "unknown Suru." << name << " value: " << val;
            return false;
        }
        *rgba = qquicksuru_color(static_cast<Color>(val));
    } else {
        int val = QMetaEnum::fromType<Color>().keyToValue(var.toByteArray());
        if (val != -1) {
            *rgba = qquicksuru_color(static_cast<Color>(val));
        } else {
            QColor color(var.toString());
            if (!color.isValid()) {
                qmlInfo(parent()) << "unknown Suru." << name << " value: " << var.toString();
                return false;
            }
            *custom = true;
            *rgba = color.rgba();
        }
    }
    return true;
}

QT_END_NAMESPACE
