#include <QFile>
#include <QGLWidget>
#include "swFont.h"

swFont::swFont() : charBase(0), charCount(0), chars(NULL) {
     type = SW_FONT;
}

swFont::swFont(QString file) : charBase(0), charCount(0), chars(NULL) {
     type = SW_FONT;
    QFile stream(file);
    stream.open(QFile::ReadOnly);
    swObject::read(&stream);
    stream.close();
}

swFont::swFont(swStream* stream) : charBase(0), charCount(0), chars(NULL) {
     type = SW_FONT;
     read(stream);
}

swFont::~swFont() {
    if(chars)
	delete chars;
}

void swFont::read(swStream *stream) {
    if(chars)
	delete chars;

    mesh.read(stream);
    stream->readChar(charCount);
    stream->readChar(charBase);
    chars = new int[charCount];
    stream->read((char*)chars, charCount * sizeof(int));
}

void swFont::write(swStream *stream) {
    mesh.write(stream);
    stream->writeChar(charCount);
    stream->writeChar(charBase);
    stream->write((char*)chars, charCount * sizeof(int));
}

void swFont::drawLetter(char letter) {
    if(letter - charBase > charCount)
	return;
    glBegin(GL_LINES);
    for(int i = 0; i < mesh.edgeCount; i++) {
	if(1 << i & chars[letter - charBase]) {
	    glVertex2dv(&mesh.verts[mesh.edges[i * 2] * 3]);
	    glVertex2dv(&mesh.verts[mesh.edges[i * 2 + 1] * 3]);
	}
    }
    glEnd();
}
