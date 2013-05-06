#ifndef CONST_HERO
#define CONST_HERO

#include "Hero.h"
#include "BaseBullet.h"
#include "BaseEnemy.h"

Hero::Hero(const char* pszFileName, EntityManager* pBulletsManager, int pHorizontalFramesCount, int pVerticalFramesCount) :
	BarEntity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		//this->setAsCollidable();

		this->mGasesAnimationTime = 0.2f;

		this->mGasesShadows = new EntityManager(10, new GasShadow());
		this->mGases = new EntityManager(10, new Gas(this));

		this->mAnimationTime = 0.1f;
		this->mAnimationTimeElapsed = 0;

		this->mShockwaveTime = 0.2f;
		this->mShockwaveTimeElapsed = 0;

		this->mAnimationFrameSide = 0;

		//this->mShockwave = new Entity("actors/shockwave.png");
		//this->mShockwave->setScale(0);

		this->mShadow = new Entity("platform/shadow.png");
		this->mShadow->setIsShadow();

		this->mEngineParticlesAnimationTime = 0.3f;
		this->mEngineParticlesAnimationTimeElapsed = 0;

		this->mBulletsManager = pBulletsManager;

		//this->mEngineParticles = new EntityManager(5, new EngineParticle());

		//this->mBulletsTexture1 = new Texture("actors/bullet1.png", 1, 1);
		//this->mBulletsTexture2 = new Texture("actors/bullet2.png", 1, 1); 
		//this->mBulletsTexture3 = new Texture("actors/bullet3.png", 1, 1); 

		this->mShootAnimators = new EntityManager(10, new ShootAnimator(), this);

		//this->reset();
	}

void Hero::reset()
{
	this->setVisible(true);

	this->setBarsManagement(true, true);
	this->hideBars(false, true);
	this->setFireTime(0.45f);
	this->setPatrons(100);

	this->setZ(Options::MIN_Z);

	this->mBulletsPower = 20;

	this->setHealth(100);

	this->mSpeedStandart = 200;

	this->setSpeed(this->mSpeedStandart); // I should remove this

	this->setCurrentFrameIndex(2);

	this->mFollowCoordinateX = 0;
	this->mFollowCoordinateY = 0;

	this->mShootPaddingStandart = 0;
	this->mShootPadding = this->mShootPaddingStandart;

	this->mIsMove = false;
	this->mIsShouldFire = false;
	this->mIsDoubleFire = false;
	this->mIsTripleFire = false;
	this->mIsQuadrupleFire = false;

	this->mHealthRegenerationTime = 3.0f;
	this->mHealthRegenerationTimeElapsed = 0;

	this->mShootFromLeftHand = true;
	this->mIsFly = false;

	this->mJetPackPowerFull = 100.0f;
	this->mJetPackPower = this->mJetPackPowerFull;

	this->mShockwaveDamage = 3.0f;

	this->mShockwaveScale = 1.5f;
}

void Hero::startFly()
{
	this->mIsFly = true;
	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/player_accelerating.wav");
}

void Hero::endFly()
{
	if(!this->mIsFly) return;

	this->mIsFly = false;
	this->mFlyDownSpeed = 0;
}

bool Hero::isCanFly()
{
	return this->mJetPackPower > this->mJetPackPowerFull / 2;
}

bool Hero::startFlyDamage()
{
	if(this->mFlyDownSpeed >= 5) return false;
	if(this->getZ() < 10) return false;
	if(!this->isOnPizza()) return false;

	this->mIsFly = false;
	this->mFlyDownSpeed = 20;

	return true;
}

float Hero::getPatrons()
{
	return this->mPatrons;
}

void Hero::setPatrons(float pPatrons)
{
	this->mPatrons = pPatrons;
}

void Hero::setFollowCoordinates(float pX, float pY)
{
	this->mIsMove = true;

	this->mFollowCoordinateX = pX;
	this->mFollowCoordinateY = pY + this->getZ();
}

