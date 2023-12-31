//
//  GameOverSence.cpp
//  PUBG
//
//  Created by PC1 on 2021/6/7.
//

#include "GameOverSence.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    return GameOver::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
    
    clickItem = MenuItemImage::create(
                                           "GameOver.png",
                                           "GameOver.png",
                                           CC_CALLBACK_1(GameOver::mainMenuCallback, this));

    if (clickItem == nullptr ||
        clickItem->getContentSize().width <= 0 ||
        clickItem->getContentSize().height <= 0)
    {
        problemLoading("'GameOver.png'");
    }
    else
    {
        float x = visibleSize.width/2;
        float y = visibleSize.height/2;
        clickItem->setPosition(Vec2(x,y));
    }
    
    closeButtonMenu = Menu::create(clickItem, NULL);
    closeButtonMenu->setPosition(Vec2::ZERO);
    this->addChild(closeButtonMenu, 1);
    
    labelTips = Label::createWithTTF("Click to return", "fonts\\IRANYekanBold.ttf",20 );
    if (labelTips == nullptr)
    {
        problemLoading("'IRANYekanBold.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        labelTips->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height/3 - labelTips->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(labelTips, 1);
    }
    return true;
}


void GameOver::mainMenuCallback(Ref* pSender)
{
    //Close the cocos2d-x game over scene and jump to the start scene
    //Director::getInstance()->replaceScene(HelloWorld::create());
    Director::getInstance()->end();
}

