//
//  PistolBulletBag.cpp
//  PUBG
//
//  Created by PC1 on 2021/6/19.
//

#include <stdio.h>
#include "PistolBulletBag.h"
#include "const.h"
using namespace tagConsts;

USING_NS_CC;

PistolBulletBag::PistolBulletBag()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
    bindSprite(Sprite::create("BulletType3.png"));
    if (mySprite == nullptr)
    {
        log("BulletType3.png is not found");
    }
}

bool PistolBulletBag::init()
{
    return true;
}






