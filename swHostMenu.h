#ifndef SWHOSTMENU_H
#define SWHOSTMENU_H

#include "swTextMenu.h"

class swHostMenu : public swTextMenu {

public:
    swHostMenu(swGame* g);
    virtual ~swHostMenu();

    virtual void enteredText(QString value);
};

#endif // SWHOSTMENU_H
