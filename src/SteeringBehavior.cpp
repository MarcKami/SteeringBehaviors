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

//Perimeter Avoidance
Vector2D SteeringBehavior::PerimeterAvoidance(Agent *agent, Vector2D steering, Vector2D window, int border) {

	if (agent->position.x < border)
		steering.x = agent->max_velocity;
	else if (agent->position.x > window.x - border)
		steering.x = -agent->max_velocity;
	if (agent->position.y < border - 30)
		steering.y = agent->max_velocity;
	else if (agent->position.y > window.y - (border + 30))
		steering.y = -agent->max_velocity;

	return steering;
}

//Seek & Flee Behaviors
Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, Vector2D window, int border, float dtime)
{
	Vector2D steering = target - agent->position;
	steering.Normalize();
	steering *= agent->max_velocity;
	steering = PerimeterAvoidance(agent, steering, window, border);
	Vector2D steeringForce = (steering - agent->velocity);
	steeringForce /= agent->max_velocity;

	return steeringForce * agent->max_force;
}

Vector2D SteeringBehavior::Seek(Agent *agent, Agent *target, Vector2D window, int border, float dtime)
{
	return Seek(agent, target->position, window, border, dtime);
}

Vector2D SteeringBehavior::Flee(Agent *agent, Vector2D target, Vector2D window, int border, float dtime)
{
	Vector2D steering = agent->position - target;
	steering.Normalize();
	steering *= agent->max_velocity;
	steering = PerimeterAvoidance(agent, steering, window, border);
	Vector2D steeringForce = (steering - agent->velocity);
	steeringForce /= agent->max_velocity;

	return steeringForce * agent->max_force;
}

Vector2D SteeringBehavior::Flee(Agent *agent, Agent *target, Vector2D window, int border, float dtime)
{
	return Flee(agent, target->position, window, border, dtime);
}


//Arrive Behavior
Vector2D SteeringBehavior::Arrive(Agent *agent, Vector2D target, Vector2D window, int border, float radius, float dtime)
{
	Vector2D steering = target - agent->position;
	Vector2D distance = steering;
	float factor = distance.Length() / radius;
	steering.Normalize();
	if (distance.Length() > radius) {
		steering *= agent->max_velocity;
		steering = PerimeterAvoidance(agent, steering, window, border);
		Vector2D steeringForce = (steering - agent->velocity);
		steeringForce /= agent->max_velocity;

		return steeringForce * agent->max_force;
	}
	else if (distance.Length() < radius && distance.Length() > 10){
		steering *= (agent->max_velocity * factor);
		steering = PerimeterAvoidance(agent, steering, window, border);
		Vector2D steeringForce = (steering - agent->velocity);
		steeringForce /= (agent->max_velocity * factor);

		return steeringForce * agent->max_force;
	}
	else {
		agent->setVelocity({ 0,0 });
		Vector2D steeringForce = { 0,0 };
		return steeringForce;
	}
}

Vector2D SteeringBehavior::Arrive(Agent *agent, Agent *target, Vector2D window, int border, float radius, float dtime)
{
	return Arrive(agent, target->position, window, border, radius, dtime);
}


//Pursue & Evade Behaviors
Vector2D SteeringBehavior::Pursue(Agent *agent, Agent *target, Vector2D window, int border, float dtime)
{
	Vector2D steering = target->position - agent->position;
	Vector2D distance = steering;
	steering.Normalize();
	steering *= agent->max_velocity;
	float myT = distance.Length() / steering.Length();
	Vector2D predictedSteering = target->position + target->velocity * myT;

	return Seek(agent, predictedSteering, window, border, dtime);
}

Vector2D SteeringBehavior::Evade(Agent *agent, Agent *target, Vector2D window, int border, float dtime)
{
	Vector2D steering = target->position - agent->position;
	Vector2D distance = steering;
	steering.Normalize();
	steering *= agent->max_velocity;
	float myT = distance.Length() / steering.Length();
	Vector2D predictedSteering = target->position + target->velocity * myT;

	return Flee(agent, predictedSteering, window, border, dtime);
}

//Wander Behavior
Vector2D SteeringBehavior::Wander(Agent *agent, Vector2D window, int border, float angle, float *wanderAngle, int wanderMaxChange, int wanderCircleOffset, int wanderCircleRadius, float dtime) {
	Vector2D wanderCircleCenter = { agent->position.x + wanderCircleOffset*cos(angle * DEG2RAD), agent->position.y + wanderCircleOffset*sin(angle * DEG2RAD) };
	*wanderAngle += (rand() % (wanderMaxChange * 2) - wanderMaxChange);
	Vector2D randomSteering = { wanderCircleCenter.x + wanderCircleRadius*cos((*wanderAngle) * DEG2RAD), wanderCircleCenter.y + wanderCircleRadius*sin((*wanderAngle) * DEG2RAD) };

	return Seek(agent, randomSteering, window, border, dtime);
}

//Path Following Behavior
Vector2D SteeringBehavior::PathFollow(Agent *agent, Path path, Vector2D window, int border, float dtime) {
	if (Vector2D().Distance(agent->position, path.pathArray[agent->currentTargetIndex]) < path.arrivalDistance) {
		agent->setIndex(agent->currentTargetIndex + agent->pathDir);

		if (agent->currentTargetIndex >= 5 || agent->currentTargetIndex < 0) {
			agent->setPathDir(agent->pathDir * -1);
			agent->setIndex(agent->currentTargetIndex + agent->pathDir);
		}
	}

	return Arrive(agent, path.pathArray[agent->currentTargetIndex], window, border, 50, dtime);
}

//Flocking Behavior
Vector2D SteeringBehavior::FlockingFlee(Agent *agent, std::vector<Agent*> target) {
	int neighborCount = 0;
	Vector2D separationVector = {};
	for (int i = 0; i < (int)target.size(); i++){
		if (Vector2D().Distance(agent->position, target[i]->position) < agent->neighborRadius) {
			separationVector += (agent->position - target[i]->position);
			++neighborCount;
		}
	}
	separationVector /= neighborCount;
	return Vector2D().Normalize(separationVector);
}

Vector2D SteeringBehavior::FlockingSeek(Agent *agent, std::vector<Agent*> target) {
	int neighborCount = 0;
	Vector2D averageVector = {};
	for (int i = 0; i < (int)target.size(); i++) {
		if (Vector2D().Distance(agent->position, target[i]->position) < agent->neighborRadius) {
			averageVector += target[i]->position;
			++neighborCount;
		}
	}
	averageVector /= neighborCount;
	averageVector -= agent->position;
	return Vector2D().Normalize(averageVector);
}

Vector2D SteeringBehavior::FlockingAlignment(Agent *agent, std::vector<Agent*> target) {
	int neighborCount = 0;
	Vector2D averageVelocity = {};
	for (int i = 0; i < (int)target.size(); i++) {
		if (Vector2D().Distance(agent->position, target[i]->position) < agent->neighborRadius) {
			averageVelocity += target[i]->velocity;
			++neighborCount;
		}
	}
	averageVelocity /= neighborCount;
	return Vector2D().Normalize(averageVelocity);
}

Vector2D SteeringBehavior::Flocking(Agent *agent, std::vector<Agent*> target, float kFlee, float kSeek, float kAligment, float kMaxFlocking, Vector2D window, int border, float dtime) {
	Vector2D separationDirection = FlockingFlee(agent, target);
	Vector2D cohesionDirection = FlockingSeek(agent, target);
	Vector2D alignmentDirection = FlockingAlignment(agent, target);

	Vector2D flockingForce = separationDirection * kFlee + cohesionDirection * kSeek + alignmentDirection * kAligment;
	return flockingForce * kMaxFlocking;
}



