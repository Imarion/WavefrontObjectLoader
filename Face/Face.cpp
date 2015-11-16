
#include <QDebug>

#include "Face.h"

void Face::init()
{
    mNumFaceData  = 0;
    mMaterialName = "default";
}

Face::Face()
{
    init();
}

Face::~Face()
{

}

void Face::clear()
{
    mFaceData.clear();
    init();
}

bool Face::read(stringstream &chaine, bool hasNormalCoord, bool hasTextureCoord, int &NumData, string mtlName)
{
    FaceData fd;

    while (!chaine.eof() && !chaine.fail())
    {
        if (fd.read(chaine, hasNormalCoord, hasTextureCoord))
        {
            mFaceData.push_back(fd);
            mNumFaceData++;
        }
    }
    mMaterialName = mtlName;
    NumData = mNumFaceData;

    return !chaine.fail();
}

int Face::getVertexIndices(unsigned int *buffer)
{
    for (std::vector<FaceData>::iterator it = mFaceData.begin(); it != mFaceData.end(); it++)
    {
        *buffer=it->getv()-1;
        buffer++;
    }
    return mNumFaceData;
}

int Face::getNormalIndices(unsigned int *buffer)
{
    for (std::vector<FaceData>::iterator it = mFaceData.begin(); it != mFaceData.end(); it++)
    {
        *buffer=it->getvn()-1;
        buffer++;
    }
    return mNumFaceData;
}

string Face::getMaterialName()
{
    return mMaterialName;
}

unsigned int Face::getNumFaceData()
{
    return mNumFaceData;
}

void Face::print()
{
    qDebug() << "Facedata: " << mNumFaceData;
    qDebug() << "Material name: " << mMaterialName.c_str();
    for (std::vector<FaceData>::iterator it = mFaceData.begin(); it != mFaceData.end(); ++it) it->print();
}
