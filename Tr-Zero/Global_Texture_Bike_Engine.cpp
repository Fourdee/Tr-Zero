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
#include "Global_Texture_Bike_Engine.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - TIRE - CONSTRUCTORS
///*****************************************************************
Global_Texture_Bike_Engine::Global_Texture_Bike_Engine(void)
{
	//-------------------------------------------------------------
	Diffuse						= NULL;
	Normal						= NULL;
	Glow_A						= NULL;
	//-------------------------------------------------------------
}

Global_Texture_Bike_Engine::~Global_Texture_Bike_Engine(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - TIRE - CREATE
///*****************************************************************
void Global_Texture_Bike_Engine::Create(void)
{
	//-------------------------------------------------------------
	///Carl
	Diffuse = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\engine\\dm.dds");
	Normal = iTexture2DCreate("trzero_res\\textures\\normal_map\\engine\\nm.dds");
	Glow_A = iTexture2DCreate("trzero_res\\textures\\emissive_map\\engine\\em.dds");
	///Dave - USES BIKE TEXTURES
	//-------------------------------------------------------------
	//apply samplers
	SamplerSet();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - TIRE - SAMPLER SET
///*****************************************************************
void Global_Texture_Bike_Engine::SamplerSet(void)
{
	//-------------------------------------------------------------
	cGame_Texture2D_Sampler.WrapSet(Diffuse);
	cGame_Texture2D_Sampler.WrapSet(Normal);
	cGame_Texture2D_Sampler.WrapSet(Glow_A);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - TIRE - DESTROY
///*****************************************************************
void Global_Texture_Bike_Engine::Destroy(void)
{
	//-------------------------------------------------------------
	iTexture2DDestroy(Glow_A);
	iTexture2DDestroy(Normal);
	iTexture2DDestroy(Diffuse);
	//-------------------------------------------------------------
}