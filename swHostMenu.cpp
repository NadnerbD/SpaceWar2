#include "swHostMenu.h"

swHostMenu::swHostMenu(swGame* g) : swTextMenu(g) {
    type = SW_HOST_MENU;
    // set the default text
    title.string = "ENTER A HOSTNAME OR IP";
    text.string = "LOCALHOST";
}

swHostMenu::~swHostMenu() {}

void swHostMenu::enteredText(QString value) {
    // prepare to connect to the entered host
    //game->drawables.append(new somethingElse(game));
    remove();
}
