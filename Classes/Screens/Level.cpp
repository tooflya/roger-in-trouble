#ifndef CONST_LEVEL
#define CONST_LEVEL

#include "Level.h"

#include "UpgradeManager.h"

// ===========================================================
// Inner Classes
// ===========================================================

class PauseButton : public Entity
{
	private:
		Level* mWorld;

	public:
		PauseButton(Level* pWorld) :
			Entity("controls/pause-button.png")
			{
				this->mWorld = pWorld;

				this->setRegisterAsTouchable(true);
			}

		void onTouch(CCTouch* touch, CCEvent* event)
		{
			if(this->mWorld->mUpgradeLayer->getParent())
			{
				this->mWorld->removeChild(this->mWorld->mUpgradeLayer);
				this->mWorld->mUnitsLayer->onEnter();

				this->mWorld->mPause = false;
			}
			else
			{
				this->mWorld->addChild(this->mWorld->mUpgradeLayer);
				this->mWorld->mUnitsLayer->onExit();
				
				this->mWorld->mPause = true;
			}
		}

};

// ===========================================================
// Constants
// ===========================================================

int Level::ENTITIES = 0;

int* Level::COINS = new int[3];

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

Level::Level()
{
	COINS[0] = 1110;
	COINS[1] = 1110;
	COINS[2] = 1110;

	this->mLastTimeTap = this->millisecondNow();

	this->setRegisterAsTouchable(true);

	this->mPause = false;

	this->mBubbleAppearTime = 1.0f;
	this->mBubbleAppearTimeElapsed = 0;

	this->mStartBattleTime = 5.0f;
	this->mStartBattleTimeElapsed = 0;

	this->mTestLevelTime = 10.0f;
	this->mTestLevelTimeElapsed = 0;

	this->mPizzaPartTime = 10.0f;
	this->mPizzaPartTimeElapsed = 0;

	this->mLowHealthTime = 1.5f;
	this->mLowHealthTimeElapsed = 0;

	this->mUpgradeLevelStartTime = 1.0f;
	this->mUpgradeLevelStartTimeElapsed = 0;

	this->mShowLevelTextPauseTime = 5.0f;
	this->mShowLevelTextPauseTimeElapsed = 0;

	this->mCurrentLevel = 0;

	this->mTextSeconds = 0;

	this->mIsGameStarted = false;
	this->mStartBattleShows = true;
	this->mIsShouldStartLevel = true;
	this->mIsLevelLabelShows = false;
	this->mShouldShowSeconds = false;

	this->mEnemies = new CCArray();
	this->mEnemies->initWithCapacity(4);

	this->mEnemiesGroup = new EntityManagerGroup(4);

	this->mUnitsLayer = new LayerManager();

	this->mMainLayer = new CCLayer();
	this->mStaticLayer = new CCLayer();
	this->mControlLayer = new Layer();
	this->mComicsLayer = new Layer();
	this->mUpgradeLayer = new UpgradeManager(this);

	this->mBackground = new Entity("main-menu/main-menu-background.png");
	this->mBackground->setIgnoreSorting(true);

	this->mPlatform = new Entity("platform/platform.png");
	this->mPlatform->setIgnoreSorting(true);

	/**this->generatePizzaDecorations();**/

	this->mPickups = new EntityManager(25, new Pickup(), this->mUnitsLayer, 5);
	this->mWealth = new WealthManager(25, new Entity("pickup/pickup-stuffs-sprite.png", 1, 3), this->mStaticLayer, 2);
	/**this->mBaseBubbles = new EntityManager(5, new Bubble(), this->mUnitsLayer, 3);**/
	this->mBaseBullets = new EntityManager(50, new BaseBullet(), this->mUnitsLayer, 5);
	this->mCastleBullets = new EntityManager(5, new BaseBullet(), this->mUnitsLayer, 5);
	this->mHero = new Hero("main-character/main-char-sprite.png", this->mBaseBullets, 1, 5);
	this->mEnemyBullets = new EntityManager(25, new EnemyBullet(), this->mUnitsLayer, 5);
	this->mEnemies1 = new EntityManager(25, new FollowEnemy(this->mHero), this->mUnitsLayer, 5);
	this->mEnemies2 = new EntityManager(25, new CastleEnemy(), this->mUnitsLayer, 5);
	this->mEnemies3 = new EntityManager(25, new FiredEnemy(this->mHero, this->mEnemyBullets), this->mUnitsLayer, 5);
	/**this->mSpiders = new EntityManager(5, new Spider(), this->mUnitsLayer, 4);*/
	this->mCastle = new Castle(this->mCastleBullets);

	this->mHeroExplosion = new Entity("explosion/explosion.png", 5, 2);
	this->mUnitsLayer->addChild(this->mHeroExplosion, 5);

	this->mPauseButton = new PauseButton(this);
	this->mPauseButton->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(80), Options::CAMERA_HEIGHT - Utils::coord(80));

	/**this->mEnemiesExplosions = new EntityManager(25, new BaseExplosion(), this->mUnitsLayer, 5);**/

	this->mEnemies->addObject(this->mEnemies1);
	this->mEnemies->addObject(this->mEnemies2);
	this->mEnemies->addObject(this->mEnemies3);

	this->mEnemiesGroup->add(this->mEnemies1);
	this->mEnemiesGroup->add(this->mEnemies2);
	this->mEnemiesGroup->add(this->mEnemies3);

	this->mLevelNumber1 = new Entity("labels/level-numer-sprite.png", 14, 1);
	this->mLevelNumber2 = new Entity("labels/level-numer-sprite.png", 14, 1);

	this->mPrepareToBattle = new Entity("labels/prepare.png");
	this->mLevelName = new Entity("labels/level-number.png");
	this->mWealthText = CCLabelTTF::create("Wealth:", "Fonts/Franchise-Bold.ttf",  24);
	this->mLowHealthText = new Entity("labels/low-health.png");
	this->mLevelStartText = CCLabelTTF::create("Level 1 will begin in 5 seconds...", "Fonts/Franchise-Bold.ttf",  36);

	this->mMainLayer->addChild(this->mBackground, -1);
	this->mUnitsLayer->addChild(this->mPlatform, -1);
	this->mPlatform->addChild(this->mCastle, 5);

	this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mPlatform->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(600));

	this->mBackground->setScale(0.7f);
	this->mPlatform->setScale(0.8f);

	this->mCastle->create()->setCenterPosition(this->mPlatform->getWidth() / 2, this->mPlatform->getHeight() / 2 + Utils::coord(200));

	this->mPrepareToBattle->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(200));
	this->mLevelName->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(150));
	this->mLevelNumber1->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(120), Options::CAMERA_CENTER_Y - Utils::coord(154));
	this->mLevelNumber2->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(150), Options::CAMERA_CENTER_Y - Utils::coord(154));
	this->mWealthText->setPosition(ccp(Utils::coord(200), Utils::coord(30)));
	this->mLowHealthText->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(200));
	this->mLevelStartText->setPosition(ccp(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(150)));
	this->mLowHealthText->setOpacity(0);
	this->mLevelStartText->setOpacity(0);

	this->addChild(this->mMainLayer);
	this->addChild(this->mControlLayer);

	this->mMainLayer->addChild(this->mUnitsLayer, 5);

	this->mUnitsLayer->addChild(this->mHero->mShadow->create(), 4);
	this->mHero->mGasesShadows->setParent(this->mUnitsLayer, 4);
	this->mHero->mGases->setParent(this->mUnitsLayer, 4);
	this->mUnitsLayer->addChild(this->mHero, 5);

	this->mStaticLayer->addChild(this->mPrepareToBattle, 2);
	this->mStaticLayer->addChild(this->mLevelName, 2);
	this->mStaticLayer->addChild(this->mWealthText, 2);
	this->mStaticLayer->addChild(this->mLowHealthText, 2);
	this->mStaticLayer->addChild(this->mLevelStartText, 2);
	this->mStaticLayer->addChild(this->mPauseButton, 2);
	this->mStaticLayer->addChild(this->mLevelNumber1, 2);
	this->mStaticLayer->addChild(this->mLevelNumber2, 2);

	this->mPrepareToBattle->setOpacity(0.0f);
	this->mLevelName->setOpacity(0.0f);
	this->mLevelNumber1->setOpacity(0);
	this->mLevelNumber2->setOpacity(0);

	/**this->mSlices = new EntityManager(5, new Slice(), this->mUnitsLayer, 7);*/

	this->mLeftJoystick = new Joystick(true);
	this->mRightJoystick = new Joystick(false);

	this->mStaticLayer->addChild(this->mLeftJoystick);
	this->mStaticLayer->addChild(this->mRightJoystick);

	this->mSpidersRestoreTime = 10.0f;
	this->mSpidersRestoreTimeElasped = 0;

	this->mMaxSpidersCount = 0;

	this->mUpgradeLevelStartText = false;

	// CONTROLS

	// BUTTONS

	this->mButtonsHolder1 = new ButtonHolder("controls/context-bg.png");
	this->mButtonsHolder2 = new ButtonHolder("controls/context-bg.png");

	this->mSettingsButton = new SettingsButton(this);
	this->mSocialButton = new SocialButton(this);

	this->mCreditsButton = new CreditsButton();

	this->mMusicButton = new MusicButton();
	this->mSoundButton = new SoundButton();

	this->mMoreGamesButton = new MoreGamesButton();
	this->mFacebookButton = new FacebookButton();
	this->mTwitterButton = new TwitterButton();

	this->mPlayButton = new PlayButton(this);

	this->mLogo = new Entity("main-menu/game-name.png");

	this->mButtonsHolder1->create()->setCenterPosition(Utils::coord(90), Utils::coord(90));
	this->mButtonsHolder2->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(90));

	this->mSettingsButton->create()->setCenterPosition(Utils::coord(90), Utils::coord(90));
	this->mSocialButton->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(90));

	this->mCreditsButton->create()->setCenterPosition(Utils::coord(90), Utils::coord(0));
	this->mMusicButton->create()->setCenterPosition(Utils::coord(90), -Utils::coord(80));
	this->mSoundButton->create()->setCenterPosition(Utils::coord(90), -Utils::coord(170));

	this->mMoreGamesButton->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(0));
	this->mFacebookButton->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(90), -Utils::coord(80));
	this->mTwitterButton->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(90), -Utils::coord(170));

	this->mLogo->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_HEIGHT - Utils::coord(150));
	this->mPlayButton->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(50));

	this->mMusicButton->setCurrentFrameIndex(Options::MUSIC_ENABLE ? 0 : 1);
	this->mSoundButton->setCurrentFrameIndex(Options::SOUND_ENABLE ? 0 : 1);

	this->mControlLayer->addChild(mButtonsHolder1);
	this->mControlLayer->addChild(mButtonsHolder2);

	this->mControlLayer->addChild(this->mCreditsButton);
	this->mControlLayer->addChild(this->mMusicButton);
	this->mControlLayer->addChild(this->mSoundButton);

	this->mControlLayer->addChild(this->mMoreGamesButton);
	this->mControlLayer->addChild(this->mFacebookButton);
	this->mControlLayer->addChild(this->mTwitterButton);

	this->mControlLayer->addChild(mSettingsButton);
	this->mControlLayer->addChild(mSocialButton);

	this->mControlLayer->addChild(this->mPlayButton);
	this->mControlLayer->addChild(this->mLogo);

	this->mControlLayer->setOpacity(255.0f);

	//

	this->mStars = new EntityManager(20, new Star(), this->mBackground, 5);
	this->mSmallClouds = new EntityManager(20, new SmallCloud(), this->mBackground, 5);

	//

	this->generateStartSmalClouds();

	// Comics

	this->mComicsBackground = new Entity("comics/background.png");

	this->mComicsSkipButton = new ComicsSkipButton(this);

	this->mComicsPart1 = new Entity("comics/1.png");
	this->mComicsPart2 = new Entity("comics/2.png");
	this->mComicsPart3 = new Entity("comics/3.png");
	this->mComicsPart4 = new Entity("comics/4.png");
	this->mComicsPart5 = new Entity("comics/5.png");

	this->mComicsBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);

	this->mComicsPart1->create()->setCenterPosition(Options::CAMERA_CENTER_X - Utils::coord(345) + Utils::coord(2000), Options::CAMERA_CENTER_Y + Utils::coord(140));
	this->mComicsPart2->create()->setCenterPosition(Options::CAMERA_CENTER_X - Utils::coord(20) + Utils::coord(2000), Options::CAMERA_CENTER_Y + Utils::coord(150));
	this->mComicsPart3->create()->setCenterPosition(Options::CAMERA_CENTER_X - Utils::coord(320) + Utils::coord(2000), Options::CAMERA_CENTER_Y - Utils::coord(120));
	this->mComicsPart4->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(10) + Utils::coord(2000), Options::CAMERA_CENTER_Y - Utils::coord(130));
	this->mComicsPart5->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(320) + Utils::coord(2000), Options::CAMERA_CENTER_Y);

	this->mComicsSkipButton->create()->setCenterPosition(Options::CAMERA_WIDTH - Utils::coord(90), Utils::coord(90));

	this->mComicsLayer->addChild(this->mComicsBackground);

	this->mComicsLayer->addChild(this->mComicsPart1);
	this->mComicsLayer->addChild(this->mComicsPart2);
	this->mComicsLayer->addChild(this->mComicsPart3);
	this->mComicsLayer->addChild(this->mComicsPart4);
	this->mComicsLayer->addChild(this->mComicsPart5);

	this->mComicsLayer->addChild(this->mComicsSkipButton);

	this->mComicsLayer->setOpacity(0.0f);

	this->mIsShouldShowComics = false;
	this->mIsShouldHideComics = false;

	this->mComicsShowFrame = 0;

	this->mWaitBeforeShowComicsTime = 1.0f;
	this->mWaitBeforeShowComicsTimeElasped = 0;

	this->mIsMainMenu = true;
}

