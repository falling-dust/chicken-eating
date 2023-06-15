//
//  heroUI.h
//  PUBG
//
//  Created by PC1 on 2021/5/23.
//

#ifndef heroUI_h
#define heroUI_h

#pragma once
#include <cocos2d.h>
#include "actor/actor.h"
#include "actor/hero.h"
#include "ui/UIScale9Sprite.h"
#include "const.h"
#include "Item/Weapon.h"

USING_NS_CC;
//#include "scene/SingleModeRuntimeScene.h"


class HeroUI:public Node
{
public:
    CREATE_FUNC(HeroUI)
    
    //static HeroUI* createUI();
    
    bool init();
    
    void update(float dt);
    
    //当前主/副武器状态，见const.h中内容
    int mainWeapon;
    int secondWeapon;
    int enemyNum = 10;
    
    
protected:
    
    //actor* pHero;
    
    Sprite* healthImg;
    Sprite* sliderTrack1;
    Sprite* sliderTrack2;
    Sprite* armorImg;
    Sprite* mainWeaponImg;
    Sprite* secondWeaponImg;
    
    //武器纹理
    Texture2D* pistolSelectedTex;
    Texture2D* pistolInBagTex;
    Texture2D* knifeSelectedTex;
    Texture2D* knifeInBagTex;
    Texture2D* rifleSelectedTex;
    Texture2D* rifleInBagTex;
    Texture2D* gatlingSelectedTex;
    Texture2D* gatlingInBagTex;
    Texture2D* shotgunSelectedTex;
    Texture2D* shotgunInBagTex;
    
    //武器IMG
    Sprite* pistolSelected;
    Sprite* pistolInBag;
    Sprite* knifeSelected;
    Sprite* knifeInBag;
    Sprite* rifleSelected;
    Sprite* rifleInBag;
    Sprite* gatlingSelected;
    Sprite* gatlingInBag;
    Sprite* shotgunSelected;
    Sprite* shotgunInBag;

    ui::Scale9Sprite* bulletType1;
    ui::Scale9Sprite* bulletType2;
    ui::Scale9Sprite* bulletType3;
    ui::Scale9Sprite* bulletType4;
    
    Label* pBullet1Message;
    Label* pBullet2Message;
    Label* pBullet3Message;
    Label* pBullet4Message;
    Label* enemyNumMessage;
    
    ProgressTimer* pHealth;
    ProgressTimer* pArmor;

    //Label* m_pHealthMessage;
    //Label* m_pArmorMessage;

    int m_presentHP;
    int m_presentArmor;
    int pHealthPoint;
    //int maxHealthPoint;
    int pArmorPoint;
    //int maxArmorPoint;
    
    int pBullet1;
    int pBullet2;
    int pBullet3;
    int pBullet4;
    int maxBullet1=100;
    int maxBullet2=100;
    int maxBullet3=100;
    int maxBullet4=100;
    
};

#endif /* heroUI_h */

