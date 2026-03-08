#pragma once
#include "ScriptRegister/ScriptRegister.hpp"
#include <memory>

/**
 * @brief Macro to automatically register a script type with the ScriptRegistry.
 *
 * @warning Only include this macro in a CPP file, never in a header.
 * Including it in a header can cause multiple registrations and linker errors.
 *
 * @param Type The class type to register (must inherit from your base Script class)
 *
 * @details
 * This macro creates an anonymous namespace with a static struct instance.
 * The constructor of the struct registers the script type using a lambda that
 * returns a std::unique_ptr of the script. The static instance ensures registration
 * happens at program startup.
 */
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