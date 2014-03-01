//
//  UIGameFatherLayer.h
//  Parkour
//
//  Created by sanren on 14-1-9.
//
//

#ifndef __Parkour__UIGameFatherLayer__
#define __Parkour__UIGameFatherLayer__

#include "UtCommonHeaders.h"
#include "Role.h"

class Role;

class UIGameFatherLayer :public CCLayer {
    
    
public:
    
    UIGameFatherLayer();
    ~UIGameFatherLayer();
    
    virtual bool init();
    void initUI();
    void initMap();
    void initRole();
    
    
    void initComponets();
    
    CREATE_FUNC(UIGameFatherLayer);
    
    static CCScene* scene();
    
    virtual bool ccTouchBegan(CCTouch* pTouch,CCEvent* pEvent);
    virtual void onEnter();
    virtual void onExit();
    
    void dispatchTouchRoleMove();
    
private:
    CCTMXTiledMap* m_GameMap;
    Role* m_Role;
    
    CCSpriteBatchNode* _pGoldBatchNode;
};

#endif /* defined(__Parkour__UIGameFatherLayer__) */
