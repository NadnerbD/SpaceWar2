#ifndef SWSHIPMENU_H
#define SWSHIPMENU_H

#include "swGame.h"
#include "swLabel.h"

class swShipMenu : public QObject, public swDrawable {
    Q_OBJECT

public:
    swShipMenu(swGame* g);
    virtual ~swShipMenu();

    virtual void draw();

private:
    swGame* game;

    swLabel title;
    QList<swMesh*> ships;
    int selection;

    void choose();

private slots:
    void keyHandle(QKeyEvent*);
    void mouseHandle(QMouseEvent*);
};

#endif // SWSHIPMENU_H
