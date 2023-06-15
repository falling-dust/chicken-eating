#include"Sword.h"

Sword::Sword()
{
	bindSprite(Sprite::create("sword.png"));
	if (mySprite == nullptr)
	{
		log("pistol.png is not found");
	}
	scheduleUpdate();
	weaponType = isKnife;
	setPower(swordPower);
	setShootingSpeed(swordAttackSpeed);
	setBulletCapacity(0);

}

void Sword::update(float dt)
{
	if (this->getState() == true)
	{
		mySprite->setPosition(HeroPosition);
	}
	else
		;
}

void Sword::changeBulletamount(int mode, int num)
{
	/*刀不产生子弹，不需要进行处理*/
	;
}

void Sword::Fire(Vec2 MousePosition, bool attackDirection)
{
	if (AttackState == true) 
	{
		AttackState = false;//攻击一次后，暂时无法射击
		/*音效*/
		auto engine = CocosDenshion::SimpleAudioEngine::getInstance();
		engine->playEffect("sword_effect.mp3", false);

		mySprite->setVisible(false);
		Sprite* attackSp;
		/*考虑方向问题*/
		if (attackDirection)
		{
			attackSp = Sprite::create("sword_action1.png");
			attackSp->setPosition((HeroPosition - viewPosition).x + 10, (HeroPosition - viewPosition).y);//减去视角移动的影响
		}
		else
		{
			attackSp = Sprite::create("sword_leftaction1.png");
			attackSp->setPosition((HeroPosition - viewPosition).x - 10, (HeroPosition - viewPosition).y);//减去视角移动的影响
		}
		attackSp->setTag(1000);
		this->addChild(attackSp);

		attackSp->runAction(attackAnimation(attackDirection));
		scheduleOnce(CC_SCHEDULE_SELECTOR(Sword::attackEnd), 0.2f);

		scheduleOnce(CC_SCHEDULE_SELECTOR(Sword::restoreAttackState), getShootingSpeed());

		/*攻击伤害判定*/
		for (int i = 0; i < 5; i++)
		{
			if (attackDirection)
				bulletAttack[i] = shootBullet(Vec2(2000 * 1, 2000 * 0), i * 13, attackDirection);
			else
				bulletAttack[i] = shootBullet(Vec2(2000 * -1, 2000 * 0), i * 13, attackDirection);
			bulletAttack[i]->setCameraMask((unsigned short)CameraFlag::USER2);
			addChild(bulletAttack[i], 1, tagConsts::tagBullet);	
			/*子弹消失的时间决定刀的攻击范围*/
			scheduleOnce(CC_SCHEDULE_SELECTOR(Sword::removeFire), 0.018f);
		}
	}
}

Animate* Sword::attackAnimation(bool attackDirection)
{
	int iFrameNum = 4;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	if (attackDirection)//向右攻击
	{
		for (int i = 1; i <= iFrameNum; i++)
		{
			frame = SpriteFrame::create(StringUtils::format("sword_action%d.png", i), Rect(0, 0, 60, 60));
			frameVec.pushBack(frame);
		}
	}
	else
	{
		for (int i = 1; i <= iFrameNum; i++)
		{
			frame = SpriteFrame::create(StringUtils::format("sword_leftaction%d.png", i), Rect(0, 0, 60, 60));
			frameVec.pushBack(frame);
		}
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);//设置重复次数
	animation->setDelayPerUnit(0.05f);
	Animate* action = Animate::create(animation);
	
	return action;
}

void Sword::attackEnd(float dt)
{
	/*清除动画*/
	dynamic_cast<Sprite*>(this->getChildByTag(1000))->removeFromParentAndCleanup(true);
	mySprite->setVisible(true);
}

Bullet*  Sword::shootBullet(Vec2 vec,int Coefficient, bool attackDirection)
{
	Bullet* newBullet = Bullet::create();
	if (attackDirection)
		newBullet->setPosition(getWeaponPosition().x - 20, getWeaponPosition().y - 26 + Coefficient);
	else
		newBullet->setPosition(getWeaponPosition().x + 20, getWeaponPosition().y - 26 + Coefficient);
	newBullet->m_pBulletSprite->getPhysicsBody()->setVelocity(vec);
	newBullet->setVisible(false);
	return newBullet;
}

void Sword::removeFire( float dt )
{
	for (int i = 0; i < 5; i++)
	{
		bulletAttack[i]->removeFromParentAndCleanup(true);
	}
}