void Hero::follow(float pDeltaTime)
{
	if(this->mIsMove)
	{
		float x = this->mFollowCoordinateX / this->getSpeed(1 + pDeltaTime);
		float y = this->mFollowCoordinateY / this->getSpeed(1 + pDeltaTime);

		float maxSpeed = Utils::coord(this->getSpeed(1 + pDeltaTime));
		
		if(x < 0) x = x < -maxSpeed ? -maxSpeed : x;
		if(x > 0) x = x > maxSpeed ? maxSpeed : x;

		if(y < 0) y = y < -maxSpeed ? -maxSpeed : y;
		if(y > 0) y = y > maxSpeed ? maxSpeed : y;

		x = this->getCenterX() - x;
		y = this->getCenterY() - y;

		this->setCenterPosition(x, y);
	}
}

void Hero::fire(float pVectorX, float pVectorY)
{
	if(BarEntity::fire(pVectorX, pVectorY))
	{
		BaseBullet* bullet = ((BaseBullet*) this->mBulletsManager->create());
		bullet->fire(this->getCenterX(), this->getCenterY() + this->getZ(), pVectorX, pVectorY);

		this->mPatrons--;

		if(this->getCurrentFrameIndex() > 0)
		{
			Entity* shootAnimator = this->mShootAnimators->create();
			shootAnimator->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2);
			shootAnimator->animate(0.08f, (this->getCurrentFrameIndex() - 1) * 12 + (this->mShootFromLeftHand ? 5 : 0), (this->getCurrentFrameIndex() - 1) * 12 +  + (this->mShootFromLeftHand ? 10 : 5), 1);

			this->mShootFromLeftHand = !this->mShootFromLeftHand;

			switch(bullet->getCurrentFrameIndex())
			{
				case 0:
					shootAnimator->setColor(ccc3(26.0,141.0,254.0));
				break;
				case 1:
					shootAnimator->setColor(ccc3(27.0,230.0,27.0));
				break;
				case 2:
					shootAnimator->setColor(ccc3(254.0,51.0,22.0));
				break;
				case 3:
					shootAnimator->setColor(ccc3(254.0,105.0,215.0));
				break;
				case 4:
					shootAnimator->setColor(ccc3(25.0,242.0,254.0));
				break;
				case 5:
					shootAnimator->setColor(ccc3(254.0,224.0,26.0));
				break;
				case 6:
					shootAnimator->setColor(ccc3(154.0,44.0,254.0));
				break;
				case 7:
					shootAnimator->setColor(ccc3(254.0,141.0,27.0));
				break;
				case 8:
					shootAnimator->setColor(ccc3(38.0,237.0,162.0));
				break;
				case 9:
					shootAnimator->setColor(ccc3(163.0,253.0,23.0));
				break;
			}
		}
	
		if(Options::SOUND_ENABLE)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/shot.wav");
		}
	}
}

bool Hero::onCollide(BaseBullet* pBullet)
{
	this->setRed();

	this->removeHealth(pBullet->getPower());
	
	this->mShootVectorX = pBullet->mVectorX;
	this->mShootVectorY = pBullet->mVectorY;

	this->mShootPadding = Utils::coord(5); // UPGRADE

	if(this->getHealth() <= 0)
	{
		this->destroy();

		return true;
	}

	return false;
}

bool Hero::onCollide(BaseEnemy* pEnemy)
{
	this->setRed();

	this->removeHealth(0.05f); // TODO: Adjust enemy power.

	if(this->getHealth() <= 0)
	{
		this->destroy();

		return true;
	}

	return false;
}

bool Hero::destroy()
{
	BarEntity::destroy();

	this->mShadow->destroy();
	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/player_death.wav");

	return false;
}

void Hero::setCurrentFrameIndex(int pIndex)
{
	BarEntity::setCurrentFrameIndex(pIndex);
}

