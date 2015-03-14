//-----------------------------------------------------------------
// About:
//
// name: "Global_Texture_Bike_Tire.cpp:
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
#include "Global_Texture_Bike_Tire.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - TIRE - CONSTRUCTORS
///*****************************************************************
Global_Texture_Bike_Tire::Global_Texture_Bike_Tire(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<2;i++)
	{
		Diffuse[i]				= NULL;
		Normal[i]				= NULL;
		Specular[i]				= NULL;
		DiffuseBlur[i]			= NULL;
		NormalBlur[i]			= NULL;
		SpecularBlur[i]			= NULL;
		Glow_A[i]				= NULL;
		Glow_A_Blur[i]			= NULL;
	}
	Glow_B						= NULL;
	//-------------------------------------------------------------
}

Global_Texture_Bike_Tire::~Global_Texture_Bike_Tire(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - TIRE - CREATE
///*****************************************************************
void Global_Texture_Bike_Tire::Create(void)
{
	//-------------------------------------------------------------
	//Bike Carl
	Diffuse[0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\bike_carl\\wheeldm.dds");
	DiffuseBlur[0] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\bike_carl\\wheeldmblur.dds");
	Normal[0] = iTexture2DCreate("trzero_res\\textures\\normal_map\\bike_carl\\wheelnm.dds");
	NormalBlur[0] = iTexture2DCreate("trzero_res\\textures\\normal_map\\bike_carl\\wheelnmblur.dds");
	Specular[0] = iTexture2DCreate("trzero_res\\textures\\specular_map\\bike_carl\\wheelspec.dds");
	SpecularBlur[0] = iTexture2DCreate("trzero_res\\textures\\specular_map\\bike_carl\\wheelspecblur.dds");
	Glow_A[0] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\bike_carl\\wheelem.dds");
	Glow_A_Blur[0] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\bike_carl\\wheelemblur.dds");
	//Bike Dave
	Diffuse[1] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\bike_dave\\wheeldm.dds");
	DiffuseBlur[1] = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\bike_dave\\wheeldmblur.dds");
	Normal[1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\bike_dave\\wheelnm.dds");
	NormalBlur[1] = iTexture2DCreate("trzero_res\\textures\\normal_map\\bike_dave\\wheelnmblur.dds");
	Specular[1] = iTexture2DCreate("trzero_res\\textures\\specular_map\\bike_dave\\wheelspec.dds");
	SpecularBlur[1] = iTexture2DCreate("trzero_res\\textures\\specular_map\\bike_dave\\wheelspecblur.dds");
	Glow_A[1] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\bike_dave\\wheelem.dds");
	Glow_A_Blur[1] = iTexture2DCreate("trzero_res\\textures\\emissive_map\\bike_dave\\wheelemblur.dds");

	Glow_B = iTexture2DCreate("trzero_res\\textures\\emissive_map\\bike_carl\\wheelglowem.dds");
	//-------------------------------------------------------------
	//apply samplers
	SamplerSet();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - TIRE - SAMPLER SET
///*****************************************************************
void Global_Texture_Bike_Tire::SamplerSet(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<2;i++)
	{
		cGame_Texture2D_Sampler.WrapSet(Diffuse[i]);
		cGame_Texture2D_Sampler.WrapSet(DiffuseBlur[i]);
		cGame_Texture2D_Sampler.WrapSet(Normal[i]);
		cGame_Texture2D_Sampler.WrapSet(NormalBlur[i]);
		cGame_Texture2D_Sampler.WrapSet(Specular[i]);
		cGame_Texture2D_Sampler.WrapSet(SpecularBlur[i]);
		cGame_Texture2D_Sampler.WrapSet(Glow_A[i]);
		cGame_Texture2D_Sampler.WrapSet(Glow_A_Blur[i]);
	}
	cGame_Texture2D_Sampler.WrapSet(Glow_B);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - TIRE - DESTROY
///*****************************************************************
void Global_Texture_Bike_Tire::Destroy(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<2;i++)
	{
		iTexture2DDestroy(Diffuse[i]);
		iTexture2DDestroy(DiffuseBlur[i]);
		iTexture2DDestroy(Normal[i]);
		iTexture2DDestroy(NormalBlur[i]);
		iTexture2DDestroy(Specular[i]);
		iTexture2DDestroy(SpecularBlur[i]);
		iTexture2DDestroy(Glow_A[i]);
		iTexture2DDestroy(Glow_A_Blur[i]);
	}
	iTexture2DDestroy(Glow_B);
	//-------------------------------------------------------------
}