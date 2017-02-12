#include "Hook.h"

using namespace physx;

Hook::Hook(std::string model_fname, std::string tex_fname, PxRigidBody* actor, PhysicsManager* physicsManager, ProtoCar* parentCar) :
	PhysicsObject(model_fname, tex_fname, actor, physicsManager) {
	//Record the angle of shot?
    actor->userData = this;
	actor->setName("Hook");
    mParentCar = parentCar;
    mStuck = false;

}

void Hook::applyGlobalForce(glm::vec3 direction, double magnitude) {
	PxVec3 physVec(direction.x, direction.y, direction.z);
	PxRigidBodyExt::addForceAtLocalPos(*mActor, physVec * magnitude, PxVec3(0, 0, 0));
}

void Hook::applyLocalForce(float forward, float right, float up) {
	PxVec3 physVec(forward, up, right);
	PxRigidBodyExt::addLocalForceAtLocalPos(*mActor, physVec, PxVec3(0, 0, 0));
}

void Hook::update() {
	updatePosandRot();
}