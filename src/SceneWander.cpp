#include "SceneWander.h"

using namespace std;

SceneWander::SceneWander(){
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->setMass(0.035f);
	agent->loadSpriteTexture("../res/Fly.png", 2);
	agents.push_back(agent);
	agent = new Agent();
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->setMass(0.035f);
	agent->loadSpriteTexture("../res/Fly.png", 2);
	agents.push_back(agent);

	wanderMaxChange = 90;
	wanderCircleOffset = 300;
	wanderCircleRadius = 200;

	draw_vector = true;
	border = 75;
	window = { 1280, 768 };
}

SceneWander::~SceneWander(){
	for (int i = 0; i < (int)agents.size(); i++){
		delete agents[i];
	}
}

void SceneWander::update(float dtime, SDL_Event *event){
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		break;
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_KP_PLUS) {
			Agent *agent = new Agent;
			agent->setPosition(Vector2D(640, 360));
			agent->setTarget(Vector2D(640, 360));
			agent->setMass(0.035f);
			agent->loadSpriteTexture("../res/Fly.png", 2);
			agents.push_back(agent);
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_KP_MINUS) {
			agents.pop_back();
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_V)
			draw_vector = !draw_vector;
		break;
	default:
		break;
	}
	for (int i = 0; i < (int)agents.size(); i++) {
		Vector2D velocity = agents[i]->getVelocity();
		float angle = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);

		Vector2D steering_force = agents[i]->Behavior()->Wander(agents[i], window, border, angle, wanderMaxChange, wanderCircleOffset, wanderCircleRadius, dtime);
		agents[i]->update(steering_force, dtime, event);
	}
}

void SceneWander::draw()
{
	for (int i = 0; i < (int)agents.size(); i++) {
		if (draw_vector) {
			draw_circle(TheApp::Instance()->getRenderer(), (int)agents[i]->getWanderCircleCenter().x, (int)agents[i]->getWanderCircleCenter().y, wanderCircleRadius, 255, 0, 0, 255);
			draw_circle(TheApp::Instance()->getRenderer(), (int)agents[i]->getWanderDisplacement().x, (int)agents[i]->getWanderDisplacement().y, 5, 0, 255, 0, 125);
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)agents[i]->getPosition().x, (int)agents[i]->getPosition().y, (int)(agents[i]->getWanderDisplacement().x), (int)(agents[i]->getWanderDisplacement().y));
		}
		agents[i]->draw();
	}
}

const char* SceneWander::getTitle()
{
	return "SDL Steering Behaviors :: Wander Demo";
}