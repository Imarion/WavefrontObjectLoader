
#ifndef _FACE_H_
#define _FACE_H_

#include <sstream>

using namespace std;

class FaceData
{

public:
    FaceData();
    virtual ~FaceData();

    bool read(stringstream &chaine, bool hasNormalCoord, bool hasTextureCoord);
    int  getv();
    int  getvn();
    void print();

private:    
	/**
	 * Vertex index of the Face.
	 */
	int mv;
	/**
	 * Vertex texture index of the Face.
	 */
	int mvt;
	/**
	 * Vertex normal index of the Face.
	 */
	int mvn;

};
#endif // _FACE_H_
