#include "SceneEvade.h"

using namespace std;

SceneEvade::SceneEvade() {
	Agent *agent = new Agent;
	agent->setTarget(Vector2D(100, 100));
	agent->setMass(0.3f);
	agent->setColor(0,0,255,255);
	agent->loadSpriteTexture("../res/isaac2.png", 3);
	agent->setRotate(false);
	agent->setSlow(true);
	agents.push_back(agent);
	agent = new Agent();
	agent->setPosition(Vector2D(600,50));
	agent->setTarget(Vector2D(900, 650));
	agent->loadSpriteTexture("../res/ghost2.png", 4);
	agent->setRotate(false);
	agent->setSlow(true);
	agents.push_back(agent); 
	target = Vector2D(900, 650);
	border = 75;
	window = { 1280, 768 };
}

SceneEvade::~SceneEvade() {
	for (int i = 0; i < (int)agents.size(); i++) {
		delete agents[i];
	}
}

void SceneEvade::update(float dtime, SDL_Event *event) {
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT) {
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[1]->setTarget(target);
		}
		break;
	default:
		break;
	}

	agents[0]->setTarget(agents[1]->getPosition());
	Vector2D steering_force = agents[1]->Behavior()->Arrive(agents[1], agents[1]->getTarget(), window, border, 200, dtime);
	agents[1]->update(steering_force, dtime, event);
	steering_force = agents[0]->Behavior()->Evade(agents[0], agents[1], window, border, dtime);
	agents[0]->update(steering_force, dtime, event);
}

void SceneEvade::draw() {
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	for (int i = 0; i < (int)agents.size(); i++) {
		agents[i]->draw();
	}
}

const char* SceneEvade::getTitle() {
	return "SDL Steering Behaviors :: Flee and Evade Demo";
}