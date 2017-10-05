#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "Target.h"

class SceneArrive :
	public Scene
{
public:
	SceneArrive();
	~SceneArrive();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	std::vector<Target*> targets;
	Vector2D target;
	bool draw_vector;
	bool reached;
	int border;
	Vector2D window;
};

