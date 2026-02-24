#pragma once

#include <Jolt/Jolt.h>


class RigidBody{
public:
	RigidBody() = default;

	void Create(); // Body creation;

	JPH::Body* GetBody() const { return mBody; }
private:
	JPH::Body* mBody;
};