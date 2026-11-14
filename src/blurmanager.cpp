// SPDX-License-Identifier: MIT
// Splash Dock — src/blurmanager.cpp
//
// KWindowEffects::enableBlurBehind works on both X11 and Wayland via KWin's
// org_kde_kwin_blur Wayland protocol — no xcb/X11 symbols needed.

#include "blurmanager.h"

#include <KWindowEffects>   // KF6::WindowSystem
#include <QDebug>

BlurManager::BlurManager(QObject *parent)
    : QObject(parent)
{}

void BlurManager::applyBlur(QWindow *window, bool enable)
{
    if (!window) {
        qWarning("BlurManager::applyBlur: null window");
        return;
    }
    // Passing an empty QRegion instructs KWin to blur the full surface.
    KWindowEffects::enableBlurBehind(window, enable);
    qDebug() << "BlurManager: blur" << (enable ? "enabled" : "disabled")
             << "for window" << window;
}

void BlurManager::applyBlurRegion(QWindow *window, const QRegion &region)
{
    if (!window) {
        qWarning("BlurManager::applyBlurRegion: null window");
        return;
    }
    KWindowEffects::enableBlurBehind(window, true, region);
}
