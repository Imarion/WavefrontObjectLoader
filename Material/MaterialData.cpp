
#include <QDebug>

#include "MaterialData.h"

#include "Common/wfoutils.h"


MaterialData::MaterialData()
{
    init();
}

void MaterialData::init(void)
{
    // Default ambient = full white
    Ka[0] = 1.0;
    Ka[1] = 1.0;
    Ka[2] = 1.0;

    // Default diffuse = full white
    Kd[0] = 1.0;
    Kd[1] = 1.0;
    Kd[2] = 1.0;

    // Default specular = full white
    Ks[0] = 1.0;
    Ks[1] = 1.0;
    Ks[2] = 1.0;

    Ns = 128.0;     // standard specular power
}

MaterialData::~MaterialData()
{

}

void MaterialData::read(string fileName)
{

}

bool MaterialData::readKa(stringstream &chaine)
{
    return WFOUtils::ReadTriplet(chaine, Ka);
}

bool MaterialData::readKd(stringstream &chaine)
{
    return WFOUtils::ReadTriplet(chaine, Kd);
}

bool MaterialData::readKs(stringstream &chaine)
{
    return WFOUtils::ReadTriplet(chaine, Ks);
}

bool MaterialData::readNs(stringstream &chaine)
{
    chaine >> Ns;

    return !chaine.fail();
}

unsigned int MaterialData::getKa(float inBuf[])
{
    inBuf[0] = Ka[0];
    inBuf[1] = Ka[1];
    inBuf[2] = Ka[2];

    return 3;
}

unsigned int MaterialData::getKd(float inBuf[])
{
    inBuf[0] = Kd[0];
    inBuf[1] = Kd[1];
    inBuf[2] = Kd[2];

    return 3;
}

unsigned int MaterialData::getKs(float inBuf[])
{
    inBuf[0] = Ks[0];
    inBuf[1] = Ks[1];
    inBuf[2] = Ks[2];

    return 3;
}

float MaterialData::getNs()
{
    return Ns;
}

unsigned int MaterialData::getRawDataSize()
{
   return sizeof(Ka) + sizeof(Kd) + sizeof(Ks) + sizeof(Ns);
}

void MaterialData::print()
{
    qDebug() << "Ambient: \n" << "r: " << Ka[0] << "g: " << Ka[1] << "b: " << Ka[2];
    qDebug() << "Diffuse: \n" << "r: " << Kd[0] << "g: " << Kd[1] << "b: " << Kd[2];
    qDebug() << "Specular: \n" << "r: " << Ks[0] << "g: " << Ks[1] << "b: " << Ks[2];
    qDebug() << "Specular power: " << Ns;
}
