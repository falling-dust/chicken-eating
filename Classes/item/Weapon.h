#pragma once

#ifndef _Weapon_H_
#define _Weapon_H_

#include "Item.h"
#include "Bullet.h"
using namespace cocos2d;

class Weapon :public Item
{
public:
	Weapon();

	void setPower(int power);

	int getPower();

	void setShootingSpeed(float speed);

	float getShootingSpeed();

	void setBulletCapacity(int capacity);

	int getCapacity();

	virtual void update(float dt) = 0;

	Sprite* getMouseImage();

	static int getNowBulletAmount(int type);

	virtual void changeBulletamount(int mode,int num) = 0;

	Vec2 getWeaponPosition();
	Vec2 HeroPosition;

	int weaponType = 0;

	void restoreAttackState(float dt);
	virtual void Fire(Vec2 MousePosition,bool attackDirection) = 0;
	Vec2 viewPosition;//��������ƶ�����

	static int getBulletInventory(int type);

	void setBulletInventory(bool mode,int num,int type);//mode1Ϊ���ӣ���0Ϊ����

	void setAttackState(bool state);

	void setAddBulletCD(double CD);

	double getAddBulletCD();

	Bullet* getMyBullet();
protected:
	Sprite* MouseImage;
    Bullet*  myBullet;
	int MyWeaponPower = 0;
	float ShootingSpeed = 0;
	double addBulletCD = 0;
	
	static int nowBulletAmount_1;//��ǹ�ڵ����е��ӵ�����
	static int nowBulletAmount_2;//��ǹ�ڵ����е��ӵ�����
	static int nowBulletAmount_3;//ɢ��ǹ�ڵ����е��ӵ�����
	static int nowBulletAmount_4;//�ƽ��ڵ����е��ӵ���
	bool AttackState = true;
	static int nowBulletInventory_1;//�ֱ����и���ǹ���ӵ�����
	static int nowBulletInventory_2;//�ֱ����иò�ǹ���ӵ�����
	static int nowBulletInventory_3;//�ֱ����и�ɢ��ǹ���ӵ�����
	static int nowBulletInventory_4;//�ֱ����м����ֵ��ӵ���
	int BulletCapacity;//��ǹ���ӵ�����
};
#endif