#include "Rigidbody.hpp"

RigidBody::RigidBody(JPH::ShapeRefC shape, bool isStatic) {
		Create(shape, isStatic);
}

void RigidBody::Create(JPH::ShapeRefC shape, bool isStatic) {
	JPH::BodyCreationSettings settings(shape, JPH::Vec3::sZero(), JPH::Quat::sIdentity(), isStatic? JPH::EMotionType::Static : JPH::EMotionType::Dynamic, Layers::MOVING);
	mBody = PhysicSystem::GetBodyInterface()->CreateBody(settings);
}

