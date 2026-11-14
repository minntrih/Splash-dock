// SPDX-License-Identifier: MIT
// Splash Dock — src/blurmanager.h
//
// Thin QObject wrapper around KWindowEffects::enableBlurBehind.
// Works on Wayland via KWin's blur protocol under the hood — zero X11.

#pragma once

#include <QObject>
#include <QRegion>
#include <QWindow>

class BlurManager : public QObject
{
    Q_OBJECT
public:
    explicit BlurManager(QObject *parent = nullptr);

    // Apply KWin blur behind the entire window surface.
    // Call this AFTER the window is shown and its layer surface is configured.
    Q_INVOKABLE void applyBlur(QWindow *window, bool enable = true);

    // Apply blur behind a specific region (e.g. rounded-rect approximation).
    Q_INVOKABLE void applyBlurRegion(QWindow *window, const QRegion &region);
};
