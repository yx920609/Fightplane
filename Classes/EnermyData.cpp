//
//  EnermyData.cpp
//  Fightplane
//
//  Created by yxmac on 2017/5/27.
//
//

#include "EnermyData.hpp"
USING_NS_CC;

EnermyData* EnermyData::m_singleton = nullptr;
//void EnermyData::init() {
//    Vector<Sprite *> enermyArray;
//}

EnermyData* EnermyData::sharedAnermy() {
    if (!m_singleton) {
//        Vector<Sprite *>enermyArray(1000);
        m_singleton = new EnermyData();
 
    }

    return m_singleton;
}

void EnermyData::timerAdd() {
    m_singleton-> timeAdd = m_singleton->timeAdd+2;
}
