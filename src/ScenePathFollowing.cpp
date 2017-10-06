#include "ScenePathFollowing.h"

using namespace std;


ScenePathFollowing::ScenePathFollowing()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 330));
	agent->setTarget(Vector2D(640, 330));
	agent->loadSpriteTexture("../res/lazarus.png", 3);
	agent->setRotate(false);
	agent->setSlow(true);
	agents.push_back(agent);

	//Path Definition
	myPath.arrivalDistance = 10.0f;
	myPath.pathArray[0] = {640, 330};
	myPath.pathArray[1] = {780, 330};
	myPath.pathArray[2] = {780, 570};
	myPath.pathArray[3] = {200, 570};
	myPath.pathArray[4] = {400, 70};

	draw_vector = false;
	border = 75;
	window = { 1280, 768 };
}

ScenePathFollowing::~ScenePathFollowing()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePathFollowing::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			agents[0]->setPosition(Vector2D((float)(event->button.x), (float)(event->button.y)));
		}
		break;
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_V)
			draw_vector = !draw_vector;
		break;
	default:
		break;
	}
	Vector2D steering_force = agents[0]->Behavior()->PathFollow(agents[0], myPath, window, border, dtime);
	agents[0]->update(steering_force, dtime, event);
}

void ScenePathFollowing::draw()
{
	if (draw_vector) {
		for (int i = 0; i < 5; i++) {
			draw_circle(TheApp::Instance()->getRenderer(), (int)myPath.pathArray[i].x, (int)myPath.pathArray[i].y + 20, 15, 255, 0, 0, 255);
		}
	}
	agents[0]->draw();
}

const char* ScenePathFollowing::getTitle()
{
	return "SDL Steering Behaviors :: Path Following Demo";
}