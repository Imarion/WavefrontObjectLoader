
#ifndef _NORMAL_H_
#define _NORMAL_H_

#include <sstream>

using namespace std;

class Normal
{
public:
	Normal();
	virtual ~Normal();

    bool   read(stringstream &chaine);
    void   getall(float *inBuf);
    static int getNumData();

    void print();

private:
    static const int numData = 3; // i, j, k = 4

	float i;
	float j;
	float k;
};
#endif // _NORMAL_H_
