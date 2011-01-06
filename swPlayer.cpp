#include "swStream.h"
#include "swPlayer.h"

swPlayer::swPlayer() : sock(NULL), name(""), score(0), ready(0), shipId(-1) {
    type = SW_PLAYER;
}

swPlayer::~swPlayer() {}

void swPlayer::read(swStream* stream) {
    stream->readString(name);
    stream->readInt(score);
    ready = stream->readChar();
    shipMesh.read(stream);
}

void swPlayer::write(swStream* stream) {
    stream->writeString(name);
    stream->writeInt(score);
    stream->writeChar(ready);
    shipMesh.write(stream);
}
