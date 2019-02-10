//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "dfg.h"
#include "spacewar.h"

float dfgbulletNum = 5;
float dfgstartAngle = 175;
float dfgangleBetween = 1;
float dfgincrement = 0;
float dfgoffset = -2;
bool m;
//=============================================================================
// default constructor
//=============================================================================
Dfg::Dfg() : Entity()
{
	spriteData.width = dfgNS::WIDTH;           // size of Ship1
	spriteData.height = dfgNS::HEIGHT;
	spriteData.x = dfgNS::X;                   // location on screen
	spriteData.y = dfgNS::Y;
	spriteData.rect.bottom = dfgNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = dfgNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = dfgNS::SPEED;                             // velocity Y
	frameDelay = dfgNS::DFG_ANIMATION_DELAY;
	startFrame = dfgNS::DFG_START_FRAME;     // first frame of Dfg animation
	endFrame = dfgNS::DFG_END_FRAME;     // last frame of Dfg animation
	currentFrame = startFrame;
	radius = dfgNS::WIDTH / 2.0;
	mass = dfgNS::MASS;
	health = dfgNS::DFG_HEALTH;
	shotTimer = dfgNS::DFG_SHOT_TIMER;
	collisionType = entityNS::CIRCLE;
	shot = false;
	dead = false;
	imgChanged = false;
	startheight = 0;
	endheight = 0;
}

//=============================================================================
// Initialize the Dfg.
// Post: returns true if successful, false if failed
//=============================================================================
bool Dfg::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	sw = gamePtr;
	//initialize
	dfgbTexture.initialize(gamePtr->getGraphics(), DFGBULLET_IMAGE);
	hbTexture.initialize(gamePtr->getGraphics(), HEALTHBAR_IMAGE);
	hb.initialize(sw, hbNS::WIDTH, hbNS::HEIGHT, hbNS::TEXTURE_COLS, &hbTexture);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}

//=============================================================================
// draw the Dfg
//=============================================================================
void Dfg::draw()
{
	Image::draw();
	for each (DfgBullet* b in dfgbList)
	{
		b->draw();
	}
	hb.draw();
	// draw Dfg
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Dfg::update(float frameTime)
{
	shotTimer -= frameTime;
	Entity::update(frameTime);

	hb.setY(spriteData.y - hbNS::HEIGHT);
	hb.setX(getCenterX() - hbNS::WIDTH / 2);
	hb.setWidth((health / dfgNS::DFG_HEALTH) * hbNS::WIDTH);

	hb.update(frameTime);


	if (currentFrame == 10 && shot == false)
	{
		currentFrame = 10;
		shot = true;
	}

	for each (DfgBullet* b in dfgbList)
	{
		b->update(frameTime);
	}

	if (dfgincrement <= 0)
	{
		m = true;
	}
	else if (dfgincrement >= 10)
	{
		m = false;
	}

	if (m == true)
	{
		dfgincrement++;
	}
	else if (m == false)
	{
		dfgincrement--;
	}
	for (int i = dfgoffset; i < dfgbulletNum + dfgoffset; i++)
	{
		DfgBullet* d = new DfgBullet;
		d->initialize(sw, dfrbulletNS::WIDTH, dfrbulletNS::HEIGHT, dfrbulletNS::TEXTURE_COLS, &dfgbTexture);
		d->appImpulse(spriteData.x, getCenterY(), dfgstartAngle + dfgangleBetween * i + dfgincrement, 300);
		dfgbList.push_back(d);
	}


	if (input->isKeyDown(VK_SPACE))
	{
		health -= 50;
	}

	if (health <= 0)
	{
		dead = true;
		audio->playCue(EXPLOSION1);
	}

	checkBullet();
}

void Dfg::shoot()
{
	for (int i = 0; i < spriteData.height; i++)
	{
		DfgBullet* d = new DfgBullet;
		d->initialize(sw, dfgbulletNS::WIDTH, dfgbulletNS::HEIGHT, dfrbulletNS::TEXTURE_COLS, &dfgbTexture);
		d->getDir(0, spriteData.y + i, spriteData.x,spriteData.y + i, 500);
		dfgbList.push_back(d);
	}
}