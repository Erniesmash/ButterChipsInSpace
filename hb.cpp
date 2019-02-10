//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "hb.h"

//=============================================================================
// default constructor
//=============================================================================
Hb::Hb() : Entity()
{
	spriteData.width = hbNS::WIDTH;           // size of Ship1
	spriteData.height = hbNS::HEIGHT;
	spriteData.x = hbNS::X;                   // location on screen
	spriteData.y = hbNS::Y;
	spriteData.rect.bottom = hbNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = hbNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = hbNS::HB_ANIMATION_DELAY;
	startFrame = hbNS::HB_START_FRAME;     // first frame of Hb animation
	endFrame = hbNS::HB_END_FRAME;     // last frame of Hb animation
	currentFrame = startFrame;
	radius = hbNS::WIDTH / 2.0;
	mass = hbNS::MASS;

}

//=============================================================================
// Initialize the Hb.
// Post: returns true if successful, false if failed
//=============================================================================
bool Hb::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	//hbbTexture.initialize(graphics, HBBULLET_IMAGE);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}

//=============================================================================
// draw the Hb
//=============================================================================
void Hb::draw()
{
	Image::draw();
	// draw Hb
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Hb::update(float frameTime)
{
	Entity::update(frameTime);
}
