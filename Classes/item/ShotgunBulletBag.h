//
//  ShotgunBulletBag.h
//  PUBG
//
//  Created by PC1 on 2021/6/19.
//

#ifndef ShotgunBulletBag_h
#define ShotgunBulletBag_h

#include "Item/Item.h"
#include "Item/Weapon.h"

class ShotgunBulletBag:public Item
{
public:
    ShotgunBulletBag();
    
    CREATE_FUNC(ShotgunBulletBag);
    
    bool init();

protected:
    
    
    
};

#endif /* ShotgunBulletBag_h */
