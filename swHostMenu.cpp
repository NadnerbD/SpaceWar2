#include "swHostMenu.h"
#include "swNameMenu.h"

swHostMenu::swHostMenu(swGame* g) : swTextMenu(g) {
    type = SW_HOST_MENU;
    // set the default text
    title.string = "ENTER IP ADDRESS";
    text.string = "LOCALHOST";
}

swHostMenu::~swHostMenu() {}

void swHostMenu::enteredText(QString value) {
    // prepare to connect to the entered host
    game->drawables.append(new swNameMenu(game));
    remove();
}
