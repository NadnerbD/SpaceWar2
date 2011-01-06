#ifndef SWFACTORY_H
#define SWFACTORY_H

#include "swObject.h"
#include "swMessage.h"
#include "swStream.h"

class swFactory {
public:
    swFactory();

    static swObject* readObject(QIODevice* stream);
    static swObject* readObject(swStream* stream);
    static swMessage* readMessage(QIODevice* stream);
    static swPhysical* readPhysical(QIODevice* stream);
    static void writeObject(swObject* obj, QIODevice* stream);
    static void writeObject(swObject* obj, swStream* stream);
};

#endif // SWFACTORY_H
