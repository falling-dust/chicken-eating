//
//  Slider.h
//  PUBG
//
//  Created by PC1 on 2021/5/22.
//

#ifndef Slider_h
#define Slider_h

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Slider : public Layer
{
public:
    static Scene* scene();
    
    ValueChanged(int* sender,Controller ev);
    
    CREATE_FUNC(Slider);
    
    bool init();
    
    //void ValueChanged(Object*, ControlEvent);
};

#endif /* Slider_h */
