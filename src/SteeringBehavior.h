#pragma once
#include "Agent.h"
#include "Vector2D.h"

class Agent;

class SteeringBehavior{
	public:
		SteeringBehavior();
		~SteeringBehavior();
		Vector2D KinematicSeek(Agent *agent, Vector2D target, float dtime);
		Vector2D KinematicSeek(Agent *agent, Agent *target, float dtime);
		Vector2D KinematicFlee(Agent *agent, Vector2D target, float dtime);
		Vector2D KinematicFlee(Agent *agent, Agent *target, float dtime);

		//Seek & Flee Behaviors
		Vector2D Seek(Agent *agent, Vector2D target, float dtime);
		Vector2D Seek(Agent *agent, Agent *target, float dtime);
		Vector2D Flee(Agent *agent, Vector2D target, float dtime);
		Vector2D Flee(Agent *agent, Agent *target, float dtime);

		//Arrive Behavior
		Vector2D Arrive(Agent *agent, Vector2D target, float radius, float dtime);
		Vector2D Arrive(Agent *agent, Agent *target, float radius, float dtime);

		//Pursue & Evade Behaviors
		Vector2D Pursue(Agent *agent, Agent *target, float dtime);
		Vector2D Evade(Agent *agent, Agent *target, float dtime);

		//Wander Behavior
		Vector2D Wander(Agent *agent, float angle, float *wanderAngle, int wanderMaxChange, int wanderCircleOffset, int wanderCircleRadius, float dtime);

};
