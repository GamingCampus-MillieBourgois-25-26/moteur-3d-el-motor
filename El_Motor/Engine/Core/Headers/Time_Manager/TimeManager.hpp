#pragma once
#include <iostream>
#include <chrono>
using namespace std;

namespace Engine
{
    class TimeManager {
    public:
        float deltaTime = 0.0f;
        void update(); // met à jour deltaTime
    };
}
