 #include"Bullet.h"
#include <cmath>
#include "const.h"

using namespace tagConsts;

bool Bullet::init() {
    if (!Sprite::init()) {
        return false;
    }
    initData();
    return true;
}

void Bullet::initData() {
    winSize = Director::getInstance()->getWinSize();

    m_pBulletSprite = Sprite::create("bullet.png");
    m_pBulletSprite->setPosition(0,0);
    addChild(m_pBulletSprite,0,tagBullet);

    if (this->m_pBulletSprite == nullptr)
    {
        log("failed to bind physical body for no sprite");
        return ;
    }
    else
    {
        PhysicsBody* phyBody = PhysicsBody::createBox(Size(m_pBulletSprite->getContentSize().width,m_pBulletSprite->getContentSize().height));
        phyBody->setDynamic(true);
        phyBody->setCategoryBitmask(1);
        phyBody->setCollisionBitmask(0);
        phyBody->setContactTestBitmask(1);
        m_pBulletSprite->setPhysicsBody(phyBody);
    }
}


Sprite*  Bullet::NewBullet() {
    Sprite* newBullet = Sprite::createWithTexture(m_pBulletSprite->getTexture());
    newBullet->setPosition(0,0);
    m_pBulletSprite->addChild(newBullet,0,tagBullet);


    if (m_pBulletSprite == nullptr)
    {
        log("failed to bind physical body for no sprite");
        return nullptr ;
    }
    else
    {
        PhysicsBody* phyBody = PhysicsBody::createBox(Size(m_pBulletSprite->getContentSize().width,m_pBulletSprite->getContentSize().height));
        phyBody->setDynamic(true);
        phyBody->setCategoryBitmask(1);
        phyBody->setCollisionBitmask(1);
        phyBody->setContactTestBitmask(1);
        m_pBulletSprite->setPhysicsBody(phyBody);
    }
    return newBullet;
}


void Bullet::SetDamage(int damage)
{
	BulletDamage = damage;
}

int Bullet::GetDamage()
{
	return BulletDamage;
}

