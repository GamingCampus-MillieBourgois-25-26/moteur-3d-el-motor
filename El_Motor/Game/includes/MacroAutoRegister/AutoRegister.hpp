#pragma once
#include "ScriptRegister/ScriptRegister.hpp"
#include <memory>

/// <summary>
/// Macro to automatically register a script type with the ScriptRegistry.
/// Warning: Only include this macro in a CPP file, never in a header.
/// Including in a header can cause multiple registrations and linker errors.
/// </summary>
/// <param name="Type">The class type to register (must inherit from your base Script class)</param>
#define REGISTER_SCRIPT(Type) \
namespace { \
    struct Type##AutoRegister { \
        Type##AutoRegister() { \
            ScriptRegistry::Instance().Register( \
                [](){ return std::make_unique<Type>(); } /* Lambda returns a unique_ptr of the script */ \
            ); \
        } \
    }; \
    static Type##AutoRegister global_##Type##_registrar; /* Static instance ensures registration at program startup */ \
}