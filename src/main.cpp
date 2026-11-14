// SPDX-License-Identifier: MIT
// Splash Dock — src/main.cpp

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

#include "dockwindow.h"
#include "blurmanager.h"

int main(int argc, char *argv[])
{
    // ── Force Wayland platform ────────────────────────────────────────────────
    // Ensures we always use the Wayland QPA even when DISPLAY is set.
    qputenv("QT_QPA_PLATFORM", "wayland");

    // ── High-DPI: let Qt handle scaling natively ──────────────────────────────
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    QGuiApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("Splash Dock"));
    app.setApplicationVersion(QStringLiteral("0.1.0"));
    app.setOrganizationName(QStringLiteral("SplashDock"));

    // ── QML Engine ────────────────────────────────────────────────────────────
    QQmlApplicationEngine engine;

    // Expose BlurManager to QML (optional — DockWindow already calls it in C++,
    // but exposing it lets QML trigger re-blurs if the geometry changes).
    auto *blurManager = new BlurManager(&app);
    engine.rootContext()->setContextProperty(QStringLiteral("BlurManager"), blurManager);

    // ── DockWindow factory ────────────────────────────────────────────────────
    // We set a custom initialProperties so QML can reference the window.
    engine.load(QUrl(QStringLiteral("qrc:/SplashDock/src/qml/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        qCritical("Failed to load QML root; aborting.");
        return 1;
    }

    return app.exec();
}
