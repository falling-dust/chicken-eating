//
//  GatlingBulletBag.cpp
//  PUBG
//
//  Created by PC1 on 2021/6/20.
//

#include <stdio.h>
#include "GatlingBulletBag.h"
#include "const.h"
using namespace tagConsts;

USING_NS_CC;

GatlingBulletBag::GatlingBulletBag()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
    bindSprite(Sprite::create("BulletType1.png"));
    if (mySprite == nullptr)
    {
        log("BulletType1.png is not found");
    }
}

bool GatlingBulletBag::init()
{
    return true;
}
