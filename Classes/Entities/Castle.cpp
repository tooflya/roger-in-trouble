#ifndef CONST_CASTLE
#define CONST_CASTLE

#include "Castle.h"
#include "BaseEnemy.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

Castle::Castle(EntityManager* pBullets) :
	BarEntity("base/castle.png", 4, 2)
	{
		//this->mBullets = pBullets;

		this->mShockwaveTime = 30.0f;
		this->mShockwaveTimeElapsed = 0;

		this->setBarsManagement(true, true);
		this->hideBars(false, true);

		this->setHealth(1000.0f);
		this->setFireTime(1000.0f);

		//this->mShockwave = new Entity("actors/shockwave.png");

		//this->mCastleWall1 = new Entity("actors/wall1.png");
		//this->mCastleWall2 = new Entity("actors/wall2.png");
		//this->mCastleWall3 = new Entity("actors/wall3.png");

		//this->mCastleWall1->create()->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 - Utils::coord(36));
		//this->mCastleWall2->create()->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 - Utils::coord(36));
		//this->mCastleWall3->create()->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 - Utils::coord(36));

		//this->addChild(this->mCastleWall1);
		//this->addChild(this->mCastleWall2);
		//this->addChild(this->mCastleWall3);

		this->setIgnoreSorting(true);

		//this->animate(0.1f);

		this->mShouldShoot = false;
	}

// ===========================================================
// Methods
// ===========================================================

void Castle::fire()
{
	this->mShouldShoot = true;
}

void Castle::unfire()
{
	this->mShouldShoot = false;
}

void Castle::update(int pType, int pLevel)
{
	switch(pType) // TODO: Adjust power to all upgrades.
	{
		case 0: // Tower Blaster
			switch(pLevel)
			{
				case 1:
					this->setMaxFireTime(20.0f);
				break;
				case 2:
					this->setMaxFireTime(15.0f);
				break;
				case 3:
					this->setMaxFireTime(10.0f);
				break;
				case 4:
					this->setMaxFireTime(5.0f);
				break;
				case 5:
					this->setMaxFireTime(1.0f);
				break;
			}
		break;
		case 1: // Nove Defence
			switch(pLevel)
			{
				case 1:
					this->mShockwaveTime = 15.0f;
				break;
				case 2:
					this->mShockwaveTime = 7.0f;
				break;
				case 3:
					this->mShockwaveTime = 3.0f;
				break;
			}
		break;
	}
}

bool Castle::isCanFire()
{
	return BarEntity::fire(-1, -1);
}

void Castle::fire(BaseEnemy* pEnemy)
{return;
	if(pEnemy == NULL) return;

	BaseBullet* bullet = (BaseBullet*) this->mBullets->create();
	bullet->setPower(10); // TODO: Add updates.

	bullet->fire(this->getCenterX(), this->getCenterY() + Utils::coord(50), pEnemy->getCenterX(), pEnemy->getCenterY());
	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/shot.wav");
}

// ===========================================================
// Virtual Methods
// ===========================================================

Entity* Castle::create()
{
	/*if(!this->mShockwave->getParent())
	{
		this->getParent()->addChild(this->mShockwave, 0);
	}*/

	return BarEntity::create();
}

void Castle::update(float pDeltaTime)
{
	BarEntity::update(pDeltaTime);
return;
	this->mShockwaveTimeElapsed += pDeltaTime;

	if(this->mShockwaveTimeElapsed >= this->mShockwaveTime && this->mShouldShoot)
	{
		this->mShockwaveTimeElapsed = 0;

		this->mShockwave->setScale(0);
		this->mShockwave->create()->runAction(CCScaleTo::create(0.2f, 5.0f));
	
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/baseshot.wav");

		this->mShouldShoot = false;
	}
	else
	{
		if(this->mShockwave->isVisible())
		{
			if(this->mShockwaveTimeElapsed >= 0.2f)
			{
				this->mShockwave->destroy();
			}
		}
	}

	this->mShockwave->setCenterPosition(this->getCenterX(), this->getCenterY() - Utils::coord(30));
}

#endif