void Hero::update(float pDeltaTime)
{
	if(!this->isVisible())
	{
		return;
	}

	BarEntity::update(pDeltaTime);

	// TODO: Remove this to create() or reset()
	/*if(!((Entity*) this->mEngineParticles->objectAtIndex(0))->getParent())
	{
		this->mEngineParticles->setParent(this->getParent());
	}

	this->mAnimationTimeElapsed += pDeltaTime;

	if(mAnimationTimeElapsed >= this->mAnimationTime)
	{
		this->mAnimationTimeElapsed -= mAnimationTime;

		this->mAnimationFrameSide = this->mAnimationFrameSide == 3 ? 0 : this->mAnimationFrameSide + 1;
	}*/

	this->follow(pDeltaTime);

	if(this->mIsShouldFire)
	{
		this->fire(this->mFireVectorX, this->mFireVectorY);
	}

	int pontencialFrame = 2;

	int padding1 = Utils::coord(50);
	int padding2 = Utils::coord(150);
	int padding3 = Utils::coord(100);

	float fcx;
	float fcy;

	if(this->mIsShouldFire)
	{
		fcx = -this->mFireVectorX;
		fcy = -this->mFireVectorY;
	}
	else
	{
		fcx = this->mFollowCoordinateX;
		fcy = this->mFollowCoordinateY;
	}

	if(fcy > padding1)
	{
		pontencialFrame += 1;

		if(fcy > padding2 && abs(fcx) < padding3)
		{
			pontencialFrame += 1;
		}
	}
	else if(fcy < -padding1)
	{
		pontencialFrame -= 1;

		if(fcy < -padding2 && abs(fcx) < padding3)
		{
			pontencialFrame -= 1;
		}
	}

	pontencialFrame += this->mAnimationFrameSide;

	if(fcx > 0)
	{
		this->setScaleX(1);
	}
	else
	{
		this->setScaleX(-1);
	}

	this->setCurrentFrameIndex(pontencialFrame);

    // padding on collide

	if(this->mShootPadding > 0)
	{
		float x = this->mShootVectorX;
		float y = this->mShootVectorY;

		float speedX = x / sqrt(x * x + y * y) * this->mShootPadding;
		float speedY = y / sqrt(x * x + y * y) * this->mShootPadding;

		x = this->getCenterX() + speedX;
		y = this->getCenterY() + speedY;

		this->setCenterPosition(x, y);

		this->mShootPadding -= Utils::coord(0.3f);
	}
	else if(this->getSpeed(pDeltaTime) > this->mSpeedStandart)
	{
		//this->setSpeed(this->getSpeed(pDeltaTime) - 50);

		this->mIsMove = false;
	}

	
	/**this->mEngineParticlesAnimationTimeElapsed += pDeltaTime;

	if(this->mEngineParticlesAnimationTimeElapsed >= this->mEngineParticlesAnimationTime)
	{
		this->mEngineParticlesAnimationTimeElapsed -= this->mEngineParticlesAnimationTime;

		if(!this->mIsOutOfTop && !this->mFall)
		{
			this->mEngineParticles->create()->setCenterPosition(this->getCenterX(), this->getCenterY() + this->getZ() - Utils::coord(15));
		}
	}

	this->mHealthRegenerationTimeElapsed += pDeltaTime;

	if(this->mHealthRegenerationTimeElapsed >= this->mHealthRegenerationTime)
	{
		this->mHealthRegenerationTimeElapsed = 0;

		this->addHealth(1);
	}

	if(this->mIsFly)
	{
		this->addZ(2);

		this->mEngineParticlesAnimationTime = 0.1f;
		this->mJetPackPower = this->mJetPackPower > 0 ? this->mJetPackPower - 1.0f : 0;

		if(this->mJetPackPower <= 0)
		{
			this->endFly();
		}
	}
	else
	{
		if(this->getZ() > Options::MIN_Z)
		{
			this->mEngineParticlesAnimationTime = 1000.0f;

			this->mFlyDownSpeed += 0.04f;
			this->removeZ(this->mFlyDownSpeed);
		}
		else
		{
			this->mEngineParticlesAnimationTime = 0.3f;

			this->mJetPackPower = this->mJetPackPower >= this->mJetPackPowerFull ? this->mJetPackPowerFull : this->mJetPackPower + 1.0f;

			if(this->mFlyDownSpeed >= 10.0f)
			{
				this->mShockwave->setScale(0);
				this->mShockwave->create()->runAction(CCScaleTo::create(0.2f, this->mShockwaveScale));

				this->mFlyDownSpeed = 0;
				this->mShockwaveTimeElapsed = 0;
			
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/jetpack_fail.wav");
			}
		}
	}

	this->mShockwave->setCenterPosition(this->getCenterX(), this->getCenterY());

	this->mShockwaveTimeElapsed += pDeltaTime;

	if(this->mShockwaveTimeElapsed >= this->mShockwaveTime && this->mShockwave->isVisible())
	{
		this->mShockwave->destroy();
	}*/

	
	this->mGasesAnimationTimeElapsed += pDeltaTime;

	if(this->mGasesAnimationTimeElapsed >= this->mGasesAnimationTime && this->getZ() <= Options::MIN_Z)
	{
		this->mGasesAnimationTimeElapsed = 0;

		this->mGases->create();
	}
}

