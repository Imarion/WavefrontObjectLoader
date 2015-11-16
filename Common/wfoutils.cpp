#include "wfoutils.h"

WFOUtils::WFOUtils()
{

}

WFOUtils::~WFOUtils()
{

}

string WFOUtils::GetKey(stringstream &chaine)
{
    string key = "";
    chaine >> key >> ws;

    return key;
}

bool   WFOUtils::ReadTriplet(stringstream &chaine, float (&inBuf)[3])
{
    chaine >> inBuf[0] >> ws >> inBuf[1] >> ws >> inBuf[2];

    return !chaine.fail();
}
