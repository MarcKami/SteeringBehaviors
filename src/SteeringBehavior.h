#pragma once
#include <vector>
#include "Agent.h"
#include "Target.h"
#include "Vector2D.h"

struct Path {
	Vector2D pathArray[5];
	float arrivalDistance;
	Vector2D GetPosition(int param) {
		return pathArray[param];
	}

	int GetParam(Vector2D position) {
		//Augment the array if the path have more points
		float distance[5];
		int nearest = 0;
		float maxDistance = (float)INT_MAX;
		for (int i = 0; i < 5; i++) {
			distance[i] = Vector2D::Distance(position, pathArray[i]);

			if (distance[i] < maxDistance) {
				nearest = i;
				maxDistance = distance[i];
			}
		}
		return nearest;
	}

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
		Vector2D Wander(Agent *agent, Vector2D window, int border, float angle, int wanderMaxChange, int wanderCircleOffset, int wanderCircleRadius, float dtime);

		//Path Following
		Vector2D PathFollow(Agent *agent, Path path, Vector2D window, int border, float dtime);

		//Flocking Behavior
		Vector2D FlockingFlee(Agent *agent, std::vector<Agent*> target);
		Vector2D FlockingSeek(Agent *agent, std::vector<Agent*> target);
		Vector2D FlockingAlignment(Agent *agent, std::vector<Agent*> target);
		Vector2D Flocking(Agent *agent, std::vector<Agent*> target, float kFlee, float kSeek, float kAligment, float kMaxFlocking, Vector2D window, int border, float dtime);

		//Collision Avoidance
		Vector2D CollisionAvoidance(Agent *agent, std::vector<Target*> obstacle, Vector2D window, int border, float dtime);


};
