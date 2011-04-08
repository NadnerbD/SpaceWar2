#include "swGame.h"
#include "swStarfield.h"
#include "swStar.h"
#include "swMesh.h"
#include "swShip.h"
#include "swLabel.h"
#include "swClient.h"
#include "swServer.h"
#include "swPlayer.h"
#include "swFactory.h"
#include "swMainMenu.h"
#include "swShipMenu.h"
#include "swPlayerCreateMsg.h"
#include "swPhysCreateMsg.h"
#include "swPlayerInputMsg.h"
#include "swHeadsUpDisplay.h"
#include "swPhysUpdateMsg.h"
#include "swMissile.h"

#include <QFile>
#include <QTimer>
#include <QKeyEvent>

swGame::swGame(QWidget *parent) : QGLWidget(parent), client(NULL), server(NULL) {
    // enable this so we get mousemove events without mouse buttons held down
    setMouseTracking(true);

    // create the background
    drawables.append(new swStarfield("data/starfield.binpts"));

    // load the font
    font.swObject::read("data/swfont.vfont");

    //swMainMenu* menu = new swMainMenu(this);
    //drawables.append(menu);

    // TEMP: ship menu
    swShipMenu* menu = new swShipMenu(this);
    drawables.append(menu);

    /*
    // TEMP: Create and display the HUD
    swHeadsUpDisplay* HUD = new swHeadsUpDisplay(this);
    drawables.append(HUD);

    // TEMP: create a demo ship and star, and simulate
    server = new swServer(this, 6668);
    client = new swClient(this, "localhost", 6668);

    // TEMP: use simulateOmega
    simulator.simulateOmega = true;

    // TEMP: connect our local key handler for ship movement
    connect(this, SIGNAL(keyEvent(QKeyEvent*)), SLOT(keyHandle(QKeyEvent*)));
    */

    // start the screen refresh timer
    qtimer = new QTimer(this);
    connect(qtimer, SIGNAL(timeout()), this, SLOT(updateGL()));
    qtimer->start(15);
}

void swGame::paintGL() {
    // clean up after the last frame
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    // draw everything
    foreach(swDrawable* drawable, drawables) {
	drawable->draw();
    }
    simulator.draw();
    // step the simulation
    simulator.simulate();
}

void swGame::keyHandle(QKeyEvent* event) {
    double value;
    switch(event->type()) {
	case(QKeyEvent::KeyPress):
	    value = 1;
	    break;
	case(QKeyEvent::KeyRelease):
	    value = -1;
	    break;
	default:
	    return;
	    break;
    }
    if(!event->isAutoRepeat()) {
	swPlayer* player = &client->players[client->clientId];
	if(player->shipId != -1) {
	    swShip* ship = (swShip*)simulator.objects[player->shipId];
	    switch(event->key()) {
		case(Qt::Key_Up):
		    player->controlAxes.y += value;
		    break;
		case(Qt::Key_Down):
		    player->controlAxes.y -= value;
		    break;
		case(Qt::Key_Left):
		    player->controlAxes.x -= value;
		    break;
		case(Qt::Key_Right):
		    player->controlAxes.x += value;
		    break;
		case(Qt::Key_Return):
		    if(value == 1) {
			// warp to a random location
			ship->pos.x = double(rand()) / RAND_MAX * 3 - 1.5;
			ship->pos.y = double(rand()) / RAND_MAX * 3 - 1.5;
		    }
		    break;
		case(Qt::Key_Space):
		    // fire
		    if(value == 1) {
			ship->fire();
		    }
		    break;
	    }
	    // send a playerInputMsg
	    swPlayerInputMsg inputMsg;
	    inputMsg.index = client->clientId;
	    inputMsg.controlAxes = player->controlAxes;
	    swFactory::writeObject(&inputMsg, client->sock);
	    // send a physupdate
	    swPhysUpdateMsg updateMsg;
	    updateMsg.index = player->shipId;
	    updateMsg.object = ship;
	    swFactory::writeObject(&updateMsg, client->sock);
	}
    }
}

void swGame::keyPressEvent(QKeyEvent* event) {
    keyEvent(event);
}

void swGame::keyReleaseEvent(QKeyEvent* event) {
    keyEvent(event);
}

void swGame::mouseMoveEvent(QMouseEvent* event) {
    mouseEvent(event);
}

void swGame::mousePressEvent(QMouseEvent* event) {
    mouseEvent(event);
}

void swGame::initializeGL() {
    glClearColor(0, 0, 0, 0);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void swGame::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho((-width * 1.0 / height), (width * 1.0 / height), -1.1, 1.1, 0.0, 4.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

swGame::~swGame() {
    if(client)
	delete client;
    if(server)
	delete server;
    foreach(swDrawable* drawable, drawables) {
	delete drawable;
    }
}

QSize swGame::sizeHint() const {
    return QSize(800, 600);
}

QSize swGame::minimumSizeHint() const {
    return QSize(640, 480);
}
