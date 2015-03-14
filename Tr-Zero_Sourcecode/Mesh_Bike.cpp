//-----------------------------------------------------------------
// About:
//
// name: "Mesh_Bike.cpp:
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
#include "Mesh_Bike.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE - CONSTRUCTORS
///*****************************************************************
Mesh_Bike::Mesh_Bike(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<MAX_BIKE_MODELS;i++)
	{
		Shell[i]			= NULL;
		Glow[i]				= NULL;
		Shield[i]			= NULL;
		Rider[i]			= NULL;
		RiderGlow[i]		= NULL;
		Helmet[i]			= NULL;
		HelmetGlow[i]		= NULL;
	}
	ActiveModel_Player = 0;
	ActiveModel_Ai = 1;
	SpawnLocation_Menu = D3DXVECTOR3(0.0f,1.45f,0.0f);
	vHelmetOffset = D3DXVECTOR3(0.0f,1.76f,1.63f);
	//-------------------------------------------------------------
}

Mesh_Bike::~Mesh_Bike(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE - CREATE
///*****************************************************************
void Mesh_Bike::Create(void)
{
	//-------------------------------------------------------------
	float fBumpScale = 10.0f;
	const float fAlphaTol = 0.2f;
	//Apply Model ID
	ActiveModel_Ai = 1;
	ActiveModel_Player = 0;
	if(gBikeModelType_Ai==1)
	{
		ActiveModel_Ai = 3;
		ActiveModel_Player = 2;
	}

	//Global Scale
	vHelmetOffset = D3DXVECTOR3(0.0f,1.76f,1.63f);
	vHelmetOffset.y *= gBikeScale.y;
	vHelmetOffset.z *= gBikeScale.z;
	//-------------------------------------------------------------
	//Bike Carl
	//[0]==High Poly Player
	Shell[0] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\bike_carl.bin");
	Shield[0] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\shield_carl.bin");
	Glow[0] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\bike_glow_carl.bin");
	Rider[0] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\rider_carl.bin");
	RiderGlow[0] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\rider_glow_carl.bin");
	Helmet[0] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\helmet_carl.bin");
	HelmetGlow[0] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\helmet_glow_carl.bin");
	//[1]==Low Poly AI
	Shell[1] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\lowpoly\\bike_carl.bin");
	Shield[1] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\shield_carl.bin");//
	Glow[1] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\lowpoly\\bike_glow_carl.bin");
	Rider[1] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\lowpoly\\rider_carl.bin");
	RiderGlow[1] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\lowpoly\\rider_glow_carl.bin");
	Helmet[1] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\lowpoly\\helmet_carl.bin");
	HelmetGlow[1] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\lowpoly\\helmet_glow_carl.bin");
	//Bike Dave
	//[2]==High Poly Player
	Shell[2] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_dave\\bike_dave.bin");
	Shield[2] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_dave\\shield_dave.bin");
	Glow[2] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_dave\\glow_dave.bin");
	Rider[2] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\rider_carl.bin");
	RiderGlow[2] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\rider_glow_carl.bin");
	Helmet[2] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\helmet_carl.bin");
	HelmetGlow[2] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\helmet_glow_carl.bin");
	//[3]==Low Poly AI
	Shell[3] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_dave\\lowpoly\\bike_dave.bin");
	Shield[3] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_dave\\lowpoly\\shield_dave.bin");
	Glow[3] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_dave\\lowpoly\\glow_dave.bin");
	Rider[3] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\lowpoly\\rider_carl.bin");
	RiderGlow[3] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\lowpoly\\rider_glow_carl.bin");
	Helmet[3] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\lowpoly\\helmet_carl.bin");
	HelmetGlow[3] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\lowpoly\\helmet_glow_carl.bin");
	//-------------------------------------------------------------
	//Bike
	//-------------------------------------------------------------
	for(int i=0;i<MAX_BIKE_MODELS;i++)
	{
		//shell mesh
		iMeshDirectionalLightEnableSet(Shell[i],true,false,false,false,false);
		iMeshPointLightEnableSet(Shell[i],false,false,0,false,1,false,2,false,3,false);
		iMeshDepthBiasSet(Shell[i],2);
		iMeshShaderNormalMapReflectSet(Shell[i],cGame_Asset_Global_Texture.Bike.EnvMap,gReflectRes,gReflectMipMap,0.5f,gReflectMaxRange,false,false);
		iMeshBumpScaleSet(Shell[i],fBumpScale,false);
		///Shell Colour adjustments
		iMeshColorSet(Shell[i],&gBikeShellColour,false);
		//if(i==2 || i==3)//Dave - colour for shell
		//{
		//	iMeshColorSet(Shell[i],&D3DXVECTOR3(0.9f,0.9f,0.9f),false);
		//}
		iMeshFresnelEdgeSet(Shell[i],0.0f,1.0f,0.4f,false);
		//glow mesh
		iMeshDirectionalLightEnableSet(Glow[i],false,false,false,false,false);
		iMeshPointLightEnableSet(Glow[i],false,false,0,false,1,false,2,false,3,false);
		iMeshAlphaToleranceSet(Glow[i],fAlphaTol,false);
		iMeshDepthBiasSet(Glow[i],-4);
		iMeshShaderEmissiveSet(Glow[i],false);
		//Shield mesh
		iMeshDirectionalLightEnableSet(Shield[i],false,false,false,false,false);
		iMeshPointLightEnableSet(Shield[i],false,false,0,false,1,false,2,false,3,false);
		iMeshAlphaToleranceSet(Shield[i],0.05f,false);
		iMeshDepthBiasSet(Shield[i],-3);
		iMeshShaderEmissiveSet(Shield[i],false);
		//iMeshBlendModeSet(Shield[i],2,5,1);
		//Rider
		iMeshDirectionalLightEnableSet(Rider[i],true,false,false,false,false);
		iMeshPointLightEnableSet(Rider[i],false,false,0,false,1,false,2,false,3,false);
		iMeshDepthBiasSet(Rider[i],4);
		iMeshShaderNormalMapReflectSet(Rider[i],cGame_Asset_Global_Texture.Bike.EnvMap,gReflectRes,gReflectMipMap,0.5f,gReflectMaxRange,false,false);
		iMeshBumpScaleSet(Rider[i],fBumpScale,false);
		iMeshColorSet(Rider[i],&gBikeShellColour,false);
		iMeshFresnelEdgeSet(Rider[i],0.0f,1.0f,0.4f,false);
		//RiderGlow
		iMeshDirectionalLightEnableSet(RiderGlow[i],false,false,false,false,false);
		iMeshPointLightEnableSet(RiderGlow[i],false,false,0,false,1,false,2,false,3,false);
		iMeshAlphaToleranceSet(RiderGlow[i],fAlphaTol,false);
		iMeshDepthBiasSet(RiderGlow[i],-2);
		iMeshShaderEmissiveSet(RiderGlow[i],false);
		//Helmet
		iMeshDirectionalLightEnableSet(Helmet[i],true,false,false,false,false);
		iMeshPointLightEnableSet(Helmet[i],false,false,0,false,1,false,2,false,3,false);
		iMeshDepthBiasSet(Helmet[i],4);
		iMeshShaderNormalMapReflectSet(Helmet[i],cGame_Asset_Global_Texture.Bike.EnvMap,gReflectRes,gReflectMipMap,0.5f,gReflectMaxRange,false,false);
		iMeshBumpScaleSet(Helmet[i],fBumpScale,false);
		iMeshFresnelEdgeSet(Helmet[i],0.0f ,1.0f ,0.4f ,false);
		//HelmetGlow
		iMeshDirectionalLightEnableSet(HelmetGlow[i],false,false,false,false,false);
		iMeshPointLightEnableSet(HelmetGlow[i],false,false,0,false,1,false,2,false,3,false);
		iMeshAlphaToleranceSet(HelmetGlow[i],fAlphaTol,false);
		iMeshDepthBiasSet(HelmetGlow[i],-2);
		iMeshShaderEmissiveSet(HelmetGlow[i],false);
		//-------------------------------------------------------------
		//Global Scale Adjustments
		iMeshScaleSet(Shell[i],&gBikeScale,false);
		iMeshScaleSet(Glow[i],&gBikeScale,false);
		iMeshScaleSet(Rider[i],&gBikeScale,false);
		iMeshScaleSet(RiderGlow[i],&gBikeScale,false);
		iMeshScaleSet(Helmet[i],&gBikeScale,false);
		iMeshScaleSet(HelmetGlow[i],&gBikeScale,false);
		iMeshScaleSet(Shield[i],&gBikeScale,false);
		//-------------------------------------------------------------
		//Glow
		iMeshGlowEnable(Glow[i],gGlowMeshEnable,false);
		iMeshGlowEnable(RiderGlow[i],gGlowMeshEnable,false);
		iMeshGlowEnable(HelmetGlow[i],gGlowMeshEnable,false);
		//-------------------------------------------------------------
		//Reflection Levels
		iMeshReflectionAmountSet(Shell[i],0.3f,false);
		iMeshReflectionAmountSet(Helmet[i],0.3f,false);
		iMeshReflectionAmountSet(Rider[i],0.3f,false);
		//-------------------------------------------------------------
		//Blend Modes
		iMeshBlendModeSet(Glow[i],1,7,2);
		iMeshBlendModeSet(RiderGlow[i],1,7,2);
		iMeshBlendModeSet(HelmetGlow[i],1,7,2);
	}
	//-------------------------------------------------------------
	//Create AI Imposters
	ImpostersCreate();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE - UPDATE
///*****************************************************************
void Mesh_Bike::Update(void)
{
	//-------------------------------------------------------------
	//Update Player
	Player_Update(&cGame_Mesh.Animator.vBike[gAi_Max_Count],&cGame_Mesh.Animator.qBike[gAi_Max_Count]);
	//-------------------------------------------------------------
	//Update Ai
	for(int i=0;i<gAi_Max_Count;i++)
	{
		//Update Ai Shell
		Ai_Update_Shell(i,
					&cGame_Mesh.Animator.vBike[i],
					&cGame_Mesh.Animator.qBike[i]);
		//Update Ai ShellGlow Mesh
		Ai_Update_ShellGlow(i,
					&cGame_Mesh.Animator.vBike[i],
					&cGame_Mesh.Animator.qBike[i]);
		//Update Ai Rider Mesh
		Ai_Update_Rider(i,
					&cGame_Mesh.Animator.vBike[i],
					&cGame_Mesh.Animator.qBike[i]);
		//Update Ai Shield Mesh
		Ai_Update_Shield(i,
					&cGame_Mesh.Animator.vBike[i],
					&cGame_Mesh.Animator.qBike[i]);
	}
	//-------------------------------------------------------------
	//Shaders
	ShaderUpdate();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - PLAYER UPDATE
///*****************************************************************
void Mesh_Bike::Player_Update(D3DXVECTOR3* v1,D3DXQUATERNION* q1)
{
	//-------------------------------------------------------------
	//Mesh ID
	ActiveModel_Player = 0;
	if(gBikeModelType_Player==1)
	{
		ActiveModel_Player = 2;
	}
	//-------------------------------------------------------------
	//Helmet
	D3DXVECTOR3 vHelmetOrigin = iVectorLocationOffset(v1,q1,&vHelmetOffset);
	D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
	D3DXQUATERNION qHelmetTarget = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	iVectorRotate(&vUp,&vUp,q1);
	iQuaternionLookAt(&qHelmetTarget,&vHelmetOrigin,&cGame_Bike[gAi_Max_Count].Weapons.vHelmetLookAt,&vUp);
	//-------------------------------------------------------------
	//Apply to all meshes
	for(int i=0;i<MAX_BIKE_MODELS;i++)
	{
		//Hide all sets
		iMeshHide(Shield[i],false);
		iMeshHide(Shell[i],false);
		iMeshHide(Glow[i],false);
		iMeshHide(Shield[i],false);
		iMeshHide(Rider[i],false);
		iMeshHide(RiderGlow[i],false);
		iMeshHide(Helmet[i],false);
		iMeshHide(HelmetGlow[i],false);
		//Update
		iMeshLocationSet(Shell[i],v1,false);
		iMeshLocationSet(Glow[i],v1,false);
		iMeshLocationSet(Shield[i],v1,false);
		iMeshLocationSet(Rider[i],v1,false);
		iMeshLocationSet(RiderGlow[i],v1,false);
		iMeshLocationSet(Helmet[i],&vHelmetOrigin,false);
		iMeshLocationSet(HelmetGlow[i],&vHelmetOrigin,false);

		iMeshOrientationSet(Shell[i],q1,false);
		iMeshOrientationSet(Glow[i],q1,false);
		iMeshOrientationSet(Shield[i],q1,false);
		iMeshOrientationSet(Rider[i],q1,false);
		iMeshOrientationSet(RiderGlow[i],q1,false);
		iMeshOrientationSet(Helmet[i],&qHelmetTarget,false);
		iMeshOrientationSet(HelmetGlow[i],&qHelmetTarget,false);
		//update Colours
		iMeshColorSet(Glow[i],&cGame_Bike[gAi_Max_Count].Colour.vBikeColour,false);
		iMeshColorSet(RiderGlow[i],&cGame_Bike[gAi_Max_Count].Colour.vBikeColour,false);
		iMeshColorSet(HelmetGlow[i],&cGame_Bike[gAi_Max_Count].Colour.vBikeColour,false);
	}
	//-------------------------------------------------------------
	//Show require mesh
	iMeshShow(Shell[ActiveModel_Player],false);
	iMeshShow(Glow[ActiveModel_Player],false);
	//-------------------------------------------------------------
	//Hide/Show Shield + update colour
	if(cGame_Bike[gAi_Max_Count].Colour.fShieldColourTotal > 0.4f)
	{
		iMeshColorSet(Shield[ActiveModel_Player],&cGame_Bike[gAi_Max_Count].Colour.vShieldColour,false);
		iMeshShow(Shield[ActiveModel_Player],false);
	}
	//-------------------------------------------------------------
	//Show Rider
	iMeshShow(HelmetGlow[ActiveModel_Player],false);
	iMeshShow(Helmet[ActiveModel_Player],false);
	iMeshShow(RiderGlow[ActiveModel_Player],false);
	iMeshShow(Rider[ActiveModel_Player],false);
	//Hide Rider internal view
	if(cGame_Camera.SpectateId==gAi_Max_Count &&
		cGame_Camera.Mode_InGame==3)
	{
		iMeshHide(HelmetGlow[ActiveModel_Player],false);
		iMeshHide(Helmet[ActiveModel_Player],false);
		iMeshHide(RiderGlow[ActiveModel_Player],false);
		iMeshHide(Rider[ActiveModel_Player],false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - Ai_Update_Rider
///*****************************************************************
void Mesh_Bike::Ai_Update_Rider(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1)
{
	//-------------------------------------------------------------
	//Update
	iMeshImposterLocationSet(Rider[ActiveModel_Ai],Index,v1,false);
	iMeshImposterLocationSet(RiderGlow[ActiveModel_Ai],Index,v1,false);
	iMeshImposterOrientationSet(Rider[ActiveModel_Ai],Index,q1,false);
	iMeshImposterOrientationSet(RiderGlow[ActiveModel_Ai],Index,q1,false);
	//Helmet
	D3DXVECTOR3 vHelmetOrigin = iVectorLocationOffset(v1,q1,&vHelmetOffset);
	D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
	D3DXQUATERNION qHelmetTarget = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	iVectorRotate(&vUp,&vUp,q1);
	iQuaternionLookAt(&qHelmetTarget,&vHelmetOrigin,&cGame_Bike[Index].Weapons.vHelmetLookAt,&vUp);
	iMeshImposterLocationSet(Helmet[ActiveModel_Ai],Index,&vHelmetOrigin,false);
	iMeshImposterLocationSet(HelmetGlow[ActiveModel_Ai],Index,&vHelmetOrigin,false);
	iMeshImposterOrientationSet(Helmet[ActiveModel_Ai],Index,&qHelmetTarget,false);
	iMeshImposterOrientationSet(HelmetGlow[ActiveModel_Ai],Index,&qHelmetTarget,false);
	//update Colours
	iMeshImposterColorSet(RiderGlow[ActiveModel_Ai],Index,&cGame_Bike[Index].Colour.vBikeColour,false);
	iMeshImposterColorSet(HelmetGlow[ActiveModel_Ai],Index,&cGame_Bike[Index].Colour.vBikeColour,false);
	//-------------------------------------------------------------
	//show
	iMeshImposterShow(Rider[ActiveModel_Ai],Index,false);
	iMeshImposterShow(RiderGlow[ActiveModel_Ai],Index,false);
	iMeshImposterShow(Helmet[ActiveModel_Ai],Index,false);
	iMeshImposterShow(HelmetGlow[ActiveModel_Ai],Index,false);
	//Hide rider internal view
	if(cGame_Camera.SpectateId==Index &&
		cGame_Camera.Mode_InGame==3)
	{
		iMeshImposterHide(Rider[ActiveModel_Ai],Index,false);
		iMeshImposterHide(RiderGlow[ActiveModel_Ai],Index,false);
		iMeshImposterHide(Helmet[ActiveModel_Ai],Index,false);
		iMeshImposterHide(HelmetGlow[ActiveModel_Ai],Index,false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - Ai_Update_Shell
///*****************************************************************
void Mesh_Bike::Ai_Update_Shell(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1)
{
	//-------------------------------------------------------------
	//Update
	iMeshImposterLocationSet(Shell[ActiveModel_Ai],Index,v1,false);
	iMeshImposterOrientationSet(Shell[ActiveModel_Ai],Index,q1,false);
	//-------------------------------------------------------------
	//show
	iMeshImposterShow(Shell[ActiveModel_Ai],Index,false);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - Ai_Update_ShellGlow
///*****************************************************************
void Mesh_Bike::Ai_Update_ShellGlow(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1)
{
	//-------------------------------------------------------------
	//Update
	iMeshImposterLocationSet(Glow[ActiveModel_Ai],Index,v1,false);
	iMeshImposterOrientationSet(Glow[ActiveModel_Ai],Index,q1,false);
	iMeshImposterColorSet(Glow[ActiveModel_Ai],Index,&cGame_Bike[Index].Colour.vBikeColour,false);
	//-------------------------------------------------------------
	//Show
	iMeshImposterShow(Glow[ActiveModel_Ai],Index,false);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - Ai_Update_Shield
///*****************************************************************
void Mesh_Bike::Ai_Update_Shield(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1)
{
	//-------------------------------------------------------------
	iMeshImposterHide(Shield[ActiveModel_Ai],Index,false);
	//Update
	iMeshImposterLocationSet(Shield[ActiveModel_Ai],Index,v1,false);
	iMeshImposterOrientationSet(Shield[ActiveModel_Ai],Index,q1,false);
	iMeshImposterColorSet(Shield[ActiveModel_Ai],Index,&cGame_Bike[Index].Colour.vShieldColour,false);
	//Show
	if(cGame_Mesh.Culling.bRider[Index] &&
		cGame_Bike[Index].Colour.fShieldColourTotal > 0.4f)
	{
		iMeshImposterShow(Shield[ActiveModel_Ai],Index,false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - SHADER UPDATE
///*****************************************************************
void Mesh_Bike::ShaderUpdate(void)
{
	//-------------------------------------------------------------
	int TexId = 0;
	for(int i=0;i<MAX_BIKE_MODELS;i++)
	{
		if(i>=2)
		{
			TexId = 1;
		}
		//shell
		iMeshShaderNormalMapReflRefrTextureUpdate(Shell[i],
												  cGame_Asset_Global_Texture.Bike.Diffuse[TexId],
												  cGame_Asset_Global_Texture.Bike.Normal[TexId],
												  cGame_Asset_Global_Texture.Bike.Specular[TexId],
												 //NULL,
												  cGame_Asset_Global_Texture.Bike.Refl_Mask[TexId],
												  &D3DXVECTOR2(1.0f,1.0f),
												  &D3DXVECTOR3(0.0f,-1.0f,0.0f),
												  false);
		//glow
		iMeshShaderEmissiveTextureUpdate(Glow[i],
										 cGame_Asset_Global_Texture.Bike.Glow[TexId],
										 &D3DXVECTOR2(1.0f,1.0f),
										 false);
		//Shield
		iMeshTexturePanSet(Shield[i],&D3DXVECTOR2(0.0f,gTexturePan_Slow),&D3DXVECTOR2(0.0f,0.0f),false);
		iMeshShaderEmissiveTextureUpdate(Shield[i],
										 cGame_Asset_Global_Texture.Bike.Shield,
										 &D3DXVECTOR2(2.0f,5.0f),
										 false);
		//-------------------------------------------------------------
		//Rider
		iMeshShaderNormalMapReflRefrTextureUpdate(Rider[i],
												  cGame_Asset_Global_Texture.Bike.Diffuse[0],
												  cGame_Asset_Global_Texture.Bike.Normal[0],
												  cGame_Asset_Global_Texture.Bike.Specular[0],
												 //NULL,
												  cGame_Asset_Global_Texture.Bike.Refl_Mask[0],
												  &D3DXVECTOR2(1.0f,1.0f),
												  &D3DXVECTOR3(0.0f,-1.0f,0.0f),
												  false);
		//RiderGlow
		iMeshShaderEmissiveTextureUpdate(RiderGlow[i],
										 cGame_Asset_Global_Texture.Bike.Glow[0],
										 &D3DXVECTOR2(1.0f,1.0f),
										 false);
		//Helmet
		iMeshShaderNormalMapReflRefrTextureUpdate(Helmet[i],
												  cGame_Asset_Global_Texture.Bike.Diffuse[0],
												  cGame_Asset_Global_Texture.Bike.Normal[0],
												  cGame_Asset_Global_Texture.Bike.Specular[0],
												  cGame_Asset_Global_Texture.Bike.Refl_Mask[0],
												  &D3DXVECTOR2(1.0f,1.0f),
												  &D3DXVECTOR3(0.0f,-1.0f,0.0f),
												  false);
		//HelmetGlow
		iMeshShaderEmissiveTextureUpdate(HelmetGlow[i],
										 cGame_Asset_Global_Texture.Bike.Glow[0],
										 &D3DXVECTOR2(1.0f,1.0f),
										 false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - IMPOSTERS CREATE
///*****************************************************************
void Mesh_Bike::ImpostersCreate(void)
{
	//-------------------------------------------------------------
	iMeshImpostersCreate(Shell[ActiveModel_Ai],gAi_Max_Count);
	iMeshImpostersCreate(Shield[ActiveModel_Ai],gAi_Max_Count);
	iMeshImpostersCreate(Glow[ActiveModel_Ai],gAi_Max_Count);
	iMeshImpostersCreate(Rider[ActiveModel_Ai],gAi_Max_Count);
	iMeshImpostersCreate(RiderGlow[ActiveModel_Ai],gAi_Max_Count);
	iMeshImpostersCreate(Helmet[ActiveModel_Ai],gAi_Max_Count);
	iMeshImpostersCreate(HelmetGlow[ActiveModel_Ai],gAi_Max_Count);

	for(int i=0;i<gAi_Max_Count;i++)
	{
		////!!NB!! - Must be shown for culling system to work. wtf?
		//iMeshImposterShow(Shell[ActiveModel_Ai],i,false);
		//iMeshImposterShow(Glow[ActiveModel_Ai],i,false);
		//iMeshImposterShow(Shield[ActiveModel_Ai],i,false);
		//iMeshImposterShow(Rider[ActiveModel_Ai],i,false);
		//iMeshImposterShow(RiderGlow[ActiveModel_Ai],i,false);
		//iMeshImposterShow(Helmet[ActiveModel_Ai],i,false);
		//iMeshImposterShow(HelmetGlow[ActiveModel_Ai],i,false);

		iMeshImposterAABBAutoFrustumCullingEnable(Shell[ActiveModel_Ai],i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(Glow[ActiveModel_Ai],i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(Shield[ActiveModel_Ai],i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(Rider[ActiveModel_Ai],i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(RiderGlow[ActiveModel_Ai],i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(Helmet[ActiveModel_Ai],i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(HelmetGlow[ActiveModel_Ai],i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - IMPOSTERS DESTROY
///*****************************************************************
void Mesh_Bike::ImpostersDestroy(void)
{
	//-------------------------------------------------------------
	iMeshImpostersDestroy(Glow[ActiveModel_Ai]);
	iMeshImpostersDestroy(Shell[ActiveModel_Ai]);
	iMeshImpostersDestroy(Shield[ActiveModel_Ai]);
	iMeshImpostersDestroy(Rider[ActiveModel_Ai]);
	iMeshImpostersDestroy(RiderGlow[ActiveModel_Ai]);
	iMeshImpostersDestroy(Helmet[ActiveModel_Ai]);
	iMeshImpostersDestroy(HelmetGlow[ActiveModel_Ai]);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE - DESTROY
///*****************************************************************
void Mesh_Bike::Destroy(void)
{
	//-------------------------------------------------------------
	//Destroy AI Imposters
	ImpostersDestroy();
	//-------------------------------------------------------------
	for(int i=0;i<MAX_BIKE_MODELS;i++)
	{
		iMeshDestroy(Glow[i]);
		iMeshDestroy(Shell[i]);
		iMeshDestroy(Shield[i]);
		iMeshDestroy(Rider[i]);
		iMeshDestroy(RiderGlow[i]);
		iMeshDestroy(Helmet[i]);
		iMeshDestroy(HelmetGlow[i]);
	}
	//-------------------------------------------------------------
}