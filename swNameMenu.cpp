#include "swNameMenu.h"
#include "swShipMenu.h"

swNameMenu::swNameMenu(swGame* g) : swTextMenu(g) {
    type = SW_NAME_MENU;
    // set the default text
    title.string = "CHOOSE A NAME";
    text.string = "PLAYER";
}

swNameMenu::~swNameMenu() {}

void swNameMenu::enteredText(QString value) {
    game->playerConstruct.name = value;
    game->drawables.append(new swShipMenu(game));
    remove();
}
