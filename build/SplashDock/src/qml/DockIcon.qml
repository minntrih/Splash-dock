// SPDX-License-Identifier: MIT
// Splash Dock — src/qml/DockIcon.qml
//
// A single dock icon with:
//   • Smooth spring-physics magnification on hover (macOS-style wave effect).
//   • Gaussian falloff applied to neighbour icons via rowMouseX / centerXInRow.
//   • Bounce animation on click.
//   • Label that fades in on hover.

import QtQuick
import QtQuick.Effects

Item {
    id: root

    // ── Public API ────────────────────────────────────────────────────────────
    property string iconLabel:    "?"       // emoji or single character
    property string iconBgColor:  "#5E81AC" // background fill for the icon capsule
    property string label:        "App"     // text label below icon
    property real   baseSize:     56        // un-magnified icon size in px

    // Provided by the parent Row for neighbour magnification:
    property real rowMouseX:    -9999       // current mouse X in row coordinates
    property real centerXInRow: 0           // this icon's centre X in row coordinates

    // ── Magnification physics ─────────────────────────────────────────────────
    // Gaussian influence: icons within ±80 px of the cursor magnify.
    readonly property real magnificationRadius: 80.0   // px half-width of influence
    readonly property real maxScale: 1.75               // peak scale at cursor centre

    // Raw target scale derived from cursor proximity.
    readonly property real targetScale: {
        const dist = Math.abs(rowMouseX - centerXInRow)
        if (rowMouseX < -9000 || dist > magnificationRadius * 1.5)
            return 1.0
        // Gaussian: e^(- dist² / (2 σ²)),  σ = magnificationRadius / 2
        const sigma = magnificationRadius / 2.0
        const gaussian = Math.exp(-(dist * dist) / (2.0 * sigma * sigma))
        return 1.0 + (maxScale - 1.0) * gaussian
    }

    // ── Animated scale ────────────────────────────────────────────────────────
    property real animatedScale: 1.0

    Behavior on animatedScale {
        SpringAnimation {
            spring:  1.8    // stiffness — higher = snappier
            damping: 0.18   // 0 = no damping (oscillates), 1 = critically damped
            epsilon: 0.001  // stop when within 0.1% of target
            modulus: 0      // no modular wrapping
        }
    }

    // Drive animatedScale whenever targetScale changes.
    onTargetScaleChanged: animatedScale = targetScale

    // ── Click bounce ─────────────────────────────────────────────────────────
    property bool  bouncing: false

    SequentialAnimation {
        id: bounceAnim
        NumberAnimation { target: root; property: "animatedScale"
                          to: root.animatedScale * 1.15; duration: 90
                          easing.type: Easing.OutQuad }
        NumberAnimation { target: root; property: "animatedScale"
                          to: root.targetScale; duration: 220
                          easing.type: Easing.OutElastic }
        onFinished: root.bouncing = false
    }

    // ── Geometry ──────────────────────────────────────────────────────────────
    // The Item's footprint stays at baseSize so the Row layout doesn't jitter;
    // the visual Rectangle scales around its centre via transform.
    width:  baseSize
    height: baseSize + labelArea.height + 6

    // ── Icon capsule ──────────────────────────────────────────────────────────
    Rectangle {
        id: iconCapsule

        width:  baseSize
        height: baseSize
        radius: baseSize * 0.22    // macOS-style squircle approximation

        color: root.iconBgColor

        // Scale around the centre of the capsule, growing upward (macOS behaviour).
        transform: Scale {
            origin.x: baseSize / 2
            origin.y: baseSize      // anchor at bottom so icons grow upward
            xScale: root.animatedScale
            yScale: root.animatedScale
        }

        // ── Icon label ────────────────────────────────────────────────────────
        Text {
            anchors.centerIn: parent
            text: root.iconLabel
            font.pixelSize: baseSize * 0.52
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment:   Text.AlignVCenter
        }

        // ── Subtle gloss overlay ──────────────────────────────────────────────
        Rectangle {
            anchors {
                top:   parent.top
                left:  parent.left
                right: parent.right
            }
            height: parent.height * 0.45
            radius: parent.radius

            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.rgba(1, 1, 1, 0.22) }
                GradientStop { position: 1.0; color: Qt.rgba(1, 1, 1, 0.00) }
            }
        }

        // ── Drop shadow on the icon ───────────────────────────────────────────
        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled:          true
            shadowColor:            Qt.rgba(0, 0, 0, 0.5)
            shadowBlur:             0.5
            shadowVerticalOffset:   4 * root.animatedScale
            shadowHorizontalOffset: 0
        }

        // ── Mouse interaction ─────────────────────────────────────────────────
        TapHandler {
            onTapped: {
                if (!root.bouncing) {
                    root.bouncing = true
                    bounceAnim.restart()
                }
                console.log("Launched:", root.label)
            }
        }
    }

    // ── Tooltip label ─────────────────────────────────────────────────────────
    // Fades in above the icon when hovered; hidden otherwise.
    Item {
        id: labelArea

        anchors.top:              iconCapsule.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin:        6

        width:  labelText.implicitWidth + 12
        height: labelText.implicitHeight + 6

        opacity: root.animatedScale > 1.05 ? 1.0 : 0.0
        Behavior on opacity {
            NumberAnimation { duration: 150; easing.type: Easing.InOutSine }
        }

        Rectangle {
            anchors.fill: parent
            radius: 4
            color: Qt.rgba(0, 0, 0, 0.6)
        }

        Text {
            id: labelText
            anchors.centerIn: parent
            text: root.label
            color: "white"
            font.pixelSize: 11
            font.weight: Font.Medium
        }
    }
}
