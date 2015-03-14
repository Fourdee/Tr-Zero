//-----------------------------------------------------------------
// About:
//
// name: "Mesh_Bike_Trail.cpp:
//
// included in: "Game_Asset_Global_Mesh.h"
//
// usage: 
//
// device input: none.
//
// todo:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Mesh_Bike_Trail.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - MESH - TRAIL - CONSTRUCTORS
///*****************************************************************
Mesh_Bike_Trail::Mesh_Bike_Trail(void)
{
	//-------------------------------------------------------------
	//Global Data
	///Carls Bike
	vTrailOffsetL[0] = D3DXVECTOR3(-0.96f,0.1f,-2.6f);
	vTrailOffsetR[0] = D3DXVECTOR3(0.96f,0.1f,-2.6f);
	///Dave's Bike
	vTrailOffsetL[1] = D3DXVECTOR3(-1.2f,0.09f,-2.3f);
	vTrailOffsetR[1] = D3DXVECTOR3(1.2f,0.09f,-2.3f);

	//Mesh ID
	ActiveModel_Ai = 0;
	ActiveModel_Player = 0;

	fAngle = 0.0f;
	fWidth = 0.3f;
	//Offset Scale
	for(int i=0;i<2;i++)
	{
		vTrailOffsetL[i].x *= gBikeScale.x;
		vTrailOffsetL[i].y *= gBikeScale.y;
		vTrailOffsetL[i].z *= gBikeScale.z;

		vTrailOffsetR[i].x *= gBikeScale.x;
		vTrailOffsetR[i].y *= gBikeScale.y;
		vTrailOffsetR[i].z *= gBikeScale.z;
	}
	//-------------------------------------------------------------
	//Mesh
	for(int i=0;i<MAX_TRAILS;i++)
	{
		TrailL[i] = NULL;
		TrailR[i] = NULL;
	}
	//-------------------------------------------------------------
}
Mesh_Bike_Trail::~Mesh_Bike_Trail(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MESH - TRAIL - CREATE
///*****************************************************************
void Mesh_Bike_Trail::Create(void)
{
	//-------------------------------------------------------------
	//Mesh ID
	ActiveModel_Player = gBikeModelType_Player;
	ActiveModel_Ai = gBikeModelType_Ai;
	//-------------------------------------------------------------
	//Create Mesh
	for(int i=0;i<=gAi_Max_Count;i++)//(ai + player) trails
	{
		//L
		TrailL[i] = iTrailCreate(50,2.0f,0.0f,true,true,true,false,0.0f,false,1);
		iTrailDirectionalLightEnableSet(TrailL[i],false,false,false,false),
		iTrailColorSet(TrailL[i],&D3DXVECTOR3(0.2f,1.0f,1.0f));
		iTrailAlphaToleranceSet(TrailL[i],0.025f);
		iTrailRenderModeSet(TrailL[i],1);
		iTrailShaderSet(TrailL[i],0);
		iTrailDiffuseMapTextureSet(TrailL[i],cGame_Asset_Global_Texture.Bike.Trail_em,NULL);
		iTrailWidthMultiplySet(TrailL[i],fWidth);
		//R
		TrailR[i] = iTrailCreate(50,2.0f,0.0f,true,true,true,false,0.0f,false,1);
		iTrailDirectionalLightEnableSet(TrailR[i],false,false,false,false),
		iTrailColorSet(TrailR[i],&D3DXVECTOR3(0.2f,1.0f,1.0f));
		iTrailAlphaToleranceSet(TrailR[i],0.025f);
		iTrailRenderModeSet(TrailR[i],1);
		iTrailShaderSet(TrailR[i],0);
		iTrailDiffuseMapTextureSet(TrailR[i],cGame_Asset_Global_Texture.Bike.Trail_em,NULL);
		iTrailWidthMultiplySet(TrailR[i],fWidth);

		//iTrailWireFrameModeEnable(TrailL[i],true);
		//iTrailWireFrameModeEnable(TrailR[i],true);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MESH - TRAIL - UPDATE
///*****************************************************************
void Mesh_Bike_Trail::Update(void)
{
	//-------------------------------------------------------------
	//Update
	bool bEmit = false;
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		bEmit = false;
		///Send a true bool to emit when not being culled.
		if(cGame_Mesh.Culling.bRider[i] &&
			cGame_Bike[i].InputSpeedState>=1)
		{
			bEmit = true;
		}
		Update(i,
				&cGame_Mesh.Animator.vBike[i],
				&cGame_Mesh.Animator.qBike[i],
				&cGame_Bike[i].Colour.vBikeColourTarget,
				bEmit);
	}
	////-------------------------------------------------------------
	////Optimize (iTrailReset causes 75% fps drop)
	//if(gET_DeltaTime>0.02f)
	//{
	//	for(int i=0;i<gAi_Max_Count;i++)
	//	{
	//		iTrailReset(TrailL[i]);
	//		iTrailReset(TrailR[i]);
	//	}
	//}
	//-------------------------------------------------------------
	//Shaders
	//ShaderUpdate();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - MESH - TRAIL - UPDATE
///*****************************************************************
void Mesh_Bike_Trail::Update(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1,D3DXVECTOR3* vColour,bool bEnable)
{
	//-------------------------------------------------------------
	if(gBikesGo)
	{
		//location
		D3DXVECTOR3 offsetL = iVectorLocationOffset(v1,q1,&vTrailOffsetL[ActiveModel_Ai]);
		D3DXVECTOR3 offsetR = iVectorLocationOffset(v1,q1,&vTrailOffsetR[ActiveModel_Ai]);
		//colour
		//vColour = vColour / 2.0f;
		//Rotate quat.z 90
		D3DXQUATERNION q2;
		iQuaternionFromEulerAngles(&q2,0.0f,0.0f,90.0f);
		iQuaternionMultiply(q1,&q2,q1);
		//LEFT
		iTrailEmit(TrailL[Index],&offsetL,q1,fAngle,0,false,0.0f,1.2f,0,bEnable);
		iTrailColorSet(TrailL[Index],vColour);
		//RIGHT
		iTrailEmit(TrailR[Index],&offsetR,q1,fAngle,0,false,0.0f,1.2f,0,bEnable);
		iTrailColorSet(TrailR[Index],vColour);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MESH - TRAIL - DESTROY
///*****************************************************************
void Mesh_Bike_Trail::Destroy(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<MAX_TRAILS;i++)
	{
		iTrailDestroy(TrailL[i]);
		iTrailDestroy(TrailR[i]);
	}
	//-------------------------------------------------------------
}