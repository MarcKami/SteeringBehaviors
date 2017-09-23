#include "SceneWander.h"

using namespace std;

SceneWander::SceneWander()
{
	Agent *agent = new Agent;/*
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->setMass(0.035);
	agent->loadSpriteTexture("../res/Fly.png", 2);
	agents.push_back(agent);*/
	for (int i = 0; i < 10; i++) {
		agent = new Agent();
		agent->setPosition(Vector2D(640, 360));
		agent->setTarget(Vector2D(640, 360));
		agent->setMass(0.035);
		agent->loadSpriteTexture("../res/Fly.png", 2);
		agents.push_back(agent);
	}
	wanderMaxChange = 20;
	wanderCircleOffset = 250;
	wanderCircleRadius = 100;
	wanderAngle[10] = { 0.0f };
	wanderCircleCenter[10] = {};
	wanderDisplacementVector[10] = {};
}

SceneWander::~SceneWander()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneWander::update(float dtime, SDL_Event *event)
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
	for (int i = 0; i < 10; i++) {
		Vector2D velocity = agents[i]->getVelocity();
		Vector2D position = agents[i]->getPosition();
		float angle = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);

		//Calculations for the future draw of vectors and circles
		wanderCircleCenter[i] = { position.x + wanderCircleOffset*cos(angle*DEG2RAD), position.y + wanderCircleOffset*sin(angle*DEG2RAD) };
		wanderDisplacementVector[i] = { wanderCircleCenter[i].x + wanderCircleRadius*cos(wanderAngle[i]*DEG2RAD), wanderCircleCenter[i].y + wanderCircleRadius*sin(wanderAngle[i]*DEG2RAD) };


		Vector2D steering_force = agents[i]->Behavior()->Wander(agents[i], angle, &wanderAngle[i], wanderMaxChange,
			wanderCircleOffset, wanderCircleRadius, dtime);
		agents[i]->update(steering_force, dtime, event);
	}
}

void SceneWander::draw()
{
	for (int i = 0; i < 10; i++) {
		if (agents[i]->getDrawVector()) {
			Vector2D position = agents[i]->getPosition();
			draw_circle(TheApp::Instance()->getRenderer(), (int)wanderCircleCenter[i].x, (int)wanderCircleCenter[i].y, wanderCircleRadius, 255, 0, 0, 255);
			draw_circle(TheApp::Instance()->getRenderer(), (int)wanderDisplacementVector[i].x, (int)wanderDisplacementVector[i].y, 5, 0, 255, 0, 125);
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(wanderDisplacementVector[i].x), (int)(wanderDisplacementVector[i].y));
		}
		agents[i]->draw();
	}
}

const char* SceneWander::getTitle()
{
	return "SDL Steering Behaviors :: Wander Demo";
}