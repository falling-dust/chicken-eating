//
//  ShotgunBulletBag.cpp
//  PUBG
//
//  Created by PC1 on 2021/6/19.
//

#include <stdio.h>
#include "ShotgunBulletBag.h"
#include "const.h"
using namespace tagConsts;

USING_NS_CC;

ShotgunBulletBag::ShotgunBulletBag()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
    bindSprite(Sprite::create("BulletType2.png"));
    if (mySprite == nullptr)
    {
        log("BulletType2.png is not found");
    }
}

bool ShotgunBulletBag::init()
{
    return true;
}
