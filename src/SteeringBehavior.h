#pragma once
#include <vector>
#include "Agent.h"
#include "Target.h"
#include "Vector2D.h"

struct Path {
	Vector2D pathArray[5];
	float arrivalDistance;
	Vector2D GetPosition(float param) {
		int index = trunc(param * 4);
		double decimal = (param * 4) - index;
		//For take only 1 decimals(put more 0 to take more decimals)
		int temp = 10 * decimal;
		if (index < 4) {
			Vector2D position = pathArray[index] + (((pathArray[index + 1] - pathArray[index]) / 10) * temp);
			return position;
		}
		else {
			return pathArray[index];
		}
	}

	float GetParam(Vector2D position) {
		//Augment the array if the path have more points
		float distance[5];
		int nearest = 0;
		int nearest2 = 1;
		float maxDistance = INT_MAX;
		for (int i = 0; i < 5; i++) {
			distance[i] = Vector2D::Distance(position, pathArray[i]);

			if (distance[i] < maxDistance) {
				nearest2 = nearest;
				nearest = i;
				maxDistance = distance[i];
			}
		}
		if (abs(nearest - nearest2) == 1) {
			Vector2D nPositions[10];
			float nDistances[10];
			int near = 0;
			float nMaxDistance = INT_MAX;
			for (int i = 0; i < 10; i++) {
				nPositions[i] = pathArray[nearest] + (((pathArray[nearest2] - pathArray[nearest]) / 10) * i);
				nDistances[i] = Vector2D::Distance(position, nPositions[i]);
				if (nDistances[i] < nMaxDistance) {
					near = i;
					nMaxDistance = nDistances[i];
				}
			}

			float myNear = near*1.0 / 10;
			myNear += nearest;
			return myNear;
		}
		else {
			return (float)nearest;
		}
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
