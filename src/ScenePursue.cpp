#include "ScenePursue.h"

using namespace std;

ScenePursue::ScenePursue() {
	Agent *agent = new Agent;
	agent->setTarget(Vector2D(100, 100));
	agent->setMass(0.6f);
	agent->setColor(0,0,255,255);
	agent->loadSpriteTexture("../res/ghost2.png", 4);
	agent->setRotate(false);
	agent->setSlow(true);
	agents.push_back(agent);
	agent = new Agent();
	agent->setPosition(Vector2D(600,50));
	agent->setTarget(Vector2D(900, 650));
	agent->loadSpriteTexture("../res/isaac.png", 3);
	agent->setRotate(false);
	agents.push_back(agent); 
	target = Vector2D(900, 650);
	border = 75;
	window = { 1280, 768 };
}

ScenePursue::~ScenePursue() {
	for (int i = 0; i < (int)agents.size(); i++) {
		delete agents[i];
	}
}

void ScenePursue::update(float dtime, SDL_Event *event) {
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
	steering_force = agents[0]->Behavior()->Pursue(agents[0], agents[1], window, border, dtime);
	agents[0]->update(steering_force, dtime, event);
}

void ScenePursue::draw() {
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	for (int i = 0; i < (int)agents.size(); i++) {
		agents[i]->draw();
	}
}

const char* ScenePursue::getTitle() {
	return "SDL Steering Behaviors :: Seek and Pursue Demo";
}