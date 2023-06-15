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
	/*���������ӵ�������Ҫ���д���*/
	;
}

void Sword::Fire(Vec2 MousePosition, bool attackDirection)
{
	if (AttackState == true) 
	{
		AttackState = false;//����һ�κ���ʱ�޷����
		/*��Ч*/
		auto engine = CocosDenshion::SimpleAudioEngine::getInstance();
		engine->playEffect("sword_effect.mp3", false);

		mySprite->setVisible(false);
		Sprite* attackSp;
		/*���Ƿ�������*/
		if (attackDirection)
		{
			attackSp = Sprite::create("sword_action1.png");
			attackSp->setPosition((HeroPosition - viewPosition).x + 10, (HeroPosition - viewPosition).y);//��ȥ�ӽ��ƶ���Ӱ��
		}
		else
		{
			attackSp = Sprite::create("sword_leftaction1.png");
			attackSp->setPosition((HeroPosition - viewPosition).x - 10, (HeroPosition - viewPosition).y);//��ȥ�ӽ��ƶ���Ӱ��
		}
		attackSp->setTag(1000);
		this->addChild(attackSp);

		attackSp->runAction(attackAnimation(attackDirection));
		scheduleOnce(CC_SCHEDULE_SELECTOR(Sword::attackEnd), 0.2f);

		scheduleOnce(CC_SCHEDULE_SELECTOR(Sword::restoreAttackState), getShootingSpeed());

		/*�����˺��ж�*/
		for (int i = 0; i < 5; i++)
		{
			if (attackDirection)
				bulletAttack[i] = shootBullet(Vec2(2000 * 1, 2000 * 0), i * 13, attackDirection);
			else
				bulletAttack[i] = shootBullet(Vec2(2000 * -1, 2000 * 0), i * 13, attackDirection);
			bulletAttack[i]->setCameraMask((unsigned short)CameraFlag::USER2);
			addChild(bulletAttack[i], 1, tagConsts::tagBullet);	
			/*�ӵ���ʧ��ʱ��������Ĺ�����Χ*/
			scheduleOnce(CC_SCHEDULE_SELECTOR(Sword::removeFire), 0.018f);
		}
	}
}

Animate* Sword::attackAnimation(bool attackDirection)
{
	int iFrameNum = 4;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	if (attackDirection)//���ҹ���
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
	animation->setLoops(1);//�����ظ�����
	animation->setDelayPerUnit(0.05f);
	Animate* action = Animate::create(animation);
	
	return action;
}

void Sword::attackEnd(float dt)
{
	/*�������*/
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