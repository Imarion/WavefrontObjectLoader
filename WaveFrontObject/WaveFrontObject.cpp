#include <QDebug>
#include <QFileDialog>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QRegularExpressionMatch>

#include <iostream>
#include <sstream>
#include <string>

#include "../Common/wfoutils.h"

#include "WaveFrontObject.h"

#include "../Material/MaterialData.h"

using namespace std;

ifstream WaveFrontObject::mifs;
const    string WaveFrontObject::mDefaultMaterialName="default";

void WaveFrontObject::init()
{
    mNumFaces       = 0;
    mNumIndices     = 0;
    mHasNormalCoord  = false;
    mHasTextureCoord = false;
}

WaveFrontObject::WaveFrontObject()
{
    init();
}

WaveFrontObject::~WaveFrontObject()
{

}

WaveFrontObject& WaveFrontObject::getInstance()
{
    static WaveFrontObject instance;
    return instance;
}

void WaveFrontObject::clear()
{
    for (std::vector<Face>::iterator it = mFaces.begin(); it != mFaces.end(); ++it)
    {
        it->clear();
    }
    mFaces.clear();
    mVertices.clear();
    mMaterials.clear();

    init();
}

int WaveFrontObject::load(QString FileName)
{
    string line;
    string key;
    string readSmooth;    
    stringstream chaine;    

    string curmtl = mDefaultMaterialName;

    bool smoothing = false;

    qDebug() << "wavefront load start: " << curmtl.c_str();
    clear();
    mifs.open(FileName.toStdString().c_str(), ifstream::in);

    while (mifs.good() && !mifs.eof() && getline(mifs, line))
    {
        chaine.str(line);
        chaine.seekg(0);
        chaine.clear();
        //qDebug() << chaine.str().c_str();
        key = WFOUtils::GetKey(chaine);
        //qDebug() << key.c_str();        
        if (key == "v")
        {
            // Parse vertex
            mVertices.readVertex(chaine);
        } else if (key == "vn")
        {
            // Parse normal
            mVertices.readNormal(chaine);
            mHasNormalCoord = true;
        } else if (key == "vt")
        {
            // Parse texture coordinate
            mHasTextureCoord = true;
        } else if (key == "s")
        {
            // Parse smoothing
            chaine >> readSmooth;
            smoothing = (readSmooth != "off");
        } else if (key == "usemtl")
        {
            chaine >> curmtl;
        } else if (key == "f")
        {
            // Parse faces
            Face f;
            int  numF;

            if (f.read(chaine, mHasNormalCoord, mHasTextureCoord, numF, curmtl))
            {
                mFaces.push_back(f);
                mNumFaces++;
                mNumIndices += numF;
            }
        } else if (key == "mtllib")
        {
            // Read material properties
            QString tempoMtlChaine(&chaine.str().c_str()[6]); // skip mtllib
            qDebug() << "tempoMtlChaine: " << tempoMtlChaine;
            QString materialFilename;
            QRegularExpression mtlRegExp("(.*?\\.mtl\\b)");

            QRegularExpressionMatchIterator mtlIt = mtlRegExp.globalMatch(tempoMtlChaine);
            while (mtlIt.hasNext())
            {
                QRegularExpressionMatch mtlMatch = mtlIt.next();
                materialFilename = QFileInfo(FileName).absolutePath() + '/' + mtlMatch.captured().trimmed();
                mMaterials.read(materialFilename.toStdString());
                qDebug() << "materialFilename: " <<materialFilename;
            }
        }
    }

    mifs.close();

    return 0;
}

int WaveFrontObject::getNumVertices()
{
    return mVertices.getNumVertices();
}

void WaveFrontObject::getVertex(float *buffer)
{
    mVertices.getVertex(buffer);
}

void WaveFrontObject::getIndexedVertices(float *buffer)
{
    int          numFaceData;
    unsigned int indices[3];

    for (std::vector<Face>::iterator it = mFaces.begin(); it != mFaces.end(); ++it)
    {
        numFaceData = it->getVertexIndices(indices);

        for (int i=0; i<numFaceData; i++)
        {
            mVertices.getVertex(indices[i], buffer);
            buffer += Vertex::getNumData();
        }        
    }
}

void WaveFrontObject::getIndexedNormals(float *buffer)
{
    int          numFaceData;
    unsigned int indices[3];

    if (mHasNormalCoord == true)
    {
        for (std::vector<Face>::iterator it = mFaces.begin(); it != mFaces.end(); ++it)
        {
            numFaceData = it->getNormalIndices(indices);

            for (int i=0; i<numFaceData; i++)
            {
                mVertices.getNormal(indices[i], buffer);
                buffer += Normal::getNumData();
            }
        }
    }
}

int WaveFrontObject::getNumDataPerVertex()
{
    return VertexData::getNumDataPerVertex();
}

int WaveFrontObject::getNumIndices()
{
    return mNumIndices;
}

void WaveFrontObject::getIndices(unsigned int *buffer)
{
    int numVertexIndices;
    for (std::vector<Face>::iterator it = mFaces.begin(); it != mFaces.end(); ++it)
    {
        numVertexIndices = it->getVertexIndices(buffer);
        buffer += numVertexIndices;
    }
}

void WaveFrontObject::getMaterials(float *buffer)
{
    string       materialName;
    unsigned int numFaceData;
    MaterialData material;
    bool         existMaterial;
    unsigned int num = 0;

    for (std::vector<Face>::iterator it = mFaces.begin(); it != mFaces.end(); ++it)
    {
        materialName  = it->getMaterialName();
        numFaceData   = it->getNumFaceData();
        existMaterial = mMaterials.get(materialName, material);
        for (unsigned int i=0; i<numFaceData; i++)
        {
            buffer += material.getKa(buffer);
            num+=3;
            buffer += material.getKd(buffer);
            num+=3;
            buffer += material.getKs(buffer);
            num+=3;
            *buffer++ = material.getNs();
            num++;
        }
    }
    qDebug() << "getMaterials i: " << num;
}

float WaveFrontObject::getMaxWidth()
{
    return mVertices.getMaxWidth();
}

float WaveFrontObject::getMaxHeight()
{
    return mVertices.getMaxHeight();
}

float WaveFrontObject::getMaxDepth()
{
    return mVertices.getMaxDepth();
}

/**
 * Print the data to compare; useful for debugging the reading of the data.
 */
void WaveFrontObject::print()
{
    qDebug() << "Object data: ";
    qDebug() << "Normal  coord present: " << mHasNormalCoord;
    qDebug() << "Texture coord present: " << mHasTextureCoord;
    qDebug() << "Vertex data: ";
    mVertices.print();

    qDebug() << "Face : " << mNumFaces;
    for (std::vector<Face>::iterator it = mFaces.begin(); it != mFaces.end(); ++it) it->print();

    qDebug() << "Num indices" << mNumIndices;

    qDebug() << "Material data: ";
    mMaterials.print();
}
