// SPDX-License-Identifier: MIT
// Splash Dock — src/dockwindow.h
//
// The root window of the dock.  On show() it:
//   1. Registers itself with the Wayland Layer Shell.
//   2. Anchors to the bottom of the screen, reserving exclusive zone == height.
//   3. Requests KWin blur behind its surface.

#pragma once

#include <QQuickWindow>
#include <memory>

class WaylandLayerShell;
class WaylandLayerSurface;
class BlurManager;

class DockWindow : public QQuickWindow
{
    Q_OBJECT
    Q_PROPERTY(int dockHeight READ dockHeight WRITE setDockHeight NOTIFY dockHeightChanged)

public:
    explicit DockWindow(QWindow *parent = nullptr);
    ~DockWindow() override;

    int  dockHeight() const   { return m_dockHeight; }
    void setDockHeight(int h);

signals:
    void dockHeightChanged();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void onLayerSurfaceConfigured(uint32_t serial, uint32_t width, uint32_t height);
    void onLayerSurfaceClosed();

private:
    void setupLayerShell();

    int m_dockHeight = 80;   // logical pixels

    std::unique_ptr<WaylandLayerShell>   m_layerShell;
    WaylandLayerSurface                 *m_layerSurface = nullptr;
    BlurManager                         *m_blurManager  = nullptr;

    bool m_layerShellSetup = false;
};
