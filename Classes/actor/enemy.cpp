#include "hero.h"
#include "enemy.h"
#include <cocos2d.h>
using namespace cocos2d;
enemy::enemy(int x,int y)
{
    isDead = false;
    sActorType=actorConsts::at_enemy;
    bindSprite(Sprite::create("Actor\\Monster\\O_small_monster2.png"));
    if (delegateSprite == nullptr)
    {
        log("==============failed to create sprite for enemy===================== ");
    }
    //auto moveAction = createAnimation("monster", "Monster\\O_small");
    //delegateSprite->runAction(moveAction);
    delegateSprite->setPosition(Point(x, y));
    bindPhysicalBody();
    scheduleUpdate();
    schedule(CC_SCHEDULE_SELECTOR(enemy::generateVelocity),  actorConsts::eneMoveUpdateTime);
    schedule(CC_SCHEDULE_SELECTOR(enemy::following), actorConsts::eneMoveUpdateTime);

    Pistol* pistol = new Pistol;
    myWeapon = pistol;
    SetWeaponPosition();

}
void enemy::update(float delta)
{
    SetWeaponPosition();
    //log("enemy %d: health:%d", enemyIndex, health);
}
void enemy::generateVelocity(float delta)
{
    int genx, geny;
    genx = rand() % (actorConsts::eneMaxVol*2) - actorConsts::eneMaxVol;
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
bool enemy::takeDamage(int power)
{
    health -= power;
    if (health<=0)
    {
        //die();
        return false;
    }
    else
    {
        return true;
    }
}
void enemy::die()
{
    Node* parent = getParent();
    parent->removeChild(this);
    isDead = true;
}
void enemy::setIndex(int index)
{
    enemyIndex = index;
}
void enemy::following(float  delta)
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
void enemy::SetWeaponPosition()
{
    //log("weapon position%d %d", this->delegateSprite->getPosition().x, this->delegateSprite->getPosition().y);
    if (myWeapon != nullptr)
    {
        myWeapon->HeroPosition = this->delegateSprite->getPosition();
        myWeapon->getSprite() ->setPosition(myWeapon->HeroPosition.x + 24, myWeapon->HeroPosition.y - 5);
    }
    else
    {
    }
}

void enemy::attack()
{
    auto targetPos = hero::getInstance()->delegateSprite->getPosition();
    auto selfPos = this->delegateSprite->getPosition();

    auto distance = targetPos - selfPos;
    auto shootVec = distance;
    shootVec.normalize();
    Bullet* newBullet;
    newBullet = myWeapon->shootBullet(500 * shootVec,true);
    newBullet->setCameraMask((unsigned short)CameraFlag::USER2);
    getParent()->addChild(newBullet, 1, tagConsts::tagBullet);
    return;
}
