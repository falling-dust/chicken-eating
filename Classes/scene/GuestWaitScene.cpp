//
//  GuestWaitScene.cpp
//  PUBG
//
//  Created by PC1 on 2021/6/18.
//

#include "GuestWaitScene.h"
#include <stdio.h>

Scene* GuestWait::createScene()
{
    return GuestWait::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GuestWait::init()
{
    return true;
}
