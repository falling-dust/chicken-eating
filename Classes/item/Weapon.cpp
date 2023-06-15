#include"Weapon.h"

int Weapon::nowBulletAmount_1 = pistolBulletCapacity;
int Weapon::nowBulletAmount_2 = rifleBulletCapacity;
int Weapon::nowBulletAmount_3 = shotgunBulletCapacity;
int Weapon::nowBulletAmount_4 = gatlingBulletCapacity;
int Weapon::nowBulletInventory_1 = 40;
int Weapon::nowBulletInventory_2 = 40;
int Weapon::nowBulletInventory_3 = 40;
int Weapon::nowBulletInventory_4 = 100;

Weapon::Weapon()
{
	myBullet = Bullet::create();
	MouseImage = Sprite::create("aimer.png");
	addChild(MouseImage);
	getMouseImage()->setVisible(false);
}

int Weapon::getPower()
{
	return MyWeaponPower;
}

void Weapon::setPower(int power)
{
	MyWeaponPower = power;
}

void Weapon::setShootingSpeed(float speed)
{
	ShootingSpeed = speed;
}

void Weapon::setBulletCapacity(const int capacity)
{
	Weapon::BulletCapacity = capacity;

}

int Weapon::getCapacity()
{
	return BulletCapacity;
	
}

float Weapon::getShootingSpeed()
{
	return ShootingSpeed;
}

Vec2 Weapon::getWeaponPosition()
{
	return mySprite->getPosition();
}

Sprite* Weapon::getMouseImage()
{
	return MouseImage;
}

int Weapon::getNowBulletAmount(int type)
{
	if (type == isPistol)
		return nowBulletAmount_1;
	else if (type == isRifle)
		return nowBulletAmount_2;
	else if (type == isShotgun)
		return nowBulletAmount_3;
	else if (type == isGatling)
		return nowBulletAmount_4;

	return 0;
}

void Weapon::restoreAttackState(float dt)
{
	AttackState = true;
}

int Weapon::getBulletInventory(int type)
{
	if (type == isPistol)
		return nowBulletInventory_1;
	else if (type == isRifle)
		return nowBulletInventory_2;
	else if (type == isShotgun)
		return nowBulletInventory_3; 
	else if (type == isGatling)
		return nowBulletInventory_4;

		return 0;

}

void Weapon::setBulletInventory(bool mode, int num,int type)
{
	if (mode==true)
	{
		if (type == isPistol)
			nowBulletInventory_1 += num;
		else if (type == isRifle)
			nowBulletInventory_2 += num;
		else if (type == isShotgun)
			nowBulletInventory_3 += num;
		else if (type == isGatling)
			nowBulletInventory_4 += num;
	}
	else
	{
		if (type == isPistol)
			nowBulletInventory_1 -= num;
		else if (type == isRifle)
			nowBulletInventory_2 -= num;
		else if (type == isShotgun)
			nowBulletInventory_3 -= num;
		else if (type == isGatling)
			nowBulletInventory_4 -= num;
	}
}

void Weapon::setAttackState(bool state)
{
	AttackState = state;
}

void Weapon::setAddBulletCD(double CD)
{
	addBulletCD = CD;
}

double Weapon::getAddBulletCD()
{
	return addBulletCD;
}

Bullet* Weapon::getMyBullet()
{
	return myBullet;
}