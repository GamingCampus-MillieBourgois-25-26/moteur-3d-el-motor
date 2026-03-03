#pragma once

#include "Shapes.hpp"
#include "Maths/Headers/MVec3.hpp"

// Création des Shapes

class BoxCollider{
public:
	BoxCollider(Maths::Vec3f side);
};

class SphereCollider{
public:
	SphereCollider(float radius);
};

class CapsuleCollider{
public:
	CapsuleCollider(float radius, float height);
};