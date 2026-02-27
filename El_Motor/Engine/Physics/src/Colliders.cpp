#include "Colliders.hpp"

BoxCollider::BoxCollider(float side) {
	// JPH::BoxShapeSettings settings();
	// settings.SetEmbedded();

	// ShapeSettings::ShapeResult boxShapeResult = settings.Create();
	// if (result.IsValid()){
	// ShapeRefC result = boXShapeResult.get();
    // }
	// else ... Error handling
}

SphereCollider::SphereCollider(float radius){
	// JPH::SphereShapeSettings settings(radius);
	// settings.SetEmbedded();

	// ShapeSettings::ShapeResult sphereShapeResult = settings.Create();
	// if (result.IsValid()){
	// ShapeRefC result = sphereShapeResult.get();
	// }
	// else ... Error handling
}

CapsuleCollider::CapsuleCollider(float radius, float height){
	// JPH::CapsuleShapeSettings settings(radius, height);
	// settings.SetEmbedded();

	// ShapeSettings::ShapeResult capsuleShapeResult = settings.Create();
	// if (result.IsValid()){
	// ShapeRefC result = capsuleShapeResult.get();
	// }
	// else ... Error handling
}