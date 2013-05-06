#ifndef CONST_LEVEL_H
#define CONST_LEVEL_H

#include "cocos2d.h"

#include "AppDelegate.h"

#include "EntityManager.h"
#include "EntityManagerGroup.h"
#include "LayerManager.h"
#include "BaseExplosion.h"
#include "FollowEnemy.h"
#include "FiredEnemy.h"
#include "CastleEnemy.h"
#include "BigEnemy.h"
#include "Pickup.h"
#include "Bubble.h"
#include "Slice.h"
#include "Castle.h"
#include "BaseBullet.h"
#include "EnemyBullet.h"
#include "Hero.h"
#include "Screen.h"
#include "Options.h"
#include "Utils.h"
#include "EnemyWave.h"
#include "EnemyGroup.h"
#include "WealthManager.h"
#include "Joystick.h"
#include "Spider.h"
#include "Star.h"
#include "SmallCloud.h"

class UpgradeManager;

#include "BackgroundStarsManager.h"

using namespace cocos2d;

class Level : public Screen
{
	protected:
		// ===========================================================
		// Inner Classes
		// ===========================================================

		class HiddenButton : public Entity
			{
				public:
					HiddenButton(const char* pszFileName) :
						Entity(pszFileName)
						{
						}

					HiddenButton(const char* pszFileName, int pHorizontalFrameCount, int pVerticalFrameCount) :
						Entity(pszFileName, pHorizontalFrameCount, pVerticalFrameCount)
						{
						}

					void update(float pDeltaTime)
					{
						Entity::update(pDeltaTime);

						if(this->getY() < Utils::coord(100))
						{
							this->setVisible(false);
						}
						else
						{
							this->setVisible(true);
						}
					}
			};

			class SettingsButton : public Entity
			{
				private:
					Level* mParentScreen;

					Entity* mPic;

					bool mRotated;

				public:
					SettingsButton(Level* pParentScreen) :
						Entity("controls/settings-button.png")
						{
							this->mParentScreen = pParentScreen;

							this->mPic = new Entity("controls/settings-icon.png");

							this->mPic->create()->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2 + Utils::coord(5));

							this->addChild(this->mPic);

							this->mRotated = false;

							this->setRegisterAsTouchable(true);
						}

					void onTouch(CCTouch* touch, CCEvent* event)
					{
						if(this->mParentScreen->mButtonsHolder1->numberOfRunningActions() > 0) return;

						if(this->mRotated)
						{
							this->mPic->runAction(CCRotateTo::create(0.5f, 0.0f));
							this->mParentScreen->mCreditsButton->runAction(CCMoveTo::create(0.5f, ccp(Utils::coord(90), Utils::coord(0))));
							this->mParentScreen->mMusicButton->runAction(CCMoveTo::create(0.5f, ccp(Utils::coord(90), -Utils::coord(80))));
							this->mParentScreen->mSoundButton->runAction(CCMoveTo::create(0.5f, ccp(Utils::coord(90), -Utils::coord(170))));

							this->mParentScreen->mButtonsHolder1->runAction(CCMoveTo::create(0.4f, ccp(Utils::coord(90), Utils::coord(90))));
						}
						else
						{
							this->mPic->runAction(CCRotateTo::create(0.5f, 180.0f));
							this->mParentScreen->mCreditsButton->runAction(CCMoveTo::create(0.5f, ccp(Utils::coord(90), Utils::coord(400))));
							this->mParentScreen->mMusicButton->runAction(CCMoveTo::create(0.5f, ccp(Utils::coord(90), Utils::coord(310))));
							this->mParentScreen->mSoundButton->runAction(CCMoveTo::create(0.5f, ccp(Utils::coord(90), Utils::coord(220))));

							this->mParentScreen->mButtonsHolder1->runAction(CCMoveTo::create(0.5f, ccp(Utils::coord(90), Utils::coord(300))));
						}

						this->mRotated = !this->mRotated;
					}

					void setOpacity(GLubyte pOpacity)
					{
						Entity::setOpacity(pOpacity);

						for(int i = 0; i < this->getChildren()->count(); i++)
						{
							((CCSprite*) this->getChildren()->objectAtIndex(i))->setOpacity(pOpacity);
						}
					}
			};

			class SocialButton : public Entity
			{
				private:
					Level* mParentScreen;

					Entity* mPic;

					bool mRotated;

				public:
					SocialButton(Level* pParentScreen) :
						Entity("controls/settings-button.png")
						{
							this->mParentScreen = pParentScreen;

							this->mPic = new Entity("controls/social-icon.png");

							this->mPic->create()->setCenterPosition(this->getWidth() / 2, this->getHeight() / 2);

							this->addChild(this->mPic);

							this->mRotated = false;

							this->setRegisterAsTouchable(true);
						}

					void onTouch(CCTouch* touch, CCEvent* event)
					{
						if(this->mParentScreen->mButtonsHolder2->numberOfRunningActions() > 0) return;

						if(this->mRotated)
						{
							this->mPic->runAction(CCRotateTo::create(0.5f, 0.0f));
							this->mParentScreen->mMoreGamesButton->runAction(CCMoveTo::create(0.5f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(0))));
							this->mParentScreen->mFacebookButton->runAction(CCMoveTo::create(0.5f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), -Utils::coord(80))));
							this->mParentScreen->mTwitterButton->runAction(CCMoveTo::create(0.5f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), -Utils::coord(170))));

							this->mParentScreen->mButtonsHolder2->runAction(CCMoveTo::create(0.4f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(90))));
						}
						else
						{
							this->mPic->runAction(CCRotateTo::create(0.5f, 90.0f));
							this->mParentScreen->mMoreGamesButton->runAction(CCMoveTo::create(0.5f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(400))));
							this->mParentScreen->mFacebookButton->runAction(CCMoveTo::create(0.5f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(310))));
							this->mParentScreen->mTwitterButton->runAction(CCMoveTo::create(0.5f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(220))));

							this->mParentScreen->mButtonsHolder2->runAction(CCMoveTo::create(0.5f, ccp(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(300))));
						}

						this->mRotated = !this->mRotated;
					}

					void setOpacity(GLubyte pOpacity)
					{
						Entity::setOpacity(pOpacity);
						
						for(int i = 0; i < this->getChildren()->count(); i++)
						{
							((CCSprite*) this->getChildren()->objectAtIndex(i))->setOpacity(pOpacity);
						}
					}
			};
			
			class CreditsButton : public HiddenButton
			{
				private:

				public:
					CreditsButton() :
						HiddenButton("controls/context-credits-button.png")
						{
							this->setRegisterAsTouchable(true);
						}

					void onTouch(CCTouch* touch, CCEvent* event)
					{
						
					}
			};
			
			class MusicButton : public HiddenButton
			{
				private:

				public:
					MusicButton() :
						HiddenButton("controls/music-context-button.png", 1, 2)
						{
							this->setRegisterAsTouchable(true);
						}

					void onTouch(CCTouch* touch, CCEvent* event)
					{
						Options::MUSIC_ENABLE = !Options::MUSIC_ENABLE;

						this->setCurrentFrameIndex(Options::MUSIC_ENABLE ? 0 : 1);
					}
			};
			
			class SoundButton : public HiddenButton
			{
				private:

				public:
					SoundButton() :
						HiddenButton("controls/sound-context-button.png", 1, 2)
						{
							this->setRegisterAsTouchable(true);
						}

					void onTouch(CCTouch* touch, CCEvent* event)
					{
						Options::SOUND_ENABLE = !Options::SOUND_ENABLE;

						this->setCurrentFrameIndex(Options::SOUND_ENABLE ? 0 : 1);
					}
			};
			
			class MoreGamesButton : public HiddenButton
			{
				private:

				public:
					MoreGamesButton() :
						HiddenButton("controls/context-moregames-button.png")
						{
							this->setRegisterAsTouchable(true);
						}

					void onTouch(CCTouch* touch, CCEvent* event)
					{
					}
			};
			
			class FacebookButton : public HiddenButton
			{
				private:

				public:
					FacebookButton() :
						HiddenButton("controls/context-facebook-button.png")
						{
							this->setRegisterAsTouchable(true);
						}

					void onTouch(CCTouch* touch, CCEvent* event)
					{
					}
			};
			
			class TwitterButton : public HiddenButton
			{
				private:

				public:
					TwitterButton() :
						HiddenButton("controls/context-twitter-button.png")
						{
							this->setRegisterAsTouchable(true);
						}

					void onTouch(CCTouch* touch, CCEvent* event)
					{
					}
			};

			class PlayButton : public Entity
			{
				private:
					Level* mParentScreen;

				public:
					PlayButton(Level* pParentScreen) :
						Entity("labels/start.png")
						{
							this->mParentScreen = pParentScreen;

							this->setRegisterAsTouchable(true);
						}

					void onTouch(CCTouch* touch, CCEvent* event)
					{
						this->mParentScreen->mBackground->runAction(CCScaleTo::create(1.0f, 1.0f));

						this->mParentScreen->mControlLayer->runAction(CCFadeTo::create(1.0f, 0.0f));

						this->mParentScreen->mButtonsHolder1->setOpacity(0);
						this->mParentScreen->mButtonsHolder2->setOpacity(0);

						this->mParentScreen->mIsShouldShowComics = true;
					}
			};

			class ButtonHolder : public Entity
			{
				int i;
				public:
					ButtonHolder(const char* pszFileName) :
						Entity(pszFileName)
						{
						}

					void update(float pDeltaTime)
					{
						Entity::update(pDeltaTime);

						i = this->getTexture()->getContentSize().height - (Utils::coord(300) - this->getCenterY());

						CCRect textureRectanle = CCRect(0, 0, this->getTexture()->getContentSize().width, i);

						this->setTextureRect(textureRectanle);
					}

					void setOpacity(GLubyte pOpacity)
					{
						if(this->getOpacity() != 0)
						Entity::setOpacity(pOpacity);
					}
			};
			
			class ComicsSkipButton : public HiddenButton
			{
				private:
					Level* mParentScreen;

				public:
					ComicsSkipButton(Level* pParentScreen) :
						HiddenButton("controls/skip-button.png")
						{
							this->setRegisterAsTouchable(true);

							this->mParentScreen = pParentScreen;
						}

					void onTouch(CCTouch* touch, CCEvent* event)
					{
						this->mParentScreen->mComicsLayer->runAction(CCFadeTo::create(1.0f, 0.0f));

						this->mParentScreen->mPlatform->runAction(CCScaleTo::create(1.0f, 1.0f));
						this->mParentScreen->mPlatform->runAction(CCMoveTo::create(1.0f, ccp(Options::CAMERA_CENTER_X, this->getCenterY() + Utils::coord(50))));

						this->mParentScreen->mWaitBeforeShowComicsTimeElasped = -1;
						this->mParentScreen->mIsShouldHideComics = true;
					}
			};

			class Layer : public CCLayerColor
			{
				public:
					Layer() :
						CCLayerColor()
						{
							this->init();
						}

					void setOpacity(GLubyte pOpacity)
					{
						CCLayerColor::setOpacity(pOpacity);

						for(int i = 0; i < this->getChildren()->count(); i++)
						{
							((CCSprite*) this->getChildren()->objectAtIndex(i))->setOpacity(pOpacity);
						}
					}

					void draw()
					{
						glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, m_pSquareVertices);

						CC_INCREMENT_GL_DRAWS(1);
					}
			};

		// ===========================================================
		// Constants
		// ===========================================================

		// ===========================================================
		// Fields
		// ===========================================================

		// ===========================================================
		// Constructors
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================

		// ===========================================================
		// Virtual Methods
		// ===========================================================

	private:
		// ===========================================================
		// Inner Classes
		// ===========================================================

		// ===========================================================
		// Constants
		// ===========================================================

		// ===========================================================
		// Fields
		// ===========================================================

		float mStartBattleTime;
		float mStartBattleTimeElapsed;

		float mBubbleAppearTime;
		float mBubbleAppearTimeElapsed;

		float mTestLevelTime;
		float mTestLevelTimeElapsed;

		float mPizzaPartTime;
		float mPizzaPartTimeElapsed;

		float mLowHealthTime;
		float mLowHealthTimeElapsed;

		float mShakeDuration;
		float mShakeIntensity;
		float mShakeDurationElapsed;

		float mWaitBeforeShowComicsTime;
		float mWaitBeforeShowComicsTimeElasped;

		float mPointerX;
		float mPointerY;

		float mSpidersRestoreTime;
		float mSpidersRestoreTimeElasped;

		float mUpgradeLevelStartTime;
		float mUpgradeLevelStartTimeElapsed;

		float mShowLevelTextPauseTime;
		float mShowLevelTextPauseTimeElapsed;

		bool mStartBattleShows;
		bool mIsGameStarted;
		bool mIsLevelLabelShows;
		bool mIsShouldStartLevel;
		bool mShaking;

		bool mUpgradeLevelStartText;

		bool mIsMainMenu;

		bool mShouldShowSeconds;

		bool mIsShouldShowComics;
		bool mIsShouldHideComics;

		int mCurrentLevel;
		int mMaxSpidersCount;

		int mTextSeconds;

		EntityManager* mEnemies1;
		EntityManager* mEnemies2;
		EntityManager* mEnemies3;
		EntityManager* mEnemies4;

		EntityManager* mEnemyBullets;

		EntityManager* mSlices;
		EntityManager* mSpiders;

		EntityManager* mStars;
		EntityManager* mSmallClouds;

		EntityManager* mEnemiesExplosions;

		CCLayer* mMainLayer;
		CCLayer* mStaticLayer;
		Layer* mControlLayer;
		Layer* mComicsLayer;

		Entity* mPrepareToBattle;
		Entity* mLevelName;
		Entity* mLevelNumber1;
		Entity* mLevelNumber2;
		CCLabelTTF* mWealthText;
		Entity* mLowHealthText;
		CCLabelTTF* mLevelStartText;

		Entity* mBackground;
		Entity* mPlatform;
		Entity* mHeroExplosion;

		Entity* mComicsPart1;
		Entity* mComicsPart2;
		Entity* mComicsPart3;
		Entity* mComicsPart4;
		Entity* mComicsPart5;

		Entity* mComicsSkipButton;

		EntityManager* mBaseBullets;
		EntityManager* mCastleBullets;
		EntityManager* mBaseBubbles;
		EntityManager* mPickups;

		EnemyWave* mEnemiesWave;

		Entity* mPauseButton;

		Joystick* mLeftJoystick;
		Joystick* mRightJoystick;

		long mLastTimeTap;
		
		SettingsButton* mSettingsButton;
		SocialButton* mSocialButton;

		CreditsButton* mCreditsButton;

		MusicButton* mMusicButton;
		SoundButton* mSoundButton;

		MoreGamesButton* mMoreGamesButton;
		FacebookButton* mFacebookButton;
		TwitterButton* mTwitterButton;

		ButtonHolder* mButtonsHolder1;
		ButtonHolder* mButtonsHolder2;

		Entity* mPlayButton;
		Entity* mLogo;

		Entity* mComicsBackground;

		int mComicsShowFrame;

		// ===========================================================
		// Constructors
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================

		void startLevel();
		void finishLevel();

		void generatePizzaDecorations();

		CCPoint getSafePizzaPosition();

		void checkCollisions(float pDeltaTime);

		void shake(float d, float i);
		void updateShake(float pDeltaTime);

		BaseEnemy* getClosestEnemy();

		long millisecondNow();
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================

	public:
		// ===========================================================
		// Inner Classes
		// ===========================================================

		// ===========================================================
		// Constants
		// ===========================================================

		static int ENTITIES;

		static int* COINS;

		// ===========================================================
		// Fields
		// ===========================================================

		CCArray* mEnemies;

		Castle* mCastle;

		EntityManagerGroup* mEnemiesGroup;

		UpgradeManager* mUpgradeLayer;

		LayerManager* mUnitsLayer;

		WealthManager* mWealth;

		Hero* mHero;

		bool mPause;

		// ===========================================================
		// Constructors
		// ===========================================================

		Level();

		// ===========================================================
		// Methods
		// ===========================================================

		void updateSpiders();
		
		// ===========================================================
		// Virtual Methods
		// ===========================================================

		bool ccTouchBegan(CCTouch* touch, CCEvent* event);
		void ccTouchMoved(CCTouch* touch, CCEvent* event);
		void ccTouchEnded(CCTouch* touch, CCEvent* event);

   		void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
   		void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
   		void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    	void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

		void update(float pDeltaTime);

		void onEnter();
		void onExit();

		void generateCloud();
		void generateStartSmalClouds();
		void generateSmallCloudsAndStars();
};

#endif