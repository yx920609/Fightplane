//
//  RandomPlane.cpp
//  Fightplane-mobile
//
//  Created by yxmac on 2017/11/15.
//

#include "RandomPlane.hpp"
#include "EnermyData.hpp"
#include "endLayer.hpp"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
bool RandomPlane::init() {
    
    if (!Sprite::create()) {
        return false;
    }
//    this->schedule(schedule_selector(RandomPlane::move), 1);
//    this->schedule(schedule_selector(RandomPlane::remove));
//    
    this->scheduleUpdate();
    
    return true;
}

void RandomPlane::getAngle() {
    float x = EnermyData::sharedAnermy()->hero->getPosition().x;
    float y = EnermyData::sharedAnermy()->hero->getPosition().y;
    float a = this->getPosition().x - x;
    float b = this->getPosition().y- y;
    
    this->angle = b ==0?0:atanf(a / b);
    if (this->angle) {
        float mDegree = CC_RADIANS_TO_DEGREES(this->angle);
        this->setRotation(180+mDegree);
    }
   
}

void RandomPlane::move(float dt) {
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("superEnermy.plist", "superEnermy.png");
    
    this->setSpriteFrame(StringUtils::format("img_plane_enemy_%d.png",this->planeType));
    
    
//    this->setTexture("a2-1.png");

    
    float x = EnermyData::sharedAnermy()->hero->getPosition().x;
    float y = EnermyData::sharedAnermy()->hero->getPosition().y;
    float a = this->getPosition().x - x;
    float b = this->getPosition().y- y;
    
    this->angle = b ==0?0:atanf(a / b);
    if (this->angle) {
        float mDegree = CC_RADIANS_TO_DEGREES(this->angle);
        this->setRotation(mDegree);
        float endX = this->getPosition().x-(a / b)*this->getPosition().y;
        float endY = 0;
        float flyVelocity = 200;//运行速度，可以自己控制，每秒所走的像素
        float flyLen = sqrt((this->getPosition().x - endX)*(this->getPosition().x - endX)+(this->getPosition().y - endY)*(this->getPosition().y - endY));
        float realFlyDuration = flyLen / flyVelocity;//实际飞行的时间
        //子弹运行的距离和时间，从飞机处开始运行到屏幕底部
        auto actionMove = MoveTo::create(realFlyDuration, Point(endX, endY));
        //子弹执行完动作后进行函数回调，调用移除子弹函数
      
        //连续动作
        Sequence* sequence = Sequence::create(actionMove, RemoveSelf::create(true), NULL);
        //飞机开始跑动
        this->runAction(sequence);
    }
   
}

void RandomPlane::update(float dt) {
    
    Vector<Node *>vect1;
    
    auto array = EnermyData::sharedAnermy()->enermyArray;
    
    for( Node *bullet : array) {
        if (this->boundingBox().intersectsRect(bullet->boundingBox())) {
            
            SimpleAudioEngine::getInstance()->playEffect("sounds/boom.mp3");

            
            EnermyData::sharedAnermy()->curruntScore +=100;
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("boom.plist", "boom.png");
            
            __Dictionary* dic = __Dictionary::createWithContentsOfFile("boom.plist");
            
            __Dictionary* dic2 = dynamic_cast<__Dictionary*>(dic->objectForKey("frames"));
            
            Sprite* sp = Sprite::createWithSpriteFrameName("anmition_1.png");
            sp->setFlippedX(true);
            sp->setPosition(this->getPosition());
            this->getParent()->addChild(sp);
            Vector<SpriteFrame*> allFrame;
            for (int i = 1; i <= dic2->count(); i++) {
                SpriteFrame* sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("anmition_%d.png",i));
                allFrame.pushBack(sf);
            }
            
            Animation* animtaion = Animation::createWithSpriteFrames(allFrame, 0.1);
            
            
            Animate* animte = Animate::create(animtaion);
            
            animte->setTag(100);
            
            Sequence* seq = Sequence::create(animte, RemoveSelf::create(true), NULL);
            
            sp->runAction(seq);
            
            if (bullet->getTag() == 8888) {
                
                EnermyData::sharedAnermy()->enermyArray.eraseObject(bullet);
                
                this->removeFromParentAndCleanup(true);
                
                this->stopAction(1);
                
                return;
            }
            
            EnermyData::sharedAnermy()->enermyArray.eraseObject(bullet);
            
            NotificationCenter::getInstance()->postNotification("notice");
            
            this->removeFromParentAndCleanup(true);
            
            if (bullet->getTag() != 8888) {
                
                bullet->stopAllActions();
                
                bullet->removeFromParentAndCleanup(true);
            }
            
            break;
        }
        
    }
    
    
    //    for (int i = 0 ; i<array.size(); i++) {
    //        Node *bullet = vect1.at(i);
    //        if (this->boundingBox().intersectsRect(bullet->boundingBox())) {
    //            this->removeFromParentAndCleanup(true);
    //            bullet->removeFromParentAndCleanup(true);
    //            //            EnermyData::sharedAnermy()->enermyArray.eraseObject(bullet);
    //            vect1.pushBack(bullet);
    //        }
    //    }
    
    //    for (int i = 0; i<vect1.size(); i++) {
    //        EnermyData::sharedAnermy()->enermyArray.eraseObject(vect1.at(i));
    //    }
    
    
}

bool RandomPlane:: stopAction(float dt) {
    //    Director::getInstance()->stopAnimation();
//    SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    Scene *endScene = endLayer::createScene();
    
    auto array = EnermyData::sharedAnermy()->enermyArray;
    
    array.clear();
    
    //    this->getParent()->removeAllChildren();
    
    Director::getInstance()->replaceScene(endScene);
    
    return true;
}
