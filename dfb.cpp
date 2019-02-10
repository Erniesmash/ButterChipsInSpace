//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "dfb.h"
#include "spacewar.h"

float t = 0.05;
//=============================================================================
// default constructor
//=============================================================================
Dfb::Dfb() : Entity()
{
	spriteData.width = dfbNS::WIDTH;           // size of Ship1
	spriteData.height = dfbNS::HEIGHT;
	spriteData.x = dfbNS::X;                   // location on screen
	spriteData.y = dfbNS::Y;
	spriteData.rect.bottom = dfbNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = dfbNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = dfbNS::DFB_ANIMATION_DELAY;
	startFrame = dfbNS::DFB_START_FRAME;     // first frame of Dfb animation
	endFrame = dfbNS::DFB_END_FRAME;     // last frame of Dfb animation
	currentFrame = startFrame;
	radius = dfbNS::WIDTH / 2.0;
	mass = dfbNS::MASS;
	health = dfbNS::DFB_HEALTH;
	shotTimer = dfbNS::DFB_SHOT_TIMER;
	collisionType = entityNS::CIRCLE;
	shot = false;
	dead = false;
	imgChanged = false;
	a = 0;
}

//=============================================================================
// Initialize the Dfb.
// Post: returns true if successful, false if failed
//=============================================================================
bool Dfb::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	sw = gamePtr;
	dfbbTexture.initialize(gamePtr->getGraphics(), DFBBULLET_IMAGE);
	hbTexture.initialize(gamePtr->getGraphics(), HEALTHBAR_IMAGE);
	hb.initialize(sw, hbNS::WIDTH, hbNS::HEIGHT, hbNS::TEXTURE_COLS, &hbTexture);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}

//=============================================================================
// draw the Dfb
//=============================================================================
void Dfb::draw()
{
	Image::draw();
	for each (DfbBullet* b in dfbbList)
	{
		b->draw();
	}
	hb.draw();
	// draw Dfb
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Dfb::update(float frameTime)
{
	shotTimer -= frameTime;
	Entity::update(frameTime);
	spriteData.angle += frameTime * dfbNS::ROTATION_RATE;  // rotate the Dfb
	spriteData.x += frameTime * velocity.x;         // move Dfb along X 
	spriteData.y += frameTime * velocity.y;         // move Dfb along Y
	t -= frameTime;

	hb.setY(spriteData.y - hbNS::HEIGHT);
	hb.setX(getCenterX() - hbNS::WIDTH / 2);
	hb.setWidth((health / dfbNS::DFB_HEALTH) * hbNS::WIDTH);

	hb.update(frameTime);

	if (currentFrame == 11)
	{
		shot = false;
	}
	if (currentFrame == 10 && shot == false)
	{
		shoot();
		shot = true;
	}

	for each (DfbBullet* b in dfbbList)
	{
		b->update(frameTime);
	}

	if (input->isKeyDown(VK_SPACE))
	{
		health -= 10;
	}

	if (health <= 0)
	{
		dead = true;
		audio->playCue(EXPLOSION1);
	}

	checkBullet();
}

void Dfb::shoot()
{
	for (int i = 1; i < dfbNS::BULLET_COUNT + 1; i++)
	{
		DfbBullet* d = new DfbBullet;
		d->initialize(sw, dfbbulletNS::WIDTH, dfbbulletNS::HEIGHT, dfbbulletNS::TEXTURE_COLS, &dfbbTexture);
		d->appImpulse(getCenterX() - d->getWidth() / 2, getCenterY() - d->getHeight() / 2,dfbNS::DFB_ANGLE + dfbNS::DFB_SPREAD_ANGLE*i,dfbbulletNS::SPEED);
		dfbbList.push_back(d);
	}
}