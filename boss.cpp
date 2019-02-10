//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "boss.h"
#include "spacewar.h"

float bulletfreq;
float startAngle;
float bulletNum;
float angleBetween;
float increment;
float offset;

float startAngle2;
float bulletNum2;
float angleBetween2;
float increment2;
float offset2;

bool phase1 = false;
bool phase2 = false;
bool phase3 = false;
bool phase4 = false;
bool phase5 = false;
bool phase6 = false;
bool set = false;
bool b;

//=============================================================================
// default constructor
//=============================================================================
Boss::Boss() : Entity()
{
	spriteData.width = bossNS::WIDTH;           // size of Ship1
	spriteData.height = bossNS::HEIGHT;
	spriteData.x = bossNS::X;                   // location on screen
	spriteData.y = bossNS::Y;
	spriteData.rect.bottom = bossNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = bossNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = bossNS::BOSS_ANIMATION_DELAY;
	startFrame = bossNS::BOSS_START_FRAME;     // first frame of Boss animation
	endFrame = bossNS::BOSS_END_FRAME;     // last frame of Boss animation
	currentFrame = startFrame;
	radius = bossNS::WIDTH / 2.0;
	mass = bossNS::MASS;
	health = bossNS::BOSS_HEALTH;
	shotTimer = bossNS::BOSS_SHOT_TIMER;
	collisionType = entityNS::CIRCLE;
	shot = false;
	dead = false;
	imgChanged = false;
	timer = 0;
}

//=============================================================================
// Initialize the Boss.
// Post: returns true if successful, false if failed
//=============================================================================
bool Boss::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	sw = gamePtr;
	//initialize
	ebTexture.initialize(gamePtr->getGraphics(), EBULLET_IMAGE);
	dfrbTexture.initialize(gamePtr->getGraphics(), DFRBULLET_IMAGE);
	dfbbTexture.initialize(gamePtr->getGraphics(), DFBBULLET_IMAGE);
	dfgbTexture.initialize(gamePtr->getGraphics(), DFGBULLET_IMAGE);

	hbTexture.initialize(gamePtr->getGraphics(), HEALTHBAR_IMAGE);

	hb.initialize(sw, hbNS::WIDTH, hbNS::HEIGHT, hbNS::TEXTURE_COLS, &hbTexture);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}

//=============================================================================
// draw the Boss
//=============================================================================
void Boss::draw()
{
	Image::draw();
	for each (EBullet* eb in ebList) {
		eb->draw();
	}
	for each (DfrBullet* dfrb in dfrbList) {
		dfrb->draw();
	}
	for each (DfbBullet* dfbb in dfbbList) {
		dfbb->draw();
	}
	for each (DfgBullet* dfgb in dfgbList) {
		dfgb->draw();
	}
	hb.draw();
	// draw Boss
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Boss::update(float frameTime)
{
	shotTimer -= frameTime;
	Entity::update(frameTime);
	spriteData.angle += frameTime * bossNS::ROTATION_RATE;  // rotate the Boss
	spriteData.x += frameTime * velocity.x;         // move Boss along X 
	spriteData.y += frameTime * velocity.y;         // move Boss along Y

	hb.setY(spriteData.y - hbNS::HEIGHT);
	hb.setX(getCenterX() - hbNS::WIDTH / 2);
	hb.setWidth((health / bossNS::BOSS_HEALTH) * hbNS::WIDTH);

	hb.update(frameTime);
	timer -= frameTime;

	//update for each bullet
	for each (EBullet* eb in ebList) {
		eb->update(frameTime);
	}
	for each (DfrBullet* dfrb in dfrbList) {
		dfrb->update(frameTime);
	}
	for each (DfbBullet* dfbb in dfbbList) {
		dfbb->update(frameTime);
	}
	for each (DfgBullet* dfgb in dfgbList) {
		dfgb->update(frameTime);
	}

	//phase 1
	if (health <= bossNS::PHASE_ONE && health > bossNS::PHASE_TWO)
	{
		if (phase1 == false && set == false)
		{
			bulletfreq = 0.1;
			bulletNum = 36;
			startAngle = 0;
			angleBetween = 10;
			increment = 0;
			offset = 1;
			phase1 = true;
		}

		increment += 5;

		if (timer <= 0)
		{
			for (int i = offset; i < bulletNum + offset; i++)
			{
				DfrBullet* d = new DfrBullet;
				d->initialize(sw, dfrbulletNS::WIDTH, dfrbulletNS::HEIGHT, dfrbulletNS::TEXTURE_COLS, &dfrbTexture);
				d->appImpulse(getCenterX(), getCenterY(), startAngle + angleBetween * i + increment, 600);
				dfrbList.push_back(d);
			}
			timer = bulletfreq;
		}
	}

	//phase 2
	else if (health <= bossNS::PHASE_TWO && health > bossNS::PHASE_THREE)
	{
		if (phase2 == false && set == false)
		{
			bulletfreq = 0.02;
			bulletNum = 8;
			startAngle = 0;
			angleBetween = 45;
			increment = 0;
			offset = 1;
			phase2 = true;
		}
		if (timer <= 0)
		{
			if (increment <= 0)
			{
				b = true;
			}
			else if (increment >= 90)
			{
				b = false;
			}

			if (b == true)
			{
				increment += 1;
			}
			else if (b == false)
			{
				increment -= 1;
			}
			for (int i = offset; i < bulletNum + offset; i++)
			{
				DfrBullet* d = new DfrBullet;
				d->initialize(sw, dfrbulletNS::WIDTH, dfrbulletNS::HEIGHT, dfrbulletNS::TEXTURE_COLS, &dfrbTexture);
				d->appImpulse(getCenterX(), getCenterY(), startAngle + angleBetween * i + increment, 600);
				dfrbList.push_back(d);
			}

			timer = bulletfreq;
		}

	}

	//phase 3
	else if (health <= bossNS::PHASE_THREE && health > bossNS::PHASE_FOUR)
	{
		if (phase3 == false && set == false)
		{
			bulletfreq = 0.05;
			bulletNum = 5;
			bulletNum2 = 5;
			startAngle = 180;
			angleBetween2 = 9;
			angleBetween = 9;
			increment = 0;
			increment2 = 0;
			offset = -2;
			phase3 = true;
		}

		if (increment <= 0)
		{
			b = true;
		}
		else if (increment >= 180)
		{
			b = false;
		}

		if (timer <= 0)
		{
			if (b == true)
			{
				increment += 5;
				increment2 -= 5;
			}
			else if (b == false)
			{
				increment -= 5;
				increment2 += 5;
			}
			for (int i = offset; i < bulletNum + offset; i++)
			{
				DfrBullet* d = new DfrBullet;
				d->initialize(sw, dfrbulletNS::WIDTH, dfrbulletNS::HEIGHT, dfrbulletNS::TEXTURE_COLS, &dfrbTexture);
				d->appImpulse(getCenterX(), getCenterY(), startAngle + angleBetween * i + increment, 300);
				dfrbList.push_back(d);
			}

			for (int i = offset; i < bulletNum2 + offset; i++)
			{
				DfbBullet* d = new DfbBullet;
				d->initialize(sw, dfbbulletNS::WIDTH, dfbbulletNS::HEIGHT, dfbbulletNS::TEXTURE_COLS, &dfbbTexture);
				d->appImpulse(getCenterX(), getCenterY(), startAngle + angleBetween2 * i + increment2, 300);
				dfbbList.push_back(d);
			}

			timer = bulletfreq;
		}
	}

	//phase 4
	else if (health <= bossNS::PHASE_FOUR && health > bossNS::PHASE_FIVE)
	{
		if (phase4 == false && set == false)
		{
			bulletfreq = 1;
			bulletNum = 5;
			bulletNum2 = 4;
			angleBetween2 = 90;
			angleBetween = 9;
			increment = 0;
			increment2 = 0;
			startAngle = 180;
			startAngle2 = 0;
			offset = -2;
			offset2 = 1;
			phase4 = true;
		}

		VECTOR2 ref(GAME_WIDTH - getCenterX(), 0);
		VECTOR2 to(player->getCenterX() - getCenterX(), player->getCenterY() - getCenterY());
		float angle = (acos((Graphics::Vector2Dot(&ref, &to) / (Graphics::Vector2Length(&to) * Graphics::Vector2Length(&ref)))) / (2 * PI)) * 360;
		if (timer <= 0)
		{

			if (player->getCenterY() <= getCenterY())
			{
				angle = -angle;
			}
			for (int i = offset; i < bulletNum + offset; i++)
			{
				DfgBullet* d = new DfgBullet;
				d->initialize(sw, dfgbulletNS::WIDTH, dfgbulletNS::HEIGHT, dfgbulletNS::TEXTURE_COLS, &dfgbTexture);
				d->appImpulse(getCenterX(), getCenterY(), angle + angleBetween * i, 400);
				dfgbList.push_back(d);
			}
			timer = bulletfreq;
		}

		for each (DfgBullet* d in dfgbList)
		{
			if (d->collided == true)
			{
				for (int i = offset2; i < bulletNum2 + offset2; i++)
				{
					EBullet* e = new EBullet;
					e->initialize(sw, ebulletNS::WIDTH, ebulletNS::HEIGHT, ebulletNS::TEXTURE_COLS, &ebTexture);
					e->appImpulse(d->getCenterX(), d->getCenterY(), startAngle2 + angleBetween2 * i, 30);
					ebList.push_back(e);
				}
			}
		}
	}

	//phase 5
	else if (health <= bossNS::PHASE_FIVE && health > bossNS::PHASE_SIX)
	{
		if (phase5 == false && set == false)
		{
			bulletfreq = 0.5;
			bulletNum = 72;
			bulletNum2 = 36;
			angleBetween2 = 10;
			startAngle = 0;
			angleBetween = 5;
			increment = 0;
			offset = 1;
			phase5 = true;
		}

		if (timer <= 0)
		{
			increment++;
			for (int i = offset; i < bulletNum + offset; i++)
			{
				DfrBullet* d = new DfrBullet;
				d->initialize(sw, dfrbulletNS::WIDTH, dfrbulletNS::HEIGHT, dfrbulletNS::TEXTURE_COLS, &dfrbTexture);
				d->appImpulse(getCenterX(), getCenterY(), startAngle + angleBetween * i + increment, 100);
				dfrbList.push_back(d);
			}

			for (int i = offset; i < bulletNum2 + offset; i++)
			{
				DfbBullet* d = new DfbBullet;
				d->initialize(sw, dfbbulletNS::WIDTH, dfbbulletNS::HEIGHT, dfbbulletNS::TEXTURE_COLS, &dfbbTexture);
				d->appImpulse(getCenterX(), getCenterY(), startAngle + angleBetween2 * i, 200);
				dfbbList.push_back(d);
			}
			timer = bulletfreq;
		}
	}

	//phase 6
	else if (health <= bossNS::PHASE_SIX && health > 0)
	{
		if (phase6 == false && set == false)
		{
			bulletfreq = 0.5;
			bulletNum = 72;
			bulletNum2 = 72;
			startAngle = 0;
			angleBetween2 = 5;
			angleBetween = 5;
			increment = 0;
			increment2 = 0;
			offset = 1;
			phase6 = true;
		}

		if (timer <= 0)
		{
			increment++;
			increment2--;
			for (int i = offset; i < bulletNum + offset; i++)
			{
				DfrBullet* d = new DfrBullet;
				d->initialize(sw, dfrbulletNS::WIDTH, dfrbulletNS::HEIGHT, dfrbulletNS::TEXTURE_COLS, &dfrbTexture);
				d->appImpulse(getCenterX(), getCenterY(), startAngle + angleBetween * i + increment, 100);
				dfrbList.push_back(d);
			}

			for (int i = offset; i < bulletNum2 + offset; i++)
			{
				DfbBullet* d = new DfbBullet;
				d->initialize(sw, dfbbulletNS::WIDTH, dfbbulletNS::HEIGHT, dfbbulletNS::TEXTURE_COLS, &dfbbTexture);
				d->appImpulse(getCenterX(), getCenterY(), startAngle + angleBetween2 * i + increment2, 200);
				dfbbList.push_back(d);
			}
			timer = bulletfreq;
		}
	}
	else if (health <= 0)
	{
		health = 0;
		endFrame = 5;
		dead = true;
		audio->playCue(EXPLOSION1);
	}

	if (input->isKeyDown(VK_SPACE))
	{
		health -= 50;
	}

	checkBullet();
}