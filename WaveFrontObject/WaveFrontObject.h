#ifndef _WAVEFRONT_OBJECT_
#define _WAVEFRONT_OBJECT_

#include <QString>
#include <fstream>
#include <string>

#include "../Vertex/VertexData.h"
#include "../Face/Face.h"
#include "../Material/Material.h"

using namespace std;

class WaveFrontObject
{

public:
    static WaveFrontObject& getInstance();

    int  load(QString FileName);
    int  getNumVertices();
    static int getNumDataPerVertex();
    void getVertex(float *buffer);
    void getIndexedVertices(float *buffer); // returns a buffer with all vertices based on the index (face) data.
    void getIndexedNormals(float *buffer);  // returns a buffer with all normals based on the index (face) data.

    int  getNumIndices();
    void getIndices(unsigned int *buffer);
    void getMaterials(float *buffer);

    float getMaxWidth();  // from Vertex data;
    float getMaxHeight(); // from Vertex data;
    float getMaxDepth();  // from Vertex data;

    void print();

private:
    WaveFrontObject();
    ~WaveFrontObject();

    WaveFrontObject& operator= (const WaveFrontObject&);
    WaveFrontObject (const WaveFrontObject&){}
    static WaveFrontObject instance;

    static ifstream mifs;    

	VertexData mVertices;

    vector<Face> mFaces;
    int mNumFaces; // number of data per one line ("f x/y/z/ ...)
    int mNumIndices;  // total number of indices

    Material mMaterials;
    static const string mDefaultMaterialName;

    bool mHasNormalCoord, mHasTextureCoord;

    void init();
    void clear(); // delete the current contents of the vectors

};
#endif // _WAVEFRONT_OBJECT_
