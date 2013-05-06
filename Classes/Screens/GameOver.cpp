#ifndef CONST_GAMEOVER
#define CONST_GAMEOVER

#include "GameOver.h"

// ===========================================================
// Inner Classes
// ===========================================================

class GameOverMenuButton : public Entity
{
	public:
		GameOverMenuButton() :
			Entity("controls/menu-button.png")
			{
				this->setRegisterAsTouchable(true);
			}

		void onTouch(CCTouch* touch, CCEvent* event)
		{
			// TODO: Restore MainMenu layer.
		}
};

class GameOverRestartButton : public Entity
{
	public:
		GameOverRestartButton() :
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

GameOver::GameOver()
{
	this->mBackground = new Entity("game-over/background.png");
	this->mBackgroundTitle = new Entity("game-over/title.png");

	this->mMenuButton = new GameOverMenuButton();
	this->mRestartButton = new GameOverRestartButton();

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