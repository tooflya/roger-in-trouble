#ifndef CONST_HERO_H
#define CONST_HERO_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "BarEntity.h"
#include "Gas.h"
#include "EntityManager.h"
#include "Utils.h"
#include "Options.h"

using namespace cocos2d;

class BaseBullet;
class BaseEnemy;

class GasShadow : public Entity
{
	public:
	GasShadow() :
		Entity()
		{
		}

	GasShadow(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
		Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
		{
			this->setIsShadow();
		}

	GasShadow* deepCopy()
	{
		return new GasShadow("main-character/main-char-shadow-sprite.png", 12, 1);
	}
};

class Hero : public BarEntity
{
	class ShootAnimator : public Entity
	{
		public:
		ShootAnimator() :
			Entity("main-character/shoot-animation.png", 12, 4)
			{
			}

		void onAnimationEnd()
		{
			this->destroy();
		}

		void onAnimationStart()
		{
		}

		Entity* deepCopy()
		{
			return new ShootAnimator();
		}
	};
	
	protected:
		float mShockwaveTime;
		float mShockwaveTimeElapsed;

		float mAltitude;
		float mSpeedStandart;
		float mPatrons;

		float mAnimationTime;
		float mAnimationTimeElapsed;

		float mFollowCoordinateX;
		float mFollowCoordinateY;

		float mFireVectorX;
		float mFireVectorY;

		float mShootPaddingStandart;

		float mGasesAnimationTime;
		float mGasesAnimationTimeElapsed;

		float mEngineParticlesAnimationTime;
		float mEngineParticlesAnimationTimeElapsed;

		float mHealthRegenerationTime;
		float mHealthRegenerationTimeElapsed;

		float mFlyDownSpeed;

		int mAnimationFrameSide;

		int mBulletsPower;

		bool mIsMove;
		bool mIsFly;

		bool mShootFromLeftHand;

		bool mIsDoubleFire;
		bool mIsTripleFire;
		bool mIsQuadrupleFire;

		EntityManager* mBulletsManager;
		EntityManager* mShootAnimators;
		EntityManager* mEngineParticles;

	private:
		Texture* mBulletsTexture1;
		Texture* mBulletsTexture2;
		Texture* mBulletsTexture3;

	public:
		float mShootVectorX;
		float mShootVectorY;

		float mShootPadding;

		float mJetPackPowerFull;
		float mJetPackPower;

		EntityManager* mGases;
		EntityManager* mGasesShadows;

		Entity* mShockwave;

		bool mIsShouldFire;

		Hero(const char* pszFileName, EntityManager* pBulletsManager, int pHorizontalFramesCount, int pVerticalFramesCount);

		void reset();
		
		float getPatrons();

		virtual bool destroy();

		void setPatrons(float pPatrons);

		void setFollowCoordinates(float pX, float pY);
		void follow(float pDeltaTime);

		bool onCollide(BaseBullet* pBullet);
		bool onCollide(BaseEnemy* pEnemy);

		virtual void setCurrentFrameIndex(int pIndex);

		void fire(float pVectorX, float pVectorY);

		void update(float pDeltaTime);

		void update(int type, int level);

		void setFireCoordinates(float pVectorX, float pVectorY);

		void startFly();
		void endFly();
		bool isCanFly();
		bool startFlyDamage();

		float mShockwaveDamage;

		float mShockwaveScale;
};

#endif