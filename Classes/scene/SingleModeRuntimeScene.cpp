//
//  SingleModeRunTimeScence.cpp
//  PUBG
//
//  Created by PC1 on 2021/5/19.
//

#define PTM_RATIO 32.0f

#include "HelloWorldScene.h"
#include "SingleModeRuntimeScene.h"
#include "PauseScene.h"
#include "VictoryScene.h"
#include "const.h"
#include <CCVector.h>
#include <cmath>
using namespace tagConsts;

USING_NS_CC;
SingleModeRuntime::SingleModeRuntime()
{
    /*监听鼠标的操作*/
    auto Listener = EventListenerMouse::create();
    Listener->onMouseDown = CC_CALLBACK_1(SingleModeRuntime::onMouseDown, this);
    Listener->onMouseMove = CC_CALLBACK_1(SingleModeRuntime::onMouseMove, this);
    Listener->onMouseUp = CC_CALLBACK_1(SingleModeRuntime::onMouseUp, this);
    Listener->onMouseDown = CC_CALLBACK_1(SingleModeRuntime::onMouseDown, this);
    Listener->onMouseScroll = CC_CALLBACK_1(SingleModeRuntime::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, this);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(SingleModeRuntime::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

Scene* SingleModeRuntime::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = SingleModeRuntime::create();
    scene->addChild(layer,1,10);
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool SingleModeRuntime::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
    
    //地
    testMap = TMXTiledMap::create("map.tmx");
    this->addChild(testMap,0,0);
   
    //战歌起
    groundMusicPlay();
    
    auto groupwall = testMap->getObjectGroup("wall");
    ValueVector objectsWall = groupwall->getObjects();
    for (auto wall : objectsWall)
    {
        ValueMap& dict = wall.asValueMap();

        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat();
        float width = dict["width"].asFloat();
        float height = dict["height"].asFloat();
        float rotate = dict["rotation"].asFloat();
        const auto pointsVector = dict["points"].asValueVector();
        auto size = pointsVector.size();

        Vec2* points = new Vec2[size];
        int i = 0;
        for (auto pointValue : pointsVector)
        {
            auto dicp = pointValue.asValueMap();
            auto x = dicp.at("x").asFloat();
            auto y = -dicp.at("y").asFloat();//y取负值
            points[i] = Vec2(x, y);
            i++;
        }

        PhysicsBody* tmpPhysicsBody = PhysicsBody::createEdgePolygon(points,
            size,
            PHYSICSBODY_MATERIAL_DEFAULT,
            1
        );

        tmpPhysicsBody->setDynamic(false);
        tmpPhysicsBody->setCategoryBitmask(1);
        tmpPhysicsBody->setCollisionBitmask(1);
        tmpPhysicsBody->setContactTestBitmask(1);

        Sprite* tmpSprite = Sprite::create();
        tmpSprite->setPosition(Vec2(x, y));
        tmpSprite->setAnchorPoint(Vec2::ZERO);
        tmpSprite->setContentSize(Size(width, height));
        tmpSprite->setPhysicsBody(tmpPhysicsBody);

        addChild(tmpSprite, 1, tagConsts::tagBarrier);
    }

    /*武器、角色加入到场景中*/
    player->delegateSprite->setTag(tagConsts::tagHero);
    generateEnemy();
    addChild(player,1,tagConsts::tagHero);
    

    /*地图中的武器清单*/
    for (int i = 0; i < shotgunNum; i++)
    {
        addChild(&shotgun[i], 2);
        addChild(&rifle[i], 2);
        (&rifle[i])->getSprite()->setPosition(rifleGeneratePoint[i]);
        (&shotgun[i])->getSprite()->setPosition(shotgunGeneratePoint[i]);
     }
    for (int i = 0; i < pistolNum; i++)
    {
        addChild(&pistol[i], 2);
        (&pistol[i])->getSprite()->setPosition(pistolGeneratePoint[i]);
    }
    for (int i = 0; i < knifeNum; i++)
    {
        addChild(&knife[i], 2);
        (&knife[i])->getSprite()->setVisible(false);
    }
    addChild(&goldengun, 2);
    
    (&goldengun)->getSprite()->setPosition(2250, 1200);//黄金加特林
    (player)->setMainWeapon(&knife[0]);

    /*弹药包添加进场景*/
    for (int i = 0; i < BagNum; i++)
    {
        addChild(&armorBag[i], 2);
        addChild(&pistolBulletBag[i], 2);
        addChild(&rifleBulletBag[i], 2);
        addChild(&shotgunBulletBag[i], 2);

        /*设置位置*/
        (&pistolBulletBag[i])->getSprite()->setPosition(pistolBulletBagGeneratePoint[i]);
        (&rifleBulletBag[i])->getSprite()->setPosition(rifleBulletBagGeneratePoint[i]);
        (&shotgunBulletBag[i])->getSprite()->setPosition(shotgunBulletBagGeneratePoint[i]);
        (&armorBag[i])->getSprite()->setPosition(armorBagGeneratePoint[i]);

    }
    for (int i = 0; i < GtlBulletBagNum; i++)
    {
        addChild(&gatlingBulletBag[i], 2);
        (&gatlingBulletBag[i])->getSprite()->setPosition(gtlBulletBagGeneratePoint[i]);//设置位置
    }
  
    //计时开始
    struct timeval now;
    gettimeofday(&now, NULL);
    this->num = 0;    //计时从0开始
    //log("%d", this->num);
    this->oldTime = now.tv_sec;  //获取调用定时器前的时间

    std::string totalTime = "Total time: 0s";
    countTimeMessage = Label::createWithTTF(totalTime, "fonts\\IRANYekanBold.ttf", 18.f);
    countTimeMessage->setPosition(7.5 * visibleSize.width / 56, 19 * visibleSize.height / 20);
    this->addChild(countTimeMessage, 3);

    //监听键盘
    auto* dispatcher = Director::getInstance()->getEventDispatcher();
    auto* keyListener = EventListenerKeyboard::create();
    //创建一个事件监听器监听键盘事件
    keyListener->onKeyPressed = CC_CALLBACK_2(hero::onKeyPressed, player);
    //键盘被按下时响应
    keyListener->onKeyReleased = CC_CALLBACK_2(hero::onKeyReleased, player);
    //键盘按键被弹回时响应
    dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    
    
    auto labelGameName = Label::createWithTTF("single", "fonts\\Marker Felt.ttf", 45);
    if (labelGameName == nullptr)
    {
        problemLoading("'Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        labelGameName->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - labelGameName->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(labelGameName, 1);
    }


    heroUI = HeroUI::create();
    this->addChild(heroUI);
    
    //暂停按钮
    pauseItem = MenuItemImage::create("pausebutton.png",
                                           "pausebutton.png",
                                           CC_CALLBACK_1(SingleModeRuntime::menuPauseCallback, this));

    if (pauseItem == nullptr ||
        pauseItem->getContentSize().width <= 0 ||
        pauseItem->getContentSize().height <= 0)
    {
        problemLoading("'pausebutton.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width-pauseItem->getContentSize().width/2;
        float y = origin.y + visibleSize.height-pauseItem->getContentSize().height/2;
        pauseItem->setPosition(Vec2(x,y));
    }
    auto pauseButtonMenu = Menu::create(pauseItem, NULL);
    pauseButtonMenu->setPosition(Vec2::ZERO);
    this->addChild(pauseButtonMenu, 1);

    // 视角相机
    p = Camera::createOrthographic(visibleSize.width, visibleSize.height, 0, 1);
    p->setCameraFlag(CameraFlag::USER2);
    p->setPosition3D(Vec3(0, 0, 0));
    this->setCameraMask((unsigned short)CameraFlag::USER2);
    heroUI->setCameraMask((unsigned short)CameraFlag::DEFAULT);
    countTimeMessage->setCameraMask((unsigned short)CameraFlag::DEFAULT);
    pauseItem->setCameraMask((unsigned short)CameraFlag::DEFAULT);
    pauseButtonMenu->setCameraMask((unsigned short)CameraFlag::DEFAULT);
    this->addChild(p, 1);

   //设置更新函数
    scheduleUpdate();
    
    return true;
}


void SingleModeRuntime::groundMusicPlay()
{
    auto engine = CocosDenshion::SimpleAudioEngine::getInstance();
    engine->playBackgroundMusic("bgm.mp3", true);
}

void SingleModeRuntime::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}


void SingleModeRuntime::menuPauseCallback(Ref* pSender)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto* renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
        //遍历当前类的所有子节点信息，画入renderTexture中。
        //这里类似截图。
    //auto *curScene=Director::getRunningScene();
    
    renderTexture->begin();
    this->visit();
    renderTexture->end();
      //将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
    Director::getInstance()->getOpenGLView()->setCursorVisible(true);
    Director::getInstance()->pushScene(Pause::createScene(renderTexture)); //这里实际是通过CCRenderTexture保存当前界面（相当于截屏），然后传递给暂停界面，当成背景精灵
}


void SingleModeRuntime::setCneterPointOfView()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
//因为这里是要通过传入的点p来显示设定CCLayer的位置，p为英雄坐标，当做显示中心点。
//TileMap的size肯定大于WinSize（分辨率），不然有黑边，而且也不用移动地图了。
//因此p的x、y的值肯定要大于等于屏幕中心的值
    int x = MAX(player->delegateSprite->getPosition().x, visibleSize.width / 2);
    int y = MAX(player->delegateSprite->getPosition().y, visibleSize.height / 2);

    //同理，p的x、y要小于等于TileMap的size的宽高减去WinSize的中心值,不然也会出现黑边
    x = MIN(x, testMap->getMapSize().width * testMap->getTileSize().width - visibleSize.width / 2);
    y = MIN(y, testMap->getMapSize().height * testMap->getTileSize().height - visibleSize.height / 2);
    Point actualPosition = Vec2(x, y);
    auto pos = p->getPosition3D();
    Point winCenter = Vec2(visibleSize.width / 2, visibleSize.height / 2);
    Point viewPosition = actualPosition - winCenter;
    pos.x = viewPosition.x;
    pos.y = viewPosition.y;
    p->setPosition3D(pos);

    (player)->MousePosition = Point(MouseNodePosition.x + viewPosition.x, MouseNodePosition.y + viewPosition.y);
    (player)->getMyMainWeapon()->viewPosition = viewPosition;
}

