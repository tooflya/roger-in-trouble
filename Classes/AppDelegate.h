#ifndef CONST_APPDELEGATE_H
#define CONST_APPDELEGATE_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include <vector>

#include "Options.h"

#include "Screen.h"
#include "Preloader.h"
#include "ScreenManager.h"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

class ScreenManager;

typedef struct tagResource {
	CCSize size;
	char directory[100];
} Resource;

static Resource Resources1280x720 	= { CCSizeMake(1280, 720),  "Graphics/1280x720"   };
static CCSize   designResolutionSize  = CCSizeMake(1280, 720);

class AppDelegate : private CCApplication
{
	public:
		bool applicationDidFinishLaunching();

		void applicationDidEnterBackground();
		void applicationWillEnterForeground();

		static ScreenManager* screens;
};

#endif