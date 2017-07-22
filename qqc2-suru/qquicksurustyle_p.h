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

#ifndef QQUICKSURUSTYLE_P_H
#define QQUICKSURUSTYLE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/qcolor.h>
#include <QtQuickControls2/private/qquickstyleattached_p.h>

QT_BEGIN_NAMESPACE

class QQuickSuruStylePrivate;
class QQuickSuruUnits;
class QQuickSuruAnimation;

class QQuickSuruStyle : public QQuickStyleAttached
{
    Q_OBJECT
    Q_PROPERTY(Theme theme READ theme WRITE setTheme RESET resetTheme NOTIFY themeChanged FINAL)
    Q_PROPERTY(QVariant accent READ accent WRITE setAccent RESET resetAccent NOTIFY accentChanged FINAL)
    Q_PROPERTY(QVariant positive READ positive WRITE setPositive RESET resetPositive NOTIFY positiveChanged FINAL)
    Q_PROPERTY(QVariant negative READ negative WRITE setNegative RESET resetNegative NOTIFY negativeChanged FINAL)
    Q_PROPERTY(QVariant background READ background WRITE setBackground RESET resetBackground NOTIFY backgroundChanged FINAL)
    Q_PROPERTY(QVariant foreground READ foreground WRITE setForeground RESET resetForeground NOTIFY foregroundChanged FINAL)
    Q_PROPERTY(QVariant base READ base WRITE setBase RESET resetBase NOTIFY baseChanged FINAL)


    Q_PROPERTY(QColor accentColor READ accentColor NOTIFY accentChanged FINAL) // TODO: remove?
    Q_PROPERTY(QColor positiveColor READ positiveColor NOTIFY positiveChanged FINAL) // TODO: remove?
    Q_PROPERTY(QColor negativeColor READ negativeColor NOTIFY negativeChanged FINAL) // TODO: remove?
    Q_PROPERTY(QColor backgroundColor READ backgroundColor NOTIFY backgroundChanged FINAL)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor NOTIFY foregroundChanged FINAL)
    Q_PROPERTY(QColor baseColor READ baseColor NOTIFY baseChanged FINAL)

    Q_PROPERTY(QColor primaryTextColor READ primaryTextColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor primaryHighlightedTextColor READ primaryHighlightedTextColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor secondaryTextColor READ secondaryTextColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor hintTextColor READ hintTextColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor textSelectionColor READ textSelectionColor NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor dropShadowColor READ dropShadowColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor dividerColor READ dividerColor NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor iconColor READ iconColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor iconDisabledColor READ iconDisabledColor NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor buttonColor READ buttonColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor buttonDisabledColor READ buttonDisabledColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor highlightedButtonColor READ highlightedButtonColor NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor frameColor READ frameColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor rippleColor READ rippleColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor highlightedRippleColor READ highlightedRippleColor NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor scrollBarColor READ scrollBarColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor scrollBarHoveredColor READ scrollBarHoveredColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor scrollBarPressedColor READ scrollBarPressedColor NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor dialogColor READ dialogColor NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor overlayColor READ overlayColor NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QColor listHighlightColor READ listHighlightColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor tooltipColor READ tooltipColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor toolBarColor READ toolBarColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor toolTextColor READ toolTextColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor spinBoxDisabledIconColor READ spinBoxDisabledIconColor NOTIFY paletteChanged FINAL)

    Q_PROPERTY(QQuickSuruUnits* units READ units CONSTANT)
    Q_PROPERTY(QQuickSuruAnimation* animation READ animation CONSTANT)

