//
//  OnlineJoinScene.cpp
//  PUBG
//
//  Created by PC1 on 2021/6/15.
//

#include "OnlineJoinScene.h"
#include <stdio.h>

USING_NS_CC;
using namespace ui;


Scene* OnlineJoin::createScene()
{
    return OnlineJoin::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool OnlineJoin::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值
    //输入框背景
        auto inputBox = Sprite::create("inputFrame.png");
        inputBox->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
        this->addChild(inputBox);
        
        /**
         *  输入框控件
         *  1.Size 输入框的大小
         *  2.Scale9Sprite 输入框背景，由输入框的大小决定输入框背景的大小，这里我们并没有传入参数，而是自己创建了一个输入框背景。
         */
        auto editBox = EditBox::create(Size(inputBox->getContentSize().width,inputBox->getContentSize().height), Scale9Sprite::create("inputFrame.png"));
        editBox->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
        editBox->setMaxLength(30);   //输入框最多能输入多少个字符
        editBox->setText("Please input the room number"); //初始化文字
        editBox->setFontColor(Color3B(255,0, 0));   //文字颜色
        editBox->setFontSize(10);   //文字的大小
        this->addChild(editBox);
        
        
        //进入按钮
        auto joinButtom =MenuItemImage::create("joinRoom.png", "joinRoomSelected.png");
        joinButtom->setPosition(Point(Vec2(visibleSize.width/2,visibleSize.height/3)));
        joinButtom->setCallback([&,editBox](Ref*obj){
            roomNum=editBox->getText();
            log("%s",roomNum);
            //取得输入框里面的文字，输出到控制台
            //log("%s",editBox->getText());
        });
        
        
        auto menu = Menu::create(joinButtom,NULL);
        menu->setPosition(Point::ZERO);
        this->addChild(menu);

    
    return true;
    
}
