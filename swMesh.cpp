#include <QFile>
#include <QGLWidget>
#include "swMesh.h"

swMesh::swMesh() : vertCount(0), verts(NULL), edgeCount(0), edges(NULL) {
    type = SW_MESH;
}

swMesh::swMesh(QString file) : vertCount(0), verts(NULL), edgeCount(0), edges(NULL) {
    type = SW_MESH;
    QFile stream(file);
    stream.open(QFile::ReadOnly);
    swObject::read(&stream);
    stream.close();
}

swMesh::swMesh(swStream* stream) : vertCount(0), verts(NULL), edgeCount(0), edges(NULL) {
    type = SW_MESH;
    read(stream);
}

swMesh::swMesh(const swMesh& orig) : vertCount(0), verts(NULL), edgeCount(0), edges(NULL) {
    type = SW_MESH;
    *this = orig;
}

swMesh::~swMesh() {
    if(verts)
	delete verts;
    if(edges)
	delete edges;
}

swMesh& swMesh::operator=(const swMesh& orig) {
    if(this != &orig) {
	this->~swMesh();
	vertCount = orig.vertCount;
	edgeCount = orig.edgeCount;
	verts = new double[vertCount * 3];
	memcpy(verts, orig.verts, sizeof(double) * vertCount * 3);
	edges = new int[edgeCount * 2];
	memcpy(edges, orig.edges, sizeof(int) * edgeCount * 2);
    }
    return *this;
}

void swMesh::read(swStream* stream) {
    this->~swMesh();
    stream->readInt(vertCount);
    verts = new double[vertCount * 3];
    stream->read((char*)verts, vertCount * sizeof(double) * 3);
    stream->readInt(edgeCount);
    edges = new int[edgeCount * 2];
    stream->read((char*)edges, edgeCount * sizeof(int) * 2);
}

void swMesh::write(swStream* stream) {
    stream->writeInt(vertCount);
    stream->write((char*)verts, vertCount * sizeof(double) * 3);
    stream->writeInt(edgeCount);
    stream->write((char*)edges, edgeCount * sizeof(int) * 2);
}

void swMesh::draw() {
    glPushMatrix();
    transform();

    glBegin(GL_LINES);
    for(int i = 0; i < edgeCount; i++) {
	glVertex2dv(&verts[edges[i * 2] * 3]);
	glVertex2dv(&verts[edges[i * 2 + 1] * 3]);
    }
    glEnd();

    glPopMatrix();
}
