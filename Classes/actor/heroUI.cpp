//
//  heroUI.cpp
//  PUBG
//
//  Created by PC1 on 2021/5/23.
//

#include "heroUI.h"


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

/*
HeroUI * HeroUI::createUI()
{
    HeroUI *ret = new (std::nothrow) HeroUI();
    ret->init();
    printf("%d",ret&&ret->init());
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
*/




bool HeroUI::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
    
    pHealthPoint=actor::getHealthPoint();
    pArmorPoint=actor::getDefencePoint();
    
    pistolSelected=Sprite::create("PistolSelected.png");
    pistolInBag=Sprite::create("PistolInBag.png");
    knifeSelected=Sprite::create("knifeSelected.png");
    knifeInBag=Sprite::create("knifeInBag.png");
    rifleSelected=Sprite::create("RifleSelected.png");
    rifleInBag=Sprite::create("RifleInBag.png");
    gatlingSelected=Sprite::create("gatlingSelected.png");
    gatlingInBag=Sprite::create("gatlingInBag.png");
    shotgunSelected=Sprite::create("shotgunSelected.png");
    shotgunInBag=Sprite::create("shotgunInBag.png");
    
    
    pistolSelectedTex=pistolSelected->getTexture();
    pistolInBagTex=pistolInBag->getTexture();
    knifeSelectedTex=knifeSelected->getTexture();
    knifeInBagTex=knifeInBag->getTexture();
    rifleSelectedTex=rifleSelected->getTexture();
    rifleInBagTex=rifleInBag->getTexture();
    gatlingSelectedTex=gatlingSelected->getTexture();
    gatlingInBagTex=gatlingInBag->getTexture();
    shotgunSelectedTex=shotgunSelected->getTexture();
    shotgunInBagTex=shotgunInBag->getTexture();
    
 //UI
 //血条
 healthImg = Sprite::create("HealthImg.png");
 healthImg->setPosition(visibleSize.width/4,visibleSize.height/8);
 this->addChild(healthImg, 2);

 //测试数据
 //pHealthPoint=60;
 
 sliderTrack1 = Sprite::create("SliderTrack.png");
 sliderTrack1->setPosition(visibleSize.width/2,visibleSize.height/8);
 this->addChild(sliderTrack1, 1);
 
 pHealth = ProgressTimer::create(Sprite::create("HealthBar.png"));
 pHealth->setPosition(visibleSize.width/2, visibleSize.height / 8);
 pHealth->setType(ProgressTimer::Type::BAR);
 pHealth->setMidpoint(Point(0, 0.5));
 pHealth->setBarChangeRate(Point(1, 0));
 pHealth->setPercentage(static_cast<float>(pHealthPoint)
     / static_cast<float>(maxHealthPoint) * 100);
 this->addChild(pHealth,2);
 
 //护甲条
 armorImg = Sprite::create("ArmorImg.png");
 armorImg->setPosition(Point(visibleSize.width/4,visibleSize.height/16));
 this->addChild(armorImg, 2);

 //剩余敌人数量
 std::string enemyNumString = "Enemy: " +
     std::to_string(enemyNum);
 enemyNumMessage = Label::createWithTTF(enemyNumString, "fonts\\IRANYekanBold.ttf", 18.f);
 enemyNumMessage->setPosition(7 * visibleSize.width / 56, 9 * visibleSize.height / 10);
 this->addChild(enemyNumMessage, 3);

 //测试数据
 //pArmorPoint=80;
 
 sliderTrack2 = Sprite::create("SliderTrack.png");
 sliderTrack2->setPosition(visibleSize.width/2,visibleSize.height/16);
 this->addChild(sliderTrack2, 1);
 
 pArmor = ProgressTimer::create(Sprite::create("ArmorBar.png"));
 pArmor->setPosition(origin.x + visibleSize.width/2, visibleSize.height / 16);
 pArmor->setType(ProgressTimer::Type::BAR);
 pArmor->setMidpoint(Point(0, 0.5));
 pArmor->setBarChangeRate(Point(1, 0));
 pArmor->setPercentage(static_cast<float>(pArmorPoint)
     / static_cast<float>(maxArmorPoint) * 100);
 this->addChild(pArmor,2);
 
 
 //子弹1
 bulletType1 = ui::Scale9Sprite::create("BulletType1.png");
 if(bulletType1 == nullptr)
 {
     problemLoading("'BulletType1.png'");
 }
 else
 {
     //bulletType1->setCapInsets(Rect(6, 6, 79, 61));
     //bulletType1->setContentSize(Size(300, 200));
     bulletType1->setPosition(origin.x + visibleSize.width/30, visibleSize.height / 4);
     this->addChild(bulletType1, 1);
     //测试数据
     pBullet1=30;
     
     std::string bullet1Message = std::to_string(pBullet1) + "/" +
             std::to_string(maxBullet1);
     pBullet1Message = Label::createWithTTF(bullet1Message, "fonts\\IRANYekanBold.ttf", 18.f);
     pBullet1Message->setPosition(visibleSize.width/8, visibleSize.height / 4);
     this->addChild(pBullet1Message, 3);
 }
 
 
 //子弹2
 bulletType2 = ui::Scale9Sprite::create("BulletType2.png");
 if(bulletType2 == nullptr)
 {
     problemLoading("'BulletType2.png'");
 }
 else
 {
     //bulletType1->setCapInsets(Rect(6, 6, 79, 61));
     //bulletType1->setContentSize(Size(300, 200));
     bulletType2->setPosition(origin.x + visibleSize.width/30, visibleSize.height / 4-visibleSize.height/15);
     this->addChild(bulletType2, 0);
     //测试数据
     pBullet2=40;
     
     std::string bullet2Message = std::to_string(pBullet2) + "/" +
             std::to_string(maxBullet2);
     pBullet2Message = Label::createWithTTF(bullet2Message, "fonts\\IRANYekanBold.ttf", 18.f);
     pBullet2Message->setPosition(visibleSize.width/8, visibleSize.height / 4-visibleSize.height/15);
     this->addChild(pBullet2Message, 3);
 }
 
 //子弹3
 bulletType3 = ui::Scale9Sprite::create("BulletType3.png");
 if(bulletType3 == nullptr)
 {
     problemLoading("'BulletType3.png'");
 }
 else
 {
     //bulletType1->setCapInsets(Rect(6, 6, 79, 61));
     //bulletType1->setContentSize(Size(300, 200));
     bulletType3->setPosition(origin.x + visibleSize.width/30, visibleSize.height / 4-2*visibleSize.height/15);
     this->addChild(bulletType3, 0);
     //测试数据
     pBullet3=50;
    
     std::string bullet3Message = std::to_string(pBullet3) + "/" +
             std::to_string(maxBullet3);
     pBullet3Message = Label::createWithTTF(bullet3Message, "fonts\\IRANYekanBold.ttf", 18.f);
     pBullet3Message->setPosition(visibleSize.width/8, visibleSize.height / 4-2*visibleSize.height/15);
     this->addChild(pBullet3Message, 3);
 }
 
 //子弹4
 bulletType4 = ui::Scale9Sprite::create("BulletType4.png");
 if(bulletType4 == nullptr)
 {
     problemLoading("'BulletType4.png'");
 }
 else
 {
     //bulletType1->setCapInsets(Rect(6, 6, 79, 61));
     //bulletType1->setContentSize(Size(300, 200));
     bulletType4->setPosition(origin.x + visibleSize.width/30, visibleSize.height / 4-3*visibleSize.height/15);
     this->addChild(bulletType4, 0);
     //测试数据
     pBullet4=80;
     
     std::string bullet4Message = std::to_string(pBullet4) + "/" +
             std::to_string(maxBullet4);
     pBullet4Message = Label::createWithTTF(bullet4Message, "fonts\\IRANYekanBold.ttf", 18.f);
     pBullet4Message->setPosition(visibleSize.width/8, visibleSize.height / 4-3*visibleSize.height/15);
     this->addChild(pBullet4Message, 3);
 }
    
