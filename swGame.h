#ifndef SWGAME_H
#define SWGAME_H

#include <QGLWidget>

class swClient;
class swServer;
class swDrawable;

#include "swSimulator.h"
#include "swStarfield.h"
#include "swBitmask.h"
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
    void keyHandle(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

    swClient* client;
    swServer* server;
    swSimulator simulator;
    swBitmask settings;
    swFont font;

    QList<swDrawable*> drawables;
    QTimer* qtimer;
};

#endif // SWGAME_H
