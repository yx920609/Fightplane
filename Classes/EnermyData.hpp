//
//  EnermyData.hpp
//  Fightplane
//
//  Created by yxmac on 2017/5/27.
//
//

#ifndef EnermyData_hpp
#define EnermyData_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class EnermyData {
    public:
    Vector<Node *> enermyArray;
    static EnermyData *sharedAnermy();
    int timeAdd;
    Sprite *hero;
    
    int curruntScore;
private:
    static EnermyData* m_singleton;
    void timerAdd();



};

#endif /* EnermyData_hpp */
