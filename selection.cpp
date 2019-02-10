//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "selection.h"

//=============================================================================
// default constructor
//=============================================================================
Selection::Selection() : Entity()
{
	spriteData.width = selectionNS::WIDTH;
	spriteData.height = selectionNS::HEIGHT;
	spriteData.x = selectionNS::X;                   // location on screen
	spriteData.y = selectionNS::Y;
	spriteData.rect.bottom = selectionNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = selectionNS::WIDTH;
	startFrame = selectionNS::SELECTION_START_FRAME;   
	endFrame = selectionNS::SELECTION_END_FRAME;   
	currentFrame = startFrame;
	radius = selectionNS::WIDTH / 2.0;
	spriteData.scale = 1.5;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Selection::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Selection::draw()
{
	Image::draw();
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Selection::update(float frameTime)
{
	Entity::update(frameTime);
}