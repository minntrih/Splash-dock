#version 440

// ─────────────────────────────────────────────────────────────────────────────
// Splash Dock — shaders/noise.frag
//
// Procedural value-noise fragment shader for the frosted-glass texture overlay.
//
// Compiled to noise.frag.qsb by:
//   qt6_add_shaders(splash-dock "dock_shaders" ... FILES shaders/noise.frag)
//
// Qt RHI GLSL dialect: layout qualifiers are required; gl_FragColor → out vec4.
// ─────────────────────────────────────────────────────────────────────────────

layout(location = 0) in  vec2  qt_TexCoord0;    // [0,1] UV from ShaderEffect
layout(location = 0) out vec4  fragColor;

// ── Uniforms forwarded from NoiseTexture.qml ──────────────────────────────────
layout(std140, binding = 0) uniform buf {
    mat4  qt_Matrix;        // Qt's built-in MVP (unused in flat shader)
    float qt_Opacity;       // Qt's built-in opacity (from Item.opacity)
    float noiseScale;       // controls grain size (default 2.5)
    float time;             // animated seed (0 = static)
};

// ── Value noise helpers ────────────────────────────────────────────────────────
// Hash: pseudo-random float from a 2D integer coordinate.
float hash(vec2 p) {
    p = fract(p * vec2(234.34, 435.345));
    p += dot(p, p + 34.23);
    return fract(p.x * p.y);
}

// Bilinearly-interpolated value noise.
float valueNoise(vec2 uv) {
    vec2 i = floor(uv);
    vec2 f = fract(uv);

    // Smooth-step for C1 continuity.
    vec2 u = f * f * (3.0 - 2.0 * f);

    float a = hash(i + vec2(0.0, 0.0));
    float b = hash(i + vec2(1.0, 0.0));
    float c = hash(i + vec2(0.0, 1.0));
    float d = hash(i + vec2(1.0, 1.0));

    return mix(mix(a, b, u.x),
               mix(c, d, u.x), u.y);
}

// Two-octave fBm for a more organic, paper-like texture.
float fbm(vec2 uv) {
    float v  = 0.0;
    float amp = 0.5;
    for (int i = 0; i < 2; ++i) {
        v   += amp * valueNoise(uv);
        uv  *= 2.1;
        amp *= 0.5;
    }
    return v;
}

void main() {
    // Scale UV to control grain size; add time for optional animation.
    vec2 scaledUV = qt_TexCoord0 * noiseScale * 128.0 + vec2(time * 0.5);

    float n = fbm(scaledUV);

    // Output: monochrome noise, blended with Qt's opacity.
    // Alpha is kept low; actual opacity control comes from NoiseTexture.opacity.
    fragColor = vec4(vec3(n), 1.0) * qt_Opacity;
}
