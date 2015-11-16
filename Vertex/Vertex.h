#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <sstream>

using namespace std;

class Vertex
{

public:
	Vertex();
	virtual ~Vertex();    

    bool   read(stringstream &chaine);
    void   getall(float *inBuf);
    static int getNumData();
    void   print();

private:
    static const int numData = 4; // x, y, z, w = 4

	float x;
	float y;
	float z;
	float w;

};
#endif // _VERTEX_H_
