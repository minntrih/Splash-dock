/****************************************************************************
** Meta object code from reading C++ file 'waylandlayershell.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/waylandlayershell.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'waylandlayershell.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN19WaylandLayerSurfaceE_t {};
} // unnamed namespace

template <> constexpr inline auto WaylandLayerSurface::qt_create_metaobjectdata<qt_meta_tag_ZN19WaylandLayerSurfaceE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "WaylandLayerSurface",
        "configured",
        "",
        "uint32_t",
        "serial",
        "width",
        "height",
        "closed"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'configured'
        QtMocHelpers::SignalData<void(uint32_t, uint32_t, uint32_t)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 3, 5 }, { 0x80000000 | 3, 6 },
        }}),
        // Signal 'closed'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<WaylandLayerSurface, qt_meta_tag_ZN19WaylandLayerSurfaceE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject WaylandLayerSurface::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19WaylandLayerSurfaceE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19WaylandLayerSurfaceE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN19WaylandLayerSurfaceE_t>.metaTypes,
    nullptr
} };

void WaylandLayerSurface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WaylandLayerSurface *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->configured((*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<uint32_t>>(_a[3]))); break;
        case 1: _t->closed(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (WaylandLayerSurface::*)(uint32_t , uint32_t , uint32_t )>(_a, &WaylandLayerSurface::configured, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (WaylandLayerSurface::*)()>(_a, &WaylandLayerSurface::closed, 1))
            return;
    }
}

const QMetaObject *WaylandLayerSurface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WaylandLayerSurface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19WaylandLayerSurfaceE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QtWayland::zwlr_layer_surface_v1"))
        return static_cast< QtWayland::zwlr_layer_surface_v1*>(this);
    return QObject::qt_metacast(_clname);
}

int WaylandLayerSurface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void WaylandLayerSurface::configured(uint32_t _t1, uint32_t _t2, uint32_t _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3);
}

// SIGNAL 1
void WaylandLayerSurface::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
namespace {
struct qt_meta_tag_ZN17WaylandLayerShellE_t {};
} // unnamed namespace

template <> constexpr inline auto WaylandLayerShell::qt_create_metaobjectdata<qt_meta_tag_ZN17WaylandLayerShellE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "WaylandLayerShell",
        "Layer",
        "Background",
        "Bottom",
        "Top",
        "Overlay"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Layer'
        QtMocHelpers::EnumData<enum Layer>(1, 1, QMC::EnumIsScoped).add({
            {    2, Layer::Background },
            {    3, Layer::Bottom },
            {    4, Layer::Top },
            {    5, Layer::Overlay },
        }),
    };
    return QtMocHelpers::metaObjectData<WaylandLayerShell, qt_meta_tag_ZN17WaylandLayerShellE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject WaylandLayerShell::staticMetaObject = { {
    QMetaObject::SuperData::link<QWaylandClientExtensionTemplate<WaylandLayerShell>::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17WaylandLayerShellE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17WaylandLayerShellE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17WaylandLayerShellE_t>.metaTypes,
    nullptr
} };

void WaylandLayerShell::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WaylandLayerShell *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *WaylandLayerShell::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WaylandLayerShell::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17WaylandLayerShellE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QtWayland::zwlr_layer_shell_v1"))
        return static_cast< QtWayland::zwlr_layer_shell_v1*>(this);
    return QWaylandClientExtensionTemplate<WaylandLayerShell>::qt_metacast(_clname);
}

int WaylandLayerShell::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWaylandClientExtensionTemplate<WaylandLayerShell>::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
