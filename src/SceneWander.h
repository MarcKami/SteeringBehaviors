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
public:
	// Wander fields
	int wanderMaxChange = 90;
	int wanderCircleOffset = 250;
	int wanderCircleRadius = 100;
	float wanderAngle[10] = { 0.0f };
	Vector2D wanderCircleCenter[10] = {};
	Vector2D wanderDisplacementVector[10] = {};
};

