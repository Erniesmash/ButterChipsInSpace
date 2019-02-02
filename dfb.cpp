#include "dfb.h"
#include "spacewar.h"

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
}

//=============================================================================
// Initialize the Dfb.
// Post: returns true if successful, false if failed
//=============================================================================
bool Dfb::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	sw = gamePtr;
	//dfbbTexture.initialize(graphics, DFBBULLET_IMAGE);
	//hbTexture.initialize(graphics, HEALTHBAR_IMAGE);
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

	//initialize
	dfbbTexture.initialize(graphics, DFBBULLET_IMAGE);
	hbTexture.initialize(graphics, HEALTHBAR_IMAGE);

	hb.setY(spriteData.y - hbNS::HEIGHT);
	hb.setX(getCenterX() - hbNS::WIDTH / 2);
	hb.setWidth((health / dfbNS::DFB_HEALTH) * hbNS::WIDTH);

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


	for each (DfbBullet* b in dfbbList)
	{
		b->update(frameTime);
	}
	// Bounce off walls
	if (spriteData.x > GAME_WIDTH - dfbNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - dfbNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	if (spriteData.y > GAME_HEIGHT - dfbNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - dfbNS::HEIGHT;  // position at bottom screen edge
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

void Dfb::chase(Entity *target)
{
	VECTOR2 travel(target->getCenterX() - getCenterX(), target->getCenterY() - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * dfbNS::SPEED;
}

void Dfb::shoot()
{

	for (int i = -3; i < 3; i++)
	{
		DfbBullet* d = new DfbBullet;
		d->initialize(sw, dfbbulletNS::WIDTH, dfbbulletNS::HEIGHT, dfbbulletNS::TEXTURE_COLS, &dfbbTexture);
		d->appImpulse(getX(), getY(), 0, getY() + (i));
		dfbbList.push_back(d);
	}
}

float Dfb::dir(float fromx, float fromy, float tox, float toy)
{
	VECTOR2 from(fromx, fromy);
	VECTOR2 to(tox, toy);
	float angle = acos((Graphics::Vector2Dot(&from, &to) / Graphics::Vector2Length(&from)*Graphics::Vector2Length(&to)));
	return 0;
}

void Dfb::wave()
{
	DfbBullet* a = new DfbBullet;
	a->initialize(sw, dfbbulletNS::WIDTH, dfbbulletNS::HEIGHT, dfbbulletNS::TEXTURE_COLS, &dfbbTexture);
	a->invert = true;
	a->wavy(this);
	dfbbList.push_back(a);

	DfbBullet* b = new DfbBullet;
	b->initialize(sw, dfbbulletNS::WIDTH, dfbbulletNS::HEIGHT, dfbbulletNS::TEXTURE_COLS, &dfbbTexture);
	b->wavy(this);
	dfbbList.push_back(b);
}

void Dfb::healthBar()
{
}