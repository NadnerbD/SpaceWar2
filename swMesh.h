#ifndef SWMESH_H
#define SWMESH_H

#include "swDrawable.h"

class swMesh : public swDrawable {
public:
    swMesh();
    swMesh(QString file);
    swMesh(swStream* stream);
    swMesh(const swMesh& orig);
    virtual ~swMesh();
    void clear();

    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    virtual void draw();

    swMesh &operator=(const swMesh& orig);

    int vertCount;
    double* verts;
    int edgeCount;
    int* edges;
};

#endif // SWMESH_H
