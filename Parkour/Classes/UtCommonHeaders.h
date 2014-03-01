//
//  UtCommonHeaders.h
//  Parkour
//
//  Created by sanren on 14-1-9.
//
//

#ifndef Parkour_UtCommonHeaders_h
#define Parkour_UtCommonHeaders_h

#include "cocos2d.h"
#include "UtDlog.h"
#include <vector>
#include <string>


const int ROLE_ZORDER = 10;
const int GoldBatchNode = 1000;
const int Gold_Particle_Tag = 1001;

USING_NS_CC;

struct Gold_Struct {
    CCSprite* goldSprite;
    int goldValue;
};


#endif
