//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#pragma once

#ifndef _MISSLE_H                 // Prevent multiple definitions if this 
#define _MISSLE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "TextureManager.h"

namespace missleNS
{
	const int WIDTH = 20;                   // image width
	const int HEIGHT = 50;                  // image height
	const float SPEED = 650;
	const float MASS = 300.0f;            
	const int   TEXTURE_COLS = 1;         
	const int   MISSLE_START_FRAME = 4;     
	const int   MISSLE_END_FRAME = 7;       
	const float MISSLE_ANIMATION_DELAY = 0.1f;    // time between frames

	
	const int   EXPLOSION_START_FRAME = 0; // explosion start frame
	const int   EXPLOSION_END_FRAME = 63;   // explosion end frame
	const float EXPLOSION_ANIMATION_DELAY = 0.03f;   // time between frames
	
	/*
	const int   EXPLOSION_START_FRAME = 0; // explosion start frame
	const int   EXPLOSION_END_FRAME = 2;   // explosion end frame
	const float EXPLOSION_ANIMATION_DELAY = 0.3f;   // time between frames
	*/
}

// inherits from Entity class
class Missle : public Entity
{
private:
	float gravity = 9.81;
	float theta = -PI / 4;
	bool    explosionOn = false;
	bool alreadyFired = false;

	Image   explosion;
	TextureManager explosionTexture;

public:
	// constructor
	Missle();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	void shoot(Entity *whereFrom, float frameTime);
	void explode();

	bool missleActive = false;
	bool missleOnCooldown = false;
	float missleCooldownTimer = 0;
};
#endif
