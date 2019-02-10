//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "dfr.h"
#include "spacewar.h"

//=============================================================================
// default constructor
//=============================================================================
Dfr::Dfr() : Entity()
{
	spriteData.width = dfrNS::WIDTH;           // size of Ship1
	spriteData.height = dfrNS::HEIGHT;
	spriteData.x = dfrNS::X;                   // location on screen
	spriteData.y = dfrNS::Y;
	spriteData.rect.bottom = dfrNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = dfrNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = dfrNS::DFR_ANIMATION_DELAY;
	startFrame = dfrNS::DFR_START_FRAME;     // first frame of Dfr animation
	endFrame = dfrNS::DFR_END_FRAME;     // last frame of Dfr animation
	currentFrame = startFrame;
	radius = dfrNS::WIDTH / 2.0;
	mass = dfrNS::MASS;
	health = dfrNS::DFR_HEALTH;
	shotTimer = dfrNS::DFR_SHOT_TIMER;
	collisionType = entityNS::CIRCLE;
	shot = false;
	dead = false;
	imgChanged = false;
}

//=============================================================================
// Initialize the Dfr.
// Post: returns true if successful, false if failed
//=============================================================================
bool Dfr::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	sw = gamePtr;
	//initialize
	dfrbTexture.initialize(gamePtr->getGraphics(), DFRBULLET_IMAGE);
	hbTexture.initialize(gamePtr->getGraphics(), HEALTHBAR_IMAGE);
	hb.initialize(sw, hbNS::WIDTH, hbNS::HEIGHT, hbNS::TEXTURE_COLS, &hbTexture);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}

//=============================================================================
// draw the Dfr
//=============================================================================
void Dfr::draw()
{
	Image::draw();
	for each (DfrBullet* b in dfrbList) 
	{
		b->draw();
	}
	hb.draw();
	// draw Dfr
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Dfr::update(float frameTime)
{
	shotTimer -= frameTime;
	Entity::update(frameTime);
	spriteData.angle += frameTime * dfrNS::ROTATION_RATE;  // rotate the Dfr
	spriteData.x += frameTime * velocity.x;         // move Dfr along X 
	spriteData.y += frameTime * velocity.y;         // move Dfr along Y

	hb.setY(spriteData.y - hbNS::HEIGHT);
	hb.setX(getCenterX() - hbNS::WIDTH / 2);
	hb.setWidth((health / dfrNS::DFR_HEALTH) * hbNS::WIDTH);

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

	for each (DfrBullet* b in dfrbList)
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

void Dfr::shoot()
{
	DfrBullet* d = new DfrBullet;
	d->initialize(sw, dfrbulletNS::WIDTH, dfrbulletNS::HEIGHT, dfrbulletNS::TEXTURE_COLS, &dfrbTexture);
	d->getDir(player->getCenterX(),player->getCenterY(), spriteData.x,getCenterY(), 600);
	dfrbList.push_back(d);
}

float Dfr::dir(float fromx, float fromy, float tox, float toy)
{
	VECTOR2 from(fromx, fromy);
	VECTOR2 to(tox, toy);
	float angle = acos((Graphics::Vector2Dot(&from, &to) / Graphics::Vector2Length(&from)*Graphics::Vector2Length(&to)));
	return 0;
}