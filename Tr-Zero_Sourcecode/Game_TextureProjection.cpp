//-----------------------------------------------------------------
// About:
//
// name: "Game_TextureProjection.cpp:
//
// included in: "Global_Data.h" accessed through "Global_Params.h"
//
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_TextureProjection.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - FONT - CONSTRUCTORS
///*****************************************************************
Game_TextureProjection::Game_TextureProjection(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<MAX_TEXTURE_PROJECTION_SHADOW;i++)
	{
		tpShadow[i] = NULL;
	}
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_TextureProjection::~Game_TextureProjection(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - TEXTUREPROJECTION - ZeroData
///*****************************************************************
void Game_TextureProjection::ZeroData(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXTUREPROJECTION - CREATE
///*****************************************************************
void Game_TextureProjection::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
	//iCameraTextureProjectionMapsCreate(gCamera);

	//for(int i=0;i<MAX_TEXTURE_PROJECTION_SHADOW;i++)
	//{
	//	tpShadow[i] = iTextureProjectionCreate(cGame_Asset_Global_Texture.Bike_Shadow.Bike_Shadow_TP,NULL,NULL);

	//	if(gGameState==0)
	//	{
	//		//iMeshTextureProjectionSet(cGame_Track.Mesh_Menu[0],tpShadow[i]);
	//		//iMeshTextureProjectionEnable(cGame_Track.Mesh_Menu[0],tpShadow[i],true);
	//		//iMeshTextureProjectionIntensitySet(cGame_Track.Mesh_Menu[0],tpShadow[i],5.0f);
	//		//iTextureProjectionMeshRecieverAdd(cGame_Track.Mesh_Menu[0]);

	//	}
	//	else if(gGameState==1)
	//	{
	//		iMeshTextureProjectionSet(cGame_Track.Mesh_Track[0],tpShadow[i]);
	//		iMeshTextureProjectionEnable(cGame_Track.Mesh_Track[0],tpShadow[i],true);
	//		iMeshTextureProjectionIntensitySet(cGame_Track.Mesh_Track[0],tpShadow[i],5.0f);
	//		iTextureProjectionMeshRecieverAdd(cGame_Track.Mesh_Track[0]);

	//		iMeshTextureProjectionSet(cGame_Track.Mesh_Track[1],tpShadow[i]);
	//		iMeshTextureProjectionEnable(cGame_Track.Mesh_Track[1],tpShadow[i],true);
	//		iMeshTextureProjectionIntensitySet(cGame_Track.Mesh_Track[1],tpShadow[i],5.0f);
	//		iTextureProjectionMeshRecieverAdd(cGame_Track.Mesh_Track[1]);
	//	}
	//	else if(gGameState==2)
	//	{
	//	}
	//	else if(gGameState==3)
	//	{
	//	}

	//	iTextureProjectionConeAngleSet(tpShadow[i],90.0f);

	//}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXTUREPROJECTION - Update
///*****************************************************************
void Game_TextureProjection::Update(void)
{
	//-------------------------------------------------------------
	//for(int i=0;i<MAX_TEXTURE_PROJECTION_SHADOW;i++)
	//{
	//	D3DXVECTOR3 vOffset = iVectorLocationOffset(&cGame_Bike_Player.Manager.vBikeOutput,&cGame_Bike_Player.Manager.qBikeOutput,&D3DXVECTOR3(0.0f,4.0f,0.0f));
	//	iTextureProjectionLocationSet(tpShadow[i],&vOffset);
	//	D3DXQUATERNION qDown;
	//	iQuaternionFromEulerAngles(&qDown,90.0f,0.0f,0.0f);
	//	iQuaternionMultiply(&qDown,&qDown,&cGame_Bike_Player.Manager.qBikeOutputLean);
	//	iTextureProjectionOrientationSet(tpShadow[i],&qDown);
	//}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXTUREPROJECTION - DESTROY
///*****************************************************************
void Game_TextureProjection::Destroy(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
	//iCameraTextureProjectionMapsDestroy(gCamera);
	////-------------------------------------------------------------
	//for(int i=0;i<MAX_TEXTURE_PROJECTION_SHADOW;i++)
	//{
	//	iTextureProjectionDestroy(tpShadow[i]);
	//}
	//-------------------------------------------------------------
}