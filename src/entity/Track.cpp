#include "Track.h"

Track::Track(std::string model_fname, std::string tex_fname, glm::vec3 scale, PhysicsManager* physicsManager, PxU32 filterdata, PxU32 filterdataagainst) :
    StaticPhysicsObject(model_fname, tex_fname, scale, physicsManager, filterdata, filterdataagainst)
{
    mActor->setName("track");
   // renderable = false;
}