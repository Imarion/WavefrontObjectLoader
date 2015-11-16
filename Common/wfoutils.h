#ifndef WFOUTILS_H
#define WFOUTILS_H

#include <sstream>
#include <string>

using namespace std;

class WFOUtils
{
public:
    WFOUtils();
    virtual ~WFOUtils();

    static string GetKey(stringstream &chaine);
    static bool   ReadTriplet(stringstream &chaine, float (&inBuf)[3]);
};

#endif // WFOUTILS_H
