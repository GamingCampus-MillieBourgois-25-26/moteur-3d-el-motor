#pragma once

#include <iostream>
#include <cstdarg>
#include <thread>

#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>

class MyContactListener;
class BroadPhaseLayerInterfaceImpl;

namespace Layers
{
	static constexpr JPH::ObjectLayer NON_MOVING = 0;
	static constexpr JPH::ObjectLayer MOVING = 2;
	static constexpr JPH::ObjectLayer NUM_LAYERS = 3;
};

class PhysicSystem {
public:
	void Init();
	void OnEnd();

	JPH::BodyInterface* getBodyInterface() { return mBodyInterface};

private:
	JPH::PhysicsSystem* mSystem;
	JPH::BodyInterface* mBodyInterface;
	JPH::JobSystemThreadPool* mJobSystem;

	BroadPhaseLayerInterfaceImpl* mBroadPhaseLayer;
	MyContactListener* mContactListener;
};