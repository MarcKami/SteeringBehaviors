#include "ScenePathFollowing.h"

using namespace std;


ScenePathFollowing::ScenePathFollowing()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/isaac.png", 3);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	//Path Definition
	myPath.arrivalDistance = 10.0f;
	myPath.pathArray[0] = {640, 360};
	myPath.pathArray[1] = {780, 360};
	myPath.pathArray[2] = {780, 600};
	myPath.pathArray[3] = {200, 600};
	myPath.pathArray[4] = {400, 100};
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
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}
		break;
	default:
		break;
	}
	Vector2D steering_force = agents[0]->Behavior()->PathFollow(agents[0], myPath, window, border, dtime);
	agents[0]->update(steering_force, dtime, event);
}

void ScenePathFollowing::draw()
{
	for (int i = 0; i < 5; i++){
		draw_circle(TheApp::Instance()->getRenderer(), (int)myPath.pathArray[i].x, (int)myPath.pathArray[i].y, 15, 255, 0, 0, 255);
	}
	agents[0]->draw();
}

const char* ScenePathFollowing::getTitle()
{
	return "SDL Steering Behaviors :: Path Following Demo";
}