//
//  OnlineModeRuntimeScene.cpp
//  PUBG
//
//  Created by PC1 on 2021/5/19.
//

#include "HelloWorldScene.h"
#include "OnlineModeRuntimeScene.h"
#include "OnlineJoinScene.h"
#include "OnlineHostScene.h"

USING_NS_CC;

Scene* OnlineModeRuntime::createScene()
{
    return OnlineModeRuntime::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool OnlineModeRuntime::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值

    auto labelGameName = Label::createWithTTF("online", "fonts\\Marker Felt.ttf", 45);
    if (labelGameName == nullptr)
    {
        problemLoading("'Marker Felt.ttf'");
    }
    else
    {
        labelGameName->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - labelGameName->getContentSize().height));

        this->addChild(labelGameName, 1);
    }
    
    //创建房间选择按钮
        //创建一段文字
    auto labelHost = Label::createWithTTF("Host a room","fonts\\Marker Felt.ttf", 40);
        //创建一个标签菜单对象，其实就是文字按钮拉
    auto hostItem = MenuItemLabel::create(labelHost,CC_CALLBACK_1(OnlineModeRuntime::hostSelectedCallback, this));
        //创建一个菜单，用来放上面创建出来的菜单对象 注意最后一定要加个NULL 告诉他可以开始创建了！
    auto hostMenu = Menu::create(hostItem, NULL);
    
    hostMenu->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + 3*visibleSize.height/4 - labelGameName->getContentSize().height));
    this->addChild(hostMenu,1);
    
    //加入房间选择按钮
        auto labelJoin = Label::createWithTTF("Join a room","fonts\\Marker Felt.ttf", 40);
            
        auto joinItem = MenuItemLabel::create(labelJoin,CC_CALLBACK_1(OnlineModeRuntime::joinSelectedCallback, this));
            
        auto joinMenu = Menu::create(joinItem, NULL);
        joinMenu->setPosition(Vec2(origin.x + visibleSize.width/2,
                                     origin.y + visibleSize.height/2 - labelGameName->getContentSize().height));
        this->addChild(joinMenu,1);
    

    return true;
}


void OnlineModeRuntime::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}


void OnlineModeRuntime::menuPauseCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(OnlineModeRuntime::createScene());
}


void OnlineModeRuntime::hostSelectedCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(OnlineHost::createScene());
}

void OnlineModeRuntime::joinSelectedCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(OnlineJoin::createScene());
}


