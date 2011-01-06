#ifndef SWSIMULATOR_H
#define SWSIMULATOR_H

#include <QTime>
#include <QList>

class swPhysical;

class swSimulator {
public:
    swSimulator();
    ~swSimulator();

    void simulate();
    void draw();

    // these functions directly affect the simulator
    void insert(swPhysical* object, bool net = 0);
    void update(int index, swPhysical* object);
    void remove(int index);

    static const int tickLen = 20; // in msecs
    static const double tickScale = tickLen / 1000.0;

    int lastUpdate; // from gamestart in msecs
    int netObjects; // number of netSynched objects
    bool simulateOmega;

    QList<swPhysical*> objects;
    QList<swPhysical*> deadObjects;
    QTime qtime;
};

#endif // SWSIMULATOR_H
