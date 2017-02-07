#include "PhysicsManager.h"

using namespace physx;

PhysicsManager::PhysicsManager()
{
	static PxDefaultErrorCallback gDefaultErrorCallback;
	static PxDefaultAllocator gDefaultAllocatorCallback;

	mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback,
		gDefaultErrorCallback);
	
	bool recordMemoryAllocations = true;
	
	mProfileZoneManager = &PxProfileZoneManager::createProfileZoneManager(mFoundation);

	if (!mProfileZoneManager)
		std::cout << "PxProfileZoneManager::createProfileZoneManager failed!" << std::endl;

	mTolerancesScale = PxTolerancesScale();

	mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation,
		mTolerancesScale, recordMemoryAllocations, mProfileZoneManager);
	if (!mPhysics)
		std::cout << "PxCreatePhysics failed!" << std::endl;

	mCooking = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation, PxCookingParams(mTolerancesScale));
	if (!mCooking)
		std::cout << "PxCreateCooking failed!" << std::endl;

	PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	mDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = mDispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	mScene = mPhysics->createScene(sceneDesc);

	mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);

}


PhysicsManager::~PhysicsManager()
{

	mScene->release();
	mDispatcher->release();
	mPhysics->release();
	mProfileZoneManager->release();
	mFoundation->release();
}

PxActor* PhysicsManager::createGroundPlane()
{
	PxRigidStatic* groundPlane = PxCreatePlane(*mPhysics, PxPlane(PxVec3(0, -3, 0), PxVec3(0,1,0)), *mMaterial);
	mScene->addActor(*groundPlane);
	return groundPlane;
}

PxRigidBody* PhysicsManager::createBlock()
{
	PxShape* shape = mPhysics->createShape(PxBoxGeometry(2.0f, 2.0f, 2.0f), *mMaterial);
	
	PxTransform localTm(PxVec3(0., 0., 0.) * 2.0f);
	PxRigidDynamic* body = mPhysics->createRigidDynamic(localTm);
	body->attachShape(*shape);
	body->setLinearDamping(1.0f);
	body->setAngularDamping(1.0f);
	PxRigidBodyExt::updateMassAndInertia(*body, 1.0f);
	mScene->addActor(*body);
	shape->release();
	return body;
}

void PhysicsManager::stepPhysics()
{
	PX_UNUSED(false);
	mScene->simulate(1.0f / 60.0f);
	mScene->fetchResults(true);
}