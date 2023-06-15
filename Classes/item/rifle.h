#pragma once

#ifndef _Rifle_H_
#define _Rifle_H_

#include "item/Item.h"
#include"item/Weapon.h"
using namespace cocos2d;

class Rifle :public Weapon
{
public:
	Rifle();
	Bullet* shootBullet(Vec2 vec, bool attackDirection);
	void changeBulletamount(int mode, int num) override;
	void update(float dt) override;
	void Fire(Vec2 MousePosition, bool attackDirection) override;
	CREATE_FUNC(Rifle);
};



#endif