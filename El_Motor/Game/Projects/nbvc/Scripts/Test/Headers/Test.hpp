#pragma once
#include "UserScript/UserScript.hpp"

class Test : public UserScript
{
public:
    Test() : UserScript("Test") {}
    ~Test() = default;

    void OnStart() override;
    void Update(float deltaTime) override;
};
