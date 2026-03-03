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
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>

class PShape {
public:
	PShape() = default;
	~PShape() = default;

	static void Create(JPH::Ref<JPH::Shape> mShape);
	JPH::Ref<JPH::Shape> GetShape() const { return mShape; }

protected:
	JPH::Ref<JPH::Shape> mShape;
};

