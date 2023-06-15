#include "gatling.h"

Gatling::Gatling()
{
	bindSprite(Sprite::create("golden-gatling.png"));
	if (mySprite == nullptr)
	{
		log("golden-gatling.png is not found");
	}
	scheduleUpdate();
	weaponType = isGatling;
	setPower(gatlingPower);
	setBulletCapacity(gatlingBulletCapacity);
	setShootingSpeed(gatlingShottingSpeed);
	setAddBulletCD(gatlingAddBulletCD);
}

void Gatling::update(float dt)
{

	if (getState() == false)
		;
	else
	{
		mySprite->setPosition(HeroPosition);
	}
}

Bullet* Gatling::shootBullet(Vec2 vec,bool attackDirection)
{
	Bullet* newBullet = Bullet::create();

	/*更换子弹图片*/
	newBullet->m_pBulletSprite->stopAllActions();
	newBullet->m_pBulletSprite->setTexture("gatlingBullet.png");
	if (attackDirection)
		newBullet->setPosition(getWeaponPosition().x + 20, getWeaponPosition().y + vec.y / 500);
	else
		newBullet->setPosition(getWeaponPosition().x - 20, getWeaponPosition().y + vec.y / 500);
	newBullet->m_pBulletSprite->getPhysicsBody()->setVelocity(vec);
	return newBullet;
}

void Gatling::changeBulletamount(int mode, int num)
{
	switch (mode)
	{
	case 1:
		nowBulletAmount_4--;
		break;
	case 2:
		nowBulletAmount_4 = gatlingBulletCapacity;
		break;
	case 3:
		nowBulletAmount_4 += num;
		break;
	}
}

void Gatling::Fire(Vec2 MousePosition, bool attackDirection)
{
	/*添加新子弹*/
	if (getNowBulletAmount(isGatling) > 0 && AttackState == true)
	{
		/*获取子弹发射方向*/
		auto X = MousePosition.x - (getWeaponPosition()).x;
		auto Y = MousePosition.y - (getWeaponPosition()).y ;
		auto length = hypot(X, Y);
		auto XCoefficient = X / length;
		auto YCoefficient = Y / length;
		log("=============================================================");
		/*每次点击添加一个新子弹*/
		Bullet* newBullet;
		newBullet = shootBullet(Vec2( 5000*XCoefficient, 5000 * YCoefficient),attackDirection);
		newBullet->m_pBulletSprite->setRotation(360 - atan(Y / X) * 180.0f / 3.14159);
		newBullet->setCameraMask((unsigned short)CameraFlag::USER2);
		addChild(newBullet, 1, tagConsts::tagBullet);

		changeBulletamount(1, 0);//子弹弹夹减少
		log("Fire!!!");
		log("Bullet number is %d", getNowBulletAmount(isGatling));

		AttackState = false;//射击一次后，暂时无法射击
		scheduleOnce(CC_SCHEDULE_SELECTOR(Gatling::restoreAttackState), getShootingSpeed());

		/*射击音效*/
		auto engine = CocosDenshion::SimpleAudioEngine::getInstance();
		engine->playEffect("gatling_effect.mp3", false);
	}
	else if (getNowBulletAmount(isGatling) == 0)
	{
		Texture2D* aimerLost;
		Sprite* temp = Sprite::create("aimer-lost.png");
		aimerLost = temp->getTexture();
		MouseImage->stopAllActions();
		MouseImage->setTexture(aimerLost);
		log("Bullets is ran out");
	}
}
