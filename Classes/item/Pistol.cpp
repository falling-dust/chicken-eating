#include"Pistol.h"

Pistol::Pistol()
{
	bindSprite(Sprite::create("pistol.png"));
	if (mySprite == nullptr)
	{
		log("pistol.png is not found");
	}
	scheduleUpdate();
	weaponType = isPistol;
	setPower(pistolPower);
	setBulletCapacity(pistolBulletCapacity);
	setShootingSpeed(pistolShottingSpeed);
	setAddBulletCD(pistolAddBulletCD);
}


void Pistol::update(float dt) 
{
	if (getState() == false)
		;
	else
	{
		mySprite->setPosition(HeroPosition);
	}
}

Bullet* Pistol::shootBullet(Vec2 vec, bool attackDirection)
{
	Bullet* newBullet = Bullet::create();
	if (attackDirection)
		newBullet->setPosition(getWeaponPosition().x + 15, getWeaponPosition().y);
	else
		newBullet->setPosition(getWeaponPosition().x - 15, getWeaponPosition().y);
	newBullet->m_pBulletSprite->getPhysicsBody()->setVelocity(vec);
	return newBullet;
}

void Pistol::changeBulletamount(int mode, int num)
{
	switch (mode)
	{
		case 1:
			nowBulletAmount_1--;
			break;
		case 2:
			nowBulletAmount_1 = pistolBulletCapacity;
			break;
		case 3:
			nowBulletAmount_1 += num;
			break;
	}
}

void Pistol::Fire(Vec2 MousePosition, bool attackDirection)
{
	/*添加新子弹*/
	if (getNowBulletAmount(isPistol) > 0 && AttackState == true)
	{
		/*获取子弹发射方向*/
		auto X = MousePosition.x - convertToWorldSpace(getWeaponPosition()).x;
		auto Y = MousePosition.y - convertToWorldSpace(getWeaponPosition()).y;
		auto length = hypot(X, Y);
		auto XCoefficient = X / length;
		auto YCoefficient = Y / length;
		log("=============================================================");
		/*每次点击添加一个新子弹*/
		Bullet* newBullet;
		newBullet = shootBullet(Vec2(500 * XCoefficient, 500 * YCoefficient),attackDirection);
		newBullet->setCameraMask((unsigned short)CameraFlag::USER2);
		addChild(newBullet, 1, tagConsts::tagBullet);

		changeBulletamount(1,0);//子弹弹夹减少
		log("Fire!!!");
		log("Bullet number is %d", getNowBulletAmount(isPistol));

		AttackState = false;//射击一次后，暂时无法射击
		scheduleOnce(CC_SCHEDULE_SELECTOR(Pistol::restoreAttackState), getShootingSpeed());

		/*射击音效*/
		auto engine = CocosDenshion::SimpleAudioEngine::getInstance();
		engine->playEffect("pistol_effect.mp3", false);
	}
	else if (getNowBulletAmount(isPistol) == 0)
	{
		Texture2D* aimerLost;
		Sprite* temp = Sprite::create("aimer-lost.png");
		aimerLost = temp->getTexture();
		MouseImage->stopAllActions(); 
		MouseImage->setTexture(aimerLost);
		log("Bullets is ran out");
	}
}
