#ifndef CONST_SCREENMANAGER
#define CONST_SCREENMANAGER

#include "ScreenManager.h"

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

ScreenManager::ScreenManager()
{
	this->generate();
}

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

// ===========================================================
// Getters
// ===========================================================

// ===========================================================
// Setters
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

void ScreenManager::generate()
{
	this->mScreens[0] = new Level();
	this->mScreens[1] = new GameOver();
	this->mScreens[2] = new GameWon();
}

void ScreenManager::set(float pAnimationTime, int pIndex)
{
	CCTransitionScene* transition = CCTransitionFade::create(pAnimationTime, this->mScreens[pIndex]);

	CCDirector::sharedDirector()->setDepthTest(true);
	CCDirector::sharedDirector()->replaceScene(transition);
}

// ===========================================================
// Virtual methods
// ===========================================================

#endif