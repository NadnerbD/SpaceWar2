#include "swFactory.h"
#include "swMessage.h"
#include "swShip.h"
#include "swStar.h"
#include "swMissile.h"
#include "swClientInitMsg.h"
#include "swPhysCreateMsg.h"
#include "swPlayerCreateMsg.h"
#include "swPlayerInputMsg.h"
#include "swPhysUpdateMsg.h"
#include "swPhysDeleteMsg.h"
#include "swPlayerKillMsg.h"
#include "swReadyMsg.h"

swFactory::swFactory() {}

swObject* swFactory::readObject(QIODevice* stream) {
    return readObject((swStream*)stream);
}

swObject* swFactory::readObject(swStream* stream) {
    int type = stream->readInt();
    swObject* data;
    switch(type) {
	case(swObject::SW_OBJECT):
	    data = new swObject();
	    break;
	case(swObject::SW_SHIP):
	    data = new swShip();
	    break;
	case(swObject::SW_STAR):
	    data = new swStar();
	    break;
	case(swObject::SW_MISSILE):
	    data = new swMissile();
	    break;
	case(swObject::SW_MESSAGE):
	    data = new swMessage();
	    break;
	case(swObject::SW_CLIENT_INIT_MSG):
	    data = new swClientInitMsg();
	    break;
	case(swObject::SW_PLAYER_CREATE_MSG):
	    data = new swPlayerCreateMsg();
	    break;
	case(swObject::SW_PHYS_CREATE_MSG):
	    data = new swPhysCreateMsg();
	    break;
	case(swObject::SW_PLAYER_INPUT_MSG):
	    data = new swPlayerInputMsg();
	    break;
	case(swObject::SW_PHYS_UPDATE_MSG):
	    data = new swPhysUpdateMsg();
	    break;
	case(swObject::SW_PHYS_DELETE_MSG):
	    data = new swPhysDeleteMsg();
	    break;
	case(swObject::SW_PLAYER_KILL_MSG):
	    data = new swPlayerKillMsg();
	    break;
	case(swObject::SW_READY_MSG):
	    data = new swReadyMsg();
	    break;
	default:
	    qWarning("Factory attempt to read unsupported type: %d", type);
    }
    data->read(stream);
    return data;
}

swMessage* swFactory::readMessage(QIODevice* stream) {
    swObject* msg = readObject(stream);
    if(msg->type >= swObject::SW_MESSAGE)
	return (swMessage*)msg;
    qWarning("Invalid message type read: %d", msg->type);
    return NULL;
}

swPhysical* swFactory::readPhysical(QIODevice* stream) {
    swObject* obj = readObject(stream);
    if(obj->type >= swObject::SW_PHYSICAL && obj->type <= swObject::SW_DEBRIS)
	return (swPhysical*)obj;
    qWarning("Invalid physical type read: %d", obj->type);
    return NULL;
}

void swFactory::writeObject(swObject* obj, QIODevice* stream) {
    writeObject(obj, (swStream*)stream);
}

void swFactory::writeObject(swObject* obj, swStream* stream) {
    stream->writeInt(obj->type);
    obj->write(stream);
}

