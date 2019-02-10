//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "heart.h"

//=============================================================================
// default constructor
//=============================================================================
Heart::Heart() : Entity()
{
	spriteData.width = heartNS::WIDTH;          
	spriteData.height = heartNS::HEIGHT;
	spriteData.x = heartNS::X;                   // location on screen
	spriteData.y = heartNS::Y;
	spriteData.rect.bottom = heartNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = heartNS::WIDTH;
	startFrame = heartNS::HEART_START_FRAME;     // first frame of ship animation
	endFrame = heartNS::HEART_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = heartNS::WIDTH / 2.0;
	spriteData.scale = 0.25;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Heart::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Heart::draw()
{
	Image::draw();
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Heart::update(float frameTime)
{
	Entity::update(frameTime);
}