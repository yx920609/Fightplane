//
//  endLayer.hpp
//  Fightplane-mobile
//
//  Created by yxmac on 2017/11/14.
//

#ifndef endLayer_hpp
#define endLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameLayer.hpp"
USING_NS_CC;

class endLayer:public cocos2d::Layer {

public:
    static Scene *createScene();
    
    virtual bool init();

    CREATE_FUNC(endLayer);
private:
    
    void restart(cocos2d::Ref* pSender,cocos2d::ui::Widget::TouchEventType event);

};

#endif /* endLayer_hpp */
