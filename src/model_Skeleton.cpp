// Author: Dimitrios Tzionas
//
// source code for the work:
//
// Dimitrios Tzionas and Juergen Gall
// 3D Object Reconstruction from Hand-Object Interactions
// International Conference on Computer Vision (ICCV) 2015
// http://files.is.tue.mpg.de/dtzionas/In-Hand-Scanning


#include "model.h"


void Model::readSkeleton( QString myFileString_Skeleton )
{

        QFile myFile (myFileString_Skeleton );

        myFile.open(QIODevice::ReadOnly);

        if( !myFile.isOpen() )
        {
            qDebug() << "readSkeleton - ERROR, unable to open **" << myFileString_Skeleton << "** for Skeleton Input";
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////

        QTextStream myInputFileToString(&myFile);
        QStringList myStringListFromFile;
        QString     myStringFromFile;

        myStringFromFile = myInputFileToString.readAll();
        QRegExp koftis("\r\n"); // \\s - spaei kai to "Lower Arm" !!!
        myStringListFromFile = myStringFromFile.split(koftis, QString::SkipEmptyParts);

        int length = myStringListFromFile.length();

        totalSkeletonFrames = myStringListFromFile.at(0).toInt();

        //////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////

        totalBones = (length-1) / 3;

        ///////////////////////////////////////////
        skeleton.bones.clear();
        skeleton.bones.resize(totalSkeletonFrames);
        ///////////////////////////////////////////

        int counter = 0;

        skeleton.bones[0].fatherAddress = -666;

        for (int i=1; i<length; i+=3)
        {

                skeleton.bones[counter].fatherName             = myStringListFromFile.at(i+0);
                skeleton.bones[counter].name                   = myStringListFromFile.at(i+1);
                skeleton.bones[counter].length                 = myStringListFromFile.at(i+2).toDouble();
                skeleton.bones[counter].addressSeListaBones    = counter;
                skeleton.bones[counter].addressSeListaSKINNING = -1;
                skeleton.bones[counter].isUsedForSkinning      = false;

                for (int k=0; k<totalBones; k++)
                {
                        if (skeleton.bones[k].name != "NULL")
                        {
                                if (skeleton.bones[k].name == skeleton.bones[counter].fatherName)
                                    skeleton.bones[counter].fatherAddress = k;
                        }
                }
        \
                int fatherAdd = skeleton.bones[counter].fatherAddress;
                if (fatherAdd > -1)
                {
                        skeleton.bones[ fatherAdd ].childrenVector.append(i/3);
                }

                counter++;
        }

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Model::print_SkeletonBones()
{

    std::cout << "totalSkeletonFrames -\t" << totalSkeletonFrames << std::endl << std::endl;

    for (int i=0; i<totalBones; i++)
    {
        std::cout << i << "\t\t" << skeleton.bones[i].name.toStdString() << "\t\t" << skeleton.bones[i].fatherName.toStdString() << "\t\t" << skeleton.bones[i].length << std::endl;
    }

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









