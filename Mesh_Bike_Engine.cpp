//-----------------------------------------------------------------
// About:
//
// name: "Mesh_Bike_Tire.cpp:
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
#include "Mesh_Bike_Engine.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE - ENGINE - CONSTRUCTORS
///*****************************************************************
Mesh_Bike_Engine::Mesh_Bike_Engine(void)
{
	//-------------------------------------------------------------
	//mesh
	EngineL = NULL;
	EngineL_Glow = NULL;
	EngineR = NULL;
	EngineR_Glow = NULL;

	Engine_Pos_OffsetL = D3DXVECTOR3(0.0f,0.0f,0.0f);
	Engine_Pos_OffsetR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	vEngine_Rot_Offset = D3DXVECTOR2(0.0f,0.0f);

	Rotation = 0.0f;
	Rotation_Speed = 220.0f;
	//-------------------------------------------------------------
}

Mesh_Bike_Engine::~Mesh_Bike_Engine(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE - ENGINE - CREATE
///*****************************************************************
void Mesh_Bike_Engine::Create(void)
{
	//-------------------------------------------------------------
	//Offsets
	///Bike Carl
	Engine_Pos_OffsetL = D3DXVECTOR3(-0.25f,0.2f,0.3f);
	Engine_Pos_OffsetR = D3DXVECTOR3(0.25f,0.2f,0.3f);
	vEngine_Rot_Offset = D3DXVECTOR2(2.0f,0.0f);
	/////Bike Dave
	//Engine_Pos_OffsetL[1] = D3DXVECTOR3(-0.3f,0.16f,0.0f);
	//Engine_Pos_OffsetR[1] = D3DXVECTOR3(0.3f,0.16f,0.0f);
	//vEngine_Rot_Offset[1] = D3DXVECTOR2(0.0f,0.0f);
	//Scale Offsets
	Engine_Pos_OffsetL.x *= gBikeScale.x;
	Engine_Pos_OffsetL.y *= gBikeScale.y;
	Engine_Pos_OffsetL.z *= gBikeScale.z;

	Engine_Pos_OffsetR.x *= gBikeScale.x;
	Engine_Pos_OffsetR.y *= gBikeScale.y;
	Engine_Pos_OffsetR.z *= gBikeScale.z;
	//-------------------------------------------------------------
	//Create Mesh
	///Carl
	EngineL = iMeshCreate("trzero_res\\md5mesh\\bikes\\engine\\engine_carl.md5mesh",gMeshSmoothing);
	EngineL_Glow = iMeshCreate("trzero_res\\md5mesh\\bikes\\engine\\engine_carl_glow.md5mesh",gMeshSmoothing);
	
	//else if(i==1)///Dave
	//{
	//	EngineL = iMeshCreate("trzero_res\\md5mesh\\bikes\\engine\\engine_dave.md5mesh",gMeshSmoothing);
	//	EngineL_Glow = iMeshCreate("trzero_res\\md5mesh\\bikes\\engine\\engine_dave_glow.md5mesh",gMeshSmoothing);
	//}
	EngineR = iMeshFromMeshCreate(EngineL);
	EngineR_Glow = iMeshFromMeshCreate(EngineL_Glow);

	//lighting
	iMeshDirectionalLightEnableSet(EngineL,true,false,false,false,false);
	iMeshPointLightEnableSet(EngineL,false,false,0,false,1,false,2,false,3,false);
	iMeshDirectionalLightEnableSet(EngineR,true,false,false,false,false);
	iMeshPointLightEnableSet(EngineR,false,false,0,false,1,false,2,false,3,false);

	iMeshDirectionalLightEnableSet(EngineL_Glow,false,false,false,false,false);
	iMeshPointLightEnableSet(EngineL_Glow,false,false,0,false,1,false,2,false,3,false);
	iMeshDirectionalLightEnableSet(EngineR_Glow,false,false,false,false,false);
	iMeshPointLightEnableSet(EngineR_Glow,false,false,0,false,1,false,2,false,3,false);
	///Set Colour Static (Main Parts)
	///iMeshColorSet(EngineL[0],&D3DXVECTOR3(0.9f,0.9f,0.9f),false);
	//apply shader
	iMeshShaderNormalMapSet(EngineL,false);
	iMeshShaderNormalMapSet(EngineR,false);
	iMeshShaderEmissiveSet(EngineL_Glow,false);
	iMeshShaderEmissiveSet(EngineR_Glow,false);
	//FresnelEdge
	iMeshFresnelEdgeSet(EngineL,0.0f,1.0f,1.0f,false);
	iMeshFresnelEdgeSet(EngineR,0.0f,1.0f,1.0f,false);
	//Glow
	iMeshGlowEnable(EngineL_Glow,gGlowMeshEnable,false);
	iMeshGlowEnable(EngineR_Glow,gGlowMeshEnable,false);
	//Scale
	iMeshScaleSet(EngineL,&gBikeScale,false);
	iMeshScaleSet(EngineR,&gBikeScale,false);
	iMeshScaleSet(EngineL_Glow,&gBikeScale,false);
	iMeshScaleSet(EngineR_Glow,&gBikeScale,false);
	//-------------------------------------------------------------
	//Create AI Imposters
	ImpostersCreate();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE - ENGINE - UPDATE
///*****************************************************************
void Mesh_Bike_Engine::Update(void)
{
	//-------------------------------------------------------------
	//Update
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		//Update Ai Engine Mesh
		Update_Engine(i,
						&cGame_Mesh.Animator.vBike[i],
						&cGame_Mesh.Animator.qBike[i],
						cGame_Bike[i].fTireSpin);
	}
	//-------------------------------------------------------------
	//Shaders
	ShaderUpdate();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - ENGINE - SHADER UPDATE
///*****************************************************************
void Mesh_Bike_Engine::ShaderUpdate(void)
{
	//-------------------------------------------------------------
	//BIKE CARL - USES UNIQUE TEXTURES
	//Diffuse + bump
	iMeshShaderNormalMapTextureUpdate(EngineL,
									  cGame_Asset_Global_Texture.Bike_Engine.Diffuse,
									  cGame_Asset_Global_Texture.Bike_Engine.Normal,
									  NULL,
									  &D3DXVECTOR2(1.0f,1.0f),
									  false);
	iMeshShaderNormalMapTextureUpdate(EngineR,
									  cGame_Asset_Global_Texture.Bike_Engine.Diffuse,
									  cGame_Asset_Global_Texture.Bike_Engine.Normal,
									  NULL,
									  &D3DXVECTOR2(1.0f,1.0f),
									  false);
	//glow A
	iMeshShaderEmissiveTextureUpdate(EngineL_Glow,
									 cGame_Asset_Global_Texture.Bike_Engine.Glow_A,
									 &D3DXVECTOR2(1.0f,1.0f),
									 false);
	iMeshShaderEmissiveTextureUpdate(EngineR_Glow,
									 cGame_Asset_Global_Texture.Bike_Engine.Glow_A,
									 &D3DXVECTOR2(1.0f,1.0f),
									 false);
//else if(i==1)//BIKE DAVE - USES SAME TEXTURES AS MAIN BIKE MODEL
//{
//	//Diffuse + bump
//	iMeshShaderNormalMapTextureUpdate(EngineL[i],
//									cGame_Asset_Global_Texture.Bike.Diffuse[1],
//									cGame_Asset_Global_Texture.Bike.Normal[1],
//									cGame_Asset_Global_Texture.Bike.Specular[1],
//									  &D3DXVECTOR2(1.0f,1.0f),
//									  false);
//	iMeshShaderNormalMapTextureUpdate(EngineR[i],
//									cGame_Asset_Global_Texture.Bike.Diffuse[1],
//									cGame_Asset_Global_Texture.Bike.Normal[1],
//									cGame_Asset_Global_Texture.Bike.Specular[1],
//									  &D3DXVECTOR2(1.0f,1.0f),
//									  false);
//	//glow A
//	iMeshShaderEmissiveTextureUpdate(EngineL_Glow[i],
//									cGame_Asset_Global_Texture.Bike.Glow[1],
//									 &D3DXVECTOR2(1.0f,1.0f),
//									 false);
//	iMeshShaderEmissiveTextureUpdate(EngineR_Glow[i],
//									cGame_Asset_Global_Texture.Bike.Glow[1],
//									 &D3DXVECTOR2(1.0f,1.0f),
//									 false);
//}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - ENGINE - IMPOSTERS CREATE
///*****************************************************************
void Mesh_Bike_Engine::ImpostersCreate(void)
{
	//-------------------------------------------------------------
	iMeshImpostersCreate(EngineL,gAi_Max_Count+1);
	iMeshImpostersCreate(EngineR,gAi_Max_Count+1);
	iMeshImpostersCreate(EngineL_Glow,gAi_Max_Count+1);
	iMeshImpostersCreate(EngineR_Glow,gAi_Max_Count+1);
	//frustum culling
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(EngineL,i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(EngineR,i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(EngineL_Glow,i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(EngineR_Glow,i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - ENGINE - IMPOSTERS DESTROY
///*****************************************************************
void Mesh_Bike_Engine::ImpostersDestroy(void)
{
	//-------------------------------------------------------------
	iMeshImpostersDestroy(EngineL);
	iMeshImpostersDestroy(EngineL_Glow);
	iMeshImpostersDestroy(EngineR);
	iMeshImpostersDestroy(EngineR_Glow);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE - ENGINE - DESTROY
///*****************************************************************
void Mesh_Bike_Engine::Destroy(void)
{
	//-------------------------------------------------------------
	ImpostersDestroy();
	//-------------------------------------------------------------
	iMeshDestroy(EngineL);
	iMeshDestroy(EngineL_Glow);
	iMeshDestroy(EngineR);
	iMeshDestroy(EngineR_Glow);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - ENGINE - Update_Engine
///*****************************************************************
void Mesh_Bike_Engine::Update_Engine(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1,float fTireSpin)
{
	//-------------------------------------------------------------
	//Spin
	D3DXQUATERNION qEngineSpinL;
	iQuaternionFromEulerAngles(&qEngineSpinL,vEngine_Rot_Offset.x,-vEngine_Rot_Offset.y,fTireSpin);
	iQuaternionMultiply(&qEngineSpinL,&qEngineSpinL,q1);

	D3DXQUATERNION qEngineSpinR;
	iQuaternionFromEulerAngles(&qEngineSpinR,vEngine_Rot_Offset.x,vEngine_Rot_Offset.y,fTireSpin);
	iQuaternionMultiply(&qEngineSpinR,&qEngineSpinR,q1);

	D3DXVECTOR3 Engine_OffsetL = iVectorLocationOffset(v1,q1,&Engine_Pos_OffsetL);
	D3DXVECTOR3 Engine_OffsetR = iVectorLocationOffset(v1,q1,&Engine_Pos_OffsetR);
	//-------------------------------------------------------------
	//Mesh Placement
	iMeshImposterLocationSet(EngineL,Index,&Engine_OffsetL,false);
	iMeshImposterLocationSet(EngineL_Glow,Index,&Engine_OffsetL,false);
	iMeshImposterOrientationSet(EngineL,Index,&qEngineSpinL,false);
	iMeshImposterOrientationSet(EngineL_Glow,Index,&qEngineSpinL,false);

	iMeshImposterLocationSet(EngineR,Index,&Engine_OffsetR,false);
	iMeshImposterLocationSet(EngineR_Glow,Index,&Engine_OffsetR,false);
	iMeshImposterOrientationSet(EngineR,Index,&qEngineSpinR,false);
	iMeshImposterOrientationSet(EngineR_Glow,Index,&qEngineSpinR,false);
	//-------------------------------------------------------------
	//Colour Update
	iMeshImposterColorSet(EngineL_Glow,Index,&cGame_Bike[Index].Colour.vEngineColour,false);
	iMeshImposterColorSet(EngineR_Glow,Index,&cGame_Bike[Index].Colour.vEngineColour,false);
	//-------------------------------------------------------------
	//Show
	iMeshImposterShow(EngineL,Index,false);
	iMeshImposterShow(EngineR,Index,false);
	iMeshImposterShow(EngineL_Glow,Index,false);
	iMeshImposterShow(EngineR_Glow,Index,false);
	//-------------------------------------------------------------
}