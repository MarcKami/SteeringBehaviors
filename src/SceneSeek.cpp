#include "SceneSeek.h"

using namespace std;

SceneSeek::SceneSeek()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/isaac.png", 3);
	agent->setRotate(false);
	agents.push_back(agent);

	Target *target = new Target;
	target->loadSpriteTexture("../res/coin.png", 1);
	targets.push_back(target);

	reached = false;
	border = 75;
	window = { 1280, 768 };
}

SceneSeek::~SceneSeek()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	for (int i = 0; i < (int)targets.size(); i++)
	{
		delete targets[i];
	}
}

void SceneSeek::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			targets[0]->setPosition(Vector2D((float)(event->button.x), (float)(event->button.y)));
			reached = false;
			agents[0]->setTarget(targets[0]->getPosition());
		}
		break;
	default:
		break;
	}

	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], agents[0]->getTarget(), window, border, dtime);
	agents[0]->update(steering_force, dtime, event);
	targets[0]->update(dtime, event);
	if (Vector2D().Distance(agents[0]->getPosition(), targets[0]->getPosition()) < 20.0f) reached = true;
}

void SceneSeek::draw()
{
	if (!reached) {
	targets[0]->draw(); 
	}
	agents[0]->draw();
}

const char* SceneSeek::getTitle()
{
	return "SDL Steering Behaviors :: Seek Demo";
}