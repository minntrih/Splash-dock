// SPDX-License-Identifier: MIT
// Splash Dock — src/dockwindow.cpp

#include "dockwindow.h"
#include "waylandlayershell.h"
#include "blurmanager.h"

#include <QGuiApplication>
#include <QScreen>
#include <QShowEvent>
#include <QDebug>

// ─────────────────────────────────────────────────────────────────────────────
DockWindow::DockWindow(QWindow *parent)
    : QQuickWindow(parent)
    , m_layerShell(std::make_unique<WaylandLayerShell>(this))
    , m_blurManager(new BlurManager(this))
{
    // A transparent background is required so KWin's blur shows through.
    setColor(Qt::transparent);

    // The dock only needs to be as tall as m_dockHeight; width is 0 so the
    // compositor fills the full screen width via the anchor+exclusive zone.
    resize(0, m_dockHeight);
}

DockWindow::~DockWindow() = default;

void DockWindow::setDockHeight(int h)
{
    if (m_dockHeight == h)
        return;
    m_dockHeight = h;
    resize(0, m_dockHeight);
    emit dockHeightChanged();

    // Update the exclusive zone so the compositor re-reserves space.
    if (m_layerSurface) {
        m_layerSurface->setExclusiveZone(m_dockHeight);
        m_layerSurface->setSize(0, static_cast<uint32_t>(m_dockHeight));
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Called by Qt the first time the window becomes visible.
void DockWindow::showEvent(QShowEvent *event)
{
    QQuickWindow::showEvent(event);
    if (!m_layerShellSetup) {
        setupLayerShell();
        m_layerShellSetup = true;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
void DockWindow::setupLayerShell()
{
    // The layer shell extension may not be ready immediately on the first
    // showEvent; we post the work so the event loop has ticked at least once
    // and the Wayland registry round-trip has completed.
    QMetaObject::invokeMethod(this, [this] {
        m_layerSurface = m_layerShell->createLayerSurface(
            this,
            WaylandLayerShell::Layer::Top,
            QStringLiteral("splash-dock")
        );

        if (!m_layerSurface) {
            qCritical("DockWindow: failed to create layer surface — "
                      "is the compositor running and advertising zwlr_layer_shell_v1?");
            return;
        }

        connect(m_layerSurface, &WaylandLayerSurface::configured,
                this,            &DockWindow::onLayerSurfaceConfigured);
        connect(m_layerSurface, &WaylandLayerSurface::closed,
                this,            &DockWindow::onLayerSurfaceClosed);

        // ── Anchor: left + right + bottom → full-width bar at the bottom ────
        const uint32_t anchor =
            WaylandLayerShell::AnchorBottom |
            WaylandLayerShell::AnchorLeft   |
            WaylandLayerShell::AnchorRight;

        m_layerSurface->setAnchor(anchor);

        // Height is explicit; width = 0 → compositor fills the full output width.
        m_layerSurface->setSize(0, static_cast<uint32_t>(m_dockHeight));

        // Exclusive zone == dock height → maximized windows won't overlap.
        m_layerSurface->setExclusiveZone(m_dockHeight);

        // The dock doesn't want keyboard focus.
        m_layerSurface->setKeyboardInteractivity(0 /*none*/);

        // No margins (the dock sits flush with screen edges).
        m_layerSurface->setMargin(0, 0, 0, 0);

        // Commit the wl_surface to send all pending state to the compositor.
        // Qt calls wl_surface_commit internally when the QWindow is shown;
        // we re-trigger it via a size change to flush our layer-shell requests.
        resize(width(), m_dockHeight);

    }, Qt::QueuedConnection);
}

// ─────────────────────────────────────────────────────────────────────────────
void DockWindow::onLayerSurfaceConfigured(uint32_t serial, uint32_t width, uint32_t height)
{
    qDebug() << "DockWindow: layer surface configured"
             << serial << width << height;

    // ACK the configure so the compositor knows we accepted it.
    m_layerSurface->ack_configure(serial);

    // If the compositor provided a preferred width/height, use it.
    if (width > 0 && height > 0) {
        QQuickWindow::resize(static_cast<int>(width),
                             static_cast<int>(height));
    } else if (width > 0) {
        QQuickWindow::resize(static_cast<int>(width), m_dockHeight);
    }

    // Now that the surface is properly configured, request KWin blur.
    m_blurManager->applyBlur(this, true);
}

void DockWindow::onLayerSurfaceClosed()
{
    qDebug() << "DockWindow: layer surface closed by compositor";
    close();
}
