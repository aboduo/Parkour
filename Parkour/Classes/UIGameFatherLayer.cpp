//
//  UIGameFatherLayer.cpp
//  Parkour
//
//  Created by sanren on 14-1-9.
//
//

#include "UIGameFatherLayer.h"


UIGameFatherLayer::UIGameFatherLayer()
{
    CC_SAFE_RETAIN(m_GameMap);
}

UIGameFatherLayer::~UIGameFatherLayer()
{
    CC_SAFE_RELEASE_NULL(m_GameMap);
}

bool UIGameFatherLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    initUI();
    initMap();
    initRole();
    return true;
}

void UIGameFatherLayer::initUI()
{
    
}

void UIGameFatherLayer::initMap()
{
    m_GameMap = CCTMXTiledMap::create("mapGrass.tmx");
    this->addChild(m_GameMap,1);
}

void UIGameFatherLayer::initRole()
{
    m_Role = Role::createWithTMX(m_GameMap);
    
    this->addChild(m_Role, ROLE_ZORDER);
    
//    CCTMXObjectGroup* group = m_GameMap->objectGroupNamed("Role");
//    CCDictionary* dictionary = group->objectNamed("player");
//    
//    int x = dictionary->valueForKey("x")->intValue();
//    int y = dictionary->valueForKey("y")->intValue();
//    
//    CCSprite* sp = CCSprite::create("Icon.png");
//    sp->setPosition(ccp(x,y));
//    sp->setAnchorPoint(CCPointZero);
//    
//    m_GameMap->addChild(sp, ROLE_ZORDER);
}

CCScene* UIGameFatherLayer::scene()
{
    CCScene* sc = CCScene::create();
    
    sc->addChild(UIGameFatherLayer::create());
    
    return sc;
}
