#include "swMessage.h"

swMessage::swMessage() {
    type = SW_MESSAGE;
}

swMessage::~swMessage() {}

void swMessage::cliHandle(swClient* client) {
    // this is just a template
}

void swMessage::servHandle(swServer* server, QTcpSocket* sock) {
    // this is just a template
}
