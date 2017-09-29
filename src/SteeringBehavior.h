#pragma once
#include "Agent.h"
#include "Vector2D.h"

struct Path {
	Vector2D pathArray[5];
	float arrivalDistance;
};

class Agent;

class SteeringBehavior{
	public:
		SteeringBehavior();
		~SteeringBehavior();
		Vector2D KinematicSeek(Agent *agent, Vector2D target, float dtime);
		Vector2D KinematicSeek(Agent *agent, Agent *target, float dtime);
		Vector2D KinematicFlee(Agent *agent, Vector2D target, float dtime);
		Vector2D KinematicFlee(Agent *agent, Agent *target, float dtime);

		//Perimeter Avoidance
		Vector2D PerimeterAvoidance(Agent *agent, Vector2D steering, Vector2D window, int border);

		//Seek & Flee Behaviors
		Vector2D Seek(Agent *agent, Vector2D target, Vector2D window, int border, float dtime);
		Vector2D Seek(Agent *agent, Agent *target, Vector2D window, int border, float dtime);
		Vector2D Flee(Agent *agent, Vector2D target, Vector2D window, int border, float dtime);
		Vector2D Flee(Agent *agent, Agent *target, Vector2D window, int border, float dtime);

		//Arrive Behavior
		Vector2D Arrive(Agent *agent, Vector2D target, Vector2D window, int border, float radius, float dtime);
		Vector2D Arrive(Agent *agent, Agent *target, Vector2D window, int border, float radius, float dtime);

		//Pursue & Evade Behaviors
		Vector2D Pursue(Agent *agent, Agent *target, Vector2D window, int border, float dtime);
		Vector2D Evade(Agent *agent, Agent *target, Vector2D window, int border, float dtime);

		//Wander Behavior
		Vector2D Wander(Agent *agent, Vector2D window, int border, float angle, float *wanderAngle, int wanderMaxChange, int wanderCircleOffset, int wanderCircleRadius, float dtime);

		//Path Following
		Vector2D PathFollow(Agent *agent, Path path, Vector2D window, int border, float dtime);


};
