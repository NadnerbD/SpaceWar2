#include "swMainMenu.h"

swMainMenu::swMainMenu(swGame* g) :
        swDrawable(0, 0, 0, 1, 1),
        game(g),
        title(&game->font, "SPACEWAR 2"),
        join(&game->font, "JOIN GAME"),
        host(&game->font, "HOST GAME") {
    type = SW_MAIN_MENU;
    // set up label locations
    title.pos = swVector(0, 0.8);
    title.scale = swVector(0.1, 0.1);
    join.pos = swVector(0, 0);
    host.pos = swVector(0, -0.5);
}

swMainMenu::~swMainMenu() {}

void swMainMenu::draw() {
    glPushMatrix();
    transform();
    title.draw();
    join.draw();
    host.draw();
    glPopMatrix();
}