public:
    enum Theme { Light, Dark, System };
    Q_ENUM(Theme)

    enum Color {
        White, Porcelain, Silk, Ash,
        Jet, Inkstone, Slate, Graphite,
        Blue, Green, Yellow, Orange, Red, Purple
    };
    Q_ENUM(Color)

    explicit QQuickSuruStyle(QObject *parent = nullptr);

    static QQuickSuruStyle *qmlAttachedProperties(QObject *object);

    Theme theme() const;
    void setTheme(Theme theme);
    void inheritTheme(Theme theme);
    void propagateTheme();
    void resetTheme();

    QVariant accent() const;
    void setAccent(const QVariant &accent);
    void inheritAccent(QRgb accent, bool custom);
    void propagateAccent();
    void resetAccent();

    QVariant positive() const;
    void setPositive(const QVariant &positive);
    void inheritPositive(QRgb positive, bool custom);
    void propagatePositive();
    void resetPositive();

    QVariant negative() const;
    void setNegative(const QVariant &negative);
    void inheritNegative(QRgb negative, bool custom);
    void propagateNegative();
    void resetNegative();

    QVariant foreground() const;
    void setForeground(const QVariant &foreground);
    void inheritForeground(QRgb foreground, bool custom, bool has);
    void propagateForeground();
    void resetForeground();

    QVariant background() const;
    void setBackground(const QVariant &background);
    void inheritBackground(QRgb background, bool custom, bool has);
    void propagateBackground();
    void resetBackground();

    QVariant base() const;
    void setBase(const QVariant &base);
    void inheritBase(QRgb base, bool custom, bool has);
    void propagateBase();
    void resetBase();

    QColor accentColor() const;
    QColor positiveColor() const;
    QColor negativeColor() const;
    QColor backgroundColor() const;
    QColor foregroundColor() const;
    QColor baseColor() const;
    QColor primaryTextColor() const;
    QColor primaryHighlightedTextColor() const;
    QColor secondaryTextColor() const;
    QColor hintTextColor() const;
    QColor textSelectionColor() const;
    QColor dropShadowColor() const;
    QColor dividerColor() const;
    QColor iconColor() const;
    QColor iconDisabledColor() const;
    QColor buttonColor(bool isFlat = false) const;
    QColor buttonDisabledColor(bool isFlat = false) const;
    QColor highlightedButtonColor(bool isFlat = false) const;
    QColor highlightedButtonDisabledColor(bool isFlat = false) const;
    QColor frameColor() const;
    QColor rippleColor() const;
    QColor highlightedRippleColor() const;
    QColor scrollBarColor() const;
    QColor scrollBarHoveredColor() const;
    QColor scrollBarPressedColor() const;
    QColor dialogColor() const;
    QColor overlayColor() const;
    QColor listHighlightColor() const;
    QColor tooltipColor() const;
    QColor toolBarColor() const;
    QColor toolTextColor() const;
    QColor spinBoxDisabledIconColor() const;

    QQuickSuruUnits* units() const { return m_units; }
    QQuickSuruAnimation* animation() const { return m_animation; }

    Q_INVOKABLE QColor color(Color color) const;

Q_SIGNALS:
    void themeChanged();
    void accentChanged();
    void positiveChanged();
    void negativeChanged();
    void foregroundChanged();
    void backgroundChanged();
    void baseChanged();

    void paletteChanged();

protected:
    void parentStyleChange(QQuickStyleAttached *newParent, QQuickStyleAttached *oldParent) override;

private:
    void init();
    bool variantToRgba(const QVariant &var, const char *name, QRgb *rgba, bool *custom) const;

    // These reflect whether a color value was explicitly set on the specific
    // item that this attached style object represents.
    bool m_explicitTheme;
    bool m_explicitAccent;
    bool m_explicitPositive;
    bool m_explicitNegative;
    bool m_explicitForeground;
    bool m_explicitBackground;
    bool m_explicitBase;
    // These reflect whether the color value that was either inherited or
    // explicitly set is in the form that QColor expects, rather than one of
    // our pre-defined color enum values.
    bool m_customAccent;
    bool m_customPositive;
    bool m_customNegative;
    bool m_customForeground;
    bool m_customBackground;
    bool m_customBase;
    // These will be true when this item has an explicit or inherited foreground/background
    // color, or these colors were declared globally via settings (e.g. conf or env vars).
    // Some color properties of the style will return different values depending on whether
    // or not these are set.
    bool m_hasForeground;
    bool m_hasBackground;
    bool m_hasBase;
    // The actual values for this item, whether explicit, inherited or globally set.
    QQuickSuruStyle::Theme m_theme;
    QRgb m_accent;
    QRgb m_positive;
    QRgb m_negative;
    QRgb m_foreground;
    QRgb m_background;
    QRgb m_base;

    QQuickSuruUnits* m_units;
    QQuickSuruAnimation* m_animation;
};

QT_END_NAMESPACE

QML_DECLARE_TYPEINFO(QQuickSuruStyle, QML_HAS_ATTACHED_PROPERTIES)

#endif // QQUICKSURUSTYLE_P_H
