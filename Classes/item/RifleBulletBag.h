//
//  RifleBulletBag.h
//  PUBG
//
//  Created by PC1 on 2021/6/19.
//

#ifndef RifleBulletBag_h
#define RifleBulletBag_h

#include "Item/Item.h"
#include "Item/Weapon.h"

class RifleBulletBag:public Item
{
public:
    RifleBulletBag();
    
    CREATE_FUNC(RifleBulletBag);
    
    bool init();

protected:
    
    //Vec2 ArmorBagPos;
    
    
};


#endif /* RifleBulletBag_h */
