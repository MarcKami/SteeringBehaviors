#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "Target.h"

class SceneCollisionAvoidance :
	public Scene
{
public:
	SceneCollisionAvoidance();
	~SceneCollisionAvoidance();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	std::vector<Target*> obstacles;
	std::vector<Target*> targets;
	bool reached;
	int border;
	Vector2D window;
};

