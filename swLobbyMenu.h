#ifndef SWLOBBYMENU_H
#define SWLOBBYMENU_H

#include "swGame.h"
#include "swLabel.h"

class swLobbyMenu : public QObject, public swDrawable {
    Q_OBJECT

public:
    swLobbyMenu(swGame* g);
    virtual ~swLobbyMenu();

    virtual void draw();

private:
    swGame* game;
    swLabel name;

private slots:
    void keyHandle(QKeyEvent*);
};

#endif // SWLOBBYMENU_H
