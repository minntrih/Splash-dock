// SPDX-License-Identifier: MIT
// Splash Dock — src/waylandlayershell.cpp

#include "waylandlayershell.h"

#include <QGuiApplication>
#include <QWindow>
#include <QDebug>

// QPA private header — provides QPlatformNativeInterface
// (requires Qt6::GuiPrivate in CMakeLists.txt)
#include <qpa/qplatformnativeinterface.h>

#include <wayland-client-core.h>

// ─────────────────────────────────────────────────────────────────────────────
// IMPORTANT: The generated C header wayland-wlr-layer-shell-…-client-protocol.h
// uses "namespace" as a parameter name, which is a reserved C++ keyword.
// We must NOT include that header in a C++ translation unit.
// The Qt wrapper (qwayland-wlr-layer-shell-…-v1.h) wraps it correctly and is
// the only header we need here — it is already included via waylandlayershell.h.
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// WaylandLayerSurface
// ─────────────────────────────────────────────────────────────────────────────

WaylandLayerSurface::WaylandLayerSurface(struct ::zwlr_layer_surface_v1 *surface,
                                          QObject *parent)
    : QObject(parent)
    , QtWayland::zwlr_layer_surface_v1(surface)
{}

WaylandLayerSurface::~WaylandLayerSurface()
{
    destroy();
}

void WaylandLayerSurface::setAnchor(uint32_t anchor)
{
    set_anchor(anchor);
}

void WaylandLayerSurface::setExclusiveZone(int32_t zone)
{
    set_exclusive_zone(zone);
}

void WaylandLayerSurface::setSize(uint32_t width, uint32_t height)
{
    set_size(width, height);
}

void WaylandLayerSurface::setMargin(int32_t top, int32_t right,
                                     int32_t bottom, int32_t left)
{
    set_margin(top, right, bottom, left);
}

void WaylandLayerSurface::setKeyboardInteractivity(uint32_t interactivity)
{
    set_keyboard_interactivity(interactivity);
}

// Protocol callbacks → Qt signals
void WaylandLayerSurface::zwlr_layer_surface_v1_configure(uint32_t serial,
                                                            uint32_t width,
                                                            uint32_t height)
{
    emit configured(serial, width, height);
}

void WaylandLayerSurface::zwlr_layer_surface_v1_closed()
{
    emit closed();
}

// ─────────────────────────────────────────────────────────────────────────────
// WaylandLayerShell
// ─────────────────────────────────────────────────────────────────────────────

WaylandLayerShell::WaylandLayerShell(QObject *parent)
    : QWaylandClientExtensionTemplate<WaylandLayerShell>(4 /*version*/)
    , QtWayland::zwlr_layer_shell_v1()
{
    setParent(parent);
    // Qt6: explicitly initialise the extension so the registry machinery runs.
    initialize();
}

WaylandLayerShell::~WaylandLayerShell()
{
    if (isActive())
        destroy();
}

WaylandLayerSurface *WaylandLayerShell::createLayerSurface(QWindow   *window,
                                                             Layer      layer,
                                                             const QString &nameSpace)
{
    if (!isActive()) {
        qWarning("WaylandLayerShell: protocol not advertised by compositor — "
                 "ensure KWin is running and zwlr_layer_shell_v1 is supported.");
        return nullptr;
    }

    // ── Retrieve the native wl_surface ────────────────────────────────────────
    // Qt 6 Wayland: use QPlatformNativeInterface::nativeResourceForWindow.
    // The key "surface" returns the struct wl_surface* for a Wayland window.
    QPlatformNativeInterface *nif = QGuiApplication::platformNativeInterface();
    if (!nif) {
        qWarning("WaylandLayerShell: no QPlatformNativeInterface — "
                 "are we running on Wayland?");
        return nullptr;
    }

    auto *wlSurface = static_cast<struct ::wl_surface *>(
        nif->nativeResourceForWindow(QByteArrayLiteral("surface"), window));

    if (!wlSurface) {
        qWarning("WaylandLayerShell: could not obtain wl_surface from QWindow. "
                 "Make sure the window is shown before calling createLayerSurface().");
        return nullptr;
    }

    // ── Call the Qt-generated C++ binding ────────────────────────────────────
    // QtWayland::zwlr_layer_shell_v1::get_layer_surface wraps the C call that
    // uses "namespace" as a parameter — the Qt binding renames it to avoid the clash.
    struct ::zwlr_layer_surface_v1 *raw =
        get_layer_surface(wlSurface,
                          nullptr /* output: let compositor choose */,
                          static_cast<uint32_t>(layer),
                          nameSpace);

    if (!raw) {
        qWarning("WaylandLayerShell: get_layer_surface returned null");
        return nullptr;
    }

    return new WaylandLayerSurface(raw, this);
}
