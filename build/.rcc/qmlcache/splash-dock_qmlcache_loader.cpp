#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

namespace QmlCacheGeneratedCode {
namespace _0x5f_SplashDock_src_qml_main_qml { 
    extern bool validateLookupSignatures(QQmlEngine *engine, QV4::CompiledData::CompilationUnit *cu);
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], &validateLookupSignatures
    };
}
namespace _0x5f_SplashDock_src_qml_DockBackground_qml { 
    extern bool validateLookupSignatures(QQmlEngine *engine, QV4::CompiledData::CompilationUnit *cu);
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], &validateLookupSignatures
    };
}
namespace _0x5f_SplashDock_src_qml_DockIcon_qml { 
    extern bool validateLookupSignatures(QQmlEngine *engine, QV4::CompiledData::CompilationUnit *cu);
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], &validateLookupSignatures
    };
}
namespace _0x5f_SplashDock_src_qml_NoiseTexture_qml { 
    extern bool validateLookupSignatures(QQmlEngine *engine, QV4::CompiledData::CompilationUnit *cu);
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], &validateLookupSignatures
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
    resourcePathToCachedUnit.insert(QStringLiteral("/SplashDock/src/qml/main.qml"), &QmlCacheGeneratedCode::_0x5f_SplashDock_src_qml_main_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/SplashDock/src/qml/DockBackground.qml"), &QmlCacheGeneratedCode::_0x5f_SplashDock_src_qml_DockBackground_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/SplashDock/src/qml/DockIcon.qml"), &QmlCacheGeneratedCode::_0x5f_SplashDock_src_qml_DockIcon_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/SplashDock/src/qml/NoiseTexture.qml"), &QmlCacheGeneratedCode::_0x5f_SplashDock_src_qml_NoiseTexture_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.structVersion = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qmlcache_splash_dock)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qmlcache_splash_dock))
int QT_MANGLE_NAMESPACE(qCleanupResources_qmlcache_splash_dock)() {
    return 1;
}
