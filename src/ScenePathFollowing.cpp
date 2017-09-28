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
	if (agents[0]->getPosition().Distance(agents[0]->getPosition(), myPath.pathArray[agents[0]->getIndex()]) < myPath.arrivalDistance) {
		agents[0]->setIndex(agents[0]->getIndex() + 1);
	}
	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], myPath.pathArray[agents[0]->getIndex()], dtime);
	agents[0]->update(steering_force, dtime, event);
}

void ScenePathFollowing::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
}

const char* ScenePathFollowing::getTitle()
{
	return "SDL Steering Behaviors :: Path Following Demo";
}