#ifndef CONST_MAINMENU
#define CONST_MAINMENU

#include "MainMenu.h"

// ===========================================================
// Inner Classes
// ===========================================================

class PlayButton : public Entity
{
	public:
		PlayButton(const char* pszFileName) :
			Entity(pszFileName)
			{
				this->setRegisterAsTouchable(true);
			}

			void onTouch(CCTouch* touch, CCEvent* event)
			{
				AppDelegate::screens->set(1.0f, 0);
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

MainMenu::MainMenu()
{
	new BackgroundStarsManager(this);

	this->mBackground = new Entity("gui/splash.png");
	this->mPlayButton = new PlayButton("gui/button_start.png");

	this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mPlayButton->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(150));

	this->addChild(this->mBackground);
	this->addChild(this->mPlayButton);
}

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

#endif