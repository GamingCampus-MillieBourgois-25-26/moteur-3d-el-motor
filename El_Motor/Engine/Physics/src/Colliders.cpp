#include "Colliders.hpp"

BoxCollider::BoxCollider(Maths::Vec3f halfExtent) {
	JPH::BoxShapeSettings settings(JPH::Vec3(halfExtent.x(), halfExtent.y(), halfExtent.z()));
	JPH::ShapeSettings::ShapeResult bResult = settings.Create();

	if (bResult.IsValid()){
		PShape::Create(bResult.Get());
	}
	// else 
		// Log Call
}

SphereCollider::SphereCollider(float radius){
	JPH::SphereShapeSettings settings(radius);
	JPH::ShapeSettings::ShapeResult sResult = settings.Create();

	if (sResult.IsValid()){
		PShape::Create(sResult.Get());
	}
	// else 
		// Log Call
}

CapsuleCollider::CapsuleCollider(float radius, float height){
	JPH::CapsuleShapeSettings settings(radius, height);
	JPH::ShapeSettings::ShapeResult cResult = settings.Create();

	if (cResult.IsValid()){
		PShape::Create(cResult.Get());
	}
	// else 
		// Log Call
}