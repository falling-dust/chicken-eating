//
//  GatlingBulletBag.h
//  PUBG
//
//  Created by PC1 on 2021/6/20.
//

#ifndef GatlingBulletBag_h
#define GatlingBulletBag_h

#include "Item/Item.h"
#include "Item/Weapon.h"

class GatlingBulletBag:public Item
{
public:
    GatlingBulletBag();
    
    CREATE_FUNC(GatlingBulletBag);
    
    bool init();

protected:
    
   
    
};

#endif /* GatlingBulletBag_h */
