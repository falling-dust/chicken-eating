#pragma once
//
//  enemy.h
//  PUBG
//
//  Created by wza on 2021/5/31.
//
#ifndef BOSS_H
#define BOSS_H
#include "actor.h"
#include "const.h"
#include "cocos2d.h"
#include "item/Pistol.h"
#include "item/Weapon.h"

using namespace cocos2d;
class boss :public actor
{
public:
	CREATE_FUNC(boss);
	boss(int x = 2500, int y =1200);
	void setIndex(int index);
	//bool getDead();
	bool takeDamage(int power);
	Gatling* myWeapon = nullptr;//Ö÷ÎäÆ÷
private:
	int enemyIndex;
	int health = actorConsts::enemyHealth;
	void update(float delta);
	void generateVelocity(float delta);
	void die();
	bool isDead;
	Vec2 velocity = Vec2(0, 0);

	void SetWeaponPosition();
	void attack();
	void following(float delta);
	float fireDiatance = 250;
	float kiteDiatance = 180;
	float enemyVision = 320;
};
#endif
