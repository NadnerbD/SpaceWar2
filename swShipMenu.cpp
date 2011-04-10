#include "swShipMenu.h"
#include "swLobbyMenu.h"
#include "swClient.h"

#include <QDir>
#include <QKeyEvent>
#include <QMouseEvent>

swShipMenu::swShipMenu(swGame* g) : game(g), title(&game->font, "CHOOSE A SHIP"), selection(0) {
    type = SW_SHIP_MENU;
    title.pos = swVector(0, 0.8);
    title.scale = swVector(0.1, 0.1);
    QDir dataDir("data");
    QStringList fileNames = dataDir.entryList(QStringList("*.shp"), QDir::Files, QDir::Name);
    for(int i = 0; i < fileNames.length(); i++) {
        QString fileName = fileNames[i];
        swMesh* ship = new swMesh("data/" + fileName);
        ship->scale = swVector(0.25, 0.25);
        ship->pos.x = (double)i * 0.75;
        ships.append(ship);
    }
    connect(game, SIGNAL(keyEvent(QKeyEvent*)), SLOT(keyHandle(QKeyEvent*)));
    connect(game, SIGNAL(mouseEvent(QMouseEvent*)), SLOT(mouseHandle(QMouseEvent*)));
}

swShipMenu::~swShipMenu() {
    foreach(swMesh* ship, ships)
        delete ship;
}

void swShipMenu::draw() {
    glPushMatrix();
    transform();
    title.draw();
    for(int i = 0; i < ships.length(); i++) {
        swMesh* ship = ships[i];
        ship->pos = ship->pos * 0.8 + swVector((i - selection) * 0.75, 0) * 0.2;
        double scale = i == selection ? 0.5 : 0.25;
        ship->scale = ship->scale * 0.8 + swVector(scale, scale) * 0.2;
        ship->draw();
    }
    glPopMatrix();
}

void swShipMenu::keyHandle(QKeyEvent* event) {
    if(!event->isAutoRepeat() && event->type() == QKeyEvent::KeyPress) {
        switch(event->key()) {
        case(Qt::Key_Left):
            selection--;
            break;
        case(Qt::Key_Right):
            selection++;
            break;
        case(Qt::Key_Return):
            choose();
            return;
        }
        if(selection >= ships.length())
            selection = 0;
        if(selection < 0)
            selection = ships.length() - 1;
    }
}

void swShipMenu::mouseHandle(QMouseEvent* event) {
    swVector pos = game->projMousePos(event->posF());
    if(event->type() == QMouseEvent::MouseButtonPress) {
        if(pos.y < 0.5 && pos.y > -0.5) {
            if(pos.x > 0.5 && selection < ships.length() - 1)
                selection++;
            else if(pos.x < -0.5 && selection > 0)
                selection--;
            else if(pos.x > -0.5 && pos.x < 0.5)
                choose();
        }
    }
}

void swShipMenu::choose() {
    game->playerConstruct.shipMesh = *ships[selection];
    game->client = new swClient(game, game->serverName, 6668);
    game->drawables.append(new swLobbyMenu(game));
    game->drawables.removeAll(this);
    delete this;
}
