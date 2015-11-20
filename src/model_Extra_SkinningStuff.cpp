// Author: Dimitrios Tzionas
//
// source code for the work:
//
// Dimitrios Tzionas and Juergen Gall
// 3D Object Reconstruction from Hand-Object Interactions
// International Conference on Computer Vision (ICCV) 2015
// http://files.is.tue.mpg.de/dtzionas/In-Hand-Scanning


#include "model.h"




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int Model::find_Dominant_SkinningBone( const int vertexID )
{

        for (int skkk=0; skkk<totalSkinningBones; skkk++)
        {

                if (skin.skinnedVertices[ vertexID ].skinWeights_Thresholded[skkk] == 1)
                {
                        ////////////
                        return skkk;
                        ////////////
                }

        }

}



void Model::find_Dominant_SkinningBone( const int vertexID, int &dominant_SkinningBoneID, double &dominant_SkinningBoneCONF )
{

        for (int skkk=0; skkk<totalSkinningBones; skkk++)
        {

                if (skin.skinnedVertices[ vertexID ].skinWeights_Thresholded[skkk] == 1)
                {
                        ///////////////////////////////////////////////////////////////////////////////
                        dominant_SkinningBoneID   = skkk;//////////////////////////////////////////////
                        dominant_SkinningBoneCONF = skin.skinnedVertices[ vertexID ].skinWeights[skkk];
                        ///////////////////////////////////////////////////////////////////////////////
                }

        }

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Model::create_Lookup_SkinningBone_to_Bones_ID()
{

        lookup_SkinningBone_to_Bones_ID.resize(   totalSkinningBones  );
        lookup_SkinningBone_to_Bones_ID.fill(0);


        for (int b=0; b<totalBones; b++)
        {
                if (skeleton.bones[b].isUsedForSkinning == true)
                {
                        lookup_SkinningBone_to_Bones_ID[   skeleton.bones[b].addressSeListaSKINNING   ] = b;
                }
        }

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Model::print_SkinningBoneNames()
{

        for (int i=0; i<totalSkinningBones; i++)
        {
            qDebug() << i << "\t" << skinningSkeleton.skinningBones[i].name;
        }

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Model::test_Lookup_SkinningBone_to_Bones_ID()
{

        for (int skkk=0; skkk<totalSkinningBones; skkk++)
        {
            qDebug() << skkk << "\t" << skinningSkeleton.skinningBones[skkk].name << "\t" << skeleton.bones[   lookup_SkinningBone_to_Bones_ID[ skkk ]   ].name << "\t" << skkk << lookup_SkinningBone_to_Bones_ID[ skkk ];
        }

}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






void Model::create_thresholded_SkinningWeights()
{

        for (int vvv=0; vvv<totalVertices; vvv++)
        {

                skin.skinnedVertices[vvv].skinWeights_Thresholded.resize( totalSkinningBones );
                skin.skinnedVertices[vvv].skinWeights_Thresholded.fill(0);

                float maxxx      = -666;
                int   mainBoneID = -1;

                for (int j=0; j<totalSkinningBones; j++)
                {
                        if (skin.skinnedVertices[vvv].skinWeights[j]>maxxx)         {        maxxx=skin.skinnedVertices[vvv].skinWeights[j];         mainBoneID=j;        }
                }

                skin.skinnedVertices[vvv].skinWeights_Thresholded[mainBoneID] = 1;

        }

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Model::print_thresholded_SkinningWeights()
{

        for (int j=0; j<totalSkinningBones; j++)
        {
                qDebug() << skin.skinnedVertices[2676].skinWeights_Thresholded[j] << "\t" << skin.skinnedVertices[2676].skinWeights[j];
        }

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Model::create_VerticesMainlyInfluenced_PerSkinningBone()
{
    for (int skkk=0; skkk<totalSkinningBones; skkk++)
    {
            ////////////////////////////////////////////////////////////////////////
            skinningSkeleton.skinningBones[skkk].mainlyInfluenced_TotalVertices = 0;
            ////////////////////////////////////////////////////////////////////////
            skinningSkeleton.skinningBones[skkk].mainlyInfluenced_VertexIDs.clear();
            ////////////////////////////////////////////////////////////////////////

            for (int vvv=0; vvv<totalVertices; vvv++)
            {
                    if (find_Dominant_SkinningBone( vvv ) == skkk)
                    {
                        //////////////////////////////////////////////////////////////////////
                        skinningSkeleton.skinningBones[skkk].mainlyInfluenced_TotalVertices++;
                        //////////////////////////////////////////////////////////////////////////////
                        skinningSkeleton.skinningBones[skkk].mainlyInfluenced_VertexIDs.append( vvv );
                        //////////////////////////////////////////////////////////////////////////////
                    }
            }
    }
}



void Model::print_VerticesMainlyInfluenced_PerSkinningBone()
{

    for (int skkk=0; skkk<totalSkinningBones; skkk++)
    {
        std::cout << name.toStdString() << "  \t" << skkk << "  \t" << skinningSkeleton.skinningBones[skkk].name.toStdString() << "  \t" << "mainlyInfluenced_TotalVertices = " << skinningSkeleton.skinningBones[skkk].mainlyInfluenced_TotalVertices << std::endl;
    }   std::cout << std::endl;

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
// just to see how to use indices !!! //////////////////////////////
////////////////////////////////////////////////////////////////////
// skinnedVertices.                 resize( totalVertices      ); //
// skinnedVertices[vvv].skinWeights.resize( totalSkinningBones ); //
////////////////////////////////////////////////////////////////////



void Model::create_Vertices_DominantSkinningBone()
{

        /////////////////////////////////////////////////////////
        mesh.vertices_dominantSkinningBone.resize(totalVertices);
        /////////////////////////////////////////////////////////

        for (int vvv=0; vvv<totalVertices; vvv++)
        {
             int skkk = find_Dominant_SkinningBone(vvv);

             mesh.vertices_dominantSkinningBone[vvv].skinningBoneID = skkk;
             mesh.vertices_dominantSkinningBone[vvv].skinningWeight = skin.skinnedVertices[vvv].skinWeights[skkk];
        }

}



void Model::print_Vertices_DominantSkinningBone()
{

        ///////////////////////////////////////////////////////////
        mesh.vertices_dominantSkinningBone.resize( totalVertices );
        ///////////////////////////////////////////////////////////

        std::cout << std::endl;

        for (int vvv=0; vvv<totalVertices; vvv++)
        {
            std::cout << "Model::print_Vertices_DominantSkinningBone()" << "\t\t" << name.toStdString() << "\t\t" << "vertexID = " << vvv << "\t\t" << "mainSkinningBoneID = " << mesh.vertices_dominantSkinningBone[vvv].skinningBoneID << std::endl;
        }

        std::cout << std::endl;

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


