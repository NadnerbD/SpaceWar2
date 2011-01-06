#ifndef SWLABEL_H
#define SWLABEL_H

#include "swDrawable.h"
#include "swFont.h"

class swLabel : public swDrawable {
public:
    typedef enum swFontJustifications {
	SW_JUSTIFY_LEFT,
	SW_JUSTIFY_CENTER,
	SW_JUSTIFY_RIGHT
    } swFontJustification;

    swLabel();
    swLabel(swFont* fnt, QString str, double size = 0.025, int justification = SW_JUSTIFY_CENTER);
    virtual ~swLabel();

    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    virtual void draw();

    swFont* font;
    QString string;
    swFontJustification justify;
};

#endif // SWLABEL_H