// ===========================================================
// Methods
// ===========================================================

void Level::startLevel()
{
	this->mIsGameStarted = true;

	this->mIsLevelLabelShows = true;
	this->mIsShouldStartLevel = false;

	switch(++this->mCurrentLevel)
	{
		case 1:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(1, 0, 0)->addEnemy(5, 0, 0));

			ENTITIES = 6;
		break;
		case 2:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(5, 0, 0)->addEnemy(5, 0, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 15))->addEnemy(5, 0, 0)->addEnemy(5, 0, 0));

			ENTITIES = 20;
		break;
		case 3:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(10, 0, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 15))->addEnemy(8, 0, 0)->addEnemy(8, 0, 0));

			ENTITIES = 26;
		break;
		case 4:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(5, 1, 0));

			ENTITIES = 5;
		break;
		case 5:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(10, 0, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(5, 1, 0)->addEnemy(5, 1, 0));

			ENTITIES = 20;
		break;
		case 6:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(8, 2, 0));

			ENTITIES = 8;
		break;
		case 7:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(8, 2, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(5, 1, 0)->addEnemy(8, 2, 0)->addEnemy(8, 2, 0));

			ENTITIES = 29;
		break;
		case 8:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(10, 0, 0)->addEnemy(10, 0, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 5))->addEnemy(8, 1, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(8, 2, 0)->addEnemy(8, 2, 0));

			ENTITIES = 44;
		break;
		case 9:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(20, 0, 1));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(5, 2, 1)->addEnemy(5, 2, 1)->addEnemy(5, 1, 1)->addEnemy(5, 0, 1)->addEnemy(3, 2, 1)->addEnemy(7, 2, 1)->addEnemy(20, 0, 1));

			ENTITIES = 70;
		break;
		case 10:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(1, 3, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(1, 3, 0)->addEnemy(1, 3, 0)->addEnemy(1, 3, 0)->addEnemy(1, 3, 0)->addEnemy(1, 3, 0));

			ENTITIES = 6;
		break;
		case 11:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(20, 1, 1));

			ENTITIES = 20;
		break;
		case 12:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(2, 3, 0));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(3, 1, 0)->addEnemy(3, 1, 0)->addEnemy(3, 1, 0));

			ENTITIES = 11;
		break;
		case 13:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(20, 0, 1));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(5, 2, 2)->addEnemy(5, 2, 2)->addEnemy(5, 1, 2)->addEnemy(5, 0, 2)->addEnemy(3, 2, 2)->addEnemy(7, 2, 2)->addEnemy(20, 0, 1));

			ENTITIES = 70;
		break;
		case 14:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(12, 2, 1)->addEnemy(12, 2, 1));

			ENTITIES = 24;
		break;
		case 15:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(10, 0, 2));

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 25))->addEnemy(2, 3, 1)->addEnemy(2, 3, 1)->addEnemy(2, 3, 1));

			ENTITIES = 16;
		break;
		case 16:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(10, 1, 2)->addEnemy(10, 2, 2));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 20))->addEnemy(15, 2, 1)->addEnemy(10, 1, 2));

			ENTITIES = 45;
		break;
		case 17:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(1, 3, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 0, 2)->addEnemy(10, 0, 2));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 20))->addEnemy(5, 1, 3));

			ENTITIES = 26;
		break;
		case 18:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(1, 3, 3));

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 3))->addEnemy(1, 0, 3)->addEnemy(1, 1, 3)->addEnemy(1, 2, 3)->addEnemy(1, 1, 3)->addEnemy(1, 1, 3)->addEnemy(1, 1, 3)->addEnemy(1, 3, 3)->addEnemy(1, 0, 3)->addEnemy(1, 0, 3)
				->addEnemy(1, 2, 3)->addEnemy(1, 2, 3)->addEnemy(1, 2, 3)->addEnemy(1, 1, 3)->addEnemy(1, 1, 3)->addEnemy(1, 1, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(20, 1, 3));

			ENTITIES = 36;
		break;
		case 19:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(4, 0, 2)->addEnemy(4, 1, 2)->addEnemy(4, 2, 2)->addEnemy(4, 3, 1));

			ENTITIES = 16;
		break;
		case 20:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(30, 1, 2));

			ENTITIES = 30;
		break;
		case 21:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(8, 2, 2));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(8, 2, 2)->addEnemy(8, 2, 2));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 15))->addEnemy(3, 3, 3));

			ENTITIES = 27;
		break;
		case 22:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(30, 0, 2));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 30))->addEnemy(10, 1, 3));

			ENTITIES = 40;
		break;
		case 23:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(15, 1, 2));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(20, 0, 2)->addEnemy(20, 2, 2)->addEnemy(5, 2, 3)->addEnemy(5, 2, 3)->addEnemy(5, 2, 3)->addEnemy(5, 2, 3));

			ENTITIES = 75;
		break;
		case 24:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(2, 3, 2)->addEnemy(2, 3, 2)->addEnemy(2, 3, 2)->addEnemy(2, 3, 2));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 20))->addEnemy(30, 1, 3));

			ENTITIES = 38;
		break;
		case 25:
			this->mEnemiesWave = new EnemyWave(this);
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 0))->addEnemy(10, 0, 3));

			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 1, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 2, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 1, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 2, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 2, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 2, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 1, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 1, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(20, 0, 3));
			this->mEnemiesWave->addGroup((new EnemyGroup(this, 10))->addEnemy(10, 3, 3));

			ENTITIES = 120;
		break;
		case 26:
			AppDelegate::screens->set(3.0f, 2);

			ENTITIES = 100;

			return;
		break;
	}

	this->addChild(this->mEnemiesWave);

	this->mLevelName->runAction(CCFadeTo::create(3.0f, 255.0f));

	this->mLevelNumber1->setCurrentFrameIndex(this->mCurrentLevel >= 10 ? floor(this->mCurrentLevel / 10) : this->mCurrentLevel);
	this->mLevelNumber2->setCurrentFrameIndex(this->mCurrentLevel >= 10 ? this->mCurrentLevel - floor(this->mCurrentLevel / 10) * 10 : 0);

	this->mLevelNumber1->runAction(CCFadeTo::create(3.0f, 255.0f));

	if(this->mCurrentLevel >= 10)
	{
		this->mLevelNumber2->runAction(CCFadeTo::create(3.0f, 255.0f));
	}

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/start_level.wav");

	this->mLevelStartText->runAction(CCFadeTo::create(1.0f, 0.0f));

	this->mUpgradeLevelStartText = false;
}

