//
//  HostWaitScene.h
//  PUBG
//
//  Created by PC1 on 2021/6/18.
//

#ifndef HostWaitScene_h
#define HostWaitScene_h
#include "cocos2d.h"

USING_NS_CC;

class HostWait : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    //EditBox* editBox;
    
    const char* roomNum;
    
    CREATE_FUNC(HostWait);
    
protected:
    
    Label* playerID1;
    Label* playerID2;
    Label* playerID3;
    Label* playerID4;
    
    std::string ID1="null";
    std::string ID2="null";
    std::string ID3="null";
    std::string ID4="null";
    
    
};


#endif /* HostWaitScene_h */