void SingleModeRuntime::update(float dt)
{
    countTime();
    gameoverJudge();
    setCneterPointOfView();
    ((player)->getMyMainWeapon()->getMouseImage())->setPosition(convertToNodeSpace((player)->MousePosition));

    heroUI->mainWeapon = (player)->getMyMainWeapon()->weaponType;

    heroUI->enemyNum = enemyCnt;

    /*只有英雄点击拾取键才检测，避免浪费资源多次运行*/
    /*联机时在这里对每个英雄进行一次遍历*/
    if ((player)->getPickingState() == true)
    {
        addItemToCheck();
        (player)->setPickingState(false);
        log("set inPicking false");
        playerPickCheck(player);
      
    }
}

bool SingleModeRuntime::onMouseDown(Event* pEvent)
{
    log("Mouse Down");
    (player)->mouseKeys["Down"] = true;
    return true;
}

void SingleModeRuntime::onMouseUp(Event* pEvent)
{
    log("Mouse Up");
    (player)->mouseKeys["Down"] = false;
}

void SingleModeRuntime::onMouseMove(Event* pEvent)
{
    EventMouse* e = (EventMouse*)pEvent;
    MouseNodePosition = Point(e->getCursorX(), e->getCursorY());
    /*对于鼠标瞄准镜图像的一些说明：
    *当鼠标移动时，利用该函数获取鼠标坐标（以英雄为参考点），
    *并将瞄准镜图像贴在屏幕中，update函数中反复调用*/

    if ((player)->getMyMainWeapon()->weaponType != 0)
    {
        auto X = (player)->MousePosition.x - convertToWorldSpace((player)->getMyMainWeapon()->getWeaponPosition()).x;
        auto Y = (player)->MousePosition.y - convertToWorldSpace((player)->getMyMainWeapon()->getWeaponPosition()).y;
        (player)->getMyMainWeapon()->getSprite()->setRotation(360 - atan(Y / X) * 180.0f / 3.14159);
       
    }

    /*设置鼠标不可见*/
    Director::getInstance()->getOpenGLView()->setCursorVisible(false);

}

