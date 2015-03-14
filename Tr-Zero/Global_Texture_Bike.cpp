//-----------------------------------------------------------------
// About:
//
// name: "Global_Texture_Bike.cpp:
//
// included in: "Game_Asset_Global_Textures.h"
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
#include "Global_Texture_Bike.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - CONSTRUCTORS
///*****************************************************************
Global_Texture_Bike::Global_Texture_Bike(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<2;i++)
	{
		Diffuse[i]							= NULL;
		Normal[i]							= NULL;
		Specular[i]						= NULL;
		Refl_Mask[i]						= NULL;
		Glow[i]							= NULL;
	}
	//---------------------------------------------------------
	//Headlight
	Shield							= NULL;
	Headlight_B						= NULL;
	Headlight_C						= NULL;
	Trail_em						= NULL;
	EnvMap						= NULL;
	//-------------------------------------------------------------
}

Global_Texture_Bike::~Global_Texture_Bike(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - CREATE
///*****************************************************************
void Global_Texture_Bike::Create(void)
{
	//-------------------------------------------------------------
	//Bike Carl
	Diffuse[0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\bike_carl\\dm.dds");
	Normal[0] = iTexture2DCreate("trzero_res\\textures\\normal_map\\bike_carl\\nm.dds");
	Glow[0] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\bike_carl\\em.dds");
	Specular[0] = iTexture2DCreate("trzero_res\\textures\\specular_map\\bike_carl\\spec.dds");
	Refl_Mask[0] = iTexture2DCreate("trzero_res\\textures\\reflect_map\\bike_carl.dds");

	//Bike Dave
	Diffuse[1] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\bike_dave\\dm.dds");
	Normal[1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\bike_dave\\nm.dds");
	Glow[1] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\bike_dave\\em.dds");
	Specular[1] = iTexture2DCreate("trzero_res\\textures\\specular_map\\bike_dave\\spec.dds");
	Refl_Mask[1] = iTexture2DCreate("trzero_res\\textures\\reflect_map\\bike_dave.dds");
	//---------------------------------------------------------
	Shield = iTexture2DCreate("trzero_res\\textures\\emissive_map\\bike_modern\\em_shield.dds");
	Headlight_B = iTexture2DCreate("trzero_res\\textures\\emissive_map\\bike_carl\\headlight_B.dds");
	Headlight_C = iTexture2DCreate("trzero_res\\textures\\emissive_map\\bike_carl\\headlight_C.dds");
	Trail_em = iTexture2DCreate("trzero_res\\textures\\emissive_map\\trail\\em1.dds");
	EnvMap = iTextureCubeCreate("trzero_res\\textures\\env_map\\Menu.dds");	
	//-------------------------------------------------------------
	//apply samplers
	SamplerSet();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - SAMPLER SET
///*****************************************************************
void Global_Texture_Bike::SamplerSet(void)
{
	//-------------------------------------------------------------
	//Carl
	cGame_Texture2D_Sampler.ClampSet(Diffuse[0]);
	cGame_Texture2D_Sampler.ClampSet(Normal[0]);
	cGame_Texture2D_Sampler.ClampSet(Glow[0]);
	cGame_Texture2D_Sampler.ClampSet(Specular[0]);
	cGame_Texture2D_Sampler.ClampSet(Refl_Mask[0]);
	//DAVE
	cGame_Texture2D_Sampler.WrapSet(Diffuse[1]);
	cGame_Texture2D_Sampler.WrapSet(Normal[1]);
	cGame_Texture2D_Sampler.WrapSet(Glow[1]);
	cGame_Texture2D_Sampler.WrapSet(Specular[1]);
	cGame_Texture2D_Sampler.WrapSet(Refl_Mask[1]);
	//---------------------------------------------------------
	//other
	cGame_Texture2D_Sampler.WrapSet(Shield);
	cGame_Texture2D_Sampler.WrapSet(Headlight_B);
	cGame_Texture2D_Sampler.WrapSet(Headlight_C);
	cGame_Texture2D_Sampler.WrapSet(Trail_em);
	cGame_Texture2D_Sampler.CubeWrapSet(EnvMap);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - DESTROY
///*****************************************************************
void Global_Texture_Bike::Destroy(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<2;i++)
	{
		iTexture2DDestroy(Glow[i]);
		iTexture2DDestroy(Refl_Mask[i]);
		iTexture2DDestroy(Specular[i]);
		iTexture2DDestroy(Normal[i]);
		iTexture2DDestroy(Diffuse[i]);
	}
	//---------------------------------------------------------
	//Headlight
	iTexture2DDestroy(Shield);
	iTexture2DDestroy(Headlight_B);
	iTexture2DDestroy(Headlight_C);
	iTexture2DDestroy(Trail_em);
	iTextureCubeDestroy(EnvMap);
	//-------------------------------------------------------------
}