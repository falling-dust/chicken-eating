//
//  actor.h
//  PUBG
//
//  Created by wza on 2021/5/26.
//
#ifndef actor_h
#define actor_h
#include<cocos2d.h>
#include "const.h"
#include "Item/Weapon.h"
#include "Item/Pistol.h"
#include "Item/Sword.h"
#include "item/rifle.h"
#include "item/gatling.h"
#include "item/shotgun.h"
//#include "scene/SingleModeRuntimeScene.h"    include进来会导致hero类报错

//class SingleModeRuntime;
using namespace cocos2d;
using namespace actorConsts;
class actor:public Node
{
private:
public:
    Sprite* delegateSprite;
    actor();
    static int getHealthPoint();
    static int getDefencePoint();
    bool doDamage(int attackPoint);
    Vec2 getSpritePosition();
    static bool addArmor();
    void healthRecover();
protected:
    int num;//计时变量
    int oldTime;  //调用schedule定时器前的时间
    int nowTime;   //调用schedule定时器后的时间
    bool canMove;
    bool isInvincible;
    float moveSpeedRatio;
    static int sHealthPoint;
    static int sDefencePoint;
    int sActorType;
    void bindSprite(Sprite* sprite);
    bool bindPhysicalBody();
    bool isWalking = false;
    Animate* actor::createAnimation(const char* animationName, const char* actorName);
};

#endif
