//
//  GameOverSence.h
//  PUBG
//
//  Created by PC1 on 2021/6/7.
//

#ifndef GameOverSence_h
#define GameOverSence_h

#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class GameOver : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    void mainMenuCallback(Ref* pSender);
    
    CREATE_FUNC(GameOver);
    
private:
    MenuItemImage* clickItem;
    
    Menu* closeButtonMenu;
    
    Label* labelTips;
    
};
#endif /* GameOverSence_h */
