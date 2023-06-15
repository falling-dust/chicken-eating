//
//  enemy.h
//  PUBG
//
//  Created by wza on 2021/5/31.
//
#ifndef ENEMY_H
#define ENEMY_H
#include "actor.h"
#include "const.h"
#include "cocos2d.h"
#include "item/Pistol.h"
#include "item/Weapon.h"

using namespace cocos2d;
class enemy :public actor
{
public:
	CREATE_FUNC(enemy);
	enemy(int x = 300,int y = 360);
	void setIndex(int index);
	//bool getDead();
	bool takeDamage(int power);
	Pistol* myWeapon = nullptr;//Ö÷ÎäÆ÷
private:
	int enemyIndex;
	int health=actorConsts::enemyHealth;
	void update(float delta);
	void generateVelocity(float delta);
	void die();
	bool isDead;
	Vec2 velocity = Vec2(0,0);
	
	void SetWeaponPosition();
	void attack();
	void following(float delta);
	float fireDiatance = 200;
	float kiteDiatance = 150;
	float enemyVision = 300;
};
#endif