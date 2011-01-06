#ifndef SWSHIP_H
#define SWSHIP_H

#include "swPhysical.h"

class swShip : public swPhysical {
public:
    swShip();
    virtual ~swShip();

    static const double fireVel = 4.0;

    virtual bool collide(swPhysical* other);
    virtual void draw();
    virtual void tick();
    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    virtual void fire();
    virtual void die();
    virtual void createDebris();
    virtual void handleCollision(swPhysical* other);

    int fuel;
    int ammo;
    bool killed;
};

#endif // SWSHIP_H
