//
//  OnlineModeRuntimeScene.h
//  PUBG
//
//  Created by PC1 on 2021/5/19.
//

#ifndef OnlineModeRuntimeScene_h
#define OnlineModeRuntimeScene_h

#include "cocos2d.h"
#include "actor/heroUI.h"

USING_NS_CC;

class OnlineModeRuntime : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    void menuPauseCallback(Ref* pSender);
    
    void menuCloseCallback(Ref* pSender);
    
    void hostSelectedCallback(Ref* pSender);
    
    void joinSelectedCallback(Ref* pSender);

    CREATE_FUNC(OnlineModeRuntime);
};

#endif /* OnlineModeRuntimeScene_h */
