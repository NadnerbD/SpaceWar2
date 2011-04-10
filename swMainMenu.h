#ifndef SWMAINMENU_H
#define SWMAINMENU_H

#include "swGame.h"
#include "swLabel.h"

class swMainMenu : public QObject, public swDrawable {
    Q_OBJECT

public:
    swMainMenu(swGame* g);
    virtual ~swMainMenu();

    virtual void draw();

private:
    swGame* game;
    swLabel title;
    swLabel join;
    swLabel host;
    swLabel options;

    swLabel selector;
    int selection;
    QList<swLabel*> selections;

    void choose();

private slots:
    void keyHandle(QKeyEvent*);
    void mouseHandle(QMouseEvent*);
};

#endif // SWMAINMENU_H
