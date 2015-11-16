
#include <QDebug>

#include "FaceData.h"

FaceData::FaceData()
{
    mv = mvt = mvn = 0;
}

FaceData::~FaceData()
{

}

bool FaceData::read(stringstream &chaine, bool hasNormalCoord, bool hasTextureCoord)
{
    bool ok = true;

    chaine >> mv;
    mvn = mv; // by default normal indice = vector indice

    if (hasTextureCoord)
    {
        if (chaine.peek()=='/') /*   str().find('//')) */
        {
            chaine.ignore(1); // we have 1/2 -> skip the 1st /
            chaine >> mvt;

            if ((hasNormalCoord) && (chaine.peek()=='/'))
            {
                chaine.ignore(1); // we have 1/2/3 -> skip the 2nd /
                chaine >> mvn;
            }
        }
        else // we are supposed to have texture indice but there is no '/'
        {
            ok = false;
        }
    }
    else if ((hasNormalCoord) && (chaine.str().find("//") != string::npos))
    {
        chaine.ignore(2); // we have 1//3 -> skip the //
        chaine >> mvn;
    }

    return (!chaine.fail() && ok);
}

int FaceData::getv()
{
    return mv;
}

int FaceData::getvn()
{
    return mvn;
}

void FaceData::print()
{
    qDebug() << mv << mvt << mvn;
}
