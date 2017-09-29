#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"
#include "SteeringBehavior.h"


class Agent
{
	friend class SteeringBehavior;

private:
	SteeringBehavior *steering_behavior;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;
	int currentTargetIndex;
	int pathDir;
	int neighborRadius;
	float wanderAngle;
	Vector2D wanderCircleCenter;
	Vector2D wanderDisplacementVector;

	SDL_Color color;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;
	bool rotate;
	bool slow;

public:
	Agent();
	~Agent();
	SteeringBehavior *Behavior();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	Vector2D getWanderCircleCenter();
	Vector2D getWanderDisplacement();
	float getWanderAngle();
	float getMaxVelocity();
	int getIndex();
	void setRotate(bool rot);
	void setSlow(bool slo);
	void setIndex(int index);
	void setPathDir(int dir);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void setWanderCircleCenter(Vector2D center);
	void setWanderDisplacement(Vector2D displacement);
	void setWanderAngle(float wAngle);
	void setMass(float mass);
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void update(Vector2D steering_force, float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	
};
