//
//  SingleModeRuntimeScence.h
//  PUBG
//
//  Created by PC1 on 2021/5/19.
//

#ifndef SingleModeRuntimeScene_h
#define SingleModeRuntimeScene_h

//#pragma once
#include "cocos2d.h"
#include "Box2D.h"
#include "actor/hero.h"
#include "gizmos/SimpleAudioEngine.h"
#include "Item/ArmorBag.h"
#include "Item/PistolBulletBag.h"
#include "Item/RifleBulletBag.h"
#include "Item/ShotgunBulletBag.h"
#include "Item/GatlingBulletBag.h"
#include "actor/heroUI.h"
#include "actor/enemy.h"
#include "VictoryScene.h"
#include "scene/GameOverSence.h"

USING_NS_CC;
using namespace cocos2d;
//class actor;
class SingleModeRuntime : public Scene
{
public:
    SingleModeRuntime();

    static Scene* createScene();

    virtual bool init();
    
    hero* player = new hero;
    Pistol pistol[pistolNum];
    Sword knife[knifeNum];
    Rifle rifle[rifleNum];
    Shotgun shotgun[shotgunNum];
    Gatling goldengun;

    ArmorBag armorBag[BagNum];
    PistolBulletBag pistolBulletBag[BagNum];
    RifleBulletBag rifleBulletBag[BagNum];
    ShotgunBulletBag shotgunBulletBag[BagNum];
    GatlingBulletBag gatlingBulletBag[GtlBulletBagNum];

    /*enemy位置数据*/
    Vec2 enemyGeneratePoint[gameConsts::enemyCount] = { {2300, 1300},{3400, 800} ,{3300, 2400},{2300,80},{1900,2300} ,{300,2300},{1400, 1800},
                                                           {1300, 1100},{1300, 620},{450, 800} };

    /*武器、子弹包位置数据*/
    Vec2 pistolGeneratePoint[pistolNum] = { {2500,1000} ,{2100, 1600} ,{600, 400} ,{1350, 1750} ,{320, 1700} ,{900, 2300},
                                      {2500, 2500},{3200, 1800},{3350, 800},{2400, 80},{1250, 200},{1250, 1100} };
    Vec2 rifleGeneratePoint[rifleNum] = { {2500, 1600} ,{450, 880} ,{260, 2200} ,{1800, 2200} ,{3400, 2400} ,{2400, 550} };
    Vec2 shotgunGeneratePoint[shotgunNum] = { {2100, 1300} ,{1350, 620} ,{450, 1500} ,{1400, 2400} ,{3350, 1100} ,{2800, 80} };

    Vec2 pistolBulletBagGeneratePoint[BagNum] = { {2480,1000} ,{2510,990} ,{2080,1500} ,{2100,1470} ,{580,400} ,{600,370},{1200,200},
                                                   {1340,1780} ,{1370,1780} ,{350,1700} ,{870,2300} ,{2550,1780} ,{2530,1740} ,{1400,1150},
                                                    {3150,1800} ,{3230,1820} ,{3300,800} ,{3300,700} ,{2350,100} ,{2350,40} , };
    Vec2 rifleBulletBagGeneratePoint[BagNum] = { {2400, 1500} ,{2430, 1400} ,{440, 900} ,{420, 800} ,{490, 750} ,{400, 650},{210, 2250},
                                                   {300, 2300} ,{270, 2200} ,{300, 2300} ,{1750, 2220} ,{1840, 2200} ,{1800, 2270} ,{3300, 2400},
                                                    {3350, 2500} ,{3250, 2450} ,{3600, 2600} ,{2350, 600} ,{2300, 650} ,{2100, 650} };
    Vec2 shotgunBulletBagGeneratePoint[BagNum] = { {2000, 1300} ,{2020, 1250} ,{2080, 1200} ,{1320, 620} ,{1300, 640} ,{1280, 670},{410, 1510},
                                                   {500, 1490} ,{490, 1480} ,{1350, 2450} ,{1450, 2450} ,{1350, 2350} ,{1450, 2350} ,{3250, 1120},
                                                    {3400, 1150} ,{3300, 1050} ,{2760, 70} ,{2700, 70} ,{2850, 65} ,{2900, 70} };
    Vec2 gtlBulletBagGeneratePoint[GtlBulletBagNum] = { {1700, 990} ,{1500, 110} ,{1200, 1250} ,{3200, 450} };
    Vec2 armorBagGeneratePoint[BagNum] = { {2800,2500},{3000,1700},{3200,1100},{2200,700},{2400,1300}
                                            ,{1800,1950},{2000,1500},{2100,1100},{3250,2150},{2300,80},
                                        {150,1450},{450,1700},{500,1100},{420,780},{1450,560},
                                         {1650,700},{1150,1400},{830,2400},{1500,1700},{400,200} };

    HeroUI* heroUI;
    
    void menuPauseCallback(Ref* pSender);
    
    void menuCloseCallback(Ref* pSender);
    
    static void scheduleBlood(float delta);
    
    void groundMusicPlay();
    
    void setCneterPointOfView();
    
    void update(float dt);

    bool onContactBegin(PhysicsContact& contact);

    int enemyCnt = gameConsts::enemyCount;
    enemy* enemyList[gameConsts::enemyCount];
   
    
   
                                      
    //UI更新
    //void scheduleUI(float dt);
    
    //暂停界面回调
    //void pauseByKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    
    CREATE_FUNC(SingleModeRuntime);
    
    b2World * world;
    
    TMXTiledMap *testMap;

    /*鼠标操控函数*/
    bool onMouseDown(Event* pEvent);
    void onMouseUp(cocos2d::Event* event);
    void onMouseMove(cocos2d::Event* event);
    void onMouseScroll(cocos2d::Event* event);

    void gameoverJudge();
    void playerPickCheck(hero* player);

    bool rectContactCheck(Rect rect1, Rect rect2);

    void victory();
    void generateEnemy();

    int enemyDeadNum;
    void removeEnemy(float dt);
    void addItemToCheck();//存放可能需要检测的物品
    void countTime();
protected:
    Vector<Weapon*>enemyWeaponList;
    Vector<Weapon*> contact;
    Vector<ArmorBag*> acontact;
    Vector<PistolBulletBag*> pcontact;
    Vector<RifleBulletBag*> rcontact;
    Vector<ShotgunBulletBag*> scontact;
    Vector<GatlingBulletBag*> gcontact;

    cocos2d::EventListenerMouse* mouseListener;//鼠标监听器
    Vec2 MouseNodePosition;
  
    ProgressTimer* pHealth;
    ProgressTimer* pArmor;

    Label* pBullet1Message;
    Label* pBullet2Message;
    Label* pBullet3Message;
    Label* pBullet4Message;
    Label* countTimeMessage;
    
    MenuItemImage* pauseItem;
    Menu* pauseButtonMenu;

    Camera* p;
    void SingleModeRuntime::doDamage(int index);

    int oldTime;  //调用schedule定时器前的时间
    int nowTime;   //调用schedule定时器后的时间
    int num;   //计时
};


#endif 
