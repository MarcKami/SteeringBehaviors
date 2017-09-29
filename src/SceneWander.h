#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneWander :
	public Scene
{
public:
	SceneWander();
	~SceneWander();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
	int border;
	Vector2D window;
	bool draw_vector;

	//Wander Fields
	int wanderMaxChange;
	int wanderCircleOffset;
	int wanderCircleRadius;
};

