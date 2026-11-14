// SPDX-License-Identifier: MIT
// Splash Dock — src/qml/DockBackground.qml
//
// Multi-layer frosted-glass render pipeline:
//
//   Layer 0 (bottom) — Translucent white base  (glass body)
//   Layer 1          — Saturation boost via ShaderEffect
//   Layer 2          — Noise overlay via ShaderEffect   (physical texture)
//   Layer 3 (top)    — 1px inner bright stroke + rounded clip mask
//
// KWin does the actual background blur behind the surface; we merely render
// on top of it, adding the subtle visual refinements.

import QtQuick
import QtQuick.Effects

Item {
    id: root

    // Allow child items (the icon row) to be placed inside via default property.
    default property alias content: contentArea.data

    // ── Layer 0: Translucent base ─────────────────────────────────────────────
    Rectangle {
        id: glassBase

        anchors.fill: parent
        radius: 20

        // Warm-tinted white at ~14% opacity — sits on top of KWin's blur.
        color: Qt.rgba(1.0, 1.0, 1.0, 0.14)

        // Clip children to the rounded rect.
        clip: true

        // ── Layer 1: Saturation booster ───────────────────────────────────────
        // A ShaderEffect sampling the layer's own texture is not meaningful here
        // (we can only saturate what Qt has rendered, not the compositor blur).
        // Instead we render a very subtle complementary-colour tint that visually
        // "pops" the blurred palette without reading compositor pixels.
        Rectangle {
            id: saturationTint
            anchors.fill: parent
            // A faint, desaturated violet that shifts the neutral blur warmer.
            color: Qt.rgba(0.55, 0.45, 0.80, 0.07)
            radius: parent.radius
        }

        // ── Layer 2: Noise overlay ────────────────────────────────────────────
        NoiseTexture {
            anchors.fill: parent
            opacity: 0.045          // very subtle — adds physical texture
        }

        // ── Content area (icons etc.) ─────────────────────────────────────────
        Item {
            id: contentArea
            anchors.fill: parent
        }
    }

    // ── Layer 3: Inner bright stroke ─────────────────────────────────────────
    // A Rectangle drawn *on top* of everything, with a transparent fill and a
    // bright border, creates the "depth edge" effect without overdrawing icons.
    Rectangle {
        anchors.fill: parent
        radius: glassBase.radius
        color: "transparent"

        border {
            width: 1
            // Semi-transparent white — bright at top (light source), subtle overall.
            color: Qt.rgba(1.0, 1.0, 1.0, 0.30)
        }
    }

    // ── Layer 3b: Subtle top highlight ───────────────────────────────────────
    // A very thin gradient at the top edge simulates a specular reflection.
    Rectangle {
        id: topHighlight
        anchors {
            top:   parent.top
            left:  parent.left
            right: parent.right
        }
        height: 2
        radius: glassBase.radius

        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.0; color: Qt.rgba(1, 1, 1, 0.0) }
            GradientStop { position: 0.3; color: Qt.rgba(1, 1, 1, 0.5) }
            GradientStop { position: 0.7; color: Qt.rgba(1, 1, 1, 0.5) }
            GradientStop { position: 1.0; color: Qt.rgba(1, 1, 1, 0.0) }
        }
    }

    // ── Drop shadow below the dock ────────────────────────────────────────────
    // Rendered via layer.effect so it doesn't clip; uses QtQuick.Effects.
    layer.enabled: true
    layer.effect: MultiEffect {
        shadowEnabled:    true
        shadowColor:      Qt.rgba(0, 0, 0, 0.45)
        shadowBlur:       0.6
        shadowVerticalOffset:   6
        shadowHorizontalOffset: 0
    }
}
