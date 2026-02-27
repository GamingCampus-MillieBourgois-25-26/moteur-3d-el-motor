#pragma once
#include "ScriptRegistry/ScriptRegistry.hpp"
#include <memory>

//NEVER INCLUDE THIS HEADER IN A HEADER, ONLY IN CPP, OTHERWISE IT WILL REGISTER THE SCRIPT MULTIPLE TIMES AND CAUSE LINKER ERRORS
#define REGISTER_SCRIPT(Type) \
namespace { \
    struct Type##AutoRegister { \
        Type##AutoRegister() { \
            ScriptRegistry::Instance().Register( \
                [](){ return std::make_unique<Type>(); } \
            ); \
        } \
    }; \
    static Type##AutoRegister global_##Type##_registrar; \
}