void SingleModeRuntime::onMouseScroll(Event* pEvent)
{

}

bool SingleModeRuntime::onContactBegin(PhysicsContact& contact)
{
    bool deleteTag = false;
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    //log("=========contact happen=========");

    if (nodeA == nullptr || nodeB == nullptr) 
    {
        return false;
    }
   // log("contact %d and %d", nodeA->getTag(), nodeB->getTag());
    if (nodeA->getTag() == tagConsts::tagHero || nodeB->getTag() == tagConsts::tagHero)
    {
        player->onContactBegin(contact);
    }
    else
        if (nodeA->getTag() == tagConsts::tagBullet && (nodeB->getTag() >= tagConsts::tagEnemyStart) && (nodeB->getTag() <= tagConsts::tagEnemyStart + gameConsts::enemyCount - 1))
        {
            deleteTag = true;
            //log("haha");
            doDamage(nodeB->getTag() - tagConsts::tagEnemyStart);
            nodeA->removeFromParentAndCleanup(true);
        }
        else
            if (nodeB->getTag() == tagConsts::tagBullet && (nodeA->getTag() >= tagConsts::tagEnemyStart) && (nodeA->getTag() <= tagConsts::tagEnemyStart + gameConsts::enemyCount - 1))
            {
                deleteTag = true;
                //log("fuc");
                doDamage(nodeA->getTag() - tagConsts::tagEnemyStart);
                nodeB->removeFromParentAndCleanup(true);
            }
    if (!deleteTag)
    {
        if (nodeA->getTag() == tagConsts::tagBullet)
        {
            nodeA->removeFromParentAndCleanup(true);
        }
        if (nodeB->getTag() == tagConsts::tagBullet)
        {
            nodeB->removeFromParentAndCleanup(true);
        }
    }
    return true;
}


