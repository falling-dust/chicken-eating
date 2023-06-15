#pragma once


#ifndef _Sword_H_
#define _Sword_H_

#include "Item/Item.h"
#include"Item/Weapon.h"
using namespace cocos2d;


class Sword :public Weapon
{
public:
	Sword();
	void update(float dt) override;
	void changeBulletamount(int mode, int num) override;
	void Fire(Vec2 MousePosition, bool attackDirection) override;
	Animate*  attackAnimation(bool attackDirection);
	void attackEnd(float dt);
	Bullet* shootBullet(Vec2 vec, int Coefficient, bool attackDirection);
	void removeFire(float dt);
	Bullet* bulletAttack[5];

};

#endif