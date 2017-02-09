#include "Hook.h"

Hook::Hook(std::string model_fname, std::string tex_fname, PxRigidBody* actor, float angle) :
	PhysicsObject(model_fname, tex_fname, actor) {
	//Record the angle of shot
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