void Level::finishLevel()
{
	this->mIsLevelLabelShows = true;
	this->mIsShouldStartLevel = true;

	this->removeChild(this->mEnemiesWave);
	this->mEnemiesWave->release();
	
	//this->mLevelName->setString("Level cleared!");

	this->mLevelName->runAction(CCFadeTo::create(3.0f, 255.0f));
}

void Level::generatePizzaDecorations()
{
	float cx = this->mPlatform->getWidth() / 2;
	float cy = this->mPlatform->getHeight() / 2;

	float radius = this->mPlatform->getWidth() * 0.40f;

	CCArray* decorationsSources = CCArray::create();

	decorationsSources->addObject(new Entity("pizzarelated/olive_1.png"));
	decorationsSources->addObject(new Entity("pizzarelated/salami_1.png"));
	decorationsSources->addObject(new Entity("pizzarelated/salami_2.png"));
	decorationsSources->addObject(new Entity("pizzarelated/shrooms_1.png"));

	CCArray* decorations = CCArray::create();

	for (int i = 0; i < 75; i++) {
		float angle, dist, x, y;
		bool ok;

		do {
			angle = Utils::randomf(0.0f, 1.0f) * Utils::Pi * 2.0f;
			dist = (0.3f + Utils::randomf(0.0f, 1.0f) * 0.7f) * radius * 0.95f;
			x = cx - cos(angle) * dist;
			y = cy + sin(angle) * dist * 0.5f;

			ok = true;

			for (int i = 0; i < decorations->count(); i++) {
				float dx = x - ((Entity*) decorations->objectAtIndex(i))->getCenterX();
				float dy = y + ((Entity*) decorations->objectAtIndex(i))->getCenterY();

				if (dx * dx + dy * dy < 50 * 50) {
					ok = false;
					break;
				}
			}
		} while (!ok);

		Entity* decoration = ((Entity*) decorationsSources->objectAtIndex(Utils::random(0, decorationsSources->count() - 1)))->deepCopy();
		decoration->create()->setCenterPosition(x, y);

		decorations->addObject(decoration);

		this->mPlatform->addChild(decoration);
	}

	decorationsSources->release();
	decorations->release();
}

 CCPoint Level::getSafePizzaPosition() {
	float angle, dist, x, z;

	float cx = this->mPlatform->getCenterX();
	float cy = this->mPlatform->getCenterY();

	float radius = this->mPlatform->getWidth() * 0.40f;

	angle = Utils::randomf(0.0f, 1.0f) * Utils::Pi * 2.0f;
	dist = (0.3f + Utils::randomf(0.0f, 1.0f) * .7f) * radius * 0.95f;

	x = cx + cos(angle) * dist;
	z = cy + sin(angle) * dist * 0.5f;

	return ccp(x, z);
}

