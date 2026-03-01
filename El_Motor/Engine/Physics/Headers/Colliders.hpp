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

#include "Maths/Headers/MVec3.hpp"

// Création des Shapes

class BoxCollider{
public:
	BoxCollider(Maths::Vec3f side);

private:
	JPH::ShapeRefC mShape;
};

class SphereCollider{
public:
	SphereCollider(float radius);

private:
	JPH::ShapeRefC mShape;
};

class CapsuleCollider{
public:
	CapsuleCollider(float radius, float height);

private:
	JPH::ShapeRefC mShape;
};