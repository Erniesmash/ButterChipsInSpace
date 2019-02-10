//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "skull.h"
#include "spacewar.h"

//=============================================================================
// default constructor
//=============================================================================
Skull::Skull() : Entity()
{
	spriteData.width = skullNS::WIDTH;           // size of Ship1
	spriteData.height = skullNS::HEIGHT;
	spriteData.x = skullNS::X;                   // location on screen
	spriteData.y = skullNS::Y;
	spriteData.rect.bottom = skullNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = skullNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = skullNS::SKULL_ANIMATION_DELAY;
	startFrame = skullNS::SKULL_START_FRAME;     // first frame of Skull animation
	endFrame = skullNS::SKULL_END_FRAME;     // last frame of Skull animation
	currentFrame = startFrame;
	radius = skullNS::WIDTH / 2.0;
	mass = skullNS::MASS;
	health = skullNS::SKULL_HEALTH;
	collisionType = entityNS::CIRCLE;
	active = false;
	dead = false;
	imgChanged = false;
	entered = false;
	enteredChanged == false;
	exited = false;
	textcols = skullNS::TEXTURE_COLS;
}

//=============================================================================
// Initialize the Skull.
// Post: returns true if successful, false if failed
//=============================================================================
bool Skull::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	sw = gamePtr;
	//skullbTexture.initialize(graphics, SKULLBULLET_IMAGE);
	//hbTexture.initialize(graphics, HEALTHBAR_IMAGE);
	hb.initialize(sw, hbNS::WIDTH, hbNS::HEIGHT, hbNS::TEXTURE_COLS, &hbTexture);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}

//=============================================================================
// draw the Skull
//=============================================================================
void Skull::draw()
{
	Image::draw();

	hb.draw();
	// draw Skull
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Skull::update(float frameTime)
{
	Entity::update(frameTime);

		spriteData.x -= frameTime * skullNS::SPEED;         // move Skull along X
		//initialize hb
		hbTexture.initialize(graphics, HEALTHBAR_IMAGE);

		hb.setY(spriteData.y - 2 * hbNS::HEIGHT);
		hb.setX(getCenterX() - hbNS::WIDTH / 2);
		hb.setWidth((health / skullNS::SKULL_HEALTH) * hbNS::WIDTH);

		hb.update(frameTime);

		if (spriteData.x <= -spriteData.width*2)                    // else if hit left screen edge
		{
			dead = true;
		}

		if (input->isKeyDown(VK_SPACE))
		{
			if (health >= 0)
			{
				health = health - 1;
			}
		}

		if (health <= 0)
		{
			dead = true;
			audio->playCue(EXPLOSION1);
		}
}