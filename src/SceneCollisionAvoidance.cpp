#include "SceneCollisionAvoidance.h"

using namespace std;

SceneCollisionAvoidance::SceneCollisionAvoidance(){
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/isaac.png", 3);
	agent->setRotate(false);
	agents.push_back(agent);

	Target *target = new Target;
	target->loadSpriteTexture("../res/coin.png", 1);
	targets.push_back(target);

	Target *obstacle = new Target;
	obstacle->setPosition(Vector2D(800, 250));
	obstacle->loadSpriteTexture("../res/obstacle.png", 6);
	obstacles.push_back(obstacle);
	obstacle = new Target();
	obstacle->setPosition(Vector2D(500, 250));
	obstacle->loadSpriteTexture("../res/obstacle.png", 6);
	obstacles.push_back(obstacle);
	obstacle = new Target();
	obstacle->setPosition(Vector2D(800, 450));
	obstacle->loadSpriteTexture("../res/obstacle.png", 6);
	obstacles.push_back(obstacle);
	obstacle = new Target();
	obstacle->setPosition(Vector2D(500, 450));
	obstacle->loadSpriteTexture("../res/obstacle.png", 6);
	obstacles.push_back(obstacle);

	reached = false;
	border = 75;
	window = { 1280, 768 };
}

SceneCollisionAvoidance::~SceneCollisionAvoidance(){
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	for (int i = 0; i < (int)targets.size(); i++)
	{
		delete targets[i];
	}
	for (int i = 0; i < (int)obstacles.size(); i++)
	{
		delete obstacles[i];
	}
}

void SceneCollisionAvoidance::update(float dtime, SDL_Event *event){
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

	Vector2D steering_force = agents[0]->Behavior()->Arrive(agents[0], agents[0]->getTarget(), window, border, 200, dtime);
	Vector2D avoidance_force = agents[0]->Behavior()->CollisionAvoidance(agents[0], obstacles, window, border, dtime);
	steering_force += avoidance_force;
	agents[0]->update(steering_force, dtime, event);

	targets[0]->update(dtime, event); 
	for (int i = 0; i < (int)obstacles.size(); i++){
		obstacles[i]->update(dtime, event);
	}
	if (Vector2D().Distance(agents[0]->getPosition(), targets[0]->getPosition()) < 20.0f) reached = true;
}

void SceneCollisionAvoidance::draw(){
	if (!reached) {
		targets[0]->draw();
	}
	agents[0]->draw();
	for (int i = 0; i < (int)obstacles.size(); i++) {
		obstacles[i]->draw();
	}

}

const char* SceneCollisionAvoidance::getTitle(){
	return "SDL Steering Behaviors :: Collision Avoidance Demo";
}