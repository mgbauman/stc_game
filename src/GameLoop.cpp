#include <iostream>

#include "renderer/Window.h"
#include "renderer\GLUtil.h"

#include "input/input.h"
#include "physics/PhysicsManager.h"
#include "entity/Entity.h"
#include "entity/Renderable.h"
#include "entity/PhysicsObject.h"

using namespace std;

int main(int argc, const char* argv[])
{
	std::cout << argv[0] << std::endl;
    Window * myWindow = new Window();

	//exit(0);
//	Renderer* myRenderer = new Renderer(0);
	// Input* myInput = new Input();
	PhysicsManager* myPhysics = new PhysicsManager();
	// Sound* mySound = new Sound();
	// OpponentAI* myAI = new OpponentAI();

//	myRenderer->initRenderer();
	Input *input = new Input(0);

    // TODO: convert these to unique_ptrs
    std::vector<Entity*> entities(0);
    entities.push_back(new PhysicsObject("assets/models/Crate/Crate1.obj", "assets/models/Crate/crate_1.jpg", myPhysics->createBlock()));

    // Teapot test obj
    //Renderable *teapot = new Renderable("assets/models/teapot/teapot.obj", "assets/models/teapot/teapot_tex.png");
    //teapot->scale(0.5, 0.5, 0.5);
    //entities.push_back(teapot);

    Renderable* plane = new Renderable("assets/models/plane/plane.obj", "assets/models/plane/logo_tile.png");
    plane->setPos(0, -2, 0);
    entities.push_back(plane);

    myPhysics->createGroundPlane();

	while (!myWindow->shouldClose())
	{
		// myInput->getState();
		// myAI->getState();
		myPhysics->stepPhysics();
		dynamic_cast<PhysicsObject*>(entities.front())->updatePos(); // We'll eventually have a function here that updates all positions

		// mySound->updateSound();
		myWindow->draw(entities);
		input->Update();
		//std::cout << "LS_X: " << input->LeftStick_X() << "  LS_Y: " << input->LeftStick_Y() << "  RS_X: " << input->RightStick_X() << "  RS_Y: " << input->RightStick_Y() << std::endl;
	}
	
	delete myWindow;
    delete input;
	delete myPhysics;
	return 0;
}