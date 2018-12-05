//  Module:             Gameplay Programming
//  Assignment1:        Butter Chips in Space
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "speedboost.h"

//=============================================================================
// default constructor
//=============================================================================
SpeedBoost::SpeedBoost() : Entity()
{
	spriteData.width = speedboostNS::WIDTH;           // size of Ship1
	spriteData.height = speedboostNS::HEIGHT;
	spriteData.x = speedboostNS::X;                   // location on screen
	spriteData.y = speedboostNS::Y;
	spriteData.rect.bottom = speedboostNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = speedboostNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = speedboostNS::SB_ANIMATION_DELAY;
	startFrame = speedboostNS::SB_START_FRAME;     // first frame of ship animation
	endFrame = speedboostNS::SB_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	mass = speedboostNS::MASS;
	collisionType = entityNS::CIRCLE;
	collided = false;
}

//=============================================================================
// Initialize the SpeedBoost.
// Post: returns true if successful, false if failed
//=============================================================================
bool SpeedBoost::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void SpeedBoost::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void SpeedBoost::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.angle += frameTime * speedboostNS::ROTATION_RATE;  // rotate the ship
}