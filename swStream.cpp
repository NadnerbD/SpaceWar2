#include "swStream.h"

swStream::swStream() {
    // the constructor is never actually called
    // instead, we static cast a QIODevice* to swStream*
}

void swStream::readChar(char &out) {
    read((char*)&out, sizeof(char));
}

void swStream::readInt(int &out) {
    read((char*)&out, sizeof(int));
}

void swStream::readDouble(double &out) {
    read((char*)&out, sizeof(double));
}

void swStream::readString(QString &out) {
    int length = readInt();
    QByteArray data = read(length);
    out = QString::fromUtf8(data, length);
}

char swStream::readChar() {
    char out;
    read((char*)&out, sizeof(char));
    return out;
}

int swStream::readInt() {
    int out;
    read((char*)&out, sizeof(int));
    return out;
}

double swStream::readDouble() {
    double out;
    read((char*)&out, sizeof(double));
    return out;
}

QString swStream::readString() {
    int length = readInt();
    QByteArray data = read(length);
    return QString::fromUtf8(data, length);
}

void swStream::writeChar(char out) {
    write((char*)&out, sizeof(char));
}

void swStream::writeInt(int out) {
    write((char*)&out, sizeof(int));
}

void swStream::writeDouble(double out) {
    write((char*)&out, sizeof(double));
}

void swStream::writeString(QString out) {
    QByteArray data = out.toUtf8();
    writeInt(data.count());
    write(data);
}
