#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"

class Target{
private:
	Vector2D position;

	SDL_Color color;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	bool draw_vector;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

public:
	Target();
	Vector2D getPosition();
	void setPosition(Vector2D position);
	SDL_Texture* set_icon(SDL_Renderer *surface, char* filename, int _num_frames);
	void update(float dtime, SDL_Event *event);
	void draw();
	bool Target::loadSpriteTexture(char* filename, int num_frames = 1);
};

