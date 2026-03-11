#pragma once

#include <iostream>
#include <cstdarg>
#include <thread>

#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Core/StreamWrapper.h>
#include <Jolt/Core/StreamIn.h>
#include <Jolt/Core/StreamOut.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>
#include <Jolt/Physics/Collision/Shape/ConvexHullShape.h>
#include <Jolt/Physics/Collision/Shape/ScaledShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Jolt/Physics/Character/Character.h>
#include <Jolt/Physics/Character/CharacterVirtual.h>
#include <Jolt/Physics/Collision/PhysicsMaterialSimple.h>
#include <Jolt/Physics/Collision/RayCast.h>
#include <Jolt/Physics/Collision/CastResult.h>
#include <Jolt/Physics/Collision/CollisionCollector.h>
#include <Jolt/Physics/Collision/CollisionCollectorImpl.h>
#include <Jolt/Physics/Collision/ShapeCast.h>

#include "Scene/Scene.hpp"

class MyContactListener;
class BroadPhaseLayerInterfaceImpl;

namespace Layers
{
	static constexpr JPH::ObjectLayer NON_MOVING = 0;
	static constexpr JPH::ObjectLayer MOVING = 1;
	static constexpr JPH::ObjectLayer NUM_LAYERS = 2;
};

class PhysicSystem {
public:
	void Init();
	void Exit();

	void OnStart(std::shared_ptr<Engine::Scene>& scene);
	void OnEnd(std::shared_ptr<Engine::Scene>& scene);


	void Update(std::shared_ptr<Engine::Scene>& scene, float deltaTime);

	static JPH::BodyInterface* GetBodyInterface() { return sPhysics.mBodyInterface; }

private:
	static struct PhysicsStruct{
		JPH::PhysicsSystem* mSystem;
		JPH::BodyInterface* mBodyInterface;
		JPH::JobSystemThreadPool* mJobSystem;
		JPH::TempAllocatorImpl* mTemp_allocator;

		BroadPhaseLayerInterfaceImpl* mBroadPhaseLayer;
		MyContactListener* mContactListener;
	} sPhysics;
	
};