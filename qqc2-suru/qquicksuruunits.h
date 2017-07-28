#ifndef QQUICKSURUUNITS_H
#define QQUICKSURUUNITS_H

#include <QObject>

// This file is just a temporary template for sizes.
// TODO: Is there any common pattern for sizes in the current UITK?
//       Should we implement any measure here? How?
// TODO: Should we change elements' sizes according to the attached
//       input devices (e.g. make controls bigger if touch)?

// TODO:
// Since Qt 5.6, we probably don't need to implement our custom logic
// for Hi-DPI devices. However this might require further refinements.
// e.g. Ubuntu UITK grid unit for Nexus 4 was 18px.
//      Within this new logic, that value is now 16px.
//
// We may want to add a correction factor which takes in account the
// different type of device.

// FIXME: Check if we need to do something if Qt::AA_EnableHighDpiScaling flag is
// not set
// TODO: Should this be dependant on the font size, CSS-like
#define GRID_UNIT_PX 8.0
#define UNITS_BASE_SIZE QQuickSuruUnits::gu(1)


/*** BREAKPOINTS ***/
// from http://design.italia.it/linee-guida/layout/griglie/
// FIXME: That's a reference to an Italian website
#define BREAKPOINT_LARGER_THAN_SMARTPHONE (768 / GRID_UNIT_PX) * UNITS_BASE_SIZE
#define BREAKPOINT_LARGER_THAN_DESKTOP (992 / GRID_UNIT_PX) * UNITS_BASE_SIZE
#define BREAKPOINT_LARGER_THAN_WIDE_DESKTOP (1440 / GRID_UNIT_PX) * UNITS_BASE_SIZE


/*** TYPOGRAPHY ***/
#define FONT_PIXEL_SIZE_BASE (14 / GRID_UNIT_PX) * UNITS_BASE_SIZE
#define FONT_SIZE_BASE_MULTIPLIER 1.0

#define FONT_XSMALL_MULTIPLIER 0.606
#define FONT_SMALL_MULTIPLIER 0.707
#define FONT_MEDIUM_MULTIPLIER 1.0
#define FONT_LARGE_MULTIPLIER 1.414
#define FONT_XLARGE_MULTIPLIER 1.905

/*** COLUMNS ***/
// TODO: Everything
// TODO: We may want to make the width of some elements depending on our column system, perhaps?
#define COLUMNS_TOTAL_WIDTH QQuickSuruUnits::gu(48)   // TODO: Read the width of the window

#define COLUMNS_COUNT_SMARTPHONE 4
#define COLUMNS_COUNT_DESKTOP 8
#define COLUMNS_COUNT_WIDE_DESKTOP 12

#define COLUMN_BASE_WIDTH (COLUMNS_TOTAL_WIDTH / COLUMNS_COUNT_WIDE_DESKTOP)

class QQuickSuruUnits : public QObject
{
    Q_OBJECT

    Q_PROPERTY(float SpacingSmall READ spacingSmall CONSTANT)
    Q_PROPERTY(float SpacingMedium READ spacingMedium CONSTANT)
    Q_PROPERTY(float SpacingLarge READ spacingLarge CONSTANT)
    Q_PROPERTY(float SpacingXLarge READ spacingXLarge CONSTANT)

    Q_PROPERTY(float BreakpointSmartphone READ breakpointSmartphone CONSTANT)
    Q_PROPERTY(float BreakpointDesktop READ breakpointDesktop CONSTANT)
    Q_PROPERTY(float BreakpointWideDesktop READ breakpointWideDesktop CONSTANT)

    Q_PROPERTY(float FontXSmall READ fontXSmall CONSTANT)
    Q_PROPERTY(float FontSmall READ fontSmall CONSTANT)
    Q_PROPERTY(float FontMedium READ fontMedium CONSTANT)
    Q_PROPERTY(float FontLarge READ fontLarge CONSTANT)
    Q_PROPERTY(float FontXLarge READ fontXLarge CONSTANT)

public:
    // Base
    Q_INVOKABLE static float gu(float value) {
        // This is a trimmed version of units.gu() used by the original
        // Ubuntu UI Toolkit. Since version 5.6, Qt handles Hi-DPI support
        // for us.

        return qRound(value * GRID_UNIT_PX);
    }

    Q_INVOKABLE static float dp(float value) {
        // This is a trimmed version of units.dp() used by the original
        // Ubuntu UI Toolkit. Since version 5.6, Qt handles Hi-DPI support
        // for us.

        return value;
    }

    // Spacing
    static float spacingSmall() { return QQuickSuruUnits::gu(0.5); }
    static float spacingMedium() { return QQuickSuruUnits::gu(1); }
    static float spacingLarge() { return QQuickSuruUnits::gu(2); }
    static float spacingXLarge() { return QQuickSuruUnits::gu(4); }

    // Breakpoints
    static float breakpointSmartphone() { return BREAKPOINT_LARGER_THAN_SMARTPHONE; }
    static float breakpointDesktop() { return BREAKPOINT_LARGER_THAN_DESKTOP; }
    static float breakpointWideDesktop() { return BREAKPOINT_LARGER_THAN_WIDE_DESKTOP; }

    // Typography
    static float fontXSmall() { return FONT_PIXEL_SIZE_BASE * FONT_SIZE_BASE_MULTIPLIER * FONT_XSMALL_MULTIPLIER; }
    static float fontSmall() { return FONT_PIXEL_SIZE_BASE * FONT_SIZE_BASE_MULTIPLIER * FONT_SMALL_MULTIPLIER; }
    static float fontMedium() { return FONT_PIXEL_SIZE_BASE * FONT_SIZE_BASE_MULTIPLIER * FONT_MEDIUM_MULTIPLIER; }
    static float fontLarge() { return FONT_PIXEL_SIZE_BASE * FONT_SIZE_BASE_MULTIPLIER * FONT_LARGE_MULTIPLIER; }
    static float fontXLarge() { return FONT_PIXEL_SIZE_BASE * FONT_SIZE_BASE_MULTIPLIER * FONT_XLARGE_MULTIPLIER; }
};

#endif // QQUICKSURUUNITS_H
