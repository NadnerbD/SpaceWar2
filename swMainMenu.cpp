#include "swMainMenu.h"

#include "swNameMenu.h"

#include <QKeyEvent>
#include <QMouseEvent>

swMainMenu::swMainMenu(swGame* g) :
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
        case(Qt::Key_Return):
            choose();
            return; // get out of here, this no longer exists
        }
        if(selection >= selections.length())
            selection = 0;
        if(selection < 0)
            selection = selections.length() - 1;
    }
}

void swMainMenu::choose() {
    // this will move us to the next menu
    switch(selection) {
    case(0): // host game
        return;
        break;
    case(1): // join game
        game->drawables.append(new swNameMenu(game));
        break;
    case(2): // options
        return;
        break;
    }
    // remove and destroy this menu
    game->drawables.removeAll(this);
    delete this;
}

void swMainMenu::mouseHandle(QMouseEvent* event) {
    swVector pos = game->projMousePos(event->posF());
    if(event->type() == QMouseEvent::MouseMove) {
        for(int i = 0; i < selections.length(); i++) {
            swLabel* item = selections[i];
            if(pos.x < item->pos.x + item->scale.x * (item->string.length() - 1) &&
               pos.x > item->pos.x - item->scale.x * (item->string.length() - 1) &&
               pos.y < item->pos.y + item->scale.y &&
               pos.y > item->pos.y - item->scale.y) {
                selection = i;
            }
        }
    }else if(event->type() == QMouseEvent::MouseButtonPress) {
        choose();
    }
}
