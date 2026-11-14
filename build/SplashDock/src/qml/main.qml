// SPDX-License-Identifier: MIT
// Splash Dock — src/qml/main.qml
//
// Root scene.  The DockWindow QQuickWindow is instantiated in C++ (main.cpp)
// and renders this QML scene.  We use a plain Item as the root visual so we
// can fill the window and lay out the dock bar centrally.

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    // The scene fills the entire window surface (which the layer shell sizes).
    width:  Window.window ? Window.window.width  : 1920
    height: Window.window ? Window.window.height : 80

    // ── App model ─────────────────────────────────────────────────────────────
    // Placeholder list; replace with a real D-Bus / .desktop parser later.
    ListModel {
        id: appModel
        ListElement { name: "Files";    iconColor: "#5E81AC"; iconChar: "📁" }
        ListElement { name: "Terminal"; iconColor: "#A3BE8C"; iconChar: "⬛" }
        ListElement { name: "Browser";  iconColor: "#88C0D0"; iconChar: "🌐" }
        ListElement { name: "Settings"; iconColor: "#EBCB8B"; iconChar: "⚙" }
        ListElement { name: "Music";    iconColor: "#B48EAD"; iconChar: "🎵" }
        ListElement { name: "Mail";     iconColor: "#BF616A"; iconChar: "✉" }
        ListElement { name: "Calendar"; iconColor: "#D08770"; iconChar: "📅" }
    }

    // ── Dock container: centred horizontally, flush to bottom ─────────────────
    DockBackground {
        id: dock

        // Calculate the content width from the number of icons.
        readonly property int iconSize: 56
        readonly property int iconSpacing: 8
        readonly property int paddingH: 16
        readonly property int paddingV: 10

        // Intrinsic width based on icon count + padding.
        width:  appModel.count * (iconSize + iconSpacing) - iconSpacing + paddingH * 2
        height: iconSize + paddingV * 2

        // Centre horizontally, sit at the very bottom.
        anchors.bottom:              parent.bottom
        anchors.horizontalCenter:    parent.horizontalCenter
        anchors.bottomMargin:        8

        // ── Icons row ─────────────────────────────────────────────────────────
        Row {
            id: iconRow

            anchors.centerIn: parent
            spacing: dock.iconSpacing

            // Track global mouse X within the row for neighbour magnification.
            property real mouseXInRow: 0

            HoverHandler {
                id: rowHover
                onPointChanged: {
                    if (rowHover.hovered)
                        iconRow.mouseXInRow = point.position.x
                }
                onHoveredChanged: {
                    if (!rowHover.hovered)
                        iconRow.mouseXInRow = -9999  // off-screen sentinel
                }
            }

            Repeater {
                model: appModel
                delegate: DockIcon {
                    required property string  name
                    required property string  iconColor
                    required property string  iconChar
                    required property int     index

                    iconLabel:    iconChar
                    iconBgColor:  iconColor
                    label:        name
                    baseSize:     dock.iconSize
                    rowMouseX:    iconRow.mouseXInRow
                    // Each icon's centre X within the row.
                    centerXInRow: index * (dock.iconSize + dock.iconSpacing)
                                  + dock.iconSize / 2
                }
            }
        }
    }
}
