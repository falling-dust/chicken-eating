#pragma once

#ifndef _Pistol_H_
#define _Pistol_H_

#include "Item/Item.h"
#include"Item/Weapon.h"
using namespace cocos2d;

class Pistol :public Weapon
{
public:
	Pistol();
	Bullet* shootBullet(Vec2 vec, bool attackDirection);
	void changeBulletamount(int mode, int num) override;
	void update(float dt) override;
	void Fire(Vec2 MousePosition, bool attackDirection) override;
	CREATE_FUNC(Pistol);
};

#endif