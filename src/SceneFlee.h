#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "Target.h"

class SceneFlee :
	public Scene
{
public:
	SceneFlee();
	~SceneFlee();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	std::vector<Target*> targets;
};

