#include "Rigidbody.hpp"

RigidBody::RigidBody(PShape shape, bool isStatic) {
		Create(shape, isStatic);
}

void RigidBody::Create(PShape shape, bool isStatic) {
	JPH::BodyCreationSettings settings(reinterpret_cast<JPH::ShapeRefC*>(shape.GetShape().GetPtr()), JPH::Vec3::sZero(), JPH::Quat::sIdentity(), isStatic ? JPH::EMotionType::Static : JPH::EMotionType::Dynamic, Layers::MOVING);
	mBody = PhysicSystem::GetBodyInterface()->CreateBody(settings);
}

