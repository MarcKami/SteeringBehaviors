#include "SceneWander.h"

using namespace std;

SceneWander::SceneWander()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(640, 360));
	agent->setMass(0.035);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	wanderMaxChange = 90;
	wanderCircleOffset = 200;
	wanderCircleRadius = 60;
	wanderAngle = 0.0f;
	wanderCircleCenter = {};
	wanderDisplacementVector = {};
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
	Vector2D position = agents[0]->getPosition();
	float angle = (float)(atan2(position.y, position.x) * RAD2DEG);

	wanderCircleCenter = { position.x + wanderCircleOffset*cos(angle), position.y + wanderCircleOffset*sin(angle) };
	wanderDisplacementVector = { wanderCircleCenter.x + wanderCircleRadius*cos(wanderAngle), wanderCircleCenter.y + wanderCircleRadius*sin(wanderAngle) };
	

	Vector2D steering_force = agents[0]->Behavior()->Wander(agents[0], angle, &wanderAngle, wanderMaxChange,
		wanderCircleOffset, wanderCircleRadius, dtime);
	agents[0]->update(steering_force, dtime, event);
}

void SceneWander::draw()
{
	Vector2D position = agents[0]->getPosition();
	draw_circle(TheApp::Instance()->getRenderer(), (int)wanderCircleCenter.x, (int)wanderCircleCenter.y, wanderCircleRadius, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)wanderDisplacementVector.x, (int)wanderDisplacementVector.y, 5, 0, 255, 0, 125);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(wanderDisplacementVector.x), (int)(wanderDisplacementVector.y));
	agents[0]->draw();
}

const char* SceneWander::getTitle()
{
	return "SDL Steering Behaviors :: Wander Demo";
}