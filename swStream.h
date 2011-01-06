#ifndef SWSTREAM_H
#define SWSTREAM_H

#include <QIODevice>

class swStream : public QIODevice {
public:
    swStream();

    void readChar(char& out);
    void readInt(int& out);
    void readDouble(double& out);
    void readString(QString& out);

    char readChar();
    int readInt();
    double readDouble();
    QString readString();

    void writeChar(char out);
    void writeInt(int out);
    void writeDouble(double out);
    void writeString(QString out);
};

#endif // SWSTREAM_H
