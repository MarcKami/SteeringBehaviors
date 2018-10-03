#include "SceneArrive.h"

using namespace std;

SceneArrive::SceneArrive() {
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(0, 0));
	agent->loadSpriteTexture("../res/isaac.png", 3);
	agent->setRotate(false);
	agents.push_back(agent);

	Target *target = new Target;
	target->loadSpriteTexture("../res/item.png", 4);
	targets.push_back(target);
	target = new Target();
	target->loadSpriteTexture("../res/item2.png", 1);
	targets.push_back(target);

	draw_vector = false;
	reached = false;
	border = 75;
	window = { 1280, 768 };
}

SceneArrive::~SceneArrive() {
	for (int i = 0; i < (int)agents.size(); i++) {
		delete agents[i];
	}
	for (int i = 0; i < (int)targets.size(); i++) {
		delete targets[i];
	}
}

void SceneArrive::update(float dtime, SDL_Event *event) {
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT) {
			targets[0]->setPosition(Vector2D((float)(event->button.x), (float)(event->button.y)));
			targets[1]->setPosition(Vector2D((float)(event->button.x), (float)(event->button.y)));
			agents[0]->setTarget(targets[0]->getPosition());
			reached = false;
			target = targets[0]->getPosition();
		}
		break;
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_V)
			draw_vector = !draw_vector;
		break;
	default:
		break;
	}
	Vector2D steering_force = agents[0]->Behavior()->Arrive(agents[0], agents[0]->getTarget(), window, border, 200, dtime);
	agents[0]->update(steering_force, dtime, event);
	targets[0]->update(dtime, event);
	if (Vector2D().Distance(agents[0]->getPosition(), targets[0]->getPosition()) < 25.0f) reached = true;
}

void SceneArrive::draw() {
	if (draw_vector) {
		draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
		draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 200, 0, 255, 0, 255);
	}
	if (reached) targets[1]->draw();
	else targets[0]->draw();
	agents[0]->draw();
}

const char* SceneArrive::getTitle() {
	return "SDL Steering Behaviors :: Arrive Demo";
}