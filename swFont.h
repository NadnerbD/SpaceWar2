#ifndef SWFONT_H
#define SWFONT_H

#include "swObject.h"
#include "swMesh.h"

class swFont : public swObject
{
public:
    swFont();
    swFont(QString file);
    swFont(swStream* stream);
    virtual ~swFont();

    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    void drawLetter(char letter);
    bool hasLetter(char letter);

    swMesh mesh;
    char charBase;
    char charCount;
    int* chars;
};

#endif // SWFONT_H
