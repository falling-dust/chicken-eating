#pragma once

#ifndef _Bullet_H_
#define _Bullet_H_
#include "cocos2d.h"

#include <vector>
using namespace cocos2d;


class Bullet :public Sprite
{
public:
	virtual bool init();
	
	Sprite* NewBullet();

	void SetDamage(int damage);

	int GetDamage();

	CREATE_FUNC(Bullet);

	Sprite* m_pBulletSprite;
protected:
	
	Size winSize;
	void initData();

	int BulletDamage;


};

#endif