#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Target.h"


using namespace std;

Target::Target() :  
	position(Vector2D(100, 100)),
	sprite_num_frames(0),
	sprite_w(0),
	sprite_h(0),
	color({ 255, 0, 0, 255 }),
	draw_sprite(false)
	{}


Vector2D Target::getPosition() {
	return position;
}


void Target::setPosition(Vector2D _position) {
	position = _position;
}


void Target::update(float dtime, SDL_Event *event) {

	//cout << "agent update:" << endl;

	switch (event->type) {
		/* Keyboard & Mouse events */
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_sprite = !draw_sprite;
		if (event->key.keysym.scancode == SDL_SCANCODE_V)
			draw_vector = !draw_vector;
		break;
	default:
		break;
	}

	// Trim position values to window size
	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;
}


void Target::draw() {
	if (draw_sprite) {
		Uint32 sprite;

		if (sprite_num_frames == 24) sprite = (int)(SDL_GetTicks() / 48) % sprite_num_frames;
		else sprite = (int)(SDL_GetTicks() / 10) % sprite_num_frames;

		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, 0, &center, SDL_FLIP_NONE);
	}
	else {
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, color.r, color.g, color.b, color.a);
	}
}


bool Target::loadSpriteTexture(char* filename, int _num_frames) {
	if (_num_frames < 1) return false;

	SDL_Surface *image = IMG_Load(filename);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = _num_frames;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;
	draw_sprite = true;

	if (image)
		SDL_FreeSurface(image);

	return true;
}