#include "ScriptRegister/ScriptRegister.hpp"
#include "UserScript/UserScript.hpp"

ScriptRegistry& ScriptRegistry::Instance()
{
    static ScriptRegistry instance;
    return instance;
}

void ScriptRegistry::Register(ScriptFactory factory)
{
    factories.push_back(factory);
}

std::vector<std::unique_ptr<UserScript>> ScriptRegistry::CreateAll()
{
    std::vector<std::unique_ptr<UserScript>> result;
    result.reserve(factories.size());

    for (auto& factory : factories)
        result.push_back(factory());

    return result;
}