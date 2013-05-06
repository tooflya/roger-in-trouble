#ifndef CONST_PRELOADER
#define CONST_PRELOADER

#include "Preloader.h"

// ===========================================================
// Init
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

Preloader::Preloader(void)
{
	this->mNumberOfLoadedSprites = 0;
	this->mNumberOfSprites = 1;

	this->mBackground = new Entity("start-preloader/preloader-bg.png");
	this->mBarBackground = new Entity("start-preloader/preloader-bar.png");
	this->mBar = new Entity("start-preloader/preloader-fill.png");

	this->mLoadingText = CCLabelTTF::create("00 %", "Fonts/Franchise-Bold.ttf", 36);

	this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mBarBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(230));
	this->mBar->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(230));

	this->mLoadingText->setPosition(ccp(this->mBar->getCenterX(), this->mBar->getCenterY()));

	this->addChild(this->mBackground);
	this->addChild(this->mBarBackground);
	this->addChild(this->mBar);

	this->addChild(this->mLoadingText);

	CCTextureCache::sharedTextureCache()->addImageAsync("base/cherry.png", this, callfuncO_selector(Preloader::loadingCallBack));
}

// ===========================================================
// Getters
// ===========================================================

// ===========================================================
// Setters
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

void Preloader::loadingCallBack(CCObject *obj)
{
	++mNumberOfLoadedSprites;
	
	int percent = (int) (((float) mNumberOfLoadedSprites / mNumberOfSprites) * 100);
	
	this->mLoadingText->setString((Utils::intToString(percent) + " %").c_str());

	if(mNumberOfLoadedSprites == mNumberOfSprites)
	{
		AppDelegate::screens = new ScreenManager();

		AppDelegate::screens->set(1.0f, 0);
	}
	else
	{

	}
}

// ===========================================================
// Virtual methods
// ===========================================================

void Preloader::update(float pDeltaTime)
{
	Screen::update(pDeltaTime);

	this->mBar->setRotation(this->mBar->getRotation() + 1);
}

#endif