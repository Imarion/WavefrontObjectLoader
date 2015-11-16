
#include <QDebug>

#include "Normal.h"

Normal::Normal()
{
    i=j=k=0.0f;
}


Normal::~Normal()
{

}

void Normal::getall(float *inBuf)
{
    inBuf[0] = i;
    inBuf[1] = j;
    inBuf[2] = k;
}

int Normal::getNumData()
{
    return numData;
}

bool Normal::read(stringstream &chaine)
{
    chaine >> i >> ws >> j >> ws >> k;

    return !chaine.fail();
}


void Normal::print()
{
    qDebug() << i << " " << j << " " << k;
}