void Level::checkCollisions(float pDeltaTime)
{
	int enemiesNearCastleCount = 0;
	bool castleCanFire = this->mCastle->isCanFire();

	/*for(int i = 0; i < this->mBaseBullets->getCount(); i++)
	{
		BaseBullet* bullet = (BaseBullet*) this->mBaseBullets->objectAtIndex(i);

		for(int j = 0; j < this->mBaseBubbles->getCount(); j++)
		{
			Bubble* bubble = (Bubble*) this->mBaseBubbles->objectAtIndex(j);

			if(bullet->collideWith(bubble))
			{
				bubble->removeHealth(bullet->getPower());

				bullet->onCollide();
				
				if(bubble->onCollide())
				{
					this->mPickups->create()->setCenterPosition(bubble->getCenterX(), bubble->getCenterY());
				}
			}
		}

		for(int j = 0; j < this->mEnemies1->getCount(); j++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies1->objectAtIndex(j);

			if(bullet->collideWith(enemy))
			{
				bullet->onCollide();
				
				if(enemy->onCollide(bullet))
				{
					if(Utils::probably(20))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}

					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

					this->shake(0.5f, 4.0f);

					ENTITIES--;
				}
			}
		}

		for(int j = 0; j < this->mEnemies2->getCount(); j++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies2->objectAtIndex(j);

			if(bullet->collideWith(enemy))
			{
				bullet->onCollide();
				
				if(enemy->onCollide(bullet))
				{
					if(Utils::probably(20))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}

					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

					this->shake(0.5f, 4.0f);

					ENTITIES--;
				}
			}
		}

		for(int j = 0; j < this->mEnemies3->getCount(); j++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies3->objectAtIndex(j);

			if(bullet->collideWith(enemy))
			{
				bullet->onCollide();
				
				if(enemy->onCollide(bullet))
				{
					if(Utils::probably(20))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}

					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

					this->shake(0.5f, 4.0f);

					ENTITIES--;
				}
			}
		}
	}*/

	/*for(int i = 0; i < this->mPickups->getCount(); i++)
	{
		Pickup* pickup = (Pickup*) this->mPickups->objectAtIndex(i);

		if(pickup->mIsMustDestroy) continue;

		if(this->mHero->collideWith(pickup, Utils::coord(4.0f)))
		{
			pickup->follow(this->mHero->getCenterX(), this->mHero->getCenterY());

			if(this->mHero->collideWith(pickup))
			{
				pickup->onCollide();

				this->mWealth->add(pickup->getCurrentFrameIndex());
			}
		}
	}*/

	for(int i = 0; i < this->mEnemies1->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies1->objectAtIndex(i);

		if(enemy->collideWith(this->mHero))
		{
				this->mHeroExplosion->create()->setCenterPosition(this->mHero->getCenterX(), this->mHero->getCenterY());
				this->mHeroExplosion->animate(0.1f, 0, 17, 1);
			if(this->mHero->onCollide(enemy))
			{
				this->mHeroExplosion->create()->setCenterPosition(this->mHero->getCenterX(), this->mHero->getCenterY());
				this->mHeroExplosion->animate(0.1f, 0, 17, 1);

				this->shake(2.5f, 6.0f);

				AppDelegate::screens->set(3.0f, 1);
			}
		}

		if(enemy->getHealth() <= 0 && enemy->isVisible())
		{
			enemy->death();
			
			if(Utils::probably(30))
			{
				this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
			}

			this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

			this->shake(0.5f, 4.0f);

			ENTITIES--;
		}

		/*for(int j = 0; j < this->mSpiders->getCount(); j++)
		{
			Spider* spider = (Spider*) this->mSpiders->objectAtIndex(j);

			if(spider->collideWith(enemy, 2.0f))
			{
				spider->follow(enemy->getCenterX(), spider->getCenterY(), pDeltaTime);

				if(spider->collideWith(enemy))
				{
					spider->onCollide(enemy);
				}
			}
		}

		if(this->mCastle->collideWith(enemy, 2.0f))
		{
			enemiesNearCastleCount++;
		}*/
	}

	for(int i = 0; i < this->mEnemies2->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies2->objectAtIndex(i);
		
		if(enemy->collideWith(this->mHero))
		{
			if(this->mHero->onCollide(enemy))
			{
				this->mHeroExplosion->create()->setCenterPosition(this->mHero->getCenterX(), this->mHero->getCenterY());
				this->mHeroExplosion->animate(0.1f, 0, 17, 1);

				this->shake(2.5f, 6.0f);

				AppDelegate::screens->set(3.0f, 1);
			}
		}

		if(enemy->getHealth() <= 0 && enemy->isVisible())
		{
			enemy->death();

			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/basedamage.wav");

			this->mHeroExplosion->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
			this->mHeroExplosion->animate(0.1f, 0, 17, 1);

			if(Utils::probably(30))
			{
				this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
			}

			this->shake(0.5f, 5.0f);

			ENTITIES--;

			this->mCastle->removeHealth(0.5f);
		}

		/*for(int j = 0; j < this->mSpiders->getCount(); j++)
		{
			Spider* spider = (Spider*) this->mSpiders->objectAtIndex(j);

			if(spider->collideWith(enemy, 2.0f))
			{
				spider->follow(enemy->getCenterX(), spider->getCenterY(), pDeltaTime);

				if(spider->collideWith(enemy))
				{
					spider->onCollide(enemy);
				}
			}
		}

		if(this->mCastle->collideWith(enemy, 2.0f))
		{
			enemiesNearCastleCount++;
		}*/
	}

	for(int i = 0; i < this->mEnemies3->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies3->objectAtIndex(i);
		
		if(enemy->collideWith(this->mHero))
		{
			if(this->mHero->onCollide(enemy))
			{
				this->mHeroExplosion->create()->setCenterPosition(this->mHero->getCenterX(), this->mHero->getCenterY());
				this->mHeroExplosion->animate(0.1f, 0, 17, 1);

				this->shake(2.5f, 6.0f);

				AppDelegate::screens->set(3.0f, 1);
			}
		}

		if(enemy->getHealth() <= 0 && enemy->isVisible())
		{
			enemy->death();

			if(Utils::probably(30))
			{
				this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
			}

			this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

			this->shake(0.5f, 4.0f);

			ENTITIES--;
		}

		/*for(int j = 0; j < this->mSpiders->getCount(); j++)
		{
			Spider* spider = (Spider*) this->mSpiders->objectAtIndex(j);

			if(spider->collideWith(enemy, 2.0f))
			{
				spider->follow(enemy->getCenterX(), spider->getCenterY(), pDeltaTime);

				if(spider->collideWith(enemy))
				{
					spider->onCollide(enemy);
				}
			}
		}

		if(this->mCastle->collideWith(enemy, 2.0f))
		{
			enemiesNearCastleCount++;
		}*/
	}
return;
	for(int i = 0; i < this->mEnemyBullets->getCount(); i++)
	{
		BaseBullet* bullet = (BaseBullet*) this->mEnemyBullets->objectAtIndex(i);

		if(this->mHero->collideWith(bullet))
		{
			bullet->destroy();

			if(this->mHero->onCollide(bullet))
			{
				this->mHeroExplosion->create()->setCenterPosition(this->mHero->getCenterX(), this->mHero->getCenterY());
				this->mHeroExplosion->animate(0.1f, 0, 17, 1);

				this->shake(2.5f, 6.0f);

				AppDelegate::screens->set(3.0f, 1);
			}
	
			this->mHero->mShootVectorX = bullet->mVectorX;
			this->mHero->mShootVectorY = bullet->mVectorY;

			this->mHero->mShootPadding = Utils::coord(3);
		}
	}

	if(enemiesNearCastleCount >= 5)
	{
		this->mCastle->fire();
	}
	else
	{
		this->mCastle->unfire();
	}

	if(this->mCastle->mShockwave->isVisible())
	{
		for(int i = 0; i < this->mEnemies1->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies1->objectAtIndex(i);

			if(enemy->collideWith(this->mCastle->mShockwave, 2.0f))
			{
				enemy->onCollideC(this->mCastle);
			}
		}

		for(int i = 0; i < this->mEnemies2->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies2->objectAtIndex(i);

			if(enemy->collideWith(this->mCastle->mShockwave, 2.0f))
			{
				enemy->onCollideC(this->mCastle);
			}
		}
		
		for(int i = 0; i < this->mEnemies3->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies3->objectAtIndex(i);

			if(enemy->collideWith(this->mCastle->mShockwave, 2.0f))
			{
				enemy->onCollideC(this->mCastle);
			}
		}
	}

	if(castleCanFire)
	{
		this->mCastle->fire(this->getClosestEnemy());
	}

	for(int j = 0; j < this->mCastle->mBullets->getCount(); j++)
	{
		BaseBullet* bullet = (BaseBullet*) this->mCastle->mBullets->objectAtIndex(j);

		for(int i = 0; i < this->mEnemies1->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies1->objectAtIndex(i);

			if(enemy->collideWith(bullet))
			{
				enemy->onCollide(bullet);
				bullet->destroy();
			}
		}

		for(int i = 0; i < this->mEnemies2->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies2->objectAtIndex(i);

			if(enemy->collideWith(bullet))
			{
				enemy->onCollide(bullet);
				bullet->destroy();
			}
		}
		
		for(int i = 0; i < this->mEnemies3->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies3->objectAtIndex(i);

			if(enemy->collideWith(bullet))
			{
				enemy->onCollide(bullet);
				bullet->destroy();
			}
		}
	}

	if(this->mHero->mShockwave->isVisible())
	{
		for(int i = 0; i < this->mEnemies1->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies1->objectAtIndex(i);

			if(enemy->collideWith(this->mHero->mShockwave, this->mHero->mShockwaveScale))
			{
				if(enemy->onCollide(this->mHero->mShockwaveDamage, enemy->getCenterX()-this->mHero->getCenterX(), enemy->getCenterY()-this->mHero->getCenterY()))
				{
					if(Utils::probably(30))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}

					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

					this->shake(0.5f, 4.0f);

					ENTITIES--;
				}
			}
		}

		for(int i = 0; i < this->mEnemies2->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies2->objectAtIndex(i);

			if(enemy->collideWith(this->mHero->mShockwave, this->mHero->mShockwaveScale))
			{
				if(enemy->onCollide(this->mHero->mShockwaveDamage, enemy->getCenterX()-this->mHero->getCenterX(), enemy->getCenterY()-this->mHero->getCenterY()))
				{
					if(Utils::probably(30))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}

					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

					this->shake(0.5f, 4.0f);

					ENTITIES--;
				}
			}
		}
		
		for(int i = 0; i < this->mEnemies3->getCount(); i++)
		{
			BaseEnemy* enemy = (BaseEnemy*) this->mEnemies3->objectAtIndex(i);

			if(enemy->collideWith(this->mHero->mShockwave, this->mHero->mShockwaveScale))
			{
				if(enemy->onCollide(this->mHero->mShockwaveDamage, enemy->getCenterX()-this->mHero->getCenterX(), enemy->getCenterY()-this->mHero->getCenterY()))
				{
					if(Utils::probably(30))
					{
						this->mPickups->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());
					}

					this->mEnemiesExplosions->create()->setCenterPosition(enemy->getCenterX(), enemy->getCenterY());

					this->shake(0.5f, 4.0f);

					ENTITIES--;
				}
			}
		}

		for(int i = 0; i < this->mBaseBubbles->getCount(); i++)
		{
			Bubble* bubble = (Bubble*) this->mBaseBubbles->objectAtIndex(i);

			if(bubble->collideWith(this->mHero->mShockwave))
			{
				bubble->removeHealth(this->mHero->mShockwaveDamage);

				if(bubble->onCollide())
				{
					this->mPickups->create()->setCenterPosition(bubble->getCenterX(), bubble->getCenterY());
				}
			}
		}
	}
}

