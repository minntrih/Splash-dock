cmake_minimum_required(VERSION 3.22)

project(splash-dock
    VERSION 0.1.0
    DESCRIPTION "A premium macOS-style dock for Linux/KDE Plasma 6/Wayland"
    LANGUAGES CXX C
)

# ── C++ standard ──────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Automatic Qt helpers ───────────────────────────────────────────────────────
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# ── Qt CMake policies ─────────────────────────────────────────────────────────
# QTP0001: use :/qt/qml/ as the default QML resource prefix.
# QTP0004: suppress qmldir requirement for extra QML directories.
# QTP0006: default to PRIVATE_CODE in qt6_generate_wayland_protocol_client_sources.
if(POLICY CMP0071)
    cmake_policy(SET CMP0071 NEW)
endif()

# ── Qt 6 ──────────────────────────────────────────────────────────────────────
find_package(Qt6 6.6 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Quick
    ShaderTools      # qt6_add_shaders / qsb
    WaylandClient    # QWaylandClientExtension + native interface
    WaylandScannerTools  # qt6_generate_wayland_protocol_client_sources
)

# GuiPrivate exposes QPA headers (qpa/qplatformnativeinterface.h) needed to
# retrieve the native wl_surface from a QWindow on Wayland.
find_package(Qt6GuiPrivate REQUIRED)

# ── KDE Frameworks 6 ──────────────────────────────────────────────────────────
# On Arch/CachyOS, KF6 ships individual component cmake configs (no monolithic KF6Config.cmake).
find_package(KF6WindowSystem REQUIRED)

# ── Wayland (system libwayland-client, needed by the generated C glue) ────────
find_package(Wayland REQUIRED COMPONENTS Client)
find_package(WaylandScanner REQUIRED)   # provides Wayland::Scanner

# ── Source files ──────────────────────────────────────────────────────────────
set(SOURCES
    src/main.cpp
    src/dockwindow.cpp
    src/blurmanager.cpp
    src/waylandlayershell.cpp
)

# ── QML resource ──────────────────────────────────────────────────────────────
qt_add_executable(splash-dock ${SOURCES})

qt_add_qml_module(splash-dock
    URI SplashDock
    VERSION 1.0
    QML_FILES
        src/qml/main.qml
        src/qml/DockBackground.qml
        src/qml/DockIcon.qml
        src/qml/NoiseTexture.qml
    RESOURCES
        assets/icons/placeholder.svg  # will be created by the user later
)

# ── GLSL → QSB shader compilation ─────────────────────────────────────────────
qt6_add_shaders(splash-dock "dock_shaders"
    BATCHABLE
    PRECOMPILE
    OPTIMIZED
    PREFIX "/shaders"
    FILES
        shaders/noise.frag
        shaders/saturation.frag
)

# ── Wayland protocol code generation ──────────────────────────────────────────
qt6_generate_wayland_protocol_client_sources(splash-dock
    PRIVATE_CODE
    FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/protocols/wlr-layer-shell-unstable-v1.xml
)

# ── Link libraries ────────────────────────────────────────────────────────────
target_link_libraries(splash-dock PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::GuiPrivate          # QPA headers (QPlatformNativeInterface + qpa/qplatformnativeinterface.h)
    Qt6::Qml
    Qt6::Quick
    Qt6::WaylandClient
    KF6::WindowSystem
    Wayland::Client
)

# ── Include directories ───────────────────────────────────────────────────────
target_include_directories(splash-dock PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}  # for generated Wayland headers
)

# ── Compiler warnings ─────────────────────────────────────────────────────────
target_compile_options(splash-dock PRIVATE
    -Wall -Wextra -Wpedantic
    $<$<CONFIG:Debug>:-DQT_QML_DEBUG>
)

# ── Install ───────────────────────────────────────────────────────────────────
include(GNUInstallDirs)
install(TARGETS splash-dock
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
