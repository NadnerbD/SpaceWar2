#include <QFile>
#include "swObject.h"

swObject::swObject() : type(SW_OBJECT) {}

swObject::~swObject() {}

void swObject::read(QString file) {
    QFile* inFile = new QFile(file);
    inFile->open(QFile::ReadOnly);
    read(inFile);
    inFile->close();
    delete inFile;
}

void swObject::read(QIODevice* stream) {
    read(static_cast<swStream*>(stream));
}

void swObject::write(QIODevice* stream) {
    write(static_cast<swStream*>(stream));
}

void swObject::read(swStream *stream) {}

void swObject::write(swStream *stream) {}
