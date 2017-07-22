import QtQuick 2.8
import QtQuick.Templates 2.1 as T
import QtQuick.Controls.Suru 2.1

T.Label {
    id: control
    opacity: enabled ? 1.0 : 0.3
    color: control.Suru.primaryTextColor
    linkColor: control.Suru.accentColor
}
