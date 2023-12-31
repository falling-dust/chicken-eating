//
//  ArmorBag.h
//  PUBG
//
//  Created by PC1 on 2021/6/18.
//

#ifndef ArmorBag_h
#define ArmorBag_h

#pragma once
#include <cocos2d.h>
#include "const.h"
#include "actor/actor.h"
#include "actor/hero.h"
#include "Item/Item.h"

USING_NS_CC;
//#include "scene/SingleModeRuntimeScene.h"


class ArmorBag:public Item
{
public:
    ArmorBag();
    
    CREATE_FUNC(ArmorBag)
    
    void addArmor(/*hero* pHero*/);
    
    void destroySelf();
    
    void pickUpJug();
    
    Vec2 getArmorBagPos();
    
    Sprite* ArmorBagImg;
    
    bool init();

protected:
    
    Vec2 ArmorBagPos;
    
    const int ArmorNum=100;
};

#endif /* ArmorBag_h */