BaseEnemy* Level::getClosestEnemy()
{
	BaseEnemy* closest = NULL;
	float distance = 0;

	for(int i = 0; i < this->mEnemies1->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies1->objectAtIndex(i);

		float d = Utils::distance(this->mCastle->getCenterX(), this->mCastle->getCenterY(), enemy->getCenterX(), enemy->getCenterY());

		if(closest == NULL || distance > d)
		{
			closest = enemy;

			distance = d;
		}
	}

	for(int i = 0; i < this->mEnemies2->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies2->objectAtIndex(i);

		float d = Utils::distance(this->mCastle->getCenterX(), this->mCastle->getCenterY(), enemy->getCenterX(), enemy->getCenterY());

		if(closest == NULL || distance > d)
		{
			closest = enemy;

			distance = d;
		}
	}
		
	for(int i = 0; i < this->mEnemies3->getCount(); i++)
	{
		BaseEnemy* enemy = (BaseEnemy*) this->mEnemies3->objectAtIndex(i);

		float d = Utils::distance(this->mCastle->getCenterX(), this->mCastle->getCenterY(), enemy->getCenterX(), enemy->getCenterY());

		if(closest == NULL || distance > d)
		{
			closest = enemy;

			distance = d;
		}
	}

	return closest;
}

