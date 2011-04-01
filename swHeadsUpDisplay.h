#ifndef SWHEADSUPDISPLAY_H
#define SWHEADSUPDISPLAY_H

#include "swGame.h"
#include "swLabel.h"

class swHeadsUpDisplay : public swDrawable
{
public:
    swHeadsUpDisplay(swGame* g);
    virtual ~swHeadsUpDisplay();

    virtual void draw();

    swGame* game;
    swLabel fuel;
    swLabel score;
    swLabel ammo;
};

#endif // SWHEADSUPDISPLAY_H
