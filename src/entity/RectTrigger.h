#pragma once
#include "StaticPhysicsObject.h"

class RectTrigger : public StaticPhysicsObject {
protected:
    bool triggered = false;

public:
    RectTrigger(PhysicsManager* physicsManager, std::string texName, float x_width, float y_width, float z_width, bool renderable = false);
};