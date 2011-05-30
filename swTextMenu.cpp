#include "swTextMenu.h"

#include <QKeyEvent>

swTextMenu::swTextMenu(swGame* g) : game(g), title(&game->font, "TITLE"), text(&game->font, "TEXT") {
    type = SW_TEXT_MENU;
    title.pos = swVector(0, 0.8);
    title.scale = swVector(0.1, 0.1);
    text.scale = swVector(0.05, 0.05);
    connect(game, SIGNAL(keyEvent(QKeyEvent*)), SLOT(keyHandle(QKeyEvent*)));
    connect(game, SIGNAL(mouseEvent(QMouseEvent*)), SLOT(mouseHandle(QMouseEvent*)));
}

swTextMenu::~swTextMenu() {}

void swTextMenu::draw() {
    glPushMatrix();
    transform();
    title.draw();
    text.draw();
    glPopMatrix();
}

void swTextMenu::keyHandle(QKeyEvent* event) {
    if(event->type() == QKeyEvent::KeyPress) {
        if(event->key() == Qt::Key_Backspace && text.string.length()) {
            text.string.chop(1);
        }else if(event->key() == Qt::Key_Return && text.string.length()) {
            enteredText(text.string);
        }else if(event->text().length() < 20 &&
                 text.font->hasLetter(event->text().toUpper().toAscii().data()[0])) {
            text.string.append(event->text().toUpper());
        }
    }
}

void swTextMenu::mouseHandle(QMouseEvent*) {
    // we don't do anything interesting with the mouse here
    // maybe I should have a continue button
}

void swTextMenu::remove() {
    game->drawables.removeAll(this);
    delete this;
}

void swTextMenu::enteredText(QString) {
    // Qt doesn't like pure virtual classes
}
