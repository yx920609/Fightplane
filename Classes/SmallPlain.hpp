//
//  SmallPlain.hpp
//  Fightplane
//
//  Created by yxmac on 2017/5/27.
//
//

#ifndef SmallPlain_hpp
#define SmallPlain_hpp
USING_NS_CC;
#include <stdio.h>
#include "cocos2d.h"
#include "EnermyData.hpp"

class SmallPlain :public cocos2d::Sprite {
    
public:
    void move(float dt);
    bool init();
    bool stopAction(float dt);
    void remove(float dt);
    void update(float dt);
    CREATE_FUNC(SmallPlain);
    
};

#endif /* SmallPlain_hpp */
