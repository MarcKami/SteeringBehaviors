#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

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
	Vector2D target;
	int border;
	Vector2D window;
};

