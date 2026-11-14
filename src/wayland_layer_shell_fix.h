// SPDX-License-Identifier: MIT
// Splash Dock — src/wayland_layer_shell_fix.h
//
// The generated wayland-wlr-layer-shell-…-client-protocol.h uses "namespace"
// as a C function parameter name, which is a reserved C++ keyword and causes
// compilation failures when included in C++ code.
//
// This wrapper renames the offending parameter using a preprocessor macro
// BEFORE including the generated header, then undefines it afterwards.
//
// Include THIS header instead of the generated one in any C++ translation unit.

#pragma once

// Rename "namespace" to "ns" in all C function signatures before the header
// is parsed by the C++ compiler.
#define namespace ns
#include "wayland-wlr-layer-shell-unstable-v1-client-protocol.h"
#undef namespace
