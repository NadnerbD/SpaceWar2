#ifndef SWGAME_H
#define SWGAME_H

#include <QGLWidget>

class swClient;
class swServer;
class swDrawable;

#include "swSimulator.h"
#include "swStarfield.h"
#include "swBitmask.h"
#include "swPlayer.h"
#include "swFont.h"

class swGame : public QGLWidget {
    Q_OBJECT

public:
    typedef enum swSettings {
	ANGULAR_VELOCITY,
	GLOBAL_SOUNDS,
	GRAVITY_WELL,
	SHOW_STARFIELD,
	WINDS_OF_SPACE
    } swSetting;

    swGame(QWidget *parent = 0);
    ~swGame();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void resizeGL(int width, int height);
    void initializeGL();
    void paintGL();
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    // transforms pixel coordinate into
    // projected (-1.1 - 1.1) coordinate
    swVector projMousePos(QPointF pos);

    swClient* client;
    swServer* server;
    swSimulator simulator;
    swBitmask settings;
    swFont font;

    // for setting up a player object to
    // send to the server on connect
    swPlayer playerConstruct;
    QString serverName;

    QList<swDrawable*> drawables;
    QTimer* qtimer;

signals:
    void keyEvent(QKeyEvent*);
    void mouseEvent(QMouseEvent*);

private slots:
    void keyHandle(QKeyEvent* event);
};

#endif // SWGAME_H
