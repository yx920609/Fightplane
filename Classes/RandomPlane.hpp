//
//  RandomPlane.hpp
//  Fightplane-mobile
//
//  Created by yxmac on 2017/11/15.
//

#ifndef RandomPlane_hpp
#define RandomPlane_hpp


#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;


class RandomPlane :public Sprite {
public:
    void move(float dt);
    bool init();
    bool stopAction(float dt);
//    void remove(float dt);
    void update(float dt);
    int planeType;
    float angle;
    void getAngle();
    CREATE_FUNC(RandomPlane);
};

#endif /* RandomPlane_hpp */
