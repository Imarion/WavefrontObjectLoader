
#include <QDebug>
#include <QFileDialog>

#include <fstream>
#include <sstream>

#include "../Common/wfoutils.h"

#include "Material.h"

Material::Material()
{

}

Material::~Material()
{

}

bool Material::read(string fileName)
{
    ifstream     matFile;
    string       key, line;
    stringstream chaine;
    MaterialData matData; // current material data
    string       matName; // current material name
    bool         toInsert = false; // nothing to insert in the map the 1st time "newmtl" is read. Insert the previously read data from the 2nd "newmtl"

    matFile.open(fileName.c_str(), ifstream::in);
    qDebug() << "material file name: " << fileName.c_str();
    while (matFile.good() && !matFile.eof() && getline(matFile, line))
    {
        chaine.str(line);
        chaine.seekg(0);
        chaine.clear();
        key = WFOUtils::GetKey(chaine);
        if (key=="newmtl")
        {
            if (toInsert) mMaterialData[matName]=matData; //  .insert(material);

            chaine >> matName;
            matData.init();
            toInsert = true;
            //qDebug() << "material name " << matName.c_str();
        }
        if (key=="Ka")
        {
            matData.readKa(chaine);
        }
        if (key=="Kd")
        {
            matData.readKd(chaine);
        }
        if (key=="Ks")
        {
            matData.readKs(chaine);
        }
        if (key=="Ns")
        {
            matData.readNs(chaine);
        }
    }
    if (toInsert) mMaterialData[matName]=matData; // insert the last material read    

    return (!chaine.fail());
}

void Material::clear()
{
    mMaterialData.clear();
}

void Material::print()
{
    //matData.print();  // print previously read material data for debug purpose - TODO: remove

    for (std::map<string, MaterialData>::iterator it = mMaterialData.begin(); it != mMaterialData.end(); ++it)
    {
        qDebug() << "titi Material name: " << it->first.c_str();
        it->second.print();
    }
}

/**
 * Returns the material data if it is found or default values otherwise. See
 * Material class members default values.
 */
bool Material::get(string &name, MaterialData &MatData)
{
    MaterialData locMatData;   //initialize material data with its default values
    bool         ret = false;

    MatData = locMatData;

    if (mMaterialData.find(name)!=mMaterialData.end())
    {
        MatData = mMaterialData[name];
        ret = true;
    }

    return ret;
}
