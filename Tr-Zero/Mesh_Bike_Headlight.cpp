//-----------------------------------------------------------------
// About:
//
// name: "Mesh_Bike_Headlight.cpp:
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
#include "Mesh_Bike_Headlight.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE HEADLIGHT - CONSTRUCTORS
///*****************************************************************
Mesh_Bike_Headlight::Mesh_Bike_Headlight(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<2;i++)
	{
		Headlight[i] = NULL;
	}
	ActiveModel_Ai = 0;
	ActiveModel_Player = 0;
	//-------------------------------------------------------------
}

Mesh_Bike_Headlight::~Mesh_Bike_Headlight(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE HEADLIGHT - CREATE
///*****************************************************************
void Mesh_Bike_Headlight::Create(void)
{
	//-------------------------------------------------------------
	//Mesh ID
	ActiveModel_Player = gBikeModelType_Player;
	ActiveModel_Ai = gBikeModelType_Ai;
	//Headlight Carl
	Headlight[0] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\headlight.bin");
	//Headlight Dave
	Headlight[1] = iMeshCreate("trzero_res\\md5mesh\\bikes\\bike_dave\\headlight.md5mesh",1.0f);
	for(int i=0;i<2;i++)
	{
		iMeshDirectionalLightEnableSet(Headlight[i],false,false,false,false,false);
		iMeshPointLightEnableSet(Headlight[i],false,false,0,false,1,false,2,false,3,false);
		iMeshAlphaToleranceSet(Headlight[i],0.1f,false);
		iMeshDepthBiasSet(Headlight[i],-3);
		iMeshShaderEmissiveABMapBlendSet(Headlight[i],false);
		iMeshScaleSet(Headlight[i],&gBikeScale,false);
		iMeshGlowEnable(Headlight[i],gGlowMeshEnable,false);
	}
	//-------------------------------------------------------------
	//Create AI Imposters
	ImpostersCreate();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE HEADLIGHT - UPDATE
///*****************************************************************
void Mesh_Bike_Headlight::Update(void)
{
	//-------------------------------------------------------------
	//Update Player
	Player_Update(&cGame_Mesh.Animator.vBike[gAi_Max_Count],&cGame_Mesh.Animator.qBike[gAi_Max_Count]);
	//-------------------------------------------------------------
	//Update Ai
	for(int i=0;i<gAi_Max_Count;i++)
	{
		Ai_Update_Headlight(i,
					&cGame_Mesh.Animator.vBike[i],
					&cGame_Mesh.Animator.qBike[i]);
	}
	//-------------------------------------------------------------
	//Shaders
	ShaderUpdate();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE HEADLIGHT - PLAYER UPDATE
///*****************************************************************
void Mesh_Bike_Headlight::Player_Update(D3DXVECTOR3* v1,D3DXQUATERNION* q1)
{
	//-------------------------------------------------------------
	//Mesh ID
	ActiveModel_Player = gBikeModelType_Player;
	//-------------------------------------------------------------
	D3DXVECTOR3 vColourTarget = cGame_Bike[gAi_Max_Count].Colour.vBikeColour / 5.0f;
	 
	for(int i=0;i<2;i++)
	{
		//Set Location
		iMeshLocationSet(Headlight[i],v1,false);
		iMeshOrientationSet(Headlight[i],q1,false);
		//update Colours
		iMeshColorSet(Headlight[i],&vColourTarget,false);
		iMeshHide(Headlight[i],false);
	}
	//Show
	iMeshShow(Headlight[ActiveModel_Player],false);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE HEADLIGHT - AI UPDATE
///*****************************************************************
void Mesh_Bike_Headlight::Ai_Update_Headlight(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1)
{
	//-------------------------------------------------------------
	D3DXVECTOR3 vColourTarget = cGame_Bike[Index].Colour.vBikeColour / 5.0f;
	//Update
	iMeshImposterLocationSet(Headlight[ActiveModel_Ai],Index,v1,false);
	iMeshImposterOrientationSet(Headlight[ActiveModel_Ai],Index,q1,false);
	iMeshImposterColorSet(Headlight[ActiveModel_Ai],Index,&vColourTarget,false);
	//-------------------------------------------------------------
	//Show
	iMeshImposterShow(Headlight[ActiveModel_Ai],Index,false);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE HEADLIGHT - SHADER UPDATE
///*****************************************************************
void Mesh_Bike_Headlight::ShaderUpdate(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<2;i++)
	{
		//Texture pan
		iMeshTexturePanSet(Headlight[i],&D3DXVECTOR2(0.0f,-gTexturePan_Slow),&D3DXVECTOR2(0.0f,-gTexturePan_Slow),false);
		//Headlight
		iMeshShaderEmissiveABMapBlendTextureUpdate(Headlight[i],
										 cGame_Asset_Global_Texture.Bike_Weapons.NULL_Alpha,
										 &D3DXVECTOR2(1.0f,1.0f),
										 cGame_Asset_Global_Texture.Bike.Headlight_B,
										 &D3DXVECTOR2(1.0f,1.0f),
										 cGame_Asset_Global_Texture.Bike.Headlight_C,
										 false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE HEADLIGHT - IMPOSTERS CREATE
///*****************************************************************
void Mesh_Bike_Headlight::ImpostersCreate(void)
{
	//-------------------------------------------------------------
	iMeshImpostersCreate(Headlight[ActiveModel_Ai],gAi_Max_Count);
	//frustum culling
	for(int i=0;i<gAi_Max_Count;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(Headlight[ActiveModel_Ai],i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE HEADLIGHT - IMPOSTERS DESTROY
///*****************************************************************
void Mesh_Bike_Headlight::ImpostersDestroy(void)
{
	//-------------------------------------------------------------
	iMeshImpostersDestroy(Headlight[ActiveModel_Ai]);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE HEADLIGHT - DESTROY
///*****************************************************************
void Mesh_Bike_Headlight::Destroy(void)
{
	//-------------------------------------------------------------
	ImpostersDestroy();
	//-------------------------------------------------------------
	for(int i=0;i<2;i++)
	{
		iMeshDestroy(Headlight[i]);
	}
	//-------------------------------------------------------------
}