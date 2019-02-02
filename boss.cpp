#include "boss.h"
#include "spacewar.h"

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
}

//=============================================================================
// Initialize the Boss.
// Post: returns true if successful, false if failed
//=============================================================================
bool Boss::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	sw = gamePtr;
	//bossbTexture.initialize(graphics, BOSSBULLET_IMAGE);
	//hbTexture.initialize(graphics, HEALTHBAR_IMAGE);
	hb.initialize(sw, hbNS::WIDTH, hbNS::HEIGHT, hbNS::TEXTURE_COLS, &hbTexture);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}

//=============================================================================
// draw the Boss
//=============================================================================
void Boss::draw()
{
	Image::draw();

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

	//initialize
	hbTexture.initialize(graphics, HEALTHBAR_IMAGE);

	hb.setY(spriteData.y - hbNS::HEIGHT);
	hb.setX(getCenterX() - hbNS::WIDTH / 2);
	hb.setWidth((health / bossNS::BOSS_HEALTH) * hbNS::WIDTH);

	hb.update(frameTime);
	/*if (currentFrame == 11)
	{
		shot = false;
	}
	if (currentFrame == 10 && shot == false)
	{
		shoot();
		shot = true;
	}*/

	// Bounce off walls
	if (spriteData.x > GAME_WIDTH - bossNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - bossNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	if (spriteData.y > GAME_HEIGHT - bossNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - bossNS::HEIGHT;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
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
	}
}

void Boss::chase(Entity *target)
{
	VECTOR2 travel(target->getCenterX() - getCenterX(), target->getCenterY() - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * bossNS::SPEED;
}

void Boss::shoot()
{
	/*for (int i = -3; i < 3; i++)
	{
		BossBullet* d = new BossBullet;
		d->initialize(sw, bossbulletNS::WIDTH, bossbulletNS::HEIGHT, bossbulletNS::TEXTURE_COLS, &bossbTexture);
		d->appImpulse(getX(), getY(), 0, getY() + (i));
		bossbList.push_back(d);
	}*/
}

float Boss::dir(float fromx, float fromy, float tox, float toy)
{
	VECTOR2 from(fromx, fromy);
	VECTOR2 to(tox, toy);
	float angle = acos((Graphics::Vector2Dot(&from, &to) / Graphics::Vector2Length(&from)*Graphics::Vector2Length(&to)));
	return 0;
}

void Boss::wave()
{
	/*BossBullet* a = new BossBullet;
	a->initialize(sw, bossbulletNS::WIDTH, bossbulletNS::HEIGHT, bossbulletNS::TEXTURE_COLS, &bossbTexture);
	a->invert = true;
	a->wavy(this);
	bossbList.push_back(a);

	BossBullet* b = new BossBullet;
	b->initialize(sw, bossbulletNS::WIDTH, bossbulletNS::HEIGHT, bossbulletNS::TEXTURE_COLS, &bossbTexture);
	b->wavy(this);
	bossbList.push_back(b);*/
}

void Boss::healthBar()
{
}