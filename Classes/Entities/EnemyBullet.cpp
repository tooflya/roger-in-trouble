#ifndef CONST_EnemyBullet
#define CONST_EnemyBullet

#include "EnemyBullet.h"

EnemyBullet::EnemyBullet()
{
	this->setPower(10);
	this->setSpeed(170);
}

EnemyBullet* EnemyBullet::deepCopy()
{
	return new EnemyBullet();
}

#endif