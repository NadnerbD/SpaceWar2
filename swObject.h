#ifndef SWOBJECT_H
#define SWOBJECT_H

#include <QString>
#include <QIODevice>
#include "swStream.h"

class swObject {
public:
    typedef enum Types {
	SW_OBJECT,
	SW_DRAWABLE,
	SW_PHYSICAL,
	SW_SHIP,
	SW_MISSILE,
	SW_STAR,
	SW_DEBRIS,
	SW_LABEL,
	SW_STARFIELD,
	SW_MESH,
	SW_ANIMATABLE,
	SW_SELECTABLE,
	SW_PLAYER,
	SW_VECTOR,
	SW_BITMASK,
	SW_FONT,
        SW_HEADS_UP_DISPLAY,
        SW_MAIN_MENU,
	SW_MESSAGE,
	SW_PHYS_START_MSG,
	SW_PHYS_CREATE_MSG,
	SW_PHYS_UPDATE_MSG,
	SW_PHYS_DELETE_MSG,
	SW_PLAYER_CREATE_MSG,
	SW_PLAYER_SHIP_MSG,
	SW_PLAYER_NAME_MSG,
	SW_PLAYER_INPUT_MSG,
	SW_PLAYER_SCORE_MSG,
	SW_PLAYER_KILL_MSG,
	SW_CLIENT_INIT_MSG
    } Type;

    swObject();
    virtual ~swObject();

    void read(QString file);
    void read(QIODevice* stream);
    virtual void read(swStream* stream);

    void write(QIODevice* stream);
    virtual void write(swStream* stream);

    Type type;
};

#endif // SWOBJECT_H
