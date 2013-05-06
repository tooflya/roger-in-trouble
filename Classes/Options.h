#ifndef CONST_OPTIONS_H
#define CONST_OPTIONS_H

class Entity;

class Options
{
	public:
		static int CENTER_X;
		static int CENTER_Y;

		static int SCREEN_WIDTH;
		static int SCREEN_HEIGHT;

		static int SCREEN_CENTER_X;
		static int SCREEN_CENTER_Y;

		static int CAMERA_WIDTH;
		static int CAMERA_HEIGHT;

		static int CAMERA_CENTER_X;
		static int CAMERA_CENTER_Y;

		static float MIN_Z;
		static float MAX_Z;

		static bool MUSIC_ENABLE;
		static bool SOUND_ENABLE;

		static Entity* BASE;
};

#endif