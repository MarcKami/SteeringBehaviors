#include "SceneFlocking.h"

using namespace std;

SceneFlocking::SceneFlocking()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(100, 100));
	agent->loadSpriteTexture("../res/poo.png", 3);
	agent->setRotate(false);
	agent->setSlow(true);
	agents.push_back(agent);
	agent = new Agent();
	agent->setPosition(Vector2D(600, 400));
	agent->setTarget(Vector2D(100, 100));
	agent->loadSpriteTexture("../res/poo.png", 3);
	agent->setRotate(false);
	agent->setSlow(true);
	agents.push_back(agent);
	agent = new Agent();
	agent->setPosition(Vector2D(600, 320));
	agent->setTarget(Vector2D(100, 100));
	agent->loadSpriteTexture("../res/poo.png", 3);
	agent->setRotate(false);
	agent->setSlow(true);
	agents.push_back(agent);
	target = Vector2D(640, 360);

	kFlee = 1.0f;
	kSeek = 0.3f;
	kAlignment = 0.2f;
	kMaxForce = 100;
	border = 75;
	window = { 1280, 768 };
}

SceneFlocking::~SceneFlocking()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneFlocking::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			for (int i = 0; i < (int)agents.size(); i++) {
				agents[i]->setTarget(target);
			}
		}
		break;
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_KP_PLUS){
			Agent *agent = new Agent;
			agent->setPosition(Vector2D(600, 400));
			agent->setTarget(target);
			agent->loadSpriteTexture("../res/poo.png", 3);
			agent->setRotate(false);
			agent->setSlow(true);
			agents.push_back(agent);
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_KP_MINUS) {
			agents.pop_back();
		}
		break;
	default:
		break;
	}

	for (int i = 0; i < (int)agents.size(); i++){
		Vector2D steering_force = agents[i]->Behavior()->Arrive(agents[i], agents[i]->getTarget(), window, border, 100.0f, dtime);
		Vector2D flocking_force = agents[i]->Behavior()->Flocking(agents[i], agents, kFlee, kSeek, kAlignment, kMaxForce, window, border, dtime);
		steering_force += flocking_force;
		agents[i]->update(steering_force, dtime, event);
	}
	
	//Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], agents[0]->getTarget(), window, border, dtime);
	//agents[0]->update(steering_force, dtime, event);
}

void SceneFlocking::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	for (int i = 0; i < (int)agents.size(); i++) {
		agents[i]->draw();
	}
}

const char* SceneFlocking::getTitle()
{
	return "SDL Steering Behaviors :: Seek & Flocking Demo";
}