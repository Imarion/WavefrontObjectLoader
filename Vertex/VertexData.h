#ifndef _VERTEX_DATA_H_
#define _VERTEX_DATA_H_

#include <sstream>
#include <vector>

#include "Vertex.h"
#include "Normal.h"

using namespace std;

class VertexData
{

public:
	VertexData();
	virtual ~VertexData();

    bool readVertex(stringstream &chaine);
    bool readNormal(stringstream &chaine);

    void  getVertex(float *inBuf); // fills in the buffer with all vertices in the buffer
    void  getVertex(unsigned int index, float (&inBuf)[4]); // fills in the buffer with vertex data at index.
    void  getVertex(unsigned int index, float *inbuf); // fills in the buffer with vertex data at index.
    void  getNormal(unsigned int index, float (&inBuf)[4]); // fills in the buffer with Normal data at index.
    void  getNormal(unsigned int index, float *inbuf); // fills in the buffer with Normal data at index.
    float getMaxWidth();  // abs(xmax) + abs(xmin);
    float getMaxHeight(); // abs(ymax) + abs(ymin);
    float getMaxDepth();  // abs(zmax) + abs(zmin);

    int  getNumVertices();
    static int  getNumDataPerVertex();

    void clear();
    void print();

private:
    void init();

	/**
	 * From the 'v' tag in the object file.
	 */
    vector<Vertex> mVertices;

    /**
     * From the 'vn' tag in the object file.
     */
    vector<Normal> mNormals;

    /**
	 * Number of normals
	 */
	int mNumNormals;

    /**
     * Number of vertices
     */
    int mNumVertices;

    float mXmin, mXmax;
    float mYmin, mYmax;
    float mZmin, mZmax;
    void  updateMinMax(Vertex &v);
};
#endif // _VERTEX_DATA_H_
