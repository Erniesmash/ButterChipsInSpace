//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "explosion.h"

//=============================================================================
// default constructor
//=============================================================================
Explosion::Explosion() : Entity()
{
	spriteData.width = explosionNS::WIDTH;           // size of Ship1
	spriteData.height = explosionNS::HEIGHT;
	spriteData.x = explosionNS::X;                   // location on screen
	spriteData.y = explosionNS::Y;
	spriteData.rect.bottom = explosionNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = explosionNS::WIDTH;
	velocity.x = 1;                             // velocity X
	velocity.y = 1;                             // velocity Y
	frameDelay = explosionNS::EXPLOSION_ANIMATION_DELAY;
	startFrame = explosionNS::EXPLOSION_START_FRAME;     // first frame of ship animation
	endFrame = explosionNS::EXPLOSION_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = explosionNS::WIDTH / 2.0;
	mass = explosionNS::MASS;
	collisionType = entityNS::CIRCLE;
	exploded = false;
}

//=============================================================================
// Initialize the Explosion.
// Post: returns true if successful, false if failed
//=============================================================================
bool Explosion::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Explosion::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Explosion::update(float frameTime)
{
	Entity::update(frameTime);
	if (currentFrame == endFrame)
		exploded = true;
}