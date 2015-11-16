
#ifndef _MATERIALDATA_H_
#define _MATERIALDATA_H_

#include <string>

using namespace std;

class MaterialData
{
public:
	MaterialData();
	virtual ~MaterialData();

    void init(void);
    void read(string fileName);
	void print();

    bool readKa(stringstream &chaine);
    bool readKd(stringstream &chaine);
    bool readKs(stringstream &chaine);
    bool readNs(stringstream &chaine);

    unsigned int getKa(float inBuf[]);
    unsigned int getKd(float inBuf[]);
    unsigned int getKs(float inBuf[]);
    float getNs();

    static unsigned int getRawDataSize();

private:
	/**
	 * Ambiant color
	 */
    float Ka[3];   // [0] = red, [1] = green, [2] = blue
	/**
	 * Diffuse color
	 */
    float Kd[3];
	/**
	 * Specular color
	 */
    float Ks[3];
	/**
	 * Specular coefficient
	 */
	float Ns;
};

#endif // _MATERIALDATA_H_
