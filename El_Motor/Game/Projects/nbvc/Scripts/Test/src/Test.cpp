#include "../Headers/Test.hpp"
#include "MacroAutoRegister/AutoRegister.hpp"
#include <iostream>

void Test::OnStart()
{
    std::cout << "Test Started" << std::endl;
}

void Test::Update(float deltaTime)
{
}

REGISTER_SCRIPT(Test);
