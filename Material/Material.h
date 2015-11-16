
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <map>
#include <string>

#include "MaterialData.h"

using namespace std;

class Material
{
public:
	Material();
	virtual ~Material();	

    bool read(string fileName);
	void clear();
	void print();
    bool get(string & name, MaterialData &);

private:
	/**
	 * To be implemented as a map container with the name as value.
	 */
    map <string, MaterialData> mMaterialData;
};

#endif // _MATERIAL_H_
