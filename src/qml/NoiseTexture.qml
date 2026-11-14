// SPDX-License-Identifier: MIT
// Splash Dock — src/qml/NoiseTexture.qml
//
// Renders a tileable value-noise texture using an inline GLSL fragment shader.
// No PNG asset required — the noise is generated procedurally on the GPU.
// The shader is compiled to .qsb by qt6_add_shaders in CMakeLists.txt.

import QtQuick

ShaderEffect {
    id: root

    // ── Public API ────────────────────────────────────────────────────────────
    // Scale of the noise pattern — larger = coarser grain.
    property real noiseScale: 2.5

    // Animated time uniform — set to 0 for static noise, or bind to a
    // NumberAnimation for a subtle animated shimmer effect.
    property real time: 0.0

    // ── Shader source ─────────────────────────────────────────────────────────
    // Qt's ShaderEffect supports inline GLSL when fragmentShader is a string
    // ending in a GLSL version directive, BUT the recommended path is a .qsb
    // file compiled by qt6_add_shaders.  We use the .qsb path so the pipeline
    // is portable across RHI backends (Vulkan, Metal, D3D, OpenGL).
    fragmentShader: "qrc:/shaders/noise.frag.qsb"

    // ── Uniforms forwarded to the shader ──────────────────────────────────────
    // Qt's ShaderEffect automatically binds QML properties whose names match
    // uniform variables in the shader.
    // (noiseScale and time are declared as uniforms in noise.frag)
}
