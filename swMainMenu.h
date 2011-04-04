#ifndef SWMAINMENU_H
#define SWMAINMENU_H

#include "swGame.h"
#include "swLabel.h"

class swMainMenu : public swDrawable
{
public:
    swMainMenu(swGame* g);
    virtual ~swMainMenu();

    virtual void draw();

    swGame* game;
    swLabel title;
    swLabel join;
    swLabel host;
};

#endif // SWMAINMENU_H
