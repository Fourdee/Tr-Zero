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
#include "Mesh_Bike_Tire.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE - TIRE - CONSTRUCTORS
///*****************************************************************
Mesh_Bike_Tire::Mesh_Bike_Tire(void)
{
	//-------------------------------------------------------------
	//mesh
	for(int i=0;i<2;i++)
	{
		Back[i] = NULL;
		Back_Glow[i] = NULL;
		Back_Glow_In[i] = NULL;
		Front[i] = NULL;
		Front_Glow[i] = NULL;
		Front_Glow_In[i] = NULL;
		Back_Pos_Offset[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		Front_Pos_Offset[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}
	ActiveModel_Player = 0;
	ActiveModel_Ai = 1;
	//-------------------------------------------------------------
}

Mesh_Bike_Tire::~Mesh_Bike_Tire(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE - TIRE - CREATE
///*****************************************************************
void Mesh_Bike_Tire::Create(void)
{
	//-------------------------------------------------------------
	//Mesh ID
	ActiveModel_Player = gBikeModelType_Player;
	ActiveModel_Ai = gBikeModelType_Ai;

	//Offsets Carl
	Back_Pos_Offset[0] = D3DXVECTOR3(0.0f,0.0f,-2.68f);
	Front_Pos_Offset[0] = D3DXVECTOR3(0.0f,0.0f,3.12f);
	//Offsets Dave
	Back_Pos_Offset[1] = D3DXVECTOR3(0.0f,0.06f,-2.709f);
	Front_Pos_Offset[1] = D3DXVECTOR3(0.0f,0.06f,3.04f);

	for(int i=0;i<2;i++)
	{
		Back_Pos_Offset[i].y *= gBikeScale.y;
		Back_Pos_Offset[i].z *= gBikeScale.z;

		Front_Pos_Offset[i].y *= gBikeScale.y;
		Front_Pos_Offset[i].z *= gBikeScale.z;
	}
	//Bump factor
	float fBumpScale = 2.0f;
	//-------------------------------------------------------------
	//Carl
	Back[0] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\wheel_carl.bin");
	Front[0] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\wheel_carl.bin");

	Back_Glow[0] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\wheel_glow_carl.bin"); 
	Front_Glow[0] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\wheel_glow_carl.bin"); 

	Back_Glow_In[0] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\wheel_glow2_carl.bin"); 
	Front_Glow_In[0] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\wheel_glow2_carl.bin");

	//Dave
	Back[1] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_dave\\wheel_dave.bin");
	Front[1] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_dave\\wheel_dave.bin");

	Back_Glow[1] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_dave\\wheel_glow_dave.bin");
	Front_Glow[1] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_dave\\wheel_glow_dave.bin");

	Back_Glow_In[1] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\wheel_glow2_carl.bin"); 
	Front_Glow_In[1] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\wheel_glow2_carl.bin");
	///!!NB!! - Not used in Daves model

	for(int i=0;i<2;i++)
	{
		iMeshDirectionalLightEnableSet(Back[i],true,false,false,false,false);
		iMeshPointLightEnableSet(Back[i],false,false,0,false,1,false,2,false,3,false);
		iMeshDirectionalLightEnableSet(Back_Glow[i],false,false,false,false,false);
		iMeshPointLightEnableSet(Back_Glow[i],false,false,0,false,1,false,2,false,3,false);

		iMeshDirectionalLightEnableSet(Front[i],true,false,false,false,false);
		iMeshPointLightEnableSet(Front[i],false,false,0,false,1,false,2,false,3,false);
		iMeshDirectionalLightEnableSet(Front_Glow[i],false,false,false,false,false);
		iMeshPointLightEnableSet(Front_Glow[i],false,false,0,false,1,false,2,false,3,false);

		iMeshDirectionalLightEnableSet(Back_Glow_In[i],false,false,false,false,false);
		iMeshPointLightEnableSet(Back_Glow_In[i],false,false,0,false,1,false,2,false,3,false);
		iMeshDirectionalLightEnableSet(Front_Glow_In[i],false,false,false,false,false);
		iMeshPointLightEnableSet(Front_Glow_In[i],false,false,0,false,1,false,2,false,3,false);

		iMeshDepthBiasSet(Back_Glow[i],-4);
		iMeshDepthBiasSet(Front_Glow[i],-4);

		iMeshShaderNormalMapABSet(Back[i],false);
		iMeshShaderEmissiveABSet(Back_Glow[i],false);
		iMeshShaderNormalMapABSet(Front[i],false);
		iMeshShaderEmissiveABSet(Front_Glow[i],false);
		iMeshShaderEmissiveSet(Back_Glow_In[i],false);
		iMeshShaderEmissiveSet(Front_Glow_In[i],false);

		iMeshAlphaToleranceSet(Back_Glow[i],0.1f,false);
		iMeshAlphaToleranceSet(Front_Glow[i],0.1f,false);
		iMeshAlphaToleranceSet(Back_Glow_In[i],0.1f,false);
		iMeshAlphaToleranceSet(Front_Glow_In[i],0.1f,false);

		iMeshGlowEnable(Back_Glow[i],gGlowMeshEnable,false);
		iMeshGlowEnable(Front_Glow[i],gGlowMeshEnable,false);
		iMeshGlowEnable(Back_Glow_In[i],gGlowMeshEnable,false);
		iMeshGlowEnable(Front_Glow_In[i],gGlowMeshEnable,false);

		iMeshBlendModeSet(Back_Glow[i],1,7,2);
		iMeshBlendModeSet(Front_Glow[i],1,7,2);
		iMeshBlendModeSet(Back_Glow_In[i],1,7,2);
		iMeshBlendModeSet(Front_Glow_In[i],1,7,2);
		///FrenelEdge
		iMeshFresnelEdgeSet(Back[i],0.0f ,1.0f ,0.5f ,false );
		iMeshFresnelEdgeSet(Front[i],0.0f ,1.0f ,0.5f ,false );

		iMeshScaleSet(Back[i],&gBikeScale,false);
		iMeshScaleSet(Back_Glow[i],&gBikeScale,false);
		iMeshScaleSet(Front[i],&gBikeScale,false);
		iMeshScaleSet(Front_Glow[i],&gBikeScale,false);
		iMeshScaleSet(Back_Glow_In[i],&gBikeScale,false);
		iMeshScaleSet(Front_Glow_In[i],&gBikeScale,false);
		if(i==0)///Carl Only Extras
		{
			iMeshColorSet(Back[i],&D3DXVECTOR3(0.7f,0.7f,0.7f),false);
			iMeshColorSet(Front[i],&D3DXVECTOR3(0.7f,0.7f,0.7f),false);
			fBumpScale = 2.0f;
		}
		else if(i==1)///Dave Only extras
		{
			iMeshColorSet(Back[i],&D3DXVECTOR3(0.9f,0.9f,0.9f),false);
			iMeshColorSet(Front[i],&D3DXVECTOR3(0.9f,0.9f,0.9f),false);
			fBumpScale = 4.0f;
		}

		iMeshBumpScaleSet(Back[i],fBumpScale,false);
		iMeshBumpScaleSet(Front[i],fBumpScale,false);

	}
	//-------------------------------------------------------------
	//AI Imposters
	ImpostersCreate();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - TIRE - SHADER UPDATE
///*****************************************************************
void Mesh_Bike_Tire::ShaderUpdate(void)
{
	//-------------------------------------------------------------
	//Blur update
	float blur = 0.0f;
	if(gBikesGo)
	{
		blur = iFloatInterpolateSmooth(abs(cGame_Bike[gAi_Max_Count].Manager.fAcceleration_Speed),
									0.0f,
									2.0f,
									0.0f,
									1.0f);
	}
	//-------------------------------------------------------------
	for(int i=0;i<2;i++)
	{
		//Shaders
		///Texture Blend
		iMeshTextureBlendABSet(Back[i],blur,false);
		iMeshTextureBlendABSet(Front[i],blur,false);
		iMeshTextureBlendABSet(Back_Glow[i],blur,false);
		iMeshTextureBlendABSet(Front_Glow[i],blur,false);
		///back
		iMeshShaderNormalMapABTextureUpdate(Back[i],
										  cGame_Asset_Global_Texture.Bike_Tire.Diffuse[i],
										  cGame_Asset_Global_Texture.Bike_Tire.Normal[i],
										  cGame_Asset_Global_Texture.Bike_Tire.Specular[i],
										  &D3DXVECTOR2(1.0f,1.0f),
										  cGame_Asset_Global_Texture.Bike_Tire.DiffuseBlur[i],
										  cGame_Asset_Global_Texture.Bike_Tire.NormalBlur[i],
										  cGame_Asset_Global_Texture.Bike_Tire.SpecularBlur[i],
										  &D3DXVECTOR2(1.0f,1.0f),
										  false);
		///front
		iMeshShaderNormalMapABTextureUpdate(Front[i],
										  cGame_Asset_Global_Texture.Bike_Tire.Diffuse[i],
										  cGame_Asset_Global_Texture.Bike_Tire.Normal[i],
										  cGame_Asset_Global_Texture.Bike_Tire.Specular[i],
										  &D3DXVECTOR2(1.0f,1.0f),
										  cGame_Asset_Global_Texture.Bike_Tire.DiffuseBlur[i],
										  cGame_Asset_Global_Texture.Bike_Tire.NormalBlur[i],
										  cGame_Asset_Global_Texture.Bike_Tire.SpecularBlur[i],
										  &D3DXVECTOR2(1.0f,1.0f),
										  false);

		//Tire Glow
		///back
		iMeshShaderEmissiveABTextureUpdate(Back_Glow[i],
										 cGame_Asset_Global_Texture.Bike_Tire.Glow_A[i],
										 &D3DXVECTOR2(1.0f,1.0f),
										 cGame_Asset_Global_Texture.Bike_Tire.Glow_A_Blur[i],
										 &D3DXVECTOR2(1.0f,1.0f),
										 false);
		///front
		iMeshShaderEmissiveABTextureUpdate(Front_Glow[i],
										 cGame_Asset_Global_Texture.Bike_Tire.Glow_A[i],
										 &D3DXVECTOR2(1.0f,1.0f),
										 cGame_Asset_Global_Texture.Bike_Tire.Glow_A_Blur[i],
										 &D3DXVECTOR2(1.0f,1.0f),
										 false);
		//Carl Extra - Side Glow
		///back
		iMeshShaderEmissiveTextureUpdate(Back_Glow_In[i],
										 cGame_Asset_Global_Texture.Bike_Tire.Glow_B,
										 &D3DXVECTOR2(1.0f,1.0f),
										 false);
		///front
		iMeshShaderEmissiveTextureUpdate(Front_Glow_In[i],
										 cGame_Asset_Global_Texture.Bike_Tire.Glow_B,
										 &D3DXVECTOR2(1.0f,1.0f),
										 false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - TIRE - IMPOSTERS CREATE
///*****************************************************************
void Mesh_Bike_Tire::ImpostersCreate(void)
{
	//-------------------------------------------------------------
	iMeshImpostersCreate(Back[ActiveModel_Ai],gAi_Max_Count);
	iMeshImpostersCreate(Back_Glow[ActiveModel_Ai],gAi_Max_Count);
	iMeshImpostersCreate(Front[ActiveModel_Ai],gAi_Max_Count);
	iMeshImpostersCreate(Front_Glow[ActiveModel_Ai],gAi_Max_Count);
	iMeshImpostersCreate(Back_Glow_In[ActiveModel_Ai],gAi_Max_Count);
	iMeshImpostersCreate(Front_Glow_In[ActiveModel_Ai],gAi_Max_Count);
	//frustum culling
	for(int i=0;i<gAi_Max_Count;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(Back[ActiveModel_Ai],i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(Back_Glow[ActiveModel_Ai],i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(Front[ActiveModel_Ai],i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(Front_Glow[ActiveModel_Ai],i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(Back_Glow_In[ActiveModel_Ai],i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(Front_Glow_In[ActiveModel_Ai],i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE - TIRE - UPDATE
///*****************************************************************
void Mesh_Bike_Tire::Update(void)
{
	//-------------------------------------------------------------
	//Update Player
	Player_Update(&cGame_Mesh.Animator.vBike[gAi_Max_Count],&cGame_Mesh.Animator.qBike[gAi_Max_Count],&cGame_Bike[gAi_Max_Count].fTireSpin);
	//Update Ai
	for(int i=0;i<gAi_Max_Count;i++)
	{
		Ai_Update(i,
				&cGame_Mesh.Animator.vBike[i],
				&cGame_Mesh.Animator.qBike[i],
				&cGame_Bike[i].fTireSpin);
	}
	//-------------------------------------------------------------
	//Shaders
	ShaderUpdate();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - TIRE - IMPOSTERS DESTROY
///*****************************************************************
void Mesh_Bike_Tire::ImpostersDestroy(void)
{
	//-------------------------------------------------------------
	iMeshImpostersDestroy(Back[ActiveModel_Ai]);
	iMeshImpostersDestroy(Back_Glow[ActiveModel_Ai]);
	iMeshImpostersDestroy(Front[ActiveModel_Ai]);
	iMeshImpostersDestroy(Front_Glow[ActiveModel_Ai]);
	iMeshImpostersDestroy(Back_Glow_In[ActiveModel_Ai]);
	iMeshImpostersDestroy(Front_Glow_In[ActiveModel_Ai]);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE - TIRE - DESTROY
///*****************************************************************
void Mesh_Bike_Tire::Destroy(void)
{
	//-------------------------------------------------------------
	//Destroy AI Imposters
	ImpostersDestroy();
	//-------------------------------------------------------------
	for(int i=0;i<2;i++)
	{
		iMeshDestroy(Back[i]);
		iMeshDestroy(Back_Glow[i]);
		iMeshDestroy(Front[i]);
		iMeshDestroy(Front_Glow[i]);
		iMeshDestroy(Back_Glow_In[i]);
		iMeshDestroy(Front_Glow_In[i]);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - TIRE - PLAYER UPDATE
///*****************************************************************
void Mesh_Bike_Tire::Player_Update(D3DXVECTOR3* v1,D3DXQUATERNION* q1,float* fTireSpin)
{
	//-------------------------------------------------------------
	//Mesh ID
	ActiveModel_Player = gBikeModelType_Player;
	//-------------------------------------------------------------
	D3DXQUATERNION qTireSpin;
	iQuaternionFromEulerAngles(&qTireSpin,*fTireSpin,0.0f,180.0f);
	iQuaternionMultiply(&qTireSpin,&qTireSpin,q1);

	D3DXVECTOR3 Back_Offset = iVectorLocationOffset(v1,q1,&Back_Pos_Offset[ActiveModel_Player]);
	D3DXVECTOR3 Front_Offset = iVectorLocationOffset(v1,q1,&Front_Pos_Offset[ActiveModel_Player]);

	for(int i=0;i<2;i++)
	{
		//Hide All
		iMeshHide(Back[i],false);
		iMeshHide(Back_Glow[i],false);
		iMeshHide(Front[i],false);
		iMeshHide(Front_Glow[i],false);
		iMeshHide(Back_Glow_In[i],false);
		iMeshHide(Front_Glow_In[i],false);
		//Update
		iMeshLocationSet(Back[i],&Back_Offset,false);
		iMeshLocationSet(Back_Glow[i],&Back_Offset,false);
		iMeshLocationSet(Back_Glow_In[i],&Back_Offset,false);
		iMeshLocationSet(Front[i],&Front_Offset,false);
		iMeshLocationSet(Front_Glow[i],&Front_Offset,false);
		iMeshLocationSet(Front_Glow_In[i],&Front_Offset,false);

		iMeshOrientationSet(Back[i],&qTireSpin,false);
		iMeshOrientationSet(Back_Glow[i],&qTireSpin,false);
		iMeshOrientationSet(Back_Glow_In[i],&qTireSpin,false);
		iMeshOrientationSet(Front[i],&qTireSpin,false);
		iMeshOrientationSet(Front_Glow[i],&qTireSpin,false);
		iMeshOrientationSet(Front_Glow_In[i],&qTireSpin,false);

		iMeshColorSet(Back_Glow[i],&cGame_Bike[gAi_Max_Count].Colour.vBikeColour,false);
		iMeshColorSet(Back_Glow_In[i],&cGame_Bike[gAi_Max_Count].Colour.vBikeColour,false);
		iMeshColorSet(Front_Glow[i],&cGame_Bike[gAi_Max_Count].Colour.vBikeColour,false);
		iMeshColorSet(Front_Glow_In[i],&cGame_Bike[gAi_Max_Count].Colour.vBikeColour,false);
	}
	//Show active
	iMeshShow(Back[ActiveModel_Player],false);
	iMeshShow(Back_Glow[ActiveModel_Player],false);
	iMeshShow(Front[ActiveModel_Player],false);
	iMeshShow(Front_Glow[ActiveModel_Player],false);
	//Show carls extra bits
	if(ActiveModel_Player==0)
	{
		iMeshShow(Front_Glow_In[ActiveModel_Player],false);
		iMeshShow(Back_Glow_In[ActiveModel_Player],false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE - TIRE - AI UPDATE
///*****************************************************************
void Mesh_Bike_Tire::Ai_Update(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1,float* fTireSpin)
{
	//-------------------------------------------------------------
	//Update
	D3DXQUATERNION qTireSpin;
	iQuaternionFromEulerAngles(&qTireSpin,*fTireSpin,0.0f,180.0f);
	iQuaternionMultiply(&qTireSpin,&qTireSpin,q1);

	D3DXVECTOR3 Back_Offset = iVectorLocationOffset(v1,q1,&Back_Pos_Offset[ActiveModel_Ai]);
	D3DXVECTOR3 Front_Offset = iVectorLocationOffset(v1,q1,&Front_Pos_Offset[ActiveModel_Ai]);

	iMeshImposterLocationSet(Back[ActiveModel_Ai],Index,&Back_Offset,false);
	iMeshImposterLocationSet(Back_Glow[ActiveModel_Ai],Index,&Back_Offset,false);
	iMeshImposterLocationSet(Back_Glow_In[ActiveModel_Ai],Index,&Back_Offset,false);
	iMeshImposterLocationSet(Front[ActiveModel_Ai],Index,&Front_Offset,false);
	iMeshImposterLocationSet(Front_Glow[ActiveModel_Ai],Index,&Front_Offset,false);
	iMeshImposterLocationSet(Front_Glow_In[ActiveModel_Ai],Index,&Front_Offset,false);

	iMeshImposterOrientationSet(Back[ActiveModel_Ai],Index,&qTireSpin,false);
	iMeshImposterOrientationSet(Back_Glow[ActiveModel_Ai],Index,&qTireSpin,false);
	iMeshImposterOrientationSet(Back_Glow_In[ActiveModel_Ai],Index,&qTireSpin,false);
	iMeshImposterOrientationSet(Front[ActiveModel_Ai],Index,&qTireSpin,false);
	iMeshImposterOrientationSet(Front_Glow[ActiveModel_Ai],Index,&qTireSpin,false);
	iMeshImposterOrientationSet(Front_Glow_In[ActiveModel_Ai],Index,&qTireSpin,false);

	iMeshImposterColorSet(Back_Glow[ActiveModel_Ai],Index,&cGame_Bike[Index].Colour.vBikeColourTarget,false);
	iMeshImposterColorSet(Back_Glow_In[ActiveModel_Ai],Index,&cGame_Bike[Index].Colour.vBikeColourTarget,false);
	iMeshImposterColorSet(Front_Glow[ActiveModel_Ai],Index,&cGame_Bike[Index].Colour.vBikeColourTarget,false);
	iMeshImposterColorSet(Front_Glow_In[ActiveModel_Ai],Index,&cGame_Bike[Index].Colour.vBikeColourTarget,false);
	//-------------------------------------------------------------
	//Show
	iMeshImposterShow(Back[ActiveModel_Ai],Index,false);
	iMeshImposterShow(Front[ActiveModel_Ai],Index,false);
	iMeshImposterShow(Back_Glow[ActiveModel_Ai],Index,false);
	iMeshImposterShow(Front_Glow[ActiveModel_Ai],Index,false);
	//Carls extras
	if(ActiveModel_Ai==0)
	{
		iMeshImposterShow(Back_Glow_In[ActiveModel_Ai],Index,false);
		iMeshImposterShow(Front_Glow_In[ActiveModel_Ai],Index,false);
	}
	//-------------------------------------------------------------
}