void Hero::update(int type, int level)
{
	switch(type)
	{
		case 0: // Fire Damage
			switch(level)
			{
				case 1:
					this->mBulletsManager->changeTexture(this->mBulletsTexture1);
					this->mBulletsPower = 25;
				break;
				case 2:
					this->mBulletsManager->changeTexture(this->mBulletsTexture2);
					this->mBulletsPower = 30;
				break;
				case 3:
					this->mBulletsManager->changeTexture(this->mBulletsTexture3);
					this->mBulletsPower = 35;
				break;
			}
		break;

		case 1: // Fire Rate
			switch(level)
			{
				case 1:
					this->setMaxFireTime(0.40f);
				break;
				case 2:
					this->mIsDoubleFire = true;
					this->setMaxFireTime(0.35f);
				break;
				case 3:
					this->setMaxFireTime(0.30f);
				break;
				case 4:
					this->mIsTripleFire = true;
					this->setMaxFireTime(0.25f);
				break;
				case 5:
					this->mIsQuadrupleFire = true;
					this->setMaxFireTime(0.20f);
				break;
			}
		break;

		case 2: // Speed
			switch(level)
			{
				case 1:
					this->setSpeed(180);
				break;
				case 2:
					this->setSpeed(170);
				break;
				case 3:
					this->setSpeed(160);
				break;
				case 4:
					this->setSpeed(150);
				break;
				case 5:
					this->setSpeed(140);
				break;
			}
		break;

		case 3: // Health Regeneration
			switch(level)
			{
				case 1:
					this->mHealthRegenerationTime = 3.0f;
				break;
				case 2:
					this->mHealthRegenerationTime = 2.5f;
				break;
				case 3:
					this->mHealthRegenerationTime = 2.0f;
				break;
				case 4:
					this->mHealthRegenerationTime = 1.5f;
				break;
				case 5:
					this->mHealthRegenerationTime = 1.0f;
				break;
			}
		break;

		case 4: // Max Health
			switch(level)
			{
				case 1:
					this->setHealth(150);
				break;
				case 2:
					this->setHealth(200);
				break;
				case 3:
					this->setHealth(250);
				break;
				case 4:
					this->setHealth(300);
				break;
				case 5:
					this->setHealth(350);
				break;
			}
		break;

		case 5: // Jetpack Power
			switch(level)
			{
				case 1:
					this->mJetPackPowerFull += 50.0f;
				break;
				case 2:
					this->mJetPackPowerFull += 50.0f;
				break;
			}
		break;

		case 6: // Shockwave Damage
			switch(level)
			{
				case 1:
					this->mShockwaveDamage = 6.0f;
					this->mShockwaveScale = 2.0f;
				break;
				case 2:
					this->mShockwaveDamage = 9.0f;
					this->mShockwaveScale = 2.5f;
				break;
				case 3:
					this->mShockwaveDamage = 12.0f;
					this->mShockwaveScale = 3.0f;
				break;
			}
		break;
	}
}

void Hero::setFireCoordinates(float pVectorX, float pVectorY)
{
	this->mFireVectorX = pVectorX;
	this->mFireVectorY = pVectorY;
}

#endif