#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "Target.h"

class SceneFlocking :
	public Scene
{
public:
	SceneFlocking();
	~SceneFlocking();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Agent leader;
	Vector2D target;
	int border;
	Vector2D window;
	float kFlee;
	float kSeek;
	float kAlignment;
	float kMaxForce;
};
