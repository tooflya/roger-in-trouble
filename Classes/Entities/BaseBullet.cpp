#ifndef CONST_BASEBULLET
#define CONST_BASEBULLET

#include "BaseBullet.h"

BaseBullet::BaseBullet() :
	Entity("main-character/bullets.png", 5, 2)
	{
		this->mShadow = new Entity("main-character/bullets.png", 5, 2);
		this->mShadow->setColor(ccc3(0.0f, 0.0f, 0.0f));
		this->mShadow->setIsShadow();

		this->setSpeed(700);

		this->mLifeTime = 7;

		this->mIsMoving = false;

		this->resumeSchedulerAndActions();
	}

Entity* BaseBullet::create()
{
	if(!this->mShadow->getParent())
	{
		this->getParent()->addChild(this->mShadow, 0);
	}

	this->setCurrentFrameIndex(Utils::random(0, 10));

	return Entity::create();
}

bool BaseBullet::destroy()
{
	this->mIsMoving = false;

	this->mShadow->destroy();

	Entity::destroy();

	return false;
}

float BaseBullet::getPower()
{
	return this->mPower;
}

void BaseBullet::setPower(float pPower)
{
	this->mPower = pPower;
}

void BaseBullet::fire(float pX, float pY, float pVectorX, float pVectorY)
{
	this->mIsMoving = true;

	this->mVectorPaddingX = 0;
	this->mVectorPaddingY = 0;

	this->setCenterPosition(pX, pY);

	this->mVectorX = pVectorX - pX;
	this->mVectorY = pVectorY - pY;
}

void BaseBullet::setFirePadding(float pVectorX, float pVectorY)
{
	this->mVectorPaddingX = pVectorX;
	this->mVectorPaddingY = pVectorY;

	this->mVectorX += this->mVectorPaddingX;
	this->mVectorY += this->mVectorPaddingY;
}

BaseBullet* BaseBullet::deepCopy()
{
	return new BaseBullet();
}

void BaseBullet::changeTexture(Texture* pTexture)
{
	Entity::changeTexture(pTexture);

	this->mShadow->changeTexture(pTexture);
}

void BaseBullet::update(float pDeltaTime)
{
	Entity::update(pDeltaTime);
	
	if(this->mIsMoving)
	{
		this->mLifeTimeElapsed += pDeltaTime;

		if(this->mLifeTimeElapsed >= this->mLifeTime)
		{
			this->mLifeTimeElapsed = 0;

			this->destroy();
		}

		CCPoint vector = Utils::vectorNormalize(this->mVectorX, this->mVectorY, this->getSpeed(pDeltaTime));

		this->setCenterPosition(this->getCenterX() + vector.x, this->getCenterY() + vector.y);

		float angle = atan2(this->mVectorX, this->mVectorY) * 180 / Utils::Pi + 90;

		this->setRotation(angle);
		this->mShadow->setRotation(angle);
 
 		float padding = this->mVectorX / sqrt(this->mVectorX * this->mVectorX + this->mVectorY * this->mVectorY) * 40;

		this->mShadow->setCenterPosition(this->getCenterX(), this->getCenterY() - Utils::coord(abs(padding)));
		this->mShadow->setVisible(this->isVisible());
	}
}

bool BaseBullet::onCollide()
{
	this->destroy();

	return true;
}

#endif