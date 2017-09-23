#include "SteeringBehavior.h"



SteeringBehavior::SteeringBehavior()
{
}

SteeringBehavior::~SteeringBehavior()
{
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = target - agent->position;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Agent *target, float dtime)
{
	return KinematicSeek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = agent->position - target;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Agent *target, float dtime)
{
	return KinematicFlee(agent, target->position, dtime);
}


//Seek & Flee Behaviors
Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = target - agent->position;
	steering.Normalize();
	steering *= agent->max_velocity;
	Vector2D steeringForce = (steering - agent->velocity);
	steeringForce /= agent->max_velocity;
	return steeringForce * agent->max_force;
}

Vector2D SteeringBehavior::Seek(Agent *agent, Agent *target, float dtime)
{
	return Seek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::Flee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = agent->position - target;
	steering.Normalize();
	steering *= agent->max_velocity;
	Vector2D steeringForce = (steering - agent->velocity);
	steeringForce /= agent->max_velocity;
	return steeringForce * agent->max_force;
}

Vector2D SteeringBehavior::Flee(Agent *agent, Agent *target, float dtime)
{
	return Flee(agent, target->position, dtime);
}


//Arrive Behavior
Vector2D SteeringBehavior::Arrive(Agent *agent, Vector2D target, float radius, float dtime)
{
	Vector2D steering = target - agent->position;
	Vector2D distance = steering;
	float factor = distance.Length() / radius;
	steering.Normalize();
	if (distance.Length() > radius) {
		steering *= agent->max_velocity;
		Vector2D steeringForce = (steering - agent->velocity);
		steeringForce /= agent->max_velocity;
		return steeringForce * agent->max_force;
	}
	else {
		steering *= (agent->max_velocity * factor);
		Vector2D steeringForce = (steering - agent->velocity);
		steeringForce /= (agent->max_velocity * factor);
		return steeringForce * agent->max_force;
	}
}

Vector2D SteeringBehavior::Arrive(Agent *agent, Agent *target, float radius, float dtime)
{
	return Arrive(agent, target->position, radius, dtime);
}


//Pursue & Evade Behaviors
Vector2D SteeringBehavior::Pursue(Agent *agent, Agent *target, float dtime)
{
	Vector2D steering = target->position - agent->position;
	Vector2D distance = steering;
	steering.Normalize();
	steering *= agent->max_velocity;
	float myT = distance.Length() / steering.Length();
	Vector2D predictedSteering = target->position + target->velocity * myT;
	return Seek(agent, predictedSteering, dtime);
}

Vector2D SteeringBehavior::Evade(Agent *agent, Agent *target, float dtime)
{
	Vector2D steering = target->position - agent->position;
	Vector2D distance = steering;
	steering.Normalize();
	steering *= agent->max_velocity;
	float myT = distance.Length() / steering.Length();
	Vector2D predictedSteering = target->position + target->velocity * myT;
	return Flee(agent, predictedSteering, dtime);
}

//Wander Behavior
Vector2D SteeringBehavior::Wander(Agent *agent, float angle, float *wanderAngle, int wanderMaxChange, int wanderCircleOffset, int wanderCircleRadius, float dtime) {
	Vector2D wanderCircleCenter = { agent->position.x + wanderCircleOffset*cos(angle), agent->position.y + wanderCircleOffset*sin(angle) };
	*wanderAngle += (rand()) / static_cast <float> (RAND_MAX) * wanderMaxChange;
	Vector2D randomSteering = { wanderCircleCenter.x + wanderCircleRadius*cos(*wanderAngle), wanderCircleCenter.y + wanderCircleRadius*sin(*wanderAngle) };

	return Seek(agent, randomSteering, dtime);
}