//武器面板
    
    mainWeapon=itemConsts::isPistol;
    //主武器
    mainWeaponImg = Sprite::create("knifeInBag.png");
    mainWeaponImg->setPosition(8*visibleSize.width/20,visibleSize.height/5);
    this->addChild(mainWeaponImg, 2);
    
    //副武器
    secondWeaponImg = Sprite::create("knifeInBag.png");
    secondWeaponImg->setPosition(3*visibleSize.width/5,visibleSize.height/5);
    this->addChild(secondWeaponImg, 2);
    
    scheduleUpdate();
    
    return true;
 
}




 
 //UI更新函数
 void HeroUI::update(float dt)
 {
     auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
     Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
     
     //更新血甲
     if (pHealthPoint != actor::getHealthPoint())
     {
         pHealthPoint = actor::getHealthPoint();
         pHealth->setPercentage(static_cast<float >(pHealthPoint)
                                  / static_cast<float >(maxHealthPoint) * 100);
     }

     if (pArmorPoint != actor::getDefencePoint())
     {
         pArmorPoint = actor::getDefencePoint();
         pArmor->setPercentage(static_cast<float >(pArmorPoint)
                                / static_cast<float >(maxArmorPoint) * 100);
     }

     //更新剩余敌人数量

     std::string enemyNumString = "Enemy: " +
         std::to_string(enemyNum);
     enemyNumMessage->setString(enemyNumString);
     
     //更新武器面板
     mainWeapon=hero::getInstance()->getMyMainWeapon()->weaponType;
     if(mainWeapon==itemConsts::isPistol)
     {
         mainWeaponImg->setTexture(pistolSelectedTex);
     }
    else if(mainWeapon==itemConsts::isRifle)
     {
         mainWeaponImg->setTexture(rifleSelectedTex);
     }
    else if(mainWeapon==itemConsts::isShotgun)
     {
         mainWeaponImg->setTexture(shotgunSelectedTex);
     }
    else if(mainWeapon==itemConsts::isGatling)
     {
         mainWeaponImg->setTexture(gatlingSelectedTex);
     }
    else if(mainWeapon==itemConsts::isKnife)
    {
        mainWeaponImg->setTexture(knifeSelectedTex);
    }
     if(hero::getInstance()->getMySecondWeapon()!=nullptr)
     {
         secondWeapon=hero::getInstance()->getMySecondWeapon()->weaponType;
         if(secondWeapon==itemConsts::isPistol)
         {
             secondWeaponImg->setTexture(pistolInBagTex);
         }
        else if(secondWeapon==itemConsts::isRifle)
         {
             secondWeaponImg->setTexture(rifleInBagTex);
         }
        else if(secondWeapon==itemConsts::isShotgun)
         {
             secondWeaponImg->setTexture(shotgunInBagTex);
         }
        else if(secondWeapon==itemConsts::isGatling)
         {
             secondWeaponImg->setTexture(gatlingInBagTex);
         }
        else if(secondWeapon==itemConsts::isKnife)
        {
            secondWeaponImg->setTexture(knifeInBagTex);
        }
     }
     
      
     
     //更新加特林子弹数
     if(pBullet1!=Weapon::getNowBulletAmount(isGatling)
        ||maxBullet1!=Weapon::getBulletInventory(isGatling))
     {
         pBullet1=Weapon::getNowBulletAmount(isGatling);
         maxBullet1=Weapon::getBulletInventory(isGatling);
         std::string bullet1Message = std::to_string(pBullet1) + "/" +
                 std::to_string(maxBullet1);
         pBullet1Message->setString(bullet1Message);
     }
     
     //更新霰弹枪子弹数
     if(pBullet2!=Weapon::getNowBulletAmount(isShotgun)||maxBullet2!=Weapon::getBulletInventory(isShotgun))
     {
         pBullet2=Weapon::getNowBulletAmount(isShotgun);
         maxBullet2=Weapon::getBulletInventory(isShotgun);
         std::string bullet2Message = std::to_string(pBullet2) + "/" +
                 std::to_string(maxBullet2);
         pBullet2Message->setString(bullet2Message);
     }
     
     
     
     //更新手枪子弹数
     if(pBullet3!=Weapon::getNowBulletAmount(isPistol)||maxBullet3!=Weapon::getBulletInventory(isPistol))
     {
         pBullet3=Weapon::getNowBulletAmount(isPistol);
         maxBullet3=Weapon::getBulletInventory(isPistol);
         std::string bullet3Message = std::to_string(pBullet3) + "/" +
                 std::to_string(maxBullet3);
         pBullet3Message->setString(bullet3Message);
     }
     
     //更新步枪子弹数
     if(pBullet4!=Weapon::getNowBulletAmount(isRifle)||maxBullet4!=Weapon::getBulletInventory(isRifle))
     {
         pBullet4=Weapon::getNowBulletAmount(isRifle);
         maxBullet4=Weapon::getBulletInventory(isRifle);
         std::string bullet4Message = std::to_string(pBullet4) + "/" +
                 std::to_string(maxBullet4);
         pBullet4Message->setString(bullet4Message);
     }
    
    
 }





