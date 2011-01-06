#include <QGLWidget>
#include "swLabel.h"

swLabel::swLabel() : font(NULL) {
    type = SW_LABEL;
}

swLabel::swLabel(swFont* fnt, QString str, double size, int justification) : font(fnt), string(str) {
    type = SW_LABEL;
    justify = (swFontJustification)justification;
    scale = swVector(size, size);
}

swLabel::~swLabel() {}

void swLabel::read(swStream* stream) {
    swDrawable::read(stream);
    stream->readString(string);
    justify = (swFontJustification)stream->readInt();
}

void swLabel::write(swStream* stream) {
    swDrawable::write(stream);
    stream->writeString(string);
    stream->writeInt(justify);
}

void swLabel::draw() {
    if(font) {
	glPushMatrix();
	transform();
	if(justify == SW_JUSTIFY_CENTER)
	    glTranslated((-string.length() + 1) * 1.5 / 2.0, 0, 0);

	for(int i = 0; i < string.count(); i++) {
	    font->drawLetter(string[i].toAscii());
	    glTranslated(1.5, 0, 0);
	}
	glPopMatrix();
    }
}
