#ifndef CONST_GAMEWON
#define CONST_GAMEWON

#include "GameWon.h"

// ===========================================================
// Inner Classes
// ===========================================================

class GameWonMenuButton : public Entity
{
	public:
		GameWonMenuButton() :
			Entity("controls/menu-button.png")
			{
				this->setRegisterAsTouchable(true);
			}

		void onTouch(CCTouch* touch, CCEvent* event)
		{
			// TODO: Restore MainMenu layer.
		}
};

class GameWonRestartButton : public Entity
{
	public:
		GameWonRestartButton() :
			Entity("controls/restart-button.png")
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

GameWon::GameWon()
{
	this->mBackground = new Entity("game-passed/background.png");
	this->mBackgroundTitle = new Entity("game-passed/title.png");

	this->mMenuButton = new GameWonMenuButton();
	this->mRestartButton = new GameWonRestartButton();

	this->mBackground->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mBackgroundTitle->create()->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y + Utils::coord(200));

	this->mMenuButton->create()->setCenterPosition(Options::CAMERA_CENTER_X - Utils::coord(80), Utils::coord(90));
	this->mRestartButton->create()->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(80), Utils::coord(90));

	this->addChild(this->mBackground);
	this->addChild(this->mBackgroundTitle);

	this->addChild(this->mMenuButton);
	this->addChild(this->mRestartButton);
}

// ===========================================================
// Methods
// ===========================================================

// ===========================================================
// Virtual Methods
// ===========================================================

#endif