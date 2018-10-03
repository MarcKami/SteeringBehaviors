#include "SteeringBehavior.h"



SteeringBehavior::SteeringBehavior() {}

SteeringBehavior::~SteeringBehavior() {}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Vector2D target, float dtime) {
	Vector2D steering = target - agent->position;
	steering.Normalize();

	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Agent *target, float dtime) {
	return KinematicSeek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Vector2D target, float dtime) {
	Vector2D steering = agent->position - target;
	steering.Normalize();

	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Agent *target, float dtime) {
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
Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, Vector2D window, int border, float dtime) {
	if (Vector2D::Distance(target, agent->position) < 5) {
		agent->setVelocity({ 0,0 });
		Vector2D steeringForce = { 0,0 };
		return steeringForce;
	}
	else {
		Vector2D steering = target - agent->position;
		steering.Normalize();
		steering *= agent->max_velocity;
		steering = PerimeterAvoidance(agent, steering, window, border);
		Vector2D steeringForce = (steering - agent->velocity);
		steeringForce /= agent->max_velocity;

		return steeringForce * agent->max_force;
	}
}

Vector2D SteeringBehavior::Seek(Agent *agent, Agent *target, Vector2D window, int border, float dtime) {
	return Seek(agent, target->position, window, border, dtime);
}

Vector2D SteeringBehavior::Flee(Agent *agent, Vector2D target, Vector2D window, int border, float dtime) {
	Vector2D steering = agent->position - target;
	steering.Normalize();
	steering *= agent->max_velocity;
	steering = PerimeterAvoidance(agent, steering, window, border);
	Vector2D steeringForce = (steering - agent->velocity);
	steeringForce /= agent->max_velocity;

	return steeringForce * agent->max_force;
}

Vector2D SteeringBehavior::Flee(Agent *agent, Agent *target, Vector2D window, int border, float dtime) {
	return Flee(agent, target->position, window, border, dtime);
}


//Arrive Behavior
Vector2D SteeringBehavior::Arrive(Agent *agent, Vector2D target, Vector2D window, int border, float radius, float dtime) {
	Vector2D steering = target - agent->position;
	Vector2D distance = steering;
	float factor = distance.Length() / radius;
	steering.Normalize();
	if (distance.Length() > radius || agent->velocity.Length() == 0.f) {
		steering *= agent->max_velocity;
		steering = PerimeterAvoidance(agent, steering, window, border);
		Vector2D steeringForce = (steering - agent->velocity);
		steeringForce /= agent->max_velocity;

		return steeringForce * agent->max_force;
	}
	else if (distance.Length() < radius && agent->velocity.Length() < 0.4f) {
		agent->setVelocity({ 0,0 });
		Vector2D steeringForce = { 0,0 };
		return steeringForce;
	}
	else {
		steering *= (agent->max_velocity * factor);
		steering = PerimeterAvoidance(agent, steering, window, border);
		Vector2D steeringForce = (steering - agent->velocity);
		steeringForce /= (agent->max_velocity * factor);

		return steeringForce * agent->max_force;
	}
}

Vector2D SteeringBehavior::Arrive(Agent *agent, Agent *target, Vector2D window, int border, float radius, float dtime) {
	return Arrive(agent, target->position, window, border, radius, dtime);
}


//Pursue & Evade Behaviors
Vector2D SteeringBehavior::Pursue(Agent *agent, Agent *target, Vector2D window, int border, float dtime) {
	Vector2D steering = target->position - agent->position;
	Vector2D distance = steering;
	steering.Normalize();
	steering *= agent->max_velocity;
	float myT = distance.Length() / steering.Length();
	Vector2D predictedSteering = target->position + target->velocity * myT;

	return Seek(agent, predictedSteering, window, border, dtime);
}

Vector2D SteeringBehavior::Evade(Agent *agent, Agent *target, Vector2D window, int border, float dtime) {
	Vector2D steering = target->position - agent->position;
	Vector2D distance = steering;
	steering.Normalize();
	steering *= agent->max_velocity;
	float myT = distance.Length() / steering.Length();
	Vector2D predictedSteering = target->position + target->velocity * myT;

	return Flee(agent, predictedSteering, window, border, dtime);
}


//Wander Behavior
Vector2D SteeringBehavior::Wander(Agent *agent, Vector2D window, int border, float angle, int wanderMaxChange, int wanderCircleOffset, int wanderCircleRadius, float dtime) {
	agent->wanderCircleCenter = { agent->position.x + wanderCircleOffset*cos(angle * DEG2RAD), agent->position.y + wanderCircleOffset*sin(angle * DEG2RAD) };
	agent->wanderAngle += (rand() % (wanderMaxChange * 2) - wanderMaxChange);
	agent->wanderDisplacementVector = { agent->wanderCircleCenter.x + wanderCircleRadius*cos((agent->wanderAngle) * DEG2RAD), agent->wanderCircleCenter.y + wanderCircleRadius*sin((agent->wanderAngle) * DEG2RAD) };

	return Seek(agent, agent->wanderDisplacementVector, window, border, dtime);
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
	for (int i = 0; i < (int)target.size(); i++) {
		if (Vector2D().Distance(agent->position, target[i]->position) < agent->neighborRadius) {
			separationVector += (agent->position - target[i]->position);
			++neighborCount;
		}
	}
	separationVector /= (float)neighborCount;
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
	averageVector /= (float)neighborCount;
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
	averageVelocity /= (float)neighborCount;
	return Vector2D().Normalize(averageVelocity);
}

Vector2D SteeringBehavior::Flocking(Agent *agent, std::vector<Agent*> target, float kFlee, float kSeek, float kAligment, float kMaxFlocking, Vector2D window, int border, float dtime) {
	Vector2D separationDirection = FlockingFlee(agent, target);
	Vector2D cohesionDirection = FlockingSeek(agent, target);
	Vector2D alignmentDirection = FlockingAlignment(agent, target);

	Vector2D flockingForce = separationDirection * kFlee + cohesionDirection * kSeek + alignmentDirection * kAligment;
	return flockingForce * kMaxFlocking;
}


//Collision Avoidance
Vector2D SteeringBehavior::CollisionAvoidance(Agent *agent, std::vector<Target*> obstacles, Vector2D window, int border, float dtime) {
	Vector2D nearestTarget;
	float shortestDistance = (float)INT_MAX;
	bool collisionDetected = false;
	int wanderCircleOffset = 150;

	float angle = (float)(atan2(agent[0].velocity.y, agent[0].velocity.x) * RAD2DEG);
	Vector2D coneHeight = { agent[0].position.x + wanderCircleOffset*cos(angle * DEG2RAD), agent[0].position.y + wanderCircleOffset*sin(angle * DEG2RAD) };

	draw_circle(TheApp::Instance()->getRenderer(), (int)coneHeight.x, (int)coneHeight.y, 5, 0, 255, 0, 125);

	for (int i = 0; i < (int)obstacles.size(); i++) {
		if (Vector2DUtils::IsInsideCone(obstacles[i]->getPosition(), agent[0].position, coneHeight, 20.f)) {
			float currDist = Vector2D::Distance(agent[0].position, obstacles[i]->getPosition());
			if (currDist < shortestDistance) {
				nearestTarget = obstacles[i]->getPosition();
				shortestDistance = currDist;
				collisionDetected = true;
			}
		}
	}
	if (collisionDetected == true) return Flee(agent, nearestTarget, window, border, dtime);
	else return { 0,0 };
}



