#pragma once

class RigidBody{
private:
    JPH::BodyID m_ID;

public:
	RigidBody() = default;
	RigidBody(const JPH::BodyID& id) : m_ID(id) {}

	JPH::BodyID GetID() const { return m_ID; }
};