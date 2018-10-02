#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>

#include "SDL_SimpleApp.h"
#include "SceneKinematicSeek.h"
#include "SceneKinematicFlee.h"
#include "SceneSeek.h"
#include "SceneFlee.h"
#include "SceneArrive.h"
#include "ScenePursue.h"
#include "SceneEvade.h"
#include "SceneWander.h"
#include "ScenePathFollowing.h"
#include "SceneFlocking.h"
#include "SceneCollisionAvoidance.h"


using namespace std;

int main(int argc, char ** argv)
{
	srand((unsigned int)time(NULL));

	bool quit = false;
	SDL_Event event;

	SDL_SimpleApp *app = SDL_SimpleApp::Instance();

	Scene *curr_scene = new SceneSeek;
	app->setBackgroundImage("../res/Room3.png");
	app->setWindowTitle(curr_scene->getTitle());

	while (!quit)
	{
		// run app frame by frame
		event = app->run(curr_scene);

		/* Keyboard events */
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_1) //Seek
			{
				delete(curr_scene);
				curr_scene = new SceneSeek;
				app->setBackgroundImage("../res/Room3.png");
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_2) //Flee
			{
				delete(curr_scene);
				curr_scene = new SceneFlee;
				app->setBackgroundImage("../res/Room2.png");
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_3) //Arrive
			{
				delete(curr_scene);
				curr_scene = new SceneArrive;
				app->setBackgroundImage("../res/Room.png");
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_4) //Pursue
			{
				delete(curr_scene);
				curr_scene = new ScenePursue;
				app->setBackgroundImage("../res/Room2.png");
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_5) //Evade
			{
				delete(curr_scene);
				curr_scene = new SceneEvade;
				app->setBackgroundImage("../res/Room2.png");
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_6) //Wander
			{
				delete(curr_scene);
				curr_scene = new SceneWander;
				app->setBackgroundImage("../res/PooBackground.png");
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_7) //Flocking
			{
				delete(curr_scene);
				curr_scene = new SceneFlocking;
				app->setBackgroundImage("../res/Room4.png");
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_8) //PathFollow
			{
				delete(curr_scene);
				curr_scene = new ScenePathFollowing;
				app->setBackgroundImage("../res/Room5.png");
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_9) //Collision Avoidance
			{
				delete(curr_scene);
				curr_scene = new SceneCollisionAvoidance;
				app->setBackgroundImage("../res/Room3.png");
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_0) //Flocking ** Empty **
			{
				delete(curr_scene);
				curr_scene = new SceneFlocking;
				app->setBackgroundImage("../res/Room4.png");
				app->setWindowTitle(curr_scene->getTitle());
			}
			if ((event.key.keysym.scancode == SDL_SCANCODE_Q) || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				quit = true;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_F)
			{
				app->setFullScreen();
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}

	}

	return 0;
}