#ifndef SWMISSILE_H
#define SWMISSILE_H

#include "swPhysical.h"
#include "swPlayer.h"

class swMissile : public swPhysical {
public:
    swMissile();
    virtual ~swMissile();

    virtual void draw();
    virtual void handleCollision(swPhysical* other);
};

#endif // SWMISSILE_H