//死亡判定
void SingleModeRuntime::gameoverJudge()
{
    bool isAlive = actor::getHealthPoint();
    if (0 == isAlive)
    {
        Director::getInstance()->getOpenGLView()->setCursorVisible(true);
        Director::getInstance()->replaceScene(GameOver::createScene());
    }
}

void SingleModeRuntime::playerPickCheck(hero* player)
{
    log("go in playerPickCheck!!!!!!!!!!!!");
    (player)->setPickingState(false);
    /*拾取武器检测*/
    for (Vector<Weapon*>::iterator iter = contact.begin(); iter < contact.end(); iter++)
    {
        if (rectContactCheck((player)->delegateSprite->getBoundingBox(), (*iter)->getSprite()->getBoundingBox()) && (*iter)->getState() == false)
        {
            log("succeed to pick weapon");
            (player)->pickWeapon(*iter);
        }
    }

    /*拾取敌人武器检测*/
    for (Vector<Weapon*>::iterator iter = enemyWeaponList.begin(); iter < enemyWeaponList.end(); iter++)
    {
        if (rectContactCheck((player)->delegateSprite->getBoundingBox(), (*iter)->getSprite()->getBoundingBox())&&(*iter)->getState()==false)
        {
            log("succeed to pick weapon");
            (player)->pickWeapon(*iter);
        }
    }

    /*拾取甲包检测*/
    for (Vector<ArmorBag*>::iterator iter = acontact.begin(); iter < acontact.end(); iter++)
    {
        if (rectContactCheck((player)->delegateSprite->getBoundingBox(), (*iter)->getSprite()->getBoundingBox()) && (*iter)->getState() == false)
        {
            log("succeed to pick Armor");
            actor::addArmor();
            (*iter)->setState(false);
            (*iter)->getSprite()->setVisible(false);
            (*iter)->removeFromParentAndCleanup(true);
        }
    }
    /*拾取子弹检测*/
    for (Vector<PistolBulletBag*>::iterator iter = pcontact.begin(); iter < pcontact.end(); iter++)
    {
        if (rectContactCheck((player)->delegateSprite->getBoundingBox(), (*iter)->getSprite()->getBoundingBox()) && (*iter)->getState() == false)
        {
            log("succeed to pick PistolBullet");
            (player)->getMyMainWeapon()->setBulletInventory(true, BulletNum, isPistol);
            (*iter)->setState(false);
            (*iter)->getSprite()->setVisible(false);
            (*iter)->getSprite()->setPosition(0,0);
            (*iter)->removeFromParentAndCleanup(true);
        }
    }
    for (Vector<RifleBulletBag*>::iterator iter = rcontact.begin(); iter < rcontact.end(); iter++)
    {
        if (rectContactCheck((player)->delegateSprite->getBoundingBox(), (*iter)->getSprite()->getBoundingBox()) && (*iter)->getState() == false)
        {
            log("succeed to pick RifleBullet");
            (player)->getMyMainWeapon()->setBulletInventory(true, BulletNum, isRifle);
            (*iter)->setState(false);
            (*iter)->getSprite()->setVisible(false);
            (*iter)->removeFromParentAndCleanup(true);
        }
    }
    for (Vector<ShotgunBulletBag*>::iterator iter = scontact.begin(); iter < scontact.end(); iter++)
    {
        if (rectContactCheck((player)->delegateSprite->getBoundingBox(), (*iter)->getSprite()->getBoundingBox()) && (*iter)->getState() == false)
        {
            log("succeed to pick ShotgunBullet");
            (player)->getMyMainWeapon()->setBulletInventory(true, BulletNum, isShotgun);
            (*iter)->setState(false);
            (*iter)->getSprite()->setVisible(false);
            (*iter)->removeFromParentAndCleanup(true);
        }
    }

    for (Vector<GatlingBulletBag*>::iterator iter = gcontact.begin(); iter < gcontact.end(); iter++)
    {
        if (rectContactCheck((player)->delegateSprite->getBoundingBox(), (*iter)->getSprite()->getBoundingBox())&&(*iter)->getState()==false)
        {
            log("succeed to pick GatlingBullet");
            (player)->getMyMainWeapon()->setBulletInventory(true, GtlBulletNum, isGatling);
            (*iter)->setState(false);
            (*iter)->getSprite()->setVisible(false);
            (*iter)->removeFromParentAndCleanup(true);
        }
    }
}

bool SingleModeRuntime::rectContactCheck(Rect rect1, Rect rect2)
{
    auto minX = std::max(rect1.getMinX(), rect2.getMinX());
    auto minY = std::max(rect1.getMinY(), rect2.getMinY());
    auto maxX = std::min(rect2.getMaxX(), rect1.getMaxX());
    auto maxY = std::min(rect2.getMaxY(), rect1.getMaxY());
    return (minX < maxX&& minY < maxY);
}

void SingleModeRuntime::generateEnemy()
{
    for (int i = 0; i < gameConsts::enemyCount; ++i)
    {
        enemyList[i] = enemy::create();
        enemyList[i]->setIndex(i);
        enemyList[i]->delegateSprite->setPosition(enemyGeneratePoint[i]);
        enemyList[i]->delegateSprite->setTag(tagConsts::tagEnemyStart + i);
        addChild(enemyList[i], 1, tagConsts::tagEnemyStart + i);
        addChild(enemyList[i]->myWeapon);
        SingleModeRuntime::enemyWeaponList.pushBack(enemyList[i]->myWeapon);
    }
}

void SingleModeRuntime::doDamage(int index)
{
    log("%d enemy is hit!", index);
    if (!enemyList[index]->takeDamage(100))
    {
        enemyList[index]->myWeapon->setState(false);

        Texture2D* enemyDead;
        Sprite* temp = Sprite::create("Actor\\Monster\\O_small_monster_dead.png");
        enemyDead = temp->getTexture();
        enemyList[index]->delegateSprite->stopAllActions();
        enemyList[index]->delegateSprite->setTexture(enemyDead);
        enemyDeadNum = index;
        
        /*延时清除敌人*/
        scheduleOnce(CC_SCHEDULE_SELECTOR(SingleModeRuntime::removeEnemy), 0.5f);
    }
}
void SingleModeRuntime::victory()
{
    Victory::totalTime = num;
    Director::getInstance()->getOpenGLView()->setCursorVisible(true);
    Director::getInstance()->replaceScene(Victory::createScene());
}

