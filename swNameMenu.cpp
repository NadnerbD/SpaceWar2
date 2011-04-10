#include "swNameMenu.h"
#include "swShipMenu.h"

#include <QKeyEvent>

swNameMenu::swNameMenu(swGame* g) : game(g), title(&game->font, "CHOOSE A NAME"), name(&game->font, "PLAYER") {
    type = SW_NAME_MENU;
    title.pos = swVector(0, 0.8);
    title.scale = swVector(0.1, 0.1);
    name.scale = swVector(0.05, 0.05);
    connect(game, SIGNAL(keyEvent(QKeyEvent*)), SLOT(keyHandle(QKeyEvent*)));
    connect(game, SIGNAL(mouseEvent(QMouseEvent*)), SLOT(mouseHandle(QMouseEvent*)));
}

swNameMenu::~swNameMenu() {}

void swNameMenu::draw() {
    glPushMatrix();
    transform();
    title.draw();
    name.draw();
    glPopMatrix();
}

void swNameMenu::keyHandle(QKeyEvent* event) {
    if(event->type() == QKeyEvent::KeyPress) {
        if(event->key() == Qt::Key_Backspace && name.string.length()) {
            name.string.chop(1);
        }else if(event->key() == Qt::Key_Return && name.string.length()) {
            game->playerConstruct.name = name.string;
            game->drawables.append(new swShipMenu(game));
            game->drawables.removeAll(this);
            delete this;
        }else if(event->text().length() < 20 &&
                 name.font->hasLetter(event->text().toUpper().toAscii().data()[0])) {
            name.string.append(event->text().toUpper());
        }
    }
}

void swNameMenu::mouseHandle(QMouseEvent*) {
    // we don't do anything interesting with the mouse here
    // maybe I should have a continue button
}
