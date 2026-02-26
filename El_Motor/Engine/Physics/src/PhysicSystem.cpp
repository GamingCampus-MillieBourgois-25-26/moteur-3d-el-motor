#include "PhysicSystem.hpp"

namespace BroadPhaseLayers
{
	static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
	static constexpr JPH::BroadPhaseLayer MOVING(1);
	static constexpr JPH::uint NUM_LAYERS(2);
};

class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface
{
public:
	BPLayerInterfaceImpl()
	{
		// Create a mapping table from object to broad phase layer
		mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
		mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
	}

	virtual JPH::uint GetNumBroadPhaseLayers() const override
	{
		return BroadPhaseLayers::NUM_LAYERS;
	}

	virtual JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override
	{
		JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
		return mObjectToBroadPhase[inLayer];
	}

private:
	JPH::BroadPhaseLayer mObjectToBroadPhase[Layers::NUM_LAYERS];
};


class ObjectVsBroadPhaseLayerFilterImpl : public JPH::ObjectVsBroadPhaseLayerFilter
{
public:
	virtual bool ShouldCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2) const override
	{
		switch (inLayer1)
		{
		case Layers::NON_MOVING:
			return inLayer2 == BroadPhaseLayers::MOVING;
		case Layers::MOVING:
			return true;
		default:
			JPH_ASSERT(false);
			return false;
		}
	}
};

class ObjectLayerPairFilterImpl : public JPH::ObjectLayerPairFilter
{
public:
	virtual bool ShouldCollide(JPH::Body inBody1, JPH::Body inBody2) const override
	{
		switch (inBody1)
		{
		case Layers::NON_MOVING:
			return inBody2 == Layers::MOVING;
		case Layers::MOVING:
			return true;
		default:
			JPH_ASSERT(false);
			return false;
		}
	}
};

class MyContactListener : public JPH::ContactListener
{
public:
	// See: ContactListener
	virtual JPH::ValidateResult	OnContactValidate(const JPH::Body& inBody1, const JPH::Body& inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult& inCollisionResult) override
	{
		std::cout << "Contact validate callback" << std::endl;

		// Allows you to ignore a contact before it is created (using layers to not make objects collide is cheaper!)
		return JPH::ValidateResult::AcceptAllContactsForThisBodyPair;
	}

	virtual void OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override
	{
		std::cout << "A contact was added" << std::endl;
	}

	virtual void OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override
	{
		std::cout << "A contact was persisted" << std::endl;
	}

	virtual void OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair) override
	{
		std::cout << "A contact was removed" << std::endl;
	}
};

void PhysicSystem::Init(){
	JPH::RegisterDefaultAllocator();
	JPH::Factory::sInstance = new JPH::Factory();

	JPH::RegisterTypes();

	BPLayerInterfaceImpl BroadPhaseLayerInterface;
	ObjectVsBroadPhaseLayerFilterImpl ObjectVSBroadphaseLayerFilter;
	ObjectLayerPairFilterImpl ObjectVSObjectLayerFilter;

	const uint cMaxBodies = 65536;
	const uint cNumBodyMutexes = 0; // VAL ????
	const uint cMaxBodyPairs = 65536;
	const uint cMaxContactConstraints = 10240;

	mSystem = new JPH::PhysicsSystem();
	mSystem.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, BroadPhaseLayerInterface, ObjectVSBroadphaseLayerFilter, ObjectVSObjectLayerFilter);

	&mSystem.SetContactListener(&contactListener);

	mBodyInterface = &mSystem->GetBodyInterface();

	mJobSystem = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers);
}

void PhysicSystem::OnEnd()
{
	delete contactListener;
	delete mJobSystem;
	delete mSystem;

	JPH::Factory::sInstance = nullptr;
	delete JPH::Factory::sInstance;

	JPH::UnregisterTypes();
}

void PhysicSystem::Update(Engine::Scene& scene, float deltaTime) {
	const float cDeltaTime = 1.0f / 60.0f;
	JPH::uint step = 0;
	while() {
		++step;

		const int cCollisionSteps = 1;

		&mSystem->Update(cDeltaTime, cCollisionSteps, , &mJobSystem);
	}
}
