#ifndef _FACEDATA_H_
#define _FACEDATA_H_

#include <sstream>
#include <vector>
#include <string>

#include "FaceData.h"

using namespace std;

class Face
{

public:
    Face();
    virtual ~Face();

    bool read(stringstream &chaine, bool hasNormalCoord, bool hasTextureCoord, int &NumData, string mtlName = "default");
    void clear();
	void print();
    int  getVertexIndices(unsigned int *buffer); // fill in buffer with the vertex indices
    int  getNormalIndices(unsigned int *buffer); // fill in buffer with the normal indices

    string getMaterialName();
    unsigned int getNumFaceData();


private:
    void init();

    vector<FaceData> mFaceData;    
    unsigned int mNumFaceData;

    string mMaterialName;
};
#endif // _FACEDATA_H_
