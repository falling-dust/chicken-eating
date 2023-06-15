#include "rifle.h"

Rifle::Rifle()
{
	bindSprite(Sprite::create("rifle.png"));
	if (mySprite == nullptr)
	{
		log("rifle.png is not found");
	}
	scheduleUpdate();
	weaponType = isRifle;
	setPower(riflePower);
	setBulletCapacity(rifleBulletCapacity);
	setShootingSpeed(rifleShottingSpeed);
	setAddBulletCD(rifleAddBulletCD);
}

void Rifle::update(float dt)
{
	
	if (getState() == false)
		;
	else
	{
		mySprite->setPosition(HeroPosition);
	}
}

Bullet* Rifle::shootBullet(Vec2 vec, bool attackDirection)
{
	Bullet* newBullet = Bullet::create();
	if (attackDirection)
		newBullet->setPosition(getWeaponPosition().x + 10, getWeaponPosition().y);
	else
		newBullet->setPosition(getWeaponPosition().x - 10, getWeaponPosition().y);
	newBullet->m_pBulletSprite->getPhysicsBody()->setVelocity(vec);
	return newBullet;
}

void Rifle::changeBulletamount(int mode, int num)
{
	switch (mode)
	{
	case 1:
		nowBulletAmount_2--;
		break;
	case 2:
		nowBulletAmount_2 = rifleBulletCapacity;
		break;
	case 3:
		nowBulletAmount_2 += num;
		break;
	}
}

void Rifle::Fire(Vec2 MousePosition, bool attackDirection)
{
	/*������ӵ�*/
	if (getNowBulletAmount(isRifle) > 0 && AttackState == true)
	{
		/*��ȡ�ӵ����䷽��*/
		auto X = MousePosition.x - convertToWorldSpace(getWeaponPosition()).x;
		auto Y = MousePosition.y - convertToWorldSpace(getWeaponPosition()).y;
		auto length = hypot(X, Y);
		auto XCoefficient = X / length;
		auto YCoefficient = Y / length;
		log("=============================================================");
		/*ÿ�ε�����һ�����ӵ�*/
		Bullet* newBullet;
		newBullet = shootBullet(Vec2(500 * XCoefficient, 500 * YCoefficient),attackDirection);
		newBullet->setCameraMask((unsigned short)CameraFlag::USER2);
		addChild(newBullet, 1, tagConsts::tagBullet);

		changeBulletamount(1,0);//�ӵ����м���
		log("Fire!!!");
		log("Bullet number is %d", getNowBulletAmount(isRifle));

		AttackState = false;//���һ�κ���ʱ�޷����
		scheduleOnce(CC_SCHEDULE_SELECTOR(Rifle::restoreAttackState), getShootingSpeed());

		auto engine = CocosDenshion::SimpleAudioEngine::getInstance();
		engine->playEffect("rifle_effect.mp3", false);
	}
	else if (getNowBulletAmount(isRifle) == 0)
	{
		Texture2D* aimerLost;
		Sprite* temp = Sprite::create("aimer-lost.png");
		aimerLost = temp->getTexture();
		MouseImage->stopAllActions();
		MouseImage->setTexture(aimerLost);
		log("Bullets is ran out");
	}
}
