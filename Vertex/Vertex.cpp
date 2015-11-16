#include <QDebug>

#include "Vertex.h"


Vertex::Vertex()
{
    x=y=z=0.0f;
    w=1.0f;
}

Vertex::~Vertex()
{

}

void Vertex::getall(float *inBuf)
{
    inBuf[0] = x;
    inBuf[1] = y;
    inBuf[2] = z;
    inBuf[3] = w;
}

int Vertex::getNumData()
{
    return numData;
}


bool Vertex::read(stringstream &chaine)
{
    chaine >> x >> ws >> y >> ws >> z;

    return !chaine.fail();
}

void Vertex::print()
{
    qDebug() << x << " " << y << " " << z << " " << w;
}
