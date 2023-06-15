#include "hero.h"
#include "boss.h"
#include <cocos2d.h>
using namespace cocos2d;
boss::boss(int x, int y)
{
    isDead = false;
    sActorType = actorConsts::at_boss;
    bindSprite(Sprite::create("Actor\\Monster\\boss1.png"));
    if (delegateSprite == nullptr)
    {
        log("==============failed to create sprite for enemy===================== ");
    }
    //auto moveAction = createAnimation("monster", "Monster\\O_small");
    //delegateSprite->runAction(moveAction);
    delegateSprite->setPosition(Point(x, y));
    bindPhysicalBody();
    scheduleUpdate();
    schedule(CC_SCHEDULE_SELECTOR(boss::generateVelocity), actorConsts::eneMoveUpdateTime);
    schedule(CC_SCHEDULE_SELECTOR(boss::following), actorConsts::eneMoveUpdateTime);

   Gatling* gatling = new Gatling;
    myWeapon = gatling;
    SetWeaponPosition();

}
void boss::update(float delta)
{
    SetWeaponPosition();
    //log("enemy %d: health:%d", enemyIndex, health);
}
void boss::generateVelocity(float delta)
{
    int genx, geny;
    genx = rand() % (actorConsts::eneMaxVol * 2) - actorConsts::eneMaxVol;
    geny = rand() % (actorConsts::eneMaxVol * 2) - actorConsts::eneMaxVol;
    velocity = Vec2(genx, geny);
    if (fabs(genx) > 1e-6)
    {
        if (genx < 0)
        {
            delegateSprite->setFlippedX(true);
        }
        else
        {
            delegateSprite->setFlippedX(false);
        }
    }
    delegateSprite->getPhysicsBody()->setVelocity(velocity);
    //log("position:%d %d", delegateSprite->getPosition().x, delegateSprite->getPosition().y);
}
bool boss::takeDamage(int power)
{
    health -= power;
    if (health <= 0)
    {
        //die();
        return false;
    }
    else
    {
        return true;
    }
}
void boss::die()
{
    Node* parent = getParent();
    parent->removeChild(this);
    isDead = true;
}
void boss::setIndex(int index)
{
    enemyIndex = index;
}
void boss::following(float  delta)
{
    if (hero::getInstance() == nullptr)
        return;
    auto targetPos = hero::getInstance()->delegateSprite->getPosition();
    auto selfPos = this->delegateSprite->getPosition();
    auto distance = targetPos - selfPos;
    if (distance.length() < enemyVision)
    {
        auto enemySpeed = distance;
        enemySpeed.normalize();
        enemySpeed *= actorConsts::eneMaxVol;
        delegateSprite->getPhysicsBody()->setVelocity(enemySpeed);
    }
    if (distance.length() < fireDiatance)
    {
        attack();
    }
    if (distance.length() < kiteDiatance)
    {
        auto enemySpeed = distance;
        enemySpeed.normalize();
        enemySpeed *= actorConsts::eneMaxVol;
        delegateSprite->getPhysicsBody()->setVelocity(-enemySpeed);
    }
    else
    {
        return;
    }
}
void boss::SetWeaponPosition()
{
    //log("weapon position%d %d", this->delegateSprite->getPosition().x, this->delegateSprite->getPosition().y);
    if (myWeapon != nullptr)
    {
        myWeapon->HeroPosition = this->delegateSprite->getPosition();
        myWeapon->getSprite()->setPosition(myWeapon->HeroPosition.x + 24, myWeapon->HeroPosition.y - 5);
    }
    else
    {
    }
}
void boss::attack()
{
    auto targetPos = hero::getInstance()->delegateSprite->getPosition();
    auto selfPos = this->delegateSprite->getPosition();

    auto distance = targetPos - selfPos;
    auto shootVec = distance;
    shootVec.normalize();
    Bullet* newBullet;
    newBullet = myWeapon->shootBullet(500 * shootVec, true);
    newBullet->setCameraMask((unsigned short)CameraFlag::USER2);
    getParent()->addChild(newBullet, 1, tagConsts::tagBullet);
    return;
}
