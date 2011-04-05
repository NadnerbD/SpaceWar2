#include <QKeyEvent>
#include <QMouseEvent>

#include "swMainMenu.h"

swMainMenu::swMainMenu(swGame* g) :
        swDrawable(0, 0, 0, 1, 1),
        game(g),
        title(&game->font, "SPACEWAR 2"),
        join(&game->font, "JOIN GAME"),
        host(&game->font, "HOST GAME"),
        options(&game->font, "OPTIONS"),
        selector(&game->font, ">         <"),
        selection(0) {
    type = SW_MAIN_MENU;
    // set up label locations
    title.pos = swVector(0, 0.8);
    title.scale = swVector(0.1, 0.1);
    host.pos = swVector(0, 0);
    join.pos = swVector(0, -0.25);
    options.pos = swVector(0, -0.5);
    // add the menu options to the selections list
    selections.append(&host);
    selections.append(&join);
    selections.append(&options);
    // attach our input handlers
    connect(game, SIGNAL(keyEvent(QKeyEvent*)), SLOT(keyHandle(QKeyEvent*)));
    connect(game, SIGNAL(mouseEvent(QMouseEvent*)), SLOT(mouseHandle(QMouseEvent*)));
}

swMainMenu::~swMainMenu() {}

void swMainMenu::draw() {
    // move the selector towards it's intended position
    selector.pos = selector.pos * 0.8 + selections[selection]->pos * 0.2;
    // draw the menu
    glPushMatrix();
    transform();
    title.draw();
    foreach(swLabel* label, selections) {
        label->draw();
    }
    selector.draw();
    glPopMatrix();
}

void swMainMenu::keyHandle(QKeyEvent* event) {
    if(!event->isAutoRepeat() && event->type() == QKeyEvent::KeyPress) {
        switch(event->key()) {
        case(Qt::Key_Up):
            selection--;
            break;
        case(Qt::Key_Down):
            selection++;
            break;
        }
        if(selection >= selections.length())
            selection = 0;
        if(selection < 0)
            selection = selections.length() - 1;
    }
}

void swMainMenu::mouseHandle(QMouseEvent* event) {
    if(event->type() == QMouseEvent::MouseMove) {
        // the screen edges don't seem to be positioned quite at 1 and -1, so fudge scaling here
        swVector pos = swVector((event->posF().x() / game->size().width() * 2 - 1) * 1.1,
                                (-event->posF().y() / game->size().height() * 2 + 1) * 1.1);
        //qWarning("(%f, %f)", pos.x, pos.y);
        for(int i = 0; i < selections.length(); i++) {
            swLabel* item = selections[i];
            if(pos.x < item->pos.x + item->scale.x * 5 &&
               pos.x > item->pos.x - item->scale.x * 5 &&
               pos.y < item->pos.y + item->scale.y &&
               pos.y > item->pos.y - item->scale.y) {
                selection = i;
            }
        }
    }
}
