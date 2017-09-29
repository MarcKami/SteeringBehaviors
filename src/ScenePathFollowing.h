#pragma once
#include <vector>
#include "Scene.h"
#include "SteeringBehavior.h"


class ScenePathFollowing :
	public Scene
{
public:
	ScenePathFollowing();
	~ScenePathFollowing();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
	Path myPath;
};
