#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "Target.h"

class SceneSeek :
	public Scene
{
public:
	SceneSeek();
	~SceneSeek();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	std::vector<Target*> targets;
	bool reached;
	int border;
	Vector2D window;
};
