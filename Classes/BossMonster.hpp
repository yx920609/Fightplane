//
//  BossMonster.hpp
//  Fightplane-mobile
//
//  Created by yxmac on 2017/11/15.
//

#ifndef BossMonster_hpp
#define BossMonster_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class BossMonster :public Sprite {
public:
    CREATE_FUNC(BossMonster);
    bool init();
    void openFlyBullet(float dt);
    void fireJiguang(float dt);
    
    void bulletMove(float dt);
    bool stopAction(float dt);

    void removeFlyBullet(Ref *sender);
    
    void laserBoom(float dt);
    
    void removeLazer(Ref *sender);
private:
    Vector<Sprite *>flyBulletArray;
    
    int totalShooted = 100;
    
    void update(float dt);
    
    Sprite *lazer;

};

#endif /* BossMonster_hpp */
