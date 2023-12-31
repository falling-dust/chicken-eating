//
//  ArmorBag.cpp
//  PUBG
//
//  Created by PC1 on 2021/6/18.
//

#include "ArmorBag.h"
#include "const.h"
using namespace tagConsts;

USING_NS_CC;

ArmorBag::ArmorBag()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
    bindSprite(Sprite::create("ArmorBag.png"));
    if (mySprite == nullptr)
    {
        log("ArmorBag.png is not found");
    }
}

bool ArmorBag::init()
{
    
    //ArmorBagImg=Sprite::create("ArmorBag.png");
    //ArmorBagImg->setPosition(viseSize.width/4,visibleSize.height/8);
    //this->addChild(ArmorBagImg,1,tagArmorBag);
    return true;
}

void ArmorBag::addArmor(/*hero* pHero*/)
{
    actor::addArmor();
}

void ArmorBag::destroySelf()
{
    mySprite->release();
}

void ArmorBag::pickUpJug()
{
    
}

Vec2 ArmorBag::getArmorBagPos()
{
    return mySprite->getPosition();
}





