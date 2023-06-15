#pragma once

#ifndef _Shotgun_H_
#define _Shotgun_H_

#include "Item/Item.h"
#include"Item/Weapon.h"
using namespace cocos2d;

class Shotgun :public Weapon
{
public:
	Shotgun();
	Bullet* shootBullet(Vec2 vec, int Coefficient, bool attackDirection);
	void changeBulletamount(int mode, int num) override;
	void update(float dt) override;
	void Fire(Vec2 MousePosition, bool attackDirection) override;
	Bullet* bulletAttack[5];
	CREATE_FUNC(Shotgun);
};

#endif