#include"shotgun.h"

Shotgun::Shotgun()
{
	bindSprite(Sprite::create("shotgun.png"));
	if (mySprite == nullptr)
	{
		log("pistol.png is not found");
	}
	scheduleUpdate();
	weaponType = isShotgun;
	setPower(shotgunPower);
	setBulletCapacity(shotgunBulletCapacity);
	setShootingSpeed(shotgunShottingSpeed);
	setAddBulletCD(shotgunAddBulletCD);

}

void Shotgun::update(float dt)
{
	if (this->getState() == true)
	{
		mySprite->setPosition(HeroPosition);
	}
	else
		;
}

void Shotgun::changeBulletamount(int mode, int num)
{
	switch (mode)
	{
	case 1:
		nowBulletAmount_3--;
		break;
	case 2:
		nowBulletAmount_3 = shotgunBulletCapacity;
		break;
	case 3:
		nowBulletAmount_3 += num;
		break;
	}
}

void Shotgun::Fire(Vec2 MousePosition, bool attackDirection)
{
	if (AttackState == true && getNowBulletAmount(isShotgun) > 0)
	{
		/*��ȡ�ӵ����䷽��*/
		auto X = MousePosition.x - convertToWorldSpace(getWeaponPosition()).x;
		auto Y = MousePosition.y - convertToWorldSpace(getWeaponPosition()).y;
		auto length = hypot(X, Y);
		auto XCoefficient = X / length;
		auto YCoefficient = Y / length;
		log("=============================================================");
		
		AttackState = false;//����һ�κ���ʱ�޷����
		scheduleOnce(CC_SCHEDULE_SELECTOR(Shotgun::restoreAttackState), getShootingSpeed());

		changeBulletamount(1, 0);//�ӵ����м���
		log("Fire!!!");
		log("Bullet number is %d", getNowBulletAmount(isShotgun));

		/*�����ӵ�*/
		for (int i = 0; i < 5; i++)
		{
			bulletAttack[i] = shootBullet(Vec2(500 * XCoefficient, 500 * YCoefficient), i * 13, attackDirection);
			bulletAttack[i]->setCameraMask((unsigned short)CameraFlag::USER2);
			addChild(bulletAttack[i], 1, tagConsts::tagBullet);
		}
		/*�����Ч*/
		auto engine = CocosDenshion::SimpleAudioEngine::getInstance();
		engine->playEffect("shotgun_effect.mp3", false);
	}
	else if (getNowBulletAmount(isShotgun) == 0)
	{
		Texture2D* aimerLost;
		Sprite* temp = Sprite::create("aimer-lost.png");
		aimerLost = temp->getTexture();
		MouseImage->stopAllActions();
		MouseImage->setTexture(aimerLost);
		log("Bullets is ran out");
	}

}


Bullet* Shotgun::shootBullet(Vec2 vec, int Coefficient, bool attackDirection)
{
	Bullet* newBullet = Bullet::create();
	/*�����ӵ�ͼƬ*/
	newBullet->m_pBulletSprite->stopAllActions();
	newBullet->m_pBulletSprite->setTexture("shotgunBullet.png");

	if (attackDirection)
		newBullet->setPosition(getWeaponPosition().x + 10, getWeaponPosition().y - 26 + Coefficient);
	else
		newBullet->setPosition(getWeaponPosition().x - 10, getWeaponPosition().y - 26 + Coefficient);

	newBullet->m_pBulletSprite->getPhysicsBody()->setVelocity(vec);

	return newBullet;
}
