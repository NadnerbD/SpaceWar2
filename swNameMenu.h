#ifndef SWNAMEMENU_H
#define SWNAMEMENU_H

#include "swTextMenu.h"

class swNameMenu : public swTextMenu {

public:
    swNameMenu(swGame* g);
    virtual ~swNameMenu();

    virtual void enteredText(QString value);
};

#endif // SWNAMEMENU_H