void SingleModeRuntime::removeEnemy(float dt)
{
    enemyList[enemyDeadNum]->removeFromParentAndCleanup(true);
    enemyCnt--;
    log("enemyCnt is %d", enemyCnt);
    if (enemyCnt == 0)
    {
        victory();
    }
}

void SingleModeRuntime::addItemToCheck()
{
    for (int i = 0; i < BagNum; i++)
    {
        if ((&armorBag[i])->getState() == false)
            acontact.pushBack((&armorBag[i]));
        else
            acontact.eraseObject((&armorBag[i]));
        if ((&pistolBulletBag[i])->getState() == false)
            pcontact.pushBack((&pistolBulletBag[i]));
        else
            pcontact.eraseObject((&pistolBulletBag[i]));
        if ((&rifleBulletBag[i])->getState() == false)
            rcontact.pushBack((&rifleBulletBag[i]));
        else
            rcontact.eraseObject((&rifleBulletBag[i]));
        if ((&shotgunBulletBag[i])->getState() == false)
            scontact.pushBack((&shotgunBulletBag[i]));
        else
            scontact.eraseObject((&shotgunBulletBag[i]));
    }

    for (int i = 0; i < GtlBulletBagNum; i++)
    {
        if ((&gatlingBulletBag[i])->getState() == false)
            gcontact.pushBack((&gatlingBulletBag[i]));
        else
            gcontact.eraseObject((&gatlingBulletBag[i]));
    }

    if ((&goldengun)->getState() == false)
        contact.pushBack((&goldengun));
    else
        contact.eraseObject((&goldengun));

    /*刀的检测*/
    for (int i = 0; i < knifeNum; i++)
    {
        if ((&knife[i])->getState() == false)
            contact.pushBack((&knife[i]));
        else
            contact.eraseObject((&knife[i]));
    }

    /*手枪的检测*/
    for (int i = 0; i < pistolNum; i++)
    {
        
        if ((&pistol[i])->getState() == false)
            contact.pushBack((&pistol[i]));
        else
            contact.eraseObject((&pistol[i]));
    }
    
    /*步枪、散弹枪的检测*/
    for (int i = 0; i < rifleNum; i++)
    {
        if ((&rifle[i])->getState() == false)
            contact.pushBack((&rifle[i]));
        else
            contact.eraseObject((&rifle[i]));

        if ((&shotgun[i])->getState() == false)
            contact.pushBack((&shotgun[i]));
        else
            contact.eraseObject((&shotgun[i]));
    }
}

void SingleModeRuntime::countTime()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    nowTime = now.tv_sec;   //获取调用定时器后的时间
    if ((nowTime - oldTime) >= 1)
        //判断调用定时器后的时间（可能调用了几次定时器）是否与调用定时器前的时间相差1s
    {
        num += (nowTime - oldTime);
        log("%d", this->num);
        std::string totalTime = "Total time: " + std::to_string(num) + "s";
        countTimeMessage->setString(totalTime);
        this->oldTime = nowTime;   //重新设定调用定时器前的时间
    }
}