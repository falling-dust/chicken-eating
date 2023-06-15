#pragma once
#pragma once

#ifndef _Gatling_H_
#define _Gatling_H_

#include "item/Item.h"
#include"item/Weapon.h"
using namespace cocos2d;

class Gatling :public Weapon
{
public:
	Gatling();
	Bullet* shootBullet(Vec2 vec, bool attackDirection);
	void changeBulletamount(int mode, int num) override;
	void update(float dt) override;
	void Fire(Vec2 MousePosition, bool attackDirection) override;
	CREATE_FUNC(Gatling);
};



#endif