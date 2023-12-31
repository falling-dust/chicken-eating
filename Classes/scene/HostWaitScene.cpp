//
//  HostWaitScene.cpp
//  PUBG
//
//  Created by PC1 on 2021/6/18.
//

#include "HostWaitScene.h"
#include <stdio.h>

Scene* HostWait::createScene()
{
    return HostWait::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HostWait::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
    
    auto IDList = Label::createWithTTF("PlayerList:", "fonts\\Marker Felt.ttf",40);
    IDList->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - IDList->getContentSize().height));
    this->addChild(IDList,1);
    
    //玩家1信息
    auto IDtips1 = Label::createWithTTF("Player1:", "fonts\\Marker Felt.ttf", 25);
    IDtips1->setPosition(Vec2(origin.x + visibleSize.width/3,
                            origin.y + 3*visibleSize.height/4 - IDtips1->getContentSize().height));
    this->addChild(IDtips1, 1);
    std::string player1Message = ID1;
    playerID1 = Label::createWithTTF(player1Message, "fonts\\IRANYekanBold.ttf", 18.f);
    playerID1->setPosition(visibleSize.width/2, 2*visibleSize.height / 3);
    this->addChild(playerID1, 1);
    
    //玩家2信息
    auto IDtips2 = Label::createWithTTF("Player2:", "fonts\\Marker Felt.ttf", 25);
    IDtips2->setPosition(Vec2(origin.x + visibleSize.width/3,
                            origin.y + 3*visibleSize.height/5 - IDtips2->getContentSize().height));
    this->addChild(IDtips2, 1);
    std::string player2Message = ID2;
    playerID2 = Label::createWithTTF(player2Message, "fonts\\IRANYekanBold.ttf", 18.f);
    playerID2->setPosition(visibleSize.width/2, 21*visibleSize.height / 40);
    this->addChild(playerID2, 1);
    
    //玩家3信息
    auto IDtips3 = Label::createWithTTF("Player3:", "fonts\\Marker Felt.ttf", 25);
    IDtips3->setPosition(Vec2(origin.x + visibleSize.width/3,
                            origin.y + 9*visibleSize.height/20 - IDtips3->getContentSize().height));
    this->addChild(IDtips3, 1);
    std::string player3Message = ID3;
    playerID3 = Label::createWithTTF(player3Message, "fonts\\IRANYekanBold.ttf", 18.f);
    playerID3->setPosition(visibleSize.width/2, 15*visibleSize.height / 40);
    this->addChild(playerID3, 1);
    
    //玩家4信息
    auto IDtips4 = Label::createWithTTF("Player4:", "fonts\\Marker Felt.ttf", 25);
    IDtips4->setPosition(Vec2(origin.x + visibleSize.width/3,
                            origin.y + 3*visibleSize.height/10 - IDtips3->getContentSize().height));
    this->addChild(IDtips4, 1);
    std::string player4Message = ID4;
    playerID4 = Label::createWithTTF(player4Message, "fonts\\IRANYekanBold.ttf", 18.f);
    playerID4->setPosition(visibleSize.width/2, 9*visibleSize.height / 40);
    this->addChild(playerID4, 1);

    
    return true;
}