void Level::shake(float d, float i)
{
	this->mShaking = true;
	this->mShakeDuration = d;
	this->mShakeIntensity = i;

	this->mShakeDurationElapsed = 0;
}

void Level::updateShake(float pDeltaTime)
{
	if(this->mShaking)
	{
		this->mShakeDurationElapsed += pDeltaTime;

		if(this->mShakeDurationElapsed > this->mShakeDuration)
		{
			this->mShaking = false;
			this->mShakeDuration = 0;
		}
		else
		{
			int sentitX = 1;
			int sentitY = 1;
			 	
			if(Utils::randomf(0, 1) < 0.5) sentitX = -1;
			if(Utils::randomf(0, 1) < 0.5) sentitY = -1;

			this->mMainLayer->setPosition(this->mMainLayer->getPosition().x + Utils::randomf(0, 1) * this->mShakeIntensity * sentitX, this->mMainLayer->getPosition().y + Utils::randomf(0, 1) * this->mShakeIntensity * sentitY);
		}
	}
}

// ===========================================================
// Virtual Methods
// ===========================================================

void Level::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    
}

void Level::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{

}

void Level::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    
}

void Level::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    ccTouchesEnded(pTouches, pEvent);
}

bool Level::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(this->mPause) return false;

	if(Screen::ccTouchBegan(touch, event))
	{
		CCPoint location  = this->mStaticLayer->convertTouchToNodeSpaceAR(touch);

		this->mPointerX = location.x;
		this->mPointerY = location.y;

		if(location.x < Options::CAMERA_CENTER_X)
		{
			this->mLeftJoystick->fade(true);
			this->mLeftJoystick->setCenterPosition(location.x, location.y);

			// Fly
			if(true) // TODO: this->mHero->isCanFly()
			{
				if(this->millisecondNow() - this->mLastTimeTap < 300.0f)
				{
					if(this->mHero->getZ() > Options::MIN_Z)
					{
						if(this->mHero->startFlyDamage())
						{
							this->shake(0.8f, 4.0f);

							this->mLastTimeTap = 0;

							return true;
						}
					}
					else
					{
						this->mHero->startFly();
					}
				}

				this->mLastTimeTap = this->millisecondNow();
			}
		}
		else
		{
			this->mRightJoystick->fade(true);
			this->mRightJoystick->setCenterPosition(location.x, location.y);

			this->mHero->mIsShouldFire = true;
		}

		return true;
	}

	return false;
}

void Level::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if(this->mPause) return;
	
	CCPoint location  = this->mStaticLayer->convertTouchToNodeSpaceAR(touch);

	if(location.x < Options::CAMERA_CENTER_X)
	{
		this->mLeftJoystick->fade(false);

		this->mHero->endFly();
	}
	else
	{
		this->mRightJoystick->fade(false);

		this->mHero->mIsShouldFire = false;
	}
}

void Level::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if(this->mPause) return;

	CCPoint location  = this->mStaticLayer->convertTouchToNodeSpaceAR(touch);

	if(this->mLeftJoystick->getOpacity() > 0 && location.x < Options::CAMERA_CENTER_X) this->mLeftJoystick->update(location);
	if(this->mRightJoystick->getOpacity() > 0 && location.x > Options::CAMERA_CENTER_X) this->mRightJoystick->update(location);

	this->mPointerX = this->mLeftJoystick->getVector().x;
	this->mPointerY = this->mLeftJoystick->getVector().y;

	float x = this->mPointerX;
	float y = this->mPointerY;

	this->mHero->setFollowCoordinates(x, y);

	if(this->mHero->mIsShouldFire)
	{
		x = -this->mRightJoystick->getVector().x;
		y = -this->mRightJoystick->getVector().y;

		this->mHero->setFireCoordinates(x, y);
	}
}

void Level::update(float pDeltaTime)
{
	if(this->mPause) return;

	float potencialX = -this->mHero->getCenterX() + Options::CAMERA_CENTER_X;
	float potencialY = -this->mHero->getCenterY() + Options::CAMERA_CENTER_Y + this->mHero->getZ();

	if(potencialY < Utils::coord(205) && potencialY > -Utils::coord(205))
	this->mMainLayer->setPosition(this->mMainLayer->getPosition().x, potencialY);

	if(potencialX < Utils::coord(380) && potencialX > -Utils::coord(380))
	this->mMainLayer->setPosition(potencialX, this->mMainLayer->getPosition().y);

	// Decorations

	this->generateSmallCloudsAndStars();

	// Comics

	if(this->mIsShouldShowComics)
	{
		this->mWaitBeforeShowComicsTimeElasped += pDeltaTime;

		if(this->mWaitBeforeShowComicsTimeElasped >= this->mWaitBeforeShowComicsTime)
		{
			this->mIsShouldShowComics = false;

			this->addChild(this->mComicsLayer);

			this->removeChild(this->mControlLayer);

			this->mComicsLayer->runAction(CCFadeTo::create(1.0f, 255.0f));
		}
	}

	if(this->mIsShouldHideComics)
	{
		this->mWaitBeforeShowComicsTimeElasped += pDeltaTime;

		if(this->mWaitBeforeShowComicsTimeElasped >= this->mWaitBeforeShowComicsTime)
		{
			this->mIsShouldHideComics = false;

			this->removeChild(this->mComicsLayer);

			this->addChild(this->mStaticLayer);

			this->mHero->reset();
			this->mHero->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(0), Options::CAMERA_CENTER_Y - Utils::coord(0));

			//this->mStaticLayer->setOpacity(0.0f);
			this->mStaticLayer->runAction(CCFadeTo::create(1.0f, 255.0f));

			this->mIsMainMenu = false;
		}
	}
	else if(this->mComicsLayer->getParent())
	{
		this->mWaitBeforeShowComicsTimeElasped += pDeltaTime;

		if(this->mWaitBeforeShowComicsTimeElasped >= this->mWaitBeforeShowComicsTime)
		{
			this->mWaitBeforeShowComicsTimeElasped = 0;

			this->mComicsShowFrame++;
			
			if(this->mComicsShowFrame > 1 && this->mComicsShowFrame < 7)
			{
				//this->shake(0.3f, 12.0f);
			}

			switch(this->mComicsShowFrame)
			{
				case 1:
					this->mComicsPart1->runAction(CCMoveTo::create(this->mWaitBeforeShowComicsTime, ccp(Options::CAMERA_CENTER_X - Utils::coord(340), Options::CAMERA_CENTER_Y + Utils::coord(140))));
				break;
				case 2:
					this->mComicsPart2->runAction(CCMoveTo::create(this->mWaitBeforeShowComicsTime, ccp(Options::CAMERA_CENTER_X - Utils::coord(20), Options::CAMERA_CENTER_Y + Utils::coord(150))));
				break;
				case 3:
					this->mComicsPart3->runAction(CCMoveTo::create(this->mWaitBeforeShowComicsTime, ccp(Options::CAMERA_CENTER_X - Utils::coord(315), Options::CAMERA_CENTER_Y - Utils::coord(120))));
				break;
				case 4:
					this->mComicsPart4->runAction(CCMoveTo::create(this->mWaitBeforeShowComicsTime, ccp(Options::CAMERA_CENTER_X + Utils::coord(10), Options::CAMERA_CENTER_Y - Utils::coord(130))));
				break;
				case 5:
					this->mComicsPart5->runAction(CCMoveTo::create(this->mWaitBeforeShowComicsTime, ccp(Options::CAMERA_CENTER_X + Utils::coord(320), Options::CAMERA_CENTER_Y)));
				break;
				case 6:
					this->mComicsSkipButton->changeTexture(new Texture("controls/okey-button.png", 1, 1));
				break;
			}
		}
	}

	if(this->mIsMainMenu) return;

	// Shake 

	this->updateShake(pDeltaTime);

	// Pizza parts

	/*this->mPizzaPartTimeElapsed += pDeltaTime;

	if(this->mPizzaPartTimeElapsed >= this->mPizzaPartTime)
	{
		this->mPizzaPartTimeElapsed = 0;

		if(Utils::probably(50))
		{
			((Slice*) this->mSlices->create())->setFollowCoordinates(this->mHero->getCenterX(), this->mHero->getCenterY());

			if(Utils::probably(30) && this->mSlices->getCount() < 3)
			{
				this->mPizzaPartTimeElapsed = this->mPizzaPartTime;
			}
		}
	}

	// Bubbles

	if(this->mBaseBubbles->getCount() < 2)
	{
		this->mBubbleAppearTimeElapsed += pDeltaTime;

		if(this->mBubbleAppearTimeElapsed >= this->mBubbleAppearTime)
		{
			this->mBubbleAppearTimeElapsed = 0;
			this->mBubbleAppearTime = 5.0f + Utils::randomf(0.0f, 10.0f);

			CCPoint location = this->getSafePizzaPosition();

			this->mBaseBubbles->create()->setCenterPosition(location.x, location.y);
		}
	}*/

	// Labels

	this->mLowHealthTimeElapsed += pDeltaTime;

	if(this->mLowHealthTimeElapsed >= this->mLowHealthTime && this->mIsGameStarted)
	{
		this->mLowHealthTimeElapsed = 0;

		if(this->mHero->getHealth() <= this->mHero->getMaxHealth() / 3 && this->mLowHealthText->getOpacity() <= 0.0f && this->mPrepareToBattle->getOpacity() <= 0.0f && this->mLevelStartText->getOpacity() <= 0.0f)
		{
			if(this->mLowHealthText->getOpacity() <= 0.0f)
			{
				this->mLowHealthText->runAction(CCFadeTo::create(1.0f, 255.0f));
			}
		}
		else
		{
			if(this->mLowHealthText->getOpacity() >= 0.0f)
			{
				this->mLowHealthText->runAction(CCFadeTo::create(1.0f, 0.0f));
			}
		}
	}

	if(this->mStartBattleShows)
	{
		this->mStartBattleTimeElapsed += pDeltaTime;

		if(this->mStartBattleTimeElapsed >= this->mStartBattleTime)
		{
			this->mStartBattleShows = false;

			this->mStartBattleTimeElapsed = 0;

			this->mPrepareToBattle->runAction(CCFadeTo::create(3.0f, 255.0f));
		}
	}
	else if(!this->mIsGameStarted)
	{
		this->mStartBattleTimeElapsed += pDeltaTime;

		if(this->mStartBattleTimeElapsed >= this->mStartBattleTime && this->mTextSeconds <= 0)
		{
			this->mStartBattleTimeElapsed = 0;

			if(this->mPrepareToBattle->getOpacity() <= 0.0f)
			{
				this->startLevel();
			}
			else
			{
				this->mPrepareToBattle->runAction(CCFadeTo::create(3.0f, 0.0f));
			}
		}
	}

	if(this->mShouldShowSeconds)
	{
		this->mShowLevelTextPauseTimeElapsed += pDeltaTime;

		if(this->mShowLevelTextPauseTimeElapsed >= this->mShowLevelTextPauseTime)
		{
			this->mShowLevelTextPauseTimeElapsed = 0;

			this->mShouldShowSeconds = false;

			this->mUpgradeLevelStartText = true;
			this->mTextSeconds = 5;
			
			this->mLevelStartText->runAction(CCFadeTo::create(1.0f, 255.0f));

			char text[512];
			sprintf(text, "Level %d will begin in %d seconds...", this->mCurrentLevel + 1, this->mTextSeconds);
			this->mLevelStartText->setString(text);
		}
	}

	if(this->mIsLevelLabelShows)
	{
		this->mStartBattleTimeElapsed += pDeltaTime;

		if(this->mStartBattleTimeElapsed >= this->mStartBattleTime)
		{
			this->mStartBattleTimeElapsed = 0;

			this->mIsLevelLabelShows = false;

			this->mLevelName->runAction(CCFadeTo::create(1.0f, 0.0f));
			this->mLevelNumber1->runAction(CCFadeTo::create(1.0f, 0.0f));
			this->mLevelNumber2->runAction(CCFadeTo::create(1.0f, 0.0f));
		}
	}


	if(this->mUpgradeLevelStartText)
	{
		this->mUpgradeLevelStartTimeElapsed += pDeltaTime;

		if(this->mUpgradeLevelStartTimeElapsed >= this->mUpgradeLevelStartTime)
		{
			this->mUpgradeLevelStartTimeElapsed -= this->mUpgradeLevelStartTime;

			char text[512];
			sprintf(text, "Level %d will begin in %d seconds...", this->mCurrentLevel + 1, this->mTextSeconds);
			this->mLevelStartText->setString(text);

			this->mTextSeconds--;
		}
	}

	// HERO DEATH

	if(this->mHero->getHealth() <= 0 && this->mIsGameStarted)
	{
		this->shake(2.5f, 6.0f);

		//AppDelegate::screens->set(3.0f, 1);
	}

	if(this->mIsGameStarted)
	{
		this->mTestLevelTimeElapsed += pDeltaTime;

		if(this->mTestLevelTimeElapsed >= this->mTestLevelTime && this->mTextSeconds <= 0)
		{
			if(this->mIsShouldStartLevel)
			{
				this->mTestLevelTimeElapsed = 0;

				this->startLevel();
			}
			else
			{
				if(ENTITIES <= 0)
				{
					this->mTestLevelTimeElapsed = 0;

					this->finishLevel();

					if(this->mCurrentLevel > 0)
					{
						this->mShouldShowSeconds = true;
					}
				}
			}
		}
	}

	// Collisions

	this->checkCollisions(pDeltaTime);

	this->mUnitsLayer->update(pDeltaTime); // What for? O_o

	this->mEnemiesGroup->update(pDeltaTime); // What for? O_o

	if(this->mWealth->getCount() <= 0)
	{
		this->mWealthText->setVisible(false);
	}
	else
	{
		this->mWealthText->setVisible(true);
	}
return;
	// Spiders

	if(this->mSpiders->getCount() < this->mMaxSpidersCount)
	{
		this->mSpidersRestoreTimeElasped += pDeltaTime;

		if(this->mSpidersRestoreTimeElasped >= this->mSpidersRestoreTime)
		{
			this->mSpidersRestoreTimeElasped -= this->mSpidersRestoreTime;

			this->mSpiders->create();
		}
	}
}

void Level::onEnter()
{
	Screen::onEnter();
}

void Level::onExit()
{
	Screen::onExit();
}

// UPDATES

void Level::updateSpiders()
{
	this->mMaxSpidersCount += 6;
}

long Level::millisecondNow()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_sec / 1000);
}

void Level::generateCloud()
{
	//if(this->mClouds->getCount() < 2 && Utils::probably(1))
	{
	}
}

void Level::generateStartSmalClouds()
{
	for(int i = 0; i < 20; i++)
	{
		((SmallCloud*) this->mSmallClouds->create())->init(0, this->mBackground->getWidth(), 0, this->mBackground->getHeight(), true);
	}
}

void Level::generateSmallCloudsAndStars()
{
	if(this->mSmallClouds->getCount() < 20)
	{
		((SmallCloud*) this->mSmallClouds->create())->init(0, this->mBackground->getWidth(), 0, this->mBackground->getHeight(), false);
	}

	if(this->mStars->getCount() < 20)
	{
		((Star*) this->mStars->create())->init(0, this->mBackground->getWidth(), this->mBackground->getHeight(), 0);
	}
}

#endif