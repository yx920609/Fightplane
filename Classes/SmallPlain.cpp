//
//  SmallPlain.cpp
//  Fightplane
//
//  Created by yxmac on 2017/5/27.
//
//

#include "SmallPlain.hpp"
#include "EnermyData.hpp"
#include "endLayer.hpp"

USING_NS_CC;
bool SmallPlain::init() {
    if (!this->Sprite::initWithFile("a2-1.png")) {
        return false;
    }
//    auto winsize = Director::getInstance()->getWinSize();
//    auto origin = Director::getInstance()->getVisibleOrigin();
    
//    mynewData = EnermyData::sharedAnermy();
    
    this->schedule(schedule_selector(SmallPlain::move), 0.01);
    this->schedule(schedule_selector(SmallPlain::remove));

    this->scheduleUpdate();
    return true;
}

void SmallPlain::move(float dt) {
    this->setPosition(this->getPositionX(), this->getPositionY()-EnermyData::sharedAnermy()->timeAdd/100);
}


void SmallPlain::remove(float dt){
    
    
    if (this->getPositionY() <this->getContentSize().height+Director::getInstance()->getVisibleOrigin().y) {
        
        this->removeFromParentAndCleanup(true);
    }
    
    
}

void SmallPlain::update(float dt) {

    Vector<Node *>vect1;
    
    auto array = EnermyData::sharedAnermy()->enermyArray;
    
    for( Node *bullet : array) {
        if (this->boundingBox().intersectsRect(bullet->boundingBox())) {
          
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

bool SmallPlain:: stopAction(float dt) {
//    Director::getInstance()->stopAnimation();

    Scene *endScene = endLayer::createScene();

    auto array = EnermyData::sharedAnermy()->enermyArray;

    array.clear();
    
//    this->getParent()->removeAllChildren();

    Director::getInstance()->replaceScene(endScene);
 
    return true;
}

