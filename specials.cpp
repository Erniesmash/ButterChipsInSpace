//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "specials.h"

//=============================================================================
// default constructor
//=============================================================================
Specials::Specials() : Entity()
{
	spriteData.width = specialsNS::WIDTH;
	spriteData.height = specialsNS::HEIGHT;
	spriteData.x = specialsNS::X;                   // location on screen
	spriteData.y = specialsNS::Y;
	spriteData.rect.bottom = specialsNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = specialsNS::WIDTH;
	startFrame = specialsNS::SPECIALS_START_FRAME;     // first frame of ship animation
	endFrame = specialsNS::SPECIALS_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = specialsNS::WIDTH / 2.0;
	spriteData.scale = 1.5;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Specials::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Specials::draw()
{
	Image::draw();
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Specials::update(float frameTime)
{
	Entity::update(frameTime);
}