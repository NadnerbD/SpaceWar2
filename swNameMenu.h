#ifndef SWNAMEMENU_H
#define SWNAMEMENU_H

#include "swGame.h"
#include "swLabel.h"

class swNameMenu : public QObject, public swDrawable {
    Q_OBJECT

public:
    swNameMenu(swGame* g);
    virtual ~swNameMenu();

    virtual void draw();

private:
    swGame* game;
    swLabel title;
    swLabel name;

private slots:
    void keyHandle(QKeyEvent*);
    void mouseHandle(QMouseEvent*);
};

#endif // SWNAMEMENU_H
