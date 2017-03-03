#include "swLobbyMenu.h"
#include "swReadyMsg.h"
#include "swFactory.h"
#include "swClient.h"

#include <QKeyEvent>

swLobbyMenu::swLobbyMenu(swGame* g) : game(g), name(&game->font, "") {
    type = SW_LOBBY_MENU;
    name.justify = swLabel::SW_JUSTIFY_LEFT;
    connect(game, SIGNAL(keyEvent(QKeyEvent*)), SLOT(keyHandle(QKeyEvent*)));
}

swLobbyMenu::~swLobbyMenu() {}

void swLobbyMenu::keyHandle(QKeyEvent* event) {
    if(!event->isAutoRepeat() && event->type() == QKeyEvent::KeyPress && event->key() == Qt::Key_Return) {
        swReadyMsg readyMsg;
        swFactory::writeObject(&readyMsg, game->client->sock);
    }
}

void swLobbyMenu::draw() {
    if(game->client) {
        glPushMatrix();
        transform();
        for(int i = 0; i < game->client->players.length(); i++) {
            swPlayer* player = &game->client->players[i];
            // display player score
            name.pos.y = 1.0 - i * 0.2;
            name.pos.x = -0.85;
            name.string = QString("%1").arg(player->score);
            name.draw();
            // display player name
            name.pos.x = -0.75;
            name.string = player->name;
            name.draw();
            // display ready status
            if(player->ready) {
                name.pos.x = -1.15;
                name.string = "R";
                name.draw();
            }
            // display player ship
            // hax: preserve ship mesh position/scale
            swVector shipScale = player->shipMesh.scale;
            swVector shipPos = player->shipMesh.pos;
            player->shipMesh.pos.x = -1.0;
            player->shipMesh.pos.y = 1.0 - i * 0.2;
            player->shipMesh.scale = swVector(0.1, 0.1);
            player->shipMesh.draw();
            player->shipMesh.scale = shipScale;
            player->shipMesh.pos = shipPos;
        }
        glPopMatrix();
    }
}
