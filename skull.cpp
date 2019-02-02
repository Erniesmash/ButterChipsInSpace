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
	shotTimer = skullNS::SKULL_SHOT_TIMER;
	collisionType = entityNS::CIRCLE;
	shot = false;
	dead = false;
	imgChanged = false;
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
	shotTimer -= frameTime;
	Entity::update(frameTime);
	spriteData.angle += frameTime * skullNS::ROTATION_RATE;  // rotate the Skull
	spriteData.x += frameTime * velocity.x;         // move Skull along X 
	spriteData.y += frameTime * velocity.y;         // move Skull along Y

	//initialize
	hbTexture.initialize(graphics, HEALTHBAR_IMAGE);

	hb.setY(spriteData.y - hbNS::HEIGHT);
	hb.setX(getCenterX() - hbNS::WIDTH / 2);
	hb.setWidth((health / skullNS::SKULL_HEALTH) * hbNS::WIDTH);

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
	if (spriteData.x > GAME_WIDTH - skullNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - skullNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	if (spriteData.y > GAME_HEIGHT - skullNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - skullNS::HEIGHT;  // position at bottom screen edge
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

void Skull::chase(Entity *target)
{
	VECTOR2 travel(target->getCenterX() - getCenterX(), target->getCenterY() - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * skullNS::SPEED;
}

void Skull::shoot()
{
	/*for (int i = -3; i < 3; i++)
	{
		SkullBullet* d = new SkullBullet;
		d->initialize(sw, skullbulletNS::WIDTH, skullbulletNS::HEIGHT, skullbulletNS::TEXTURE_COLS, &skullbTexture);
		d->appImpulse(getX(), getY(), 0, getY() + (i));
		skullbList.push_back(d);
	}*/
}

float Skull::dir(float fromx, float fromy, float tox, float toy)
{
	VECTOR2 from(fromx, fromy);
	VECTOR2 to(tox, toy);
	float angle = acos((Graphics::Vector2Dot(&from, &to) / Graphics::Vector2Length(&from)*Graphics::Vector2Length(&to)));
	return 0;
}

void Skull::wave()
{
	/*SkullBullet* a = new SkullBullet;
	a->initialize(sw, skullbulletNS::WIDTH, skullbulletNS::HEIGHT, skullbulletNS::TEXTURE_COLS, &skullbTexture);
	a->invert = true;
	a->wavy(this);
	skullbList.push_back(a);

	SkullBullet* b = new SkullBullet;
	b->initialize(sw, skullbulletNS::WIDTH, skullbulletNS::HEIGHT, skullbulletNS::TEXTURE_COLS, &skullbTexture);
	b->wavy(this);
	skullbList.push_back(b);*/
}

void Skull::healthBar()
{
}