
#include <QDebug>
#include <cmath>

#include "VertexData.h"

void VertexData::init()
{
    mNumNormals   = 0;
    mNumVertices  = 0;
    mXmin = mXmax = 0.0f;
    mYmin = mYmax = 0.0f;
    mZmin = mZmax = 0.0f;
}

VertexData::VertexData()
{
    init();
}

VertexData::~VertexData()
{

}

void VertexData::clear()
{
    mVertices.clear();
    mNormals.clear();
    init();
}

bool VertexData::readVertex(stringstream &chaine)
{
    Vertex v;    

    if (v.read(chaine))
    {
        mVertices.push_back(v);
        mNumVertices++;
    }
    updateMinMax(v);
    return !chaine.fail();
}

void VertexData::updateMinMax(Vertex &v)
{
    float *buffer = new float[Vertex::getNumData()];

    v.getall(buffer);
    if (buffer[0] < mXmin) mXmin = buffer[0];
    if (buffer[0] > mXmax) mXmax = buffer[0];
    if (buffer[1] < mYmin) mYmin = buffer[1];
    if (buffer[1] > mYmax) mYmax = buffer[1];
    if (buffer[2] < mZmin) mZmin = buffer[2];
    if (buffer[2] > mZmax) mZmax = buffer[2];

    delete[] buffer;
}

bool VertexData::readNormal(stringstream &chaine)
{
    Normal n;

    if (n.read(chaine))
    {
        mNormals.push_back(n);
        mNumNormals++;
    }
    return !chaine.fail();
}

int  VertexData::getNumVertices()
{
    return mVertices.size();
}

int VertexData::getNumDataPerVertex()
{
    return Vertex::getNumData();
}

void VertexData::getVertex(float *inBuf)
{
    for (std::vector<Vertex>::iterator it = mVertices.begin(); it != mVertices.end(); it++)
    {
        it->getall(inBuf);
        inBuf += it->getNumData();
    }
}

void VertexData::getVertex(unsigned int index, float (&inBuf)[4])
{
    mVertices[index].getall(inBuf);
}

void VertexData::getVertex(unsigned int index, float *inBuf)
{
    mVertices[index].getall(inBuf);
}

void VertexData::getNormal(unsigned int index, float (&inBuf)[4])
{
    mNormals[index].getall(inBuf);
}

void VertexData::getNormal(unsigned int index, float *inBuf)
{
    mNormals[index].getall(inBuf);
}

float VertexData::getMaxWidth()
{
    return abs(mXmax) + abs(mXmin);
}

float VertexData::getMaxHeight()
{
    return abs(mYmax) + abs(mYmin);
}

float VertexData::getMaxDepth()
{
    return abs(mZmax) + abs(mZmin);
}

void VertexData::print()
{
    qDebug() << "Vertices: " << mNumVertices;
    for (std::vector<Vertex>::iterator it = mVertices.begin(); it != mVertices.end(); ++it) it->print();

    qDebug() << "Normals: " << mNumNormals;
    for (std::vector<Normal>::iterator it = mNormals.begin(); it != mNormals.end(); ++it) it->print();

    qDebug() << "Min/Max: ";
    qDebug() << "X Min / X Max: " << mXmin << " / " << mXmax;
    qDebug() << "Y Min / Y Max: " << mYmin << " / " << mYmax;
    qDebug() << "Z Min / Z Max: " << mZmin << " / " << mZmax;
}
