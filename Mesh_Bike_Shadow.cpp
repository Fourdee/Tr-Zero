//-----------------------------------------------------------------
// About:
//
// name: "Mesh_Bike_Shadow.cpp:
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
#include "Mesh_Bike_Shadow.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE SHADOW - CONSTRUCTORS
///*****************************************************************
Mesh_Bike_Shadow::Mesh_Bike_Shadow(void)
{
	//-------------------------------------------------------------
	Shadow_A = NULL;
	//-------------------------------------------------------------
}

Mesh_Bike_Shadow::~Mesh_Bike_Shadow(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE SHADOW - CREATE
///*****************************************************************
void Mesh_Bike_Shadow::Create(void)
{
	//-------------------------------------------------------------
	//bike shadow
	Shadow_A = iMeshCreate("trzero_res\\md5mesh\\bikes\\shadow\\quad_D.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(Shadow_A,false,false,false,false,false);
	iMeshPointLightEnableSet(Shadow_A,false,false,0,false,1,false,2,false,3,false);
	iMeshShaderEmissiveSet(Shadow_A,false);
	iMeshAlphaToleranceSet(Shadow_A,0.02f,false);
	//iMeshCullModeSet(Shadow_A,D3D11_CULL_NONE);
	iMeshScaleSet(Shadow_A,&gBikeScale,false);
	//-------------------------------------------------------------
	//Create AI Imposters
	ImpostersCreate();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE SHADOW - UPDATE
///*****************************************************************
void Mesh_Bike_Shadow::Update(void)
{
	//-------------------------------------------------------------
	//Update Player
	Player_Update(&cGame_Bike[gAi_Max_Count].Manager.vBikeOutput,&cGame_Bike[gAi_Max_Count].Manager.qBikeOutput);
	//Update Ai
	for(int i=0;i<gAi_Max_Count;i++)
	{
		Ai_Update(i,&cGame_Bike[i].Manager.vBikeOutput,&cGame_Bike[i].Manager.qBikeOutput);
	}
	//-------------------------------------------------------------
	//Shaders
	ShaderUpdate();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE SHADOW - PLAYER UPDATE
///*****************************************************************
void Mesh_Bike_Shadow::Player_Update(D3DXVECTOR3* v1,D3DXQUATERNION* q1)
{
	//-------------------------------------------------------------
	//Offsets
	D3DXVECTOR3 vShadow = iVectorLocationOffset(v1,q1,&D3DXVECTOR3(0.0f,-1.65f,0.0f));
	iMeshLocationSet(Shadow_A,&vShadow,false);
	iMeshOrientationSet(Shadow_A,q1,false);
	//Show Mesh
	iMeshShow(Shadow_A,false);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE SHADOW - AI UPDATE
///*****************************************************************
void Mesh_Bike_Shadow::Ai_Update(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1)
{
	//-------------------------------------------------------------
	//Update
	D3DXVECTOR3 vShadow = iVectorLocationOffset(v1,q1,&D3DXVECTOR3(0.0f,-1.65f,0.0f));
	iMeshImposterLocationSet(Shadow_A,Index,&vShadow,false);
	iMeshImposterOrientationSet(Shadow_A,Index,q1,false);
	//-------------------------------------------------------------
	//Show
	iMeshImposterShow(Shadow_A,Index,false);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE SHADOW - SHADER UPDATE
///*****************************************************************
void Mesh_Bike_Shadow::ShaderUpdate(void)
{
	//-------------------------------------------------------------
	//Shadow
	iMeshShaderEmissiveTextureUpdate(Shadow_A,
								     cGame_Asset_Global_Texture.Bike_Shadow.Bike_Shadow,
								     &D3DXVECTOR2(1.0f,1.0f),
								     false);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE SHADOW - IMPOSTERS CREATE
///*****************************************************************
void Mesh_Bike_Shadow::ImpostersCreate(void)
{
	//-------------------------------------------------------------
	iMeshImpostersCreate(Shadow_A,gAi_Max_Count);
	//frustum culling
	for(int i=0;i<gAi_Max_Count;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(Shadow_A,i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE SHADOW - IMPOSTERS DESTROY
///*****************************************************************
void Mesh_Bike_Shadow::ImpostersDestroy(void)
{
	//-------------------------------------------------------------
	iMeshImpostersDestroy(Shadow_A);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE SHADOW - DESTROY
///*****************************************************************
void Mesh_Bike_Shadow::Destroy(void)
{
	//-------------------------------------------------------------
	ImpostersDestroy();
	//-------------------------------------------------------------
	iMeshDestroy(Shadow_A);
	//-------------------------------------------------------------
}