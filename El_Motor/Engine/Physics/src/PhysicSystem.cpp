#include "PhysicSystem.hpp"
#include "Maths/Headers/MQuaternion.hpp"
#include "Entity/Component/RigidBodyComponent.hpp"

//PhysicSystem::PhysicsStruct PhysicSystem::sPhysics{};

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
	virtual bool ShouldCollide(JPH::ObjectLayer inBody1, JPH::ObjectLayer inBody2) const override
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

BPLayerInterfaceImpl broadPhaseLayerInterface = BPLayerInterfaceImpl();
ObjectVsBroadPhaseLayerFilterImpl objectVSBroadphaseLayerFilter;
ObjectLayerPairFilterImpl objectVSObjectLayerFilter;

void PhysicSystem::Init(){
	JPH::RegisterDefaultAllocator();
	JPH::Factory::sInstance = new JPH::Factory();

	JPH::RegisterTypes();

	// Allocate a temp allocator on the heap and store the pointer in the member
	sPhysics.mTemp_allocator = new JPH::TempAllocatorImpl(10 * 1024 * 1024);

	const JPH::uint cMaxBodies = 65536;
	const JPH::uint cNumBodyMutexes = 0; // VAL ???? 
	const JPH::uint cMaxBodyPairs = 65536;
	const JPH::uint cMaxContactConstraints = 10240;

	sPhysics.mSystem = new JPH::PhysicsSystem();
	sPhysics.mSystem->Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, broadPhaseLayerInterface, objectVSBroadphaseLayerFilter, objectVSObjectLayerFilter);

	// Create and register contact listener
	sPhysics.mContactListener = new MyContactListener();
	sPhysics.mSystem->SetContactListener(sPhysics.mContactListener);
	sPhysics.mSystem->SetGravity(JPH::Vec3(0, -9.81f, 0));

	sPhysics.mBodyInterface = &sPhysics.mSystem->GetBodyInterface();

	sPhysics.mJobSystem = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers);
}

void PhysicSystem::Exit()
{
	// Delete owned objects in reverse order of creation where appropriate
	delete sPhysics.mContactListener;
	sPhysics.mContactListener = nullptr;

	delete sPhysics.mJobSystem;
	sPhysics.mJobSystem = nullptr;

	delete sPhysics.mSystem;
	sPhysics.mSystem = nullptr;

	sPhysics.mTemp_allocator = nullptr;
	// Delete the temp allocator
	delete sPhysics.mTemp_allocator;

	// Destroy the factory instance properly
	delete JPH::Factory::sInstance;
	JPH::Factory::sInstance = nullptr;

	JPH::UnregisterTypes();
}

void PhysicSystem::OnStart(std::shared_ptr<Engine::Scene>& scene) {
	auto objects = scene->GetRootObjects();

	for (auto& it : objects) {
		for (auto& comp : it->GetAllComponents()) {
			if (comp->GetTypeName() == "RigidBody") {
				auto* rbComp = static_cast<Engine::RigidBodyComponent*>(comp);
				JPH::Body* body = rbComp->GetRigidBody().GetBody();

				sPhysics.mBodyInterface->AddBody(body->GetID(), JPH::EActivation::Activate);
			}
		}
	}
}

void PhysicSystem::OnEnd(std::shared_ptr<Engine::Scene>& scene) {
	auto objects = scene->GetRootObjects();

	for (auto& it : objects) {
		for (auto& comp : it->GetAllComponents()) {
			if (comp->GetTypeName() == "RigidBody") {
				auto* rbComp = static_cast<Engine::RigidBodyComponent*>(comp);
				JPH::Body* body = rbComp->GetRigidBody().GetBody();

				sPhysics.mBodyInterface->RemoveBody(body->GetID());
				sPhysics.mBodyInterface->DestroyBody(body->GetID());
			}
		}
	}
}

void PhysicSystem::Update(std::shared_ptr<Engine::Scene>& scene, float deltaTime) {
	const float cDeltaTime = 1.0f / 60.0f;
	const int cCollisionSteps = 1;

	sPhysics.mSystem->Update(cDeltaTime, cCollisionSteps, sPhysics.mTemp_allocator, sPhysics.mJobSystem);

	// Transforms Update || (pos et rot)
	// pour tous aller chercher le body in rigidBody 
	auto objects = scene->GetRootObjects();

	for (auto& it : objects){
		for (auto& comp : it->GetAllComponents()){
			if (comp->GetTypeName() == "RigidBody"){
				auto* rbComp = static_cast<Engine::RigidBodyComponent*>(comp);

				JPH::Body* body = rbComp->GetRigidBody().GetBody();

				if (!body)
					continue;

				// Position / Rotation depuis Jolt
				JPH::Vec3 pos = body->GetPosition();
				JPH::Quat rot = body->GetRotation();

				auto* transform = it->GetTransform();
				if (!transform)
					continue;

				// Update position
				transform->SetPosition(Maths::Vec3f(pos.GetX(), pos.GetY(), pos.GetZ()));

				// Update rotation
				transform->SetRotation(Maths::Quatf(rot.GetX(), rot.GetY(), rot.GetZ(), rot.GetW()));
			}
		}
	}
}
