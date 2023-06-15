//
//  Slider.cpp
//  PUBG
//
//  Created by PC1 on 2021/5/22.
//

#include "Slider.h"

Scene* Slider::scene()
{
    auto* s = Scene::create();
    auto* layer = Slider::create();
    s->addChild(layer);
    return s;
}

bool Slider::init()
{
    //初始化父类
    Layer::init();

    //得到窗体的尺寸
    auto visibleSize = Director::getInstance()->getVisibleSize();//实际窗口尺寸
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//偏移值

    //创建一个滑块
    auto* slider = ControlSlider::create("SliderTrack.png", "SliderProgress.png", "SliderThumb.png");
    
    //加入滑块
    addChild(slider);
    
    //设置滑块的位置
    slider->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + 2*visibleSize.height/5));

    //设置滑块滑动范围的最小值
    slider->setMinimumValue(0);

    //设置滑块的最大值
    slider->setMaximumValue(100);
    
    
    //设置滑块滑动时的最大值，此功能经常使用于视频站点中的免费试看的电影
    slider->setMaximumAllowedValue(90);

    //设置滑块滑动的最小值，此功能经常使用于视频站点中的免费试看的电影
    slider->setMinimumAllowedValue(10);
    
    //设置滑块当前值
    slider->setValue(30);

    //滑块响应函数(当滑块滑动时调用ValueChanged函数)
    slider->addTargetWithActionForControlEvents(this,
        cccontrol_selector(Slider::ValueChanged),
        ValueChanged(<#int *#>, <#Controller#>));
    
        return true;
}

void Slider::ValueChanged(int* sender,Controller ev)
{
    //当滑块滑动时
    if (ev == ControlEventValueChanged)
    {
        ControlSlider* slider = (ControlSlider*)sender;
        
        //得到滑块的值
        float f = slider->getValue();
        
        //打印滑块的值
        log("current value is %f", f);
    }
}
}
