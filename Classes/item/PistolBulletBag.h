//
//  PistolBulletBag.h
//  PUBG
//
//  Created by PC1 on 2021/6/19.
//

#ifndef PistolBulletBag_h
#define PistolBulletBag_h
#include "Item/Item.h"
#include "Item/Weapon.h"

class PistolBulletBag:public Item
{
public:
    PistolBulletBag();
    
    CREATE_FUNC(PistolBulletBag);
    
    bool init();

protected:
    
    //Vec2 ArmorBagPos;
    
    
};


#endif /* PistolBulletBag_h */
