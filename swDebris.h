#ifndef SWDEBRIS_H
#define SWDEBRIS_H

#include "swPhysical.h"

class swDebris : public swPhysical {
public:
    swDebris();
    virtual ~swDebris();

    virtual void draw();
    virtual bool collide(swPhysical* other);
    virtual void handleCollision(swPhysical* other);
};

#endif // SWDEBRIS_H
