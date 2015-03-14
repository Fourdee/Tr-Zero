//-----------------------------------------------------------------
// About:
//
// name: "Game_Track.cpp:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Track.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - ENVIRONMENT - TRACK - CONSTRUCTORS
///*****************************************************************
Game_Track::Game_Track(void)
{
	//-------------------------------------------------------------
	//Track Mesh
	for(int i=0;i<MAX_TRACK_MESH;i++)
	{
		Mesh_Track[i] = NULL;
		Mesh_Track_ShadowType[i] = -1;
		Mesh_Track_ShadowDoubleSided[i] = false;
	}
	//-------------------------------------------------------------
	//Showroom Mesh
	for(int i=0;i<MAX_SHOWROOM;i++)
	{
		Mesh_ShowRoom[i]	= NULL;
	}
	bShowroom				= false;
	//---------------------------------------------------------
	//Texture Pool
	for(int i=0;i<MAX_TEXTURES_TRACK;i++)
	{
		for(int j=0;j<MAX_TEXTURES_TRACK_TYPES;j++)
		{
			Texture[i][j] = NULL;
		}
	}
	//Video Texture
	VideoTexture = NULL;
	//-------------------------------------------------------------
}
Game_Track::~Game_Track(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ENVIRONMENT - TRACK - Create
///*****************************************************************
void Game_Track::Create(void)
{
	//-------------------------------------------------------------
	if(gGameState==0)
	{
		Chapter_000_Menu_Main_Create();
	}
	else if(gGameState==1)
	{
		Chapter_001_Volex_Create();
	}
	else if(gGameState==2)
	{
		Chapter_002_Silence_Create();
	}
	else if(gGameState==3)
	{
		Chapter_003_Phantom_Create();
	}
	else if(gGameState==10)
	{
		Chapter_010_Rez_Create();
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ENVIRONMENT - TRACK - UPDATE
///*****************************************************************
void Game_Track::Update(void)
{
	//-------------------------------------------------------------
	if(gGameState==0)
	{
		Chapter_000_Menu_Main_Update();
	}
	else if(gGameState==1)
	{
		Chapter_001_Volex_Update();
	}
	else if(gGameState==2)
	{
		Chapter_002_Silence_Update();
	}
	else if(gGameState==3)
	{
		Chapter_003_Phantom_Update();
	}
	else if(gGameState==10)
	{
		Chapter_010_Rez_Update();
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ENVIRONMENT - TRACK - CHAPTER - 000 - MENU MAIN - CREATE
///*****************************************************************
void Game_Track::Chapter_000_Menu_Main_Create(void)
{
 	//-------------------------------------------------------------
     //int = caster mode.
     //         0 - cast and recieve shadow (default).nww
     //         1 - recieve shadows only.
     //         2 - cast shadows only.
     //         3 - cannot cast or recieve shadows.	
	//-------------------------------------------------------------
	//Clouds
	Clouds.Create();
	//-------------------------------------------------------------
	//Create Textures
	TexturesCreate();
	//-------------------------------------------------------------
	//create meshes
	Mesh_Track[2] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_menu\\track_menu.md5mesh",gMeshSmoothing);
	Mesh_Track[4] = iMeshSubPartGet(Mesh_Track[2],0);
	Mesh_Track[8] = iMeshSubPartGet(Mesh_Track[2],2);
	Mesh_Track[1] = iMeshSubPartGet(Mesh_Track[2],3);
	Mesh_Track[7] = iMeshSubPartGet(Mesh_Track[2],4);
	Mesh_Track[6] = iMeshSubPartGet(Mesh_Track[2],5);
	Mesh_Track[5] = iMeshSubPartGet(Mesh_Track[2],6);
	Mesh_Track[3] = iMeshSubPartGet(Mesh_Track[2],1);
	Mesh_Track[0] = iMeshSubPartGet(Mesh_Track[2],7);
	///-------------------------------------------------------------
	//lighting
	iMeshDirectionalLightEnableSet(	Mesh_Track[0],false,true,false,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[0],false,false,0,false,1,false,2,false,3,false);
	iMeshDirectionalLightEnableSet(	Mesh_Track[1],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[1],false,false,0,false,1,false,2,false,3,false);
	iMeshDirectionalLightEnableSet(	Mesh_Track[2],false,true,false,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[2],false,false,0,false,1,false,2,false,3,false);
	iMeshDirectionalLightEnableSet(	Mesh_Track[3],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[3],false,false,0,false,1,false,2,false,3,false);
	iMeshDirectionalLightEnableSet(	Mesh_Track[4],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[4],false,false,0,false,1,false,2,false,3,false);
	iMeshDirectionalLightEnableSet(	Mesh_Track[5],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[5],false,false,0,false,1,false,2,false,3,false);
	iMeshDirectionalLightEnableSet(	Mesh_Track[6],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[6],false,false,0,false,1,false,2,false,3,false);
	iMeshDirectionalLightEnableSet(	Mesh_Track[7],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[7],false,false,0,false,1,false,2,false,3,false);
	iMeshDirectionalLightEnableSet(	Mesh_Track[8],false,false,false,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[8],false,false,0,false,1,false,2,false,3,false);
	///-------------------------------------------------------------
	//Grid Top Layer
	iMeshShaderNormalMapReflectSet(Mesh_Track[0],cGame_Asset_Global_Texture.Bike.EnvMap,gReflectRes,gReflectMipMap,gReflectMinRange,gReflectMaxRange,false,false);
	iMeshCullModeSet(Mesh_Track[0],D3D11_CULL_NONE);
	iMeshColorSet(Mesh_Track[0],&D3DXVECTOR3(0.15f,0.15f,0.15f),false);
	iMeshBumpScaleSet(Mesh_Track[0],0.1f,false);
	iMeshReflectionAmountSet(Mesh_Track[0],0.1f,false);
	iMeshGlowEnable(Mesh_Track[0],gGlowMeshEnable,false);
	Mesh_Track_ShadowType[0] = 1;
	///-------------------------------------------------------------
	//TrZero LOgo,
	iMeshShaderNormalMapSet(Mesh_Track[1],false);
	iMeshBumpScaleSet(Mesh_Track[1],0.1f,false);
	iMeshAlphaToleranceSet(Mesh_Track[1],0.1f,false);
	iMeshDepthBiasSet(Mesh_Track[1],-5);
	iMeshColorSet(Mesh_Track[1],&D3DXVECTOR3(4.0f,4.0f,4.0f),false);
	iMeshGlowEnable(Mesh_Track[1],gGlowMeshEnable,false);
	Mesh_Track_ShadowType[1] = 2;
	///-------------------------------------------------------------
	//Grid Bottom Layer
	iMeshShaderNormalMapReflectSet(Mesh_Track[2],cGame_Asset_Global_Texture.Bike.EnvMap,gReflectRes,gReflectMipMap,gReflectMinRange,gReflectMaxRange,false,false);
	iMeshColorSet(Mesh_Track[2],&D3DXVECTOR3(0.2f,0.2f,0.2f),false);
	iMeshBumpScaleSet(Mesh_Track[2],0.1f,false);
	iMeshReflectionAmountSet(Mesh_Track[2],0.1f,false);
	iMeshGlowEnable(Mesh_Track[2],gGlowMeshEnable,false);
	Mesh_Track_ShadowType[2] = 1;
	///-------------------------------------------------------------
	//PipeGlow
	iMeshShaderEmissiveSet(Mesh_Track[3],false);
	iMeshAlphaToleranceSet(Mesh_Track[3],0.5f,false);
	iMeshDepthBiasSet(Mesh_Track[3],-10);
	iMeshColorSet(Mesh_Track[3],&gMenuTrackColour,false);
	iMeshGlowEnable(Mesh_Track[3],gGlowMeshEnable,false);
	iMeshBlendModeSet(Mesh_Track[3],2,5,6);
	///-------------------------------------------------------------
	//WallSilver
	iMeshShaderNormalMapSet(Mesh_Track[4],false);
	iMeshColorSet(Mesh_Track[4],&D3DXVECTOR3(1.3f,1.3f,1.3f),false);
	iMeshBumpScaleSet(Mesh_Track[4],15.0f,false);
	Mesh_Track_ShadowType[4] = 0;
	Mesh_Track_ShadowDoubleSided[4] = true;
	///-------------------------------------------------------------
	//Pipe
	iMeshShaderNormalMapSet(Mesh_Track[5],false);
	iMeshBumpScaleSet(Mesh_Track[5],3.0f,false);
	iMeshColorSet(Mesh_Track[5],&D3DXVECTOR3(0.8f,0.8f,0.8f),false);
	Mesh_Track_ShadowType[5] = 0;
	///-------------------------------------------------------------
	//metal
	iMeshShaderNormalMapSet(Mesh_Track[6],false);
	iMeshBumpScaleSet(Mesh_Track[6],5.0f,false);
	iMeshDepthBiasSet(Mesh_Track[6],5);
	Mesh_Track_ShadowType[6] = 0;
	Mesh_Track_ShadowDoubleSided[6] = true;
	///-------------------------------------------------------------
	//Rock
	iMeshShaderNormalMapSet(Mesh_Track[7],false);
	iMeshBumpScaleSet(Mesh_Track[7],20.0f,false);
	Mesh_Track_ShadowType[7] = 0;
	Mesh_Track_ShadowDoubleSided[7] = true;
	///-------------------------------------------------------------
	//OE2 Logo
	iMeshShaderEmissiveSet(Mesh_Track[8],false);
	iMeshAlphaToleranceSet(Mesh_Track[8],0.2f,false);
	iMeshDepthBiasSet(Mesh_Track[8],-5);
	iMeshColorSet(Mesh_Track[8],&D3DXVECTOR3(1.3f,1.3f,1.3f),false);
	Mesh_Track_ShadowType[8] = 2;

	for(int i=0;i<MAX_000;i++)
	{
		if(Mesh_Track[i]!=NULL)
		{
			iMeshShow(Mesh_Track[i],false);
			//fog?
			if(gFog)
			{
				iMeshFogEnable(Mesh_Track[i],true,false);
				iMeshFogRangeSet(Mesh_Track[i],gFog_Min,gFog_Max,false);
				iMeshFogColorSet(Mesh_Track[i],&gFog_Colour,false);
			}
		}
	}
	//-------------------------------------------------------------
	//Showroom Mesh
	Mesh_ShowRoom[0] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_menu\\showroom\\showroom_floor.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(	Mesh_ShowRoom[0],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_ShowRoom[0],true,true,0,true,1,true,2,true,3,true);
	iMeshEulerOrientationSet(Mesh_ShowRoom[0],-90.0f,0.0f,0.0f,false);
	iMeshShaderNormalMapSet(Mesh_ShowRoom[0],false);
	iMeshReflectionAmountSet(Mesh_ShowRoom[0],0.4f,false);
	iMeshBumpScaleSet(Mesh_ShowRoom[0],0.075f,false);

	Mesh_ShowRoom[1] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_menu\\showroom\\showroom_box.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(	Mesh_ShowRoom[1],false,false,false,false,false);
	iMeshPointLightEnableSet(		Mesh_ShowRoom[1],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderEmissiveSet(Mesh_ShowRoom[1],false);
	iMeshColorSet(Mesh_ShowRoom[1],&D3DXVECTOR3(0.5f,0.5f,0.5f),false);

	Mesh_ShowRoom[2] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_menu\\showroom\\showroom_ring.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(	Mesh_ShowRoom[2],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_ShowRoom[2],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderNormalMapSet(Mesh_ShowRoom[2],false);
	iMeshBumpScaleSet(Mesh_ShowRoom[2],15.0f,false);

	Mesh_ShowRoom[3] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_menu\\showroom\\showroom_glow.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(	Mesh_ShowRoom[3],false,false,false,false,false);
	iMeshPointLightEnableSet(		Mesh_ShowRoom[3],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderEmissiveSet(Mesh_ShowRoom[3],false);
	iMeshDepthBiasSet(Mesh_ShowRoom[3],-5);
	iMeshGlowEnable(Mesh_ShowRoom[3],gGlowMeshEnable,false);
	iMeshColorSet(Mesh_ShowRoom[3],&gMenuTrackColour,false);
	iMeshAlphaToleranceSet(Mesh_ShowRoom[3],0.1f,false);
	//-------------------------------------------------------------
	//Texture Sampler
	SamplerSet();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ENVIRONMENT - TRACK - CHAPTER - 001 - VOLEX - CREATE
///*****************************************************************
void Game_Track::Chapter_001_Volex_Create(void)
{
	//-------------------------------------------------------------
	//Clouds
	Clouds.Create();
	//-------------------------------------------------------------
	//Create Textures
	TexturesCreate();
	//-------------------------------------------------------------
	//create meshes
	Mesh_Track[3] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_volex\\rock.md5mesh",0.0f);//iMeshSubPartGet(Mesh_Track[0],6);
	Mesh_Track[4] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_volex\\electric.md5mesh",gMeshSmoothing);
	Mesh_Track[6] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_volex\\metal_test.md5mesh",gMeshSmoothing);
	Mesh_Track[5] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_volex\\glow_test.md5mesh",gMeshSmoothing);
	Mesh_Track[1] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_volex\\inwall.md5mesh",gMeshSmoothing);
	Mesh_Track[2] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_volex\\outwall.md5mesh",gMeshSmoothing);
	Mesh_Track[0] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_volex\\road.md5mesh",gMeshSmoothing);
	//Mesh_Track[7] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_volex\\props.md5mesh",0.0f);
	///-------------------------------------------------------------
	//ROAD
	iMeshDirectionalLightEnableSet(	Mesh_Track[0],false,true,false,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[0],true,true,0,true,1,true,2,true,3,true);
	iMeshShaderNormalMapReflectSet(Mesh_Track[0],cGame_Asset_Global_Texture.Bike.EnvMap,gReflectRes,gReflectMipMap,gReflectMinRange,gReflectMaxRange,false,false);
	iMeshColorSet(Mesh_Track[0],&D3DXVECTOR3(1.0f*0.6f,1.0f*0.6f,1.12f*0.6f),false);
	iMeshBumpScaleSet(Mesh_Track[0],0.2f,false);
	iMeshReflectionAmountSet(Mesh_Track[0],0.1f,false);
	Mesh_Track_ShadowType[0] = 0;
	//iMeshBlendModeSet(Mesh_Track[0],1,7,8);///138 178 188
	//Mesh_Track_ShadowDoubleSided[0] = true;
	///-------------------------------------------------------------
	//Wall
	iMeshDirectionalLightEnableSet(	Mesh_Track[1],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[1],true,true,0,true,1,true,2,true,3,true);
	iMeshShaderEmissiveSet(Mesh_Track[1],false);
	iMeshColorSet(Mesh_Track[1],&D3DXVECTOR3(0.9f,0.9f,0.9f),false);
	Mesh_Track_ShadowType[1] = 0;
	///-------------------------------------------------------------
	//Outside wall
	iMeshDirectionalLightEnableSet(	Mesh_Track[2],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[2],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderNormalMapSet(Mesh_Track[2],false);
	iMeshColorSet(Mesh_Track[2],&D3DXVECTOR3(1.8f,1.8f,1.8f),false);
	iMeshBumpScaleSet(Mesh_Track[2],3.0f,false);
	Mesh_Track_ShadowType[2] = 0;
	//Mesh_Track_ShadowDoubleSided[2] = true;
	///-------------------------------------------------------------
	//ROCK
	iMeshDirectionalLightEnableSet(	Mesh_Track[3],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[3],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderNormalMapSet(Mesh_Track[3],false);
	iMeshBumpScaleSet(Mesh_Track[3],3.0f,false);
	Mesh_Track_ShadowType[3] = 0;
	///-------------------------------------------------------------
	//Electric
	iMeshDirectionalLightEnableSet(	Mesh_Track[4],false,false,false,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[4],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderEmissiveSet(Mesh_Track[4],false);
	iMeshColorSet(Mesh_Track[4],&D3DXVECTOR3(2.0f,0.7f,0.2f),false);
	iMeshAlphaToleranceSet(Mesh_Track[4],0.2f,false);
	iMeshGlowEnable(Mesh_Track[4],gGlowMeshEnable,false);
	///-------------------------------------------------------------
	//Glow
	iMeshDirectionalLightEnableSet(	Mesh_Track[5],false,false,false,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[5],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderEmissiveSet(Mesh_Track[5],false);
	iMeshDepthBiasSet(Mesh_Track[5],-2);
	iMeshAlphaToleranceSet(Mesh_Track[5],0.1f,false);
	iMeshColorSet(Mesh_Track[5],&D3DXVECTOR3(2.0f,0.5f,0.1f),false);
	iMeshGlowEnable(Mesh_Track[5],gGlowMeshEnable,false);
	///-------------------------------------------------------------
	//Metal
	iMeshDirectionalLightEnableSet(	Mesh_Track[6],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[6],true,true,0,true,1,true,2,true,3,true);
	iMeshColorSet(Mesh_Track[6],&D3DXVECTOR3(1.1f,1.1f,1.15f),false);
	iMeshShaderSmoothReflectSet(Mesh_Track[6],cGame_Asset_Global_Texture.Bike.EnvMap,gReflectRes,gReflectMipMap,gReflectMinRange,gReflectMaxRange,false,false);
	iMeshReflectionAmountSet(Mesh_Track[6],0.11f,false);
	Mesh_Track_ShadowType[6] = 0;
	/////-------------------------------------------------------------
	////props
	//iMeshDirectionalLightEnableSet(	Mesh_Track[7],false,false,true,false,false);
	//iMeshPointLightEnableSet(		Mesh_Track[7],false,false,0,false,1,false,2,false,3,false);
	//iMeshShaderNormalMapSet(Mesh_Track[7],false);
	////iMeshColorSet(Mesh_Track[7],&D3DXVECTOR3(1.8f,1.8f,1.8f),false);
	//iMeshBumpScaleSet(Mesh_Track[7],3.0f,false);
	//Mesh_Track_ShadowType[7] = 0;
	////Mesh_Track_ShadowDoubleSided[2] = true;
	/////-------------------------------------------------------------
	////props glow
	//iMeshDirectionalLightEnableSet(	Mesh_Track[7],false,false,true,false,false);
	//iMeshPointLightEnableSet(		Mesh_Track[7],false,false,0,false,1,false,2,false,3,false);
	//iMeshShaderNormalMapSet(Mesh_Track[7],false);
	////iMeshColorSet(Mesh_Track[7],&D3DXVECTOR3(1.8f,1.8f,1.8f),false);
	//iMeshBumpScaleSet(Mesh_Track[7],3.0f,false);

	for(int i=0;i<MAX_001;i++)
	{
		if(Mesh_Track[i]!=NULL)
		{
			iMeshShow(Mesh_Track[i],false);
			//fog?
			if(gFog)
			{
				iMeshFogEnable(Mesh_Track[i],true,false);
				iMeshFogRangeSet(Mesh_Track[i],gFog_Min,gFog_Max,false);
				iMeshFogColorSet(Mesh_Track[i],&gFog_Colour,false);
			}
		}
	}
	//-------------------------------------------------------------
	//Texture Sampler
	SamplerSet();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ENVIRONMENT - TRACK - CHAPTER - 002 - SILENCE - CREATE
///*****************************************************************
void Game_Track::Chapter_002_Silence_Create(void)
{
	//-------------------------------------------------------------
	//Clouds
	Clouds.Create();
	//-------------------------------------------------------------
	//Create Textures
	TexturesCreate();
	//-------------------------------------------------------------
	//create mesh
	///InsideTunnel
	Mesh_Track[0] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\tracks\\track_silence\\world_tunnel.bin");
	iMeshDirectionalLightEnableSet(	Mesh_Track[0],false,false,false,true,false);
	iMeshPointLightEnableSet(		Mesh_Track[0],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderNormalMapSet(Mesh_Track[0],false);
	iMeshBumpScaleSet(Mesh_Track[0],1.0f,false);
	//Mesh_Track_ShadowType[0] = 0;
	///-------------------------------------------------------------
	///Water
	Mesh_Track[1] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\tracks\\track_silence\\world_water.bin");
	iMeshDirectionalLightEnableSet(	Mesh_Track[1],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[1],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderNormalMapSet(Mesh_Track[1],false);
	iMeshBumpScaleSet(Mesh_Track[1],15.0f,false);
	Mesh_Track_ShadowType[1] = 1;
	///-------------------------------------------------------------
	///Road
	Mesh_Track[2] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\tracks\\track_silence\\road.bin");
	iMeshDirectionalLightEnableSet(	Mesh_Track[2],false,true,false,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[2],true,true,0,true,1,true,2,true,3,true);
	iMeshShaderNormalMapSet(Mesh_Track[2],false);
	iMeshBumpScaleSet(Mesh_Track[2],1.0f,false);
	iMeshTextureRotationSet(Mesh_Track[2],-180.0f,false);
	Mesh_Track_ShadowType[2] = 0;
	Mesh_Track_ShadowDoubleSided[2] = true;
	///-------------------------------------------------------------
	///building
	Mesh_Track[3] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\tracks\\track_silence\\world_building.bin");
	iMeshDirectionalLightEnableSet(	Mesh_Track[3],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[3],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderNormalMapSet(Mesh_Track[3],false);
	iMeshColorSet(Mesh_Track[3],&D3DXVECTOR3(1.1f,1.1f,1.1f),false);
	iMeshBumpScaleSet(Mesh_Track[3],20.0f,false);
	Mesh_Track_ShadowType[3] = 0;
	Mesh_Track_ShadowDoubleSided[3] = true;
	///-------------------------------------------------------------
	///Inside Mountain
	Mesh_Track[4] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\tracks\\track_silence\\world_mountain.bin");
	iMeshDirectionalLightEnableSet(	Mesh_Track[4],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[4],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderNormalMapSet(Mesh_Track[4],false);
	iMeshBumpScaleSet(Mesh_Track[4],10.0f,false);
	Mesh_Track_ShadowType[4] = 0;
	Mesh_Track_ShadowDoubleSided[4] = true;
	///-------------------------------------------------------------
	///TracksideLights
	Mesh_Track[5] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\tracks\\track_silence\\world_roadside.bin");
	iMeshDirectionalLightEnableSet(	Mesh_Track[5],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[5],true,true,0,true,1,true,2,true,3,true);
	iMeshShaderNormalMapSet(Mesh_Track[5],false);
	Mesh_Track_ShadowType[5] = 0;
	///-------------------------------------------------------------
	///TrackWall
	Mesh_Track[6] = iMeshFromBinaryCreate("trzero_res\\md5mesh\\tracks\\track_silence\\world_wall.bin");
	iMeshDirectionalLightEnableSet(	Mesh_Track[6],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[6],true,true,0,true,1,true,2,true,3,true);
	iMeshShaderNormalMapSet(Mesh_Track[6],false);
	iMeshBumpScaleSet(Mesh_Track[6],2.0f,false);
	Mesh_Track_ShadowType[6] = 0;
	Mesh_Track_ShadowDoubleSided[6] = true;


	for(int i=0;i<MAX_002;i++)
	{
		if(Mesh_Track[i]!=NULL)
		{
			iMeshShow(Mesh_Track[i],false);
			//fog?
			if(gFog)
			{
				iMeshFogEnable(Mesh_Track[i],true,false);
				iMeshFogRangeSet(Mesh_Track[i],gFog_Min,gFog_Max,false);
				iMeshFogColorSet(Mesh_Track[i],&gFog_Colour,false);
			}
		}
	}

	//Should be this for all mesh creates, however, 
	//OE2 shows a debug wire cube when the mesh should be NULL, but clearly isnt being set to NULL.

	//for(int i=0;i<MAX_TRACK_MESH;i++)
	//{
	//	if(Mesh_Track[i]!=NULL)
	//	{
	//		iMeshShow(Mesh_Track[i],false);
	//		//fog?
	//		if(gFog)
	//		{
	//			iMeshFogEnable(Mesh_Track[i],true,false);
	//			iMeshFogRangeSet(Mesh_Track[i],gFog_Min,gFog_Max,false);
	//			iMeshFogColorSet(Mesh_Track[i],&gFog_Colour,false);
	//		}
	//	}
	//}
	//-------------------------------------------------------------
	//Texture Sampler
	SamplerSet();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ENVIRONMENT - TRACK - CHAPTER - 003 - PHANTOM - CREATE
///*****************************************************************
void Game_Track::Chapter_003_Phantom_Create(void)
{
	//-------------------------------------------------------------
	//Clouds
	Clouds.Create();
	//-------------------------------------------------------------
	//Create Textures
	TexturesCreate();
	//-------------------------------------------------------------
	//create mesh
	///-------------------------------------------------------------
	//Road
	Mesh_Track[0] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_phantom\\road.md5mesh",1.0f);
	iMeshDirectionalLightEnableSet(	Mesh_Track[0],false,true,false,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[0],true,true,0,true,1,true,2,true,3,true);
	iMeshShaderNormalMapSet(Mesh_Track[0],false);
	iMeshColorSet(Mesh_Track[0],&D3DXVECTOR3(0.8f,0.8f,0.8f),false);
	iMeshBumpScaleSet(Mesh_Track[0],0.1f,false);
	///-------------------------------------------------------------
	//World Test
	Mesh_Track[1] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_phantom\\world.md5mesh",0.0f);
	iMeshDirectionalLightEnableSet(	Mesh_Track[1],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[1],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderNormalMapSet(Mesh_Track[1],false);
	iMeshBumpScaleSet(Mesh_Track[1],2.0f,false);

	for(int i=0;i<MAX_003;i++)
	{
		if(Mesh_Track[i]!=NULL)
		{
			iMeshShow(Mesh_Track[i],false);
			//fog?
			if(gFog)
			{
				iMeshFogEnable(Mesh_Track[i],true,false);
				iMeshFogRangeSet(Mesh_Track[i],gFog_Min,gFog_Max,false);
				iMeshFogColorSet(Mesh_Track[i],&gFog_Colour,false);
			}
		}
	}
	//-------------------------------------------------------------
	//Texture Sampler
	SamplerSet();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ENVIRONMENT - TRACK - CHAPTER - 010 - REZ - CREATE
///*****************************************************************
void Game_Track::Chapter_010_Rez_Create(void)
{
	//-------------------------------------------------------------
	//Clouds
	Clouds.Create();
	//-------------------------------------------------------------
	//Create Textures
	TexturesCreate();
	//-------------------------------------------------------------
	//create meshes
	int Index = 0;
	///-------------------------------------------------------------
	//Road
	Mesh_Track[Index] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_rez\\road.md5mesh",1.0f);
	iMeshDirectionalLightEnableSet(	Mesh_Track[Index],false,true,false,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[Index],true,true,0,true,1,true,2,true,3,true);
	iMeshShaderNormalMapReflectSet(Mesh_Track[Index],cGame_Asset_Global_Texture.Bike.EnvMap,gReflectRes,gReflectMipMap,gReflectMinRange,gReflectMaxRange,false,false);
	iMeshColorSet(Mesh_Track[Index],&D3DXVECTOR3(0.8f,0.8f,0.8f),false);
	iMeshBumpScaleSet(Mesh_Track[Index],0.0f,false);
	iMeshBlendModeSet(Mesh_Track[Index],1,7,8);///138 178 188
	iMeshReflectionAmountSet(Mesh_Track[Index],0.1f,false);
	Mesh_Track_ShadowType[Index] = 1;
	Index++;
	///-------------------------------------------------------------
	//walls (track walls)
	Mesh_Track[Index] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_rez\\walls.md5mesh",0.0f);
	iMeshDirectionalLightEnableSet(	Mesh_Track[Index],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[Index],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderNormalMapSet(Mesh_Track[Index],false);
	iMeshBumpScaleSet(Mesh_Track[Index],5.0f,false);
	iMeshBlendModeSet(Mesh_Track[Index],1,7,8);///138 178 188
	iMeshCullModeSet(Mesh_Track[Index],D3D11_CULL_NONE);
	Mesh_Track_ShadowType[Index] = 2;
	Mesh_Track_ShadowDoubleSided[Index] = true;
	Index++;
	///-------------------------------------------------------------
	//walls trim (track walls 2)
	Mesh_Track[Index] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_rez\\walls_trim.md5mesh",0.0f);
	iMeshDirectionalLightEnableSet(	Mesh_Track[Index],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[Index],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderNormalMapSet(Mesh_Track[Index],false);
	iMeshBumpScaleSet(Mesh_Track[Index],5.0f,false);
	iMeshBlendModeSet(Mesh_Track[Index],1,7,8);///138 178 188
	iMeshCullModeSet(Mesh_Track[Index],D3D11_CULL_NONE);
	Mesh_Track_ShadowType[Index] = 2;
	Mesh_Track_ShadowDoubleSided[Index] = true;
	Index++;
	///-------------------------------------------------------------
	//Big Glow Walls
	Mesh_Track[Index] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_rez\\bigglowwall.md5mesh",0.0f);
	iMeshDirectionalLightEnableSet(	Mesh_Track[Index],false,false,false,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[Index],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderEmissiveABMapBlendSet(Mesh_Track[Index],false);
	iMeshAlphaToleranceSet(Mesh_Track[Index],0.025f,false);
	Index++;
	///-------------------------------------------------------------
	//Top
	Mesh_Track[Index] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_rez\\top.md5mesh",0.0f);
	iMeshDirectionalLightEnableSet(	Mesh_Track[Index],false,false,false,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[Index],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderEmissiveABMapBlendSet(Mesh_Track[Index],false);
	iMeshAlphaToleranceSet(Mesh_Track[Index],0.025f,false);
	Index++;
	///-------------------------------------------------------------
	//Hanging Glow
	Mesh_Track[Index] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_rez\\hanging_glow.md5mesh",0.0f);
	iMeshDirectionalLightEnableSet(	Mesh_Track[Index],false,false,false,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[Index],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderEmissiveSet(Mesh_Track[Index],false);
	iMeshBlendEnableSet(Mesh_Track[Index],false);
	iMeshAlphaToleranceSet(Mesh_Track[Index],0.025f,false);
	iMeshCullModeSet(Mesh_Track[Index],D3D11_CULL_NONE);
	iMeshGlowEnable(Mesh_Track[Index],gGlowMeshEnable,false);
	Index++;
	///-------------------------------------------------------------
	//Fixture A
	Mesh_Track[Index] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_rez\\fixture_a.md5mesh",0.0f);
	iMeshDirectionalLightEnableSet(	Mesh_Track[Index],false,false,false,true,false);
	iMeshPointLightEnableSet(		Mesh_Track[Index],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderNormalMapSet(Mesh_Track[Index],false);
	iMeshBumpScaleSet(Mesh_Track[Index],2.0f,false);
	Mesh_Track_ShadowType[Index] = 0;
	Index++;
	///-------------------------------------------------------------
	//Central Core
	Mesh_Track[Index] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_rez\\central_core.md5mesh",0.0f);
	iMeshDirectionalLightEnableSet(	Mesh_Track[Index],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[Index],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderNormalMapSet(Mesh_Track[Index],false);
	iMeshBumpScaleSet(Mesh_Track[Index],2.0f,false);
	//iMeshAlphaToleranceSet(Mesh_Track[Index],0.025f,false);
	//iMeshGlowEnable(Mesh_Track[Index],gGlowMeshEnable,false);
	Mesh_Track_ShadowType[Index] = 0;
	Index++;
	///-------------------------------------------------------------
	//Fixture B
	Mesh_Track[Index] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_rez\\fixture_a_b.md5mesh",0.0f);
	iMeshDirectionalLightEnableSet(	Mesh_Track[Index],false,false,false,true,false);
	iMeshPointLightEnableSet(		Mesh_Track[Index],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderNormalMapSet(Mesh_Track[Index],false);
	iMeshBumpScaleSet(Mesh_Track[Index],2.0f,false);
	iMeshCullModeSet(Mesh_Track[Index],D3D11_CULL_NONE);
	Mesh_Track_ShadowType[Index] = 0;
	Index++;
	///-------------------------------------------------------------
	//Spinning Glow
	Mesh_Track[Index] = iMeshCreate("trzero_res\\md5mesh\\tracks\\track_rez\\spinning.md5mesh",0.0f);
	iMeshDirectionalLightEnableSet(	Mesh_Track[Index],false,false,true,false,false);
	iMeshPointLightEnableSet(		Mesh_Track[Index],false,false,0,false,1,false,2,false,3,false);
	iMeshShaderNormalMapSet(Mesh_Track[Index],false);
	iMeshBumpScaleSet(Mesh_Track[Index],2.0f,false);
	iMeshAlphaToleranceSet(Mesh_Track[Index],0.025f,false);
	iMeshGlowEnable(Mesh_Track[Index],gGlowMeshEnable,false);
	Index++;

	for(int i=0;i<MAX_010;i++)
	{
		if(Mesh_Track[i]!=NULL)
		{
			iMeshShow(Mesh_Track[i],false);
			//fog?
			if(gFog)
			{
				iMeshFogEnable(Mesh_Track[i],true,false);
				iMeshFogRangeSet(Mesh_Track[i],gFog_Min,gFog_Max,false);
				iMeshFogColorSet(Mesh_Track[i],&gFog_Colour,false);
			}
		}
	}
	//-------------------------------------------------------------
	//Texture Sampler
	SamplerSet();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ENVIRONMENT - TRACK - SAMPLER SET
///*****************************************************************
void Game_Track::SamplerSet(void)
{
	//-------------------------------------------------------------
	//Clouds
	Clouds.SamplerSet();
	//-------------------------------------------------------------
	//Texture Pool
	for(int i=0;i<MAX_TEXTURES_TRACK;i++)
	{
		for(int j=0;j<MAX_TEXTURES_TRACK_TYPES;j++)
		{
			//Texture in use?
			if(Texture[i][j]!=NULL)
			{
				cGame_Texture2D_Sampler.WrapSet(Texture[i][j]);
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ENVIRONMENT - TRACK - TEXTURES CREATE
///*****************************************************************
void Game_Track::TexturesCreate(void)
{
	//-------------------------------------------------------------
	int Index = 0;
	//-------------------------------------------------------------
	//menu main
	if(gGameState==0)
	{
		//-------------------------------------------------------------
		//Textures (mesh)(type) - 0=dm/em 1=nm 2=sm 3=rm
		///0 Grid Top Layer
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\track_menu\\grid_alpha.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_menu\\grid.dds");
		Texture[Index][3] = iTexture2DCreate("trzero_res\\textures\\reflect_map\\grid.dds");
		Index++;
		///1 Tr-Zero Logo
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\track_menu\\chevron.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_menu\\grid.dds");
		Index++;
		///2 Grid Bottom Layer
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\track_menu\\grid.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_menu\\grid.dds");
		Texture[Index][3] = iTexture2DCreate("trzero_res\\textures\\reflect_map\\grid.dds");
		Index++;
		///3 Pipe Glow
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\track_menu\\pipeglow.dds");
		Index++;
		///4 Walls
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_menu\\Wall_Silver.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_menu\\Wall_Silver.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_menu\\Wall_Silver.dds");
		Index++;
		///5 Pipe
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_menu\\pipe.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_menu\\pipe.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_menu\\pipe.dds");
		Index++;
		///6 Metal
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_menu\\Metal.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_menu\\Metal.dds");
		Index++;
		///7 Rock
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_menu\\Rock2.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_menu\\Rock2.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_menu\\rock.dds");
		Index++;
		/////8 Video Texture
		//VideoTexture = iTexture2DVideoCreate("trzero_res\\video\\OE2_Logo_480p.flv");
		////iTexture2DVideoAlphaEnable(VideoTexture,true);
		//iTexture2DVideoPlay(VideoTexture,60.0f,true);

		//Texture[Index][0] = iTexture2DVideoHandleGet(VideoTexture);
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_menu\\showroom_floor.dds");
		Index++;

		///10 Showroom Floor
		Index = 10;
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_menu\\showroom_floor.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_menu\\showroom_floor.dds");
		Index++;
		///11+ Showroom Extras (uses textures above)
	}
	//VOLEX
	else if(gGameState==1)
	{
		//-------------------------------------------------------------
		//Textures (mesh)(type) - 0=dm/em 1=nm 2=sm 3=rm
		///0 Road
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_volex\\road.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_volex\\road.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_volex\\road.dds");
		Index++;
		///1 Inner Wall
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_volex\\wall_test.dds");
		Index++;
		///2 Outside Wall
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_volex\\outsidewall.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_volex\\outside_wall.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_volex\\outside_wall.dds");
		Index++;
		///3 Rock
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_volex\\rock.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_volex\\rock.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_volex\\rock_dry.dds");
		Index++;
		///4 Electric
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_volex\\electric.dds");
		Index++;
		///5 Glow
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\track_volex\\em_alpha.dds");
		Index++;
		///6 Metal
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_volex\\metal.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_volex\\metal.dds");
		Index++;
		/////7 Digital Props
		//Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\Digital_Props\\digital_dm.dds");
		//Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\Digital_Props\\digital_nm.dds");
		//Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\Digital_Props\\digital_sm.dds");
		//Index++;
	}
	//Silence
	else if(gGameState==2)
	{
		//-------------------------------------------------------------
		//Textures (mesh)(type) - 0=dm/em 1=nm 2=sm 3=rm
		///0 Tunnel
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_silence\\tunnel.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_silence\\tunnel.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_silence\\tunnel.dds");
		Index++;
		///1 Water
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_silence\\water.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_silence\\water.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_silence\\water.dds");
		Index++;
		///2 Road
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_silence\\road.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_silence\\road.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_silence\\road.dds");
		Index++;
		///3 Building
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_silence\\building.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_silence\\building.dds");
		Index++;
		///4 Mountain
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_silence\\rock.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_silence\\rock.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_silence\\rock.dds");
		Index++;
		///5 Roadside Lights Metal
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_silence\\metal.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_silence\\Metal.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_silence\\Metal.dds");
		Index++;
		///6 Track Walls
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_silence\\wall.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_silence\\wall.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_silence\\wall.dds");
		Index++;
		/////7 Digital Props
		//Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_silence\\digital.dds");
		//Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_silence\\digital.dds");
		//Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_silence\\digital.dds");
		//Index++;
	}
	//Phantom
	else if(gGameState==3)
	{
		///0 Road
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_phantom\\road.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_phantom\\road.dds");
		Index++;
	}
	//Rez
	else if(gGameState==10)
	{
		///0 Road
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_rez\\road.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_rez\\road.dds");
		Index++;
		///1 walls
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_rez\\Rez_TrimBumpHGlow.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_rez\\Rez_TrimBumpHGlow.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_rez\\Rez_TrimBumpHGlow.dds");
		Index++;
		///2 walls trim
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_rez\\Rez_TrimBumpHGlow.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_rez\\Rez_TrimBumpHGlow.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_rez\\Rez_TrimBumpHGlow.dds");
		Index++;
		///3 BigGlowWalls
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\track_rez\\Rez_BigGlowWallsA.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\track_rez\\Rez_BigGlowWallsB.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\track_rez\\Rez_BigGlowWallsC.dds");
		Index++;
		///4 top
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\track_rez\\Rez_Trestles_emiA.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\track_rez\\Rez_Trestles_emiB.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\track_rez\\Rez_Trestles_emiC.dds");
		Index++;
		///5 Hanging Glow
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_rez\\Rez_TrimBumpHGlow.dds");
		Index++;
		///6 Fixture A
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_rez\\Rez_FixtureA.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_rez\\Rez_FixtureA.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_rez\\Rez_FixtureA.dds");
		Index++;
		///7 Central Core
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_rez\\Rez_CentralCore_glow.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_rez\\Rez_CentralCore_glow.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_rez\\Rez_CentralCore_glow.dds");
		Index++;
		///8 Fixture A_B
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_rez\\Rez_FixtureA_B.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_rez\\Rez_FixtureA.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_rez\\Rez_FixtureA.dds");
		Index++;
		///9 Hanging Glow
		Texture[Index][0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\track_rez\\Rez_FloatingFixture_emi.dds");
		Texture[Index][1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\track_rez\\Rez_FloatingFixture_emi.dds");
		Texture[Index][2] = iTexture2DCreate("trzero_res\\textures\\specular_map\\track_rez\\Rez_FloatingFixture_emi.dds");
		Index++;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ENVIRONMENT - TRACK - TEXTURES DESTROY
///*****************************************************************
void Game_Track::TexturesDestroy(void)
{
	//-------------------------------------------------------------
	//Texture Pool
	for(int i=0;i<MAX_TEXTURES_TRACK;i++)
	{
		for(int j=0;j<MAX_TEXTURES_TRACK_TYPES;j++)
		{
			if(Texture[i][j]!=NULL)
			{
				iTexture2DDestroy(Texture[i][j]);
			}
		}
	}
	//-------------------------------------------------------------
	//Video Texture
	//if(VideoTexture!=NULL)
	//{
	//	iTexture2DVideoDestroy(VideoTexture);
	//}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ENVIRONMENT - TRACK - CHAPTER - 000 - UPDATE
///*****************************************************************
void Game_Track::Chapter_000_Menu_Main_Update(void)
{
	//-------------------------------------------------------------
	//Shader Update
	//-------------------------------------------------------------
	for(int i=0;i<MAX_000;i++)
	{
		if(i==0)
		{
			//---------------------------------------------------------
			iMeshShaderNormalMapReflRefrTextureUpdate(Mesh_Track[i],
												  Texture[i][0],
												  Texture[i][1],
												  NULL,
												  Texture[i][3],
												  &D3DXVECTOR2(1.0f,1.0f),
												  &cGame_Camera.vCamOutput,
												  //&D3DXVECTOR3(0.0f,0.5f,0.0f),
												  false);
		}
		else if(i==1)
		{
			//-----------------------------------------------------
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
												  Texture[i][0],
												  Texture[i][1],
												  NULL,
											  &D3DXVECTOR2(1.0f,1.0f),
											  false);
		}
		else if(i==2)
		{
			//-----------------------------------------------------
			iMeshShaderNormalMapReflRefrTextureUpdate(Mesh_Track[i],
												  Texture[i][0],
												  Texture[i][1],
												  NULL,
												  Texture[i][3],
												  &D3DXVECTOR2(1.0f,1.0f),
												  &cGame_Camera.vCamOutput,
												  false);
		}
		else if(i==3)
		{
			//-----------------------------------------------------
			iMeshColorSet(Mesh_Track[i],&gMenuTrackColour,false);
			iMeshShaderEmissiveTextureUpdate(Mesh_Track[i],
											 Texture[i][0],
											 &D3DXVECTOR2(1.0f,1.0f),
											 false);
		}
		else if(i==4)
		{
			//-----------------------------------------------------
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
												Texture[i][0],
												Texture[i][1],
												Texture[i][2],
												&D3DXVECTOR2(1.25f,1.25f),
												false);
		}
		else if(i==5)
		{
			//-----------------------------------------------------
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
												Texture[i][0],
												Texture[i][1],
												Texture[i][2],
											  &D3DXVECTOR2(1.0f,1.0f),
											  false);
		}
		else if(i==6)
		{
			//-----------------------------------------------------
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
												Texture[i][0],
												Texture[i][1],
											  NULL,
											  &D3DXVECTOR2(1.0f,1.0f),
											  false);
		}
		else if(i==7)
		{
			//-----------------------------------------------------
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
												Texture[i][0],
												Texture[i][1],
											  Texture[i][2],
											  &D3DXVECTOR2(1.0f,1.0f),
											  false);
		}
		else if(i==8)
		{
			//-----------------------------------------------------
			iMeshShaderEmissiveTextureUpdate(Mesh_Track[i],
											Texture[i][0],
											 &D3DXVECTOR2(1.0f,1.0f),
											 false);
		}
	}
	//-------------------------------------------------------------
	//Showroom
	//if(bShowroom)
	//{
		for(int i=0;i<MAX_SHOWROOM;i++)
		{
			//-----------------------------------------------------
			if(i==0)
			{
				iMeshShaderNormalMapTextureUpdate(Mesh_ShowRoom[i],
															Texture[10][0],
															Texture[10][1],
															  NULL,
															  &D3DXVECTOR2(8.0f,8.0f),
															  false);
			}
			//-----------------------------------------------------
			else if(i==1)
			{
				iMeshShaderEmissiveTextureUpdate(Mesh_ShowRoom[i],
												Texture[4][0],
												 &D3DXVECTOR2(1.0f,1.0f),
												 false);
			}
			//-----------------------------------------------------
			else if(i==2)
			{
				iMeshShaderNormalMapTextureUpdate(Mesh_ShowRoom[i],
												Texture[4][0],
												Texture[4][1],
												  NULL,
												  &D3DXVECTOR2(1.0f,1.0f),
												  false);
			}
			//-----------------------------------------------------
			else if(i==3)
			{
				iMeshColorSet(Mesh_ShowRoom[i],&gMenuTrackColour,false);
				iMeshTexturePanSet(Mesh_ShowRoom[i],&D3DXVECTOR2(0.0f,gTexturePan_Slow),&D3DXVECTOR2(0.0f,0.0f),false);
				iMeshShaderEmissiveTextureUpdate(Mesh_ShowRoom[i],
												Texture[3][0],
												 &D3DXVECTOR2(1.0f,1.0f),
												 false);
			}
		}
	//}
	//-------------------------------------------------------------
	//Clouds
	Clouds.Update();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ENVIRONMENT - TRACK - CHAPTER - 001 - UPDATE
///*****************************************************************
void Game_Track::Chapter_001_Volex_Update(void)
{
	//-------------------------------------------------------------
	//Shader Update
	for(int i=0;i<MAX_001;i++)
	{
		if(i==0)
		{
			//---------------------------------------------------------
			iMeshShaderNormalMapReflRefrTextureUpdate(Mesh_Track[i],
														Texture[i][0],
														Texture[i][1],
														Texture[i][2],
														NULL,
														&D3DXVECTOR2(8.0f,1.0f),
														&cGame_Camera.vCamOutput,
														false);
        }
		else if(i==1)
		{
			//-----------------------------------------------------
			iMeshShaderEmissiveTextureUpdate(Mesh_Track[i],
											 Texture[i][0],
											 &D3DXVECTOR2(1.0f,1.0f),
											 false);
		}
		else if(i==2)
		{
			//-----------------------------------------------------
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
											 Texture[i][0],
											 Texture[i][1],
											 Texture[i][2],
											 &D3DXVECTOR2(1.0f,1.0f),
											 false);
		}
		else if(i==3)
		{
			//-----------------------------------------------------
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
											  Texture[i][0],
											  Texture[i][1],
											  Texture[i][2],
											  &D3DXVECTOR2(2.0f,2.0f),
											  false);
		}
		else if(i==4)
		{
			//-----------------------------------------------------
			iMeshShaderEmissiveTextureUpdate(Mesh_Track[i],
											 Texture[i][0],
											 &D3DXVECTOR2(1.0f,1.0f),
											 false);
		}
		else if(i==5)
		{
			//-----------------------------------------------------
			iMeshShaderEmissiveTextureUpdate(Mesh_Track[i],
											 Texture[i][0],
											 &D3DXVECTOR2(1.0f,1.0f),
											 false);
		}
		else if(i==6)
		{
			//-----------------------------------------------------
			iMeshShaderSmoothReflRefrTextureUpdate(Mesh_Track[i],
														Texture[i][0],
														Texture[i][1],
														NULL,
														&D3DXVECTOR2(1.0f,1.0f),
														&cGame_Camera.vCamOutput,
														false);
		}
		//else if(i==7)
		//{
		//	//digital props
		//	iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
		//												Texture[i][0],
		//												Texture[i][1],
		//												Texture[i][2],
		//												&D3DXVECTOR2(1.0f,1.0f),
		//												false);
		//}
	}
	//-------------------------------------------------------------
	//Clouds
	Clouds.Update();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ENVIRONMENT - TRACK - CHAPTER - 002 - UPDATE
///*****************************************************************
void Game_Track::Chapter_002_Silence_Update(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<MAX_002;i++)
	{
		if(i==0)
		{
			//InsideTunnel
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
														Texture[i][0],
														Texture[i][1],
														Texture[i][2],
														&D3DXVECTOR2(1.0f,1.0f),
														false);
		}
		else if(i==1)
		{
			//water
			iMeshTexturePanSet(Mesh_Track[i],&D3DXVECTOR2(gTexturePan_Slow,-gTexturePan_Slow),&D3DXVECTOR2(0.0f,0.0f),false);
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
														Texture[i][0],
														Texture[i][1],
														Texture[i][2],
														&D3DXVECTOR2(1.0f,1.0f),
														false);
		}
		else if(i==2)
		{
			//Road
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
														Texture[i][0],
														Texture[i][1],
														Texture[i][2],
														&D3DXVECTOR2(8.0f,1.0f),
														false);
		}
		else if(i==3)
		{
			//building
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
														Texture[i][0],
														Texture[i][1],
														NULL,
														&D3DXVECTOR2(1.0f,1.0f),
														false);
		}
		else if(i==4)
		{
			//Inside Mountain
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
														Texture[i][0],
														Texture[i][1],
														Texture[i][2],
														&D3DXVECTOR2(1.0f,1.0f),
														false);
		}
		else if(i==5)
		{
			//Roadside Lights
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
														Texture[i][0],
														Texture[i][1],
														Texture[i][2],
														&D3DXVECTOR2(1.0f,1.0f),
														false);
		}
		else if(i==6)
		{
			//TrackWall
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
														Texture[i][0],
														Texture[i][1],
														Texture[i][2],
														&D3DXVECTOR2(1.0f,1.0f),
														false);
		}
		//else if(i==7)
		//{
		//	//Digital Props
		//	iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
		//												Texture[i][0],
		//												Texture[i][1],
		//												Texture[i][2],
		//												&D3DXVECTOR2(1.0f,1.0f),
		//												false);
		//}
	}
	//-------------------------------------------------------------
	//Clouds
	Clouds.Update();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ENVIRONMENT - TRACK - CHAPTER - 003 - UPDATE
///*****************************************************************
void Game_Track::Chapter_003_Phantom_Update(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<MAX_003;i++)
	{
		if(i==0)
		{
			//-----------------------------------------------------
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
											  Texture[i][0],
											  Texture[i][1],
											  NULL,
											  &D3DXVECTOR2(1.0f,1.0f),
											  false);
		}
		else if(i==1)
		{
			//-----------------------------------------------------
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
											  NULL,
											  NULL,
											  NULL,
											  &D3DXVECTOR2(1.0f,1.0f),
											  false);
		}
	}
	//-------------------------------------------------------------
	//Clouds
	Clouds.Update();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ENVIRONMENT - TRACK - CHAPTER - 010 - UPDATE
///*****************************************************************
void Game_Track::Chapter_010_Rez_Update(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<MAX_010;i++)
	{
		if(i==0)
		{
			iMeshShaderNormalMapReflRefrTextureUpdate(Mesh_Track[i],
												  Texture[i][0],
												  Texture[i][1],
												  NULL,
												  NULL,
												  &D3DXVECTOR2(1.0f,1.0f),
												  &cGame_Camera.vCamOutput,
												  //&cGame_Bike[gAi_Max_Count].Manager.vScanDownCp,
												  //&D3DXVECTOR3(0.0f,0.5f,0.0f),
												  false);
		}
		else if(i==1)
		{
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
												  Texture[i][0],
												  Texture[i][1],
												  Texture[i][2],
											  &D3DXVECTOR2(1.0f,1.0f),
											  false);
		}
		else if(i==2)
		{
			iMeshTexturePanSet(Mesh_Track[i],&D3DXVECTOR2(-gTexturePan_Slow,0.0f),&D3DXVECTOR2(0.0f,0.0f),false);
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
												  Texture[i][0],
												  Texture[i][1],
												  Texture[i][2],
											  &D3DXVECTOR2(1.0f,1.0f),
											  false);
		}
		///Big Glow walls
		else if(i==3)
		{
			iMeshTexturePanSet(Mesh_Track[i],&D3DXVECTOR2(0.0f,0.0f),&D3DXVECTOR2(0.0f,-gTexturePan_Slow),false);
			iMeshShaderEmissiveABMapBlendTextureUpdate(Mesh_Track[i],
											 Texture[i][0],
											 &D3DXVECTOR2(1.0f,1.0f),
											 Texture[i][1],
											 &D3DXVECTOR2(1.0f,1.0f),
											 Texture[i][2],
											 false);
		}
		else if(i==4)
		{
			iMeshTexturePanSet(Mesh_Track[i],&D3DXVECTOR2(0.0f,-gTexturePan_Med),&D3DXVECTOR2(0.0f,0.0f),false);
			iMeshShaderEmissiveABMapBlendTextureUpdate(Mesh_Track[i],
											 Texture[i][0],
											 &D3DXVECTOR2(1.0f,1.0f),
											 Texture[i][1],
											 &D3DXVECTOR2(1.0f,1.0f),
											 Texture[i][2],
											 false);
		}
		else if(i==5)
		{
			iMeshTexturePanSet(Mesh_Track[i],&D3DXVECTOR2(-gTexturePan_Slow,0.0f),&D3DXVECTOR2(0.0f,0.0f),false);
			iMeshShaderEmissiveTextureUpdate(Mesh_Track[i],
											 Texture[i][0],
											 &D3DXVECTOR2(1.0f,1.0f),
											 false);
		}
		///Fixture A
		else if(i==6)
		{
			//iMeshTexturePanSet(Mesh_Track[i],&D3DXVECTOR2(-gTexturePan_Slow,0.0f),&D3DXVECTOR2(0.0f,0.0f),false);
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
												  Texture[i][0],
												  Texture[i][1],
												  Texture[i][2],
											  &D3DXVECTOR2(1.0f,1.0f),
											  false);
		}
		///Central Core
		else if(i==7)
		{
			//iMeshTexturePanSet(Mesh_Track[i],&D3DXVECTOR2(-gTexturePan_Slow,0.0f),&D3DXVECTOR2(0.0f,0.0f),false);
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
												  Texture[i][0],
												  Texture[i][1],
												  Texture[i][2],
											  &D3DXVECTOR2(1.0f,1.0f),
											  false);
		}
		///Fixture A_B
		else if(i==8)
		{
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
												  Texture[i][0],
												  Texture[i][1],
												  Texture[i][2],
											  &D3DXVECTOR2(1.0f,1.0f),
											  false);
		}
		///Hanging Glow
		else if(i==9)
		{
			iMeshTexturePanSet(Mesh_Track[i],&D3DXVECTOR2(-gTexturePan_Med,0.0f),&D3DXVECTOR2(0.0f,0.0f),false);
			iMeshShaderNormalMapTextureUpdate(Mesh_Track[i],
												  Texture[i][0],
												  Texture[i][1],
												  Texture[i][2],
											  &D3DXVECTOR2(1.0f,1.0f),
											  false);
		}
	}
	//-------------------------------------------------------------
	//Clouds
	Clouds.Update();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ENVIRONMENT - TRACK - DESTROY
///*****************************************************************
void Game_Track::Destroy(void)
{
	//-------------------------------------------------------------
	//Physx
	Physx.Destroy();
	//-------------------------------------------------------------
	//Clouds
	Clouds.Destroy();
	//-------------------------------------------------------------
	//Mesh
	for(int i=0;i<MAX_TRACK_MESH;i++)
	{
		if(Mesh_Track[i]!=NULL)
		{
			iMeshDestroy(Mesh_Track[i]);
		}
		///Reset shadow types
		Mesh_Track_ShadowType[i] = -1;
		Mesh_Track_ShadowDoubleSided[i] = false;
	}
	//-------------------------------------------------------------
	//Showroom Mesh
	for(int i=0;i<MAX_SHOWROOM;i++)
	{
		if(Mesh_ShowRoom[i]!=NULL)
		{
			iMeshDestroy(Mesh_ShowRoom[i]);
		}
	}
	//-------------------------------------------------------------
	//Textures
	TexturesDestroy();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ENVIRONMENT - TRACK - Showroom_Start
///*****************************************************************
void Game_Track::Showroom_Start(void)
{
	//-------------------------------------------------------------
	if(!bShowroom)
	{
		//-------------------------------------------------------------
		//Set bike to showroom
		cGame_Bike[gAi_Max_Count].Manager.fAcceleration_Speed = 0.0f;
		cGame_Bike[gAi_Max_Count].fSteering = 0.0f;
		cGame_Bike[gAi_Max_Count].Manager.vBikeOrigin = D3DXVECTOR3(0.0f,-4996.2f,-3.0f);
		cGame_Bike[gAi_Max_Count].Manager.qBikeOrigin = cGame_Spawn.qSpawnLocation;
		cGame_Bike[gAi_Max_Count].Manager.fSmoothHeight = 0.0f;
		cGame_Bike[gAi_Max_Count].Manager.fAiSteering = 0.0f;
		cGame_Bike[gAi_Max_Count].Manager.fCollision_px = 0.0f;
		gBikesGo = false;
		//Show Mesh
		for(int i=0;i<MAX_SHOWROOM;i++)
		{
			iMeshShow(Mesh_ShowRoom[i],false);
			iMeshLocationSet(Mesh_ShowRoom[i],&D3DXVECTOR3(0.0f,-5000.0f,0.0f),false);
		}
		//-------------------------------------------------------------
		bShowroom = true;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ENVIRONMENT - TRACK - Showroom_Stop
///*****************************************************************
void Game_Track::Showroom_Stop(void)
{
	//-------------------------------------------------------------
	if(bShowroom)
	{
		//-------------------------------------------------------------
		//Showroom Mesh
		for(int i=0;i<MAX_SHOWROOM;i++)
		{
		  iMeshHide(Mesh_ShowRoom[i],false);
		}
		//-------------------------------------------------------------
		//Reset bike
		cGame_Bike[gAi_Max_Count].Manager.fAcceleration_Speed = 0.0f;
		cGame_Bike[gAi_Max_Count].fSteering = 0.0f;
		cGame_Bike[gAi_Max_Count].Manager.vBikeOrigin = cGame_Spawn.vSpawnLocation[gAi_Max_Count];
		cGame_Bike[gAi_Max_Count].Manager.qBikeOrigin = cGame_Spawn.qSpawnLocation;
		gBikesGo = true;
		//-------------------------------------------------------------
		bShowroom = false;
	}
	//-------------------------------------------------------------
}