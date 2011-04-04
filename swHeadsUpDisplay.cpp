#include "swHeadsUpDisplay.h"
#include "swPlayer.h"
#include "swClient.h"
#include "swShip.h"

swHeadsUpDisplay::swHeadsUpDisplay(swGame* g) :
        swDrawable(0, 0, 0, 1, 1),
        game(g),
        fuel(&game->font, ""),
        score(&game->font, ""),
        ammo(&game->font, "") {
    type = SW_HEADS_UP_DISPLAY;
    fuel.pos = swVector(-1, -1);
    score.pos = swVector(0, -1);
    ammo.pos = swVector(1, -1);
}

swHeadsUpDisplay::~swHeadsUpDisplay() {}

void swHeadsUpDisplay::draw() {
    // if there is information present, update the display label strings
    if(game->client && game->client->clientId != -1) {
        swPlayer* player = &game->client->players[game->client->clientId];
        score.string = QString("SCORE: %1").arg(player->score);
        if(player->shipId != -1) {
            swShip* ship = (swShip*)game->simulator.objects[player->shipId];
            fuel.string = QString("FUEL: %1").arg(ship->fuel);
            ammo.string = QString("AMMO: %1").arg(ship->ammo);
        }
    }
    // display the HUD
    // once information leaves scope, such as the player
    // ship being destroyed, the related displays will remain in
    // their last known state
    glPushMatrix();
    transform();
    score.draw();
    fuel.draw();
    ammo.draw();
    glPopMatrix();
}
