//
//  OnlineHostScene.h
//  PUBG
//
//  Created by PC1 on 2021/6/15.
//

#ifndef OnlineHostScene_h
#define OnlineHostScene_h

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "HostWaitScene.h"

USING_NS_CC;
using namespace ui;


class OnlineHost : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    //EditBox* editBox;
    
    const char* roomNum;
    
    CREATE_FUNC(OnlineHost);
    
private:
    
    
    
};

#endif /* OnlineHostScene_h */
