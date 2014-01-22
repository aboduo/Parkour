//
//  Role.h
//  Parkour
//
//  Created by sanren on 14-1-12.
//
//

#ifndef __Parkour__Role__
#define __Parkour__Role__

#include "UtCommonHeaders.h"

enum ROLE_STATE {
    ROLE_INVAILD_STATE = 0,
    ROLE_RUN,
    ROLE_JUMP_UP,
    ROLE_JUMP_DOWN,
    ROLE_STAND_BY
    };

class Role:public CCNode {
    
    
public:
    
    Role();
    ~Role();
    
    virtual bool init();
    
    static Role* createWithTMX(CCTMXTiledMap* _map);
    
    CC_SYNTHESIZE(CCTMXTiledMap*, gameMap, GameMap);
    
    CC_PROPERTY(CCPoint, currentRolePoint, CurrentRolePoint);
    
    CC_SYNTHESIZE(ROLE_STATE, currentRoleState, CurrentRoleState);
    
    CC_SYNTHESIZE(float, xSpeed, XSpeed);
    CC_SYNTHESIZE(float, ySpeed, YSpeed);
    
    CC_SYNTHESIZE(float, constXSpeed,ConstXSPeed);
    CC_SYNTHESIZE(float, constYSpeed,ConstYSpeed);
    
    void role_Update(float dt);
    void role_Logic();
private:
    
    CCSprite* mSprite;
    void extraInit();
    
private:
    
    void runLogic();
    void jumpUpLogic();
    void jumpDownLogic();
    
private:
    
    void camera_Update(float dt);
    void setMapPointByRole();//根据任务位置点设置镜头
    
};

#endif /* defined(__Parkour__Role__) */
