//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "button.h"

//=============================================================================
// default constructor
//=============================================================================
Button::Button() : Entity()
{
	spriteData.width = buttonNS::WIDTH;
	spriteData.height = buttonNS::HEIGHT;
	spriteData.x = buttonNS::X;                   // location on screen
	spriteData.y = buttonNS::Y;
	spriteData.rect.bottom = buttonNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = buttonNS::WIDTH;
	startFrame = buttonNS::BUTTON_START_FRAME;     // first frame of ship animation
	endFrame = buttonNS::BUTTON_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = buttonNS::WIDTH / 2.0;
	spriteData.scale = 1;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Button::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Button::draw()
{
	Image::draw();
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Button::update(float frameTime)
{
	Entity::update(frameTime);
}