#ifndef SWTEXTMENU_H
#define SWTEXTMENU_H

#include "swGame.h"
#include "swLabel.h"

class swTextMenu : public QObject, public swDrawable {
    Q_OBJECT

public:
    swTextMenu(swGame *g);
    virtual ~swTextMenu();

    virtual void draw();

protected:
    swGame* game;
    swLabel title;
    swLabel text;

    virtual void enteredText(QString value);
    void remove();

private slots:
    void keyHandle(QKeyEvent*);
    void mouseHandle(QMouseEvent*);
};

#endif // SWTEXTMENU_H
