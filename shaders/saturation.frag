#version 440

// ─────────────────────────────────────────────────────────────────────────────
// Splash Dock — shaders/saturation.frag
//
// Optional saturation-boost pass that can be applied to any Item via
// layer.effect ShaderEffectSource.  It converts the sampled RGBA to HSL,
// multiplies saturation by a configurable factor, and converts back.
//
// NOTE: Qt's ShaderEffect can only sample its own rendered layer, NOT the
// compositor's background blur.  Use this as a layer.effect on a Rectangle
// that is ABOVE the blur area to visually enrich Qt-rendered content.
// ─────────────────────────────────────────────────────────────────────────────

layout(location = 0) in  vec2  qt_TexCoord0;
layout(location = 0) out vec4  fragColor;

layout(std140, binding = 0) uniform buf {
    mat4  qt_Matrix;
    float qt_Opacity;
    float saturationBoost;    // multiplier, e.g. 1.4 for +40% saturation
};

layout(binding = 1) uniform sampler2D source; // Qt's layer source texture

// ── RGB ↔ HSL conversion ──────────────────────────────────────────────────────
vec3 rgb2hsl(vec3 c) {
    float maxC = max(c.r, max(c.g, c.b));
    float minC = min(c.r, min(c.g, c.b));
    float delta = maxC - minC;

    float h = 0.0;
    float s = 0.0;
    float l = (maxC + minC) * 0.5;

    if (delta > 0.0001) {
        s = delta / (1.0 - abs(2.0 * l - 1.0));
        if      (maxC == c.r) h = mod((c.g - c.b) / delta, 6.0);
        else if (maxC == c.g) h = (c.b - c.r) / delta + 2.0;
        else                  h = (c.r - c.g) / delta + 4.0;
        h /= 6.0;
    }
    return vec3(h, s, l);
}

float hue2rgb(float p, float q, float t) {
    if (t < 0.0) t += 1.0;
    if (t > 1.0) t -= 1.0;
    if (t < 1.0 / 6.0) return p + (q - p) * 6.0 * t;
    if (t < 1.0 / 2.0) return q;
    if (t < 2.0 / 3.0) return p + (q - p) * (2.0 / 3.0 - t) * 6.0;
    return p;
}

vec3 hsl2rgb(vec3 hsl) {
    if (hsl.y < 0.0001)
        return vec3(hsl.z);

    float q = hsl.z < 0.5
              ? hsl.z * (1.0 + hsl.y)
              : hsl.z + hsl.y - hsl.z * hsl.y;
    float p = 2.0 * hsl.z - q;
    return vec3(
        hue2rgb(p, q, hsl.x + 1.0 / 3.0),
        hue2rgb(p, q, hsl.x),
        hue2rgb(p, q, hsl.x - 1.0 / 3.0)
    );
}

void main() {
    vec4 color = texture(source, qt_TexCoord0);
    if (color.a < 0.001) {
        fragColor = vec4(0.0);
        return;
    }

    // Un-premultiply alpha before colour operations.
    vec3 rgb = color.rgb / color.a;
    vec3 hsl = rgb2hsl(rgb);

    // Clamp saturation to [0, 1] after boost.
    hsl.y = clamp(hsl.y * saturationBoost, 0.0, 1.0);

    vec3 boosted = hsl2rgb(hsl) * color.a;   // re-premultiply
    fragColor = vec4(boosted, color.a) * qt_Opacity;
}
