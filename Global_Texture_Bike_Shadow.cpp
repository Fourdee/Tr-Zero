//-----------------------------------------------------------------
// About:
//
// name: "Global_Texture_Bike_Shadow.cpp:
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
#include "Global_Texture_Bike_Shadow.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - SHADOW - CONSTRUCTORS
///*****************************************************************
Global_Texture_Bike_Shadow::Global_Texture_Bike_Shadow(void)
{
	//-------------------------------------------------------------
	Bike_Shadow						= NULL;
	//Bike_Shadow_TP					= NULL;
	//-------------------------------------------------------------
}

Global_Texture_Bike_Shadow::~Global_Texture_Bike_Shadow(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - SHADOW - CREATE
///*****************************************************************
void Global_Texture_Bike_Shadow::Create(void)//maybe put an int to only load the style you want, same for destroy ?
{
	//-------------------------------------------------------------
	Bike_Shadow = iTexture2DCreate("trzero_res\\textures\\shadow_map\\Shadow_A.dds");
	//Bike_Shadow_TP = iTexture2DCreate("trzero_res\\textures\\shadow_map\\Shadow_TP.dds");
	//-------------------------------------------------------------
	//apply samplers
	SamplerSet();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - SHADOW - SAMPLER SET
///*****************************************************************
void Global_Texture_Bike_Shadow::SamplerSet(void)
{
	//-------------------------------------------------------------
	cGame_Texture2D_Sampler.ClampSet(Bike_Shadow);
	//cGame_Texture2D_Sampler.ClampSet(Bike_Shadow_TP,0.0f,5.0f);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - SHADOW - DESTROY
///*****************************************************************
void Global_Texture_Bike_Shadow::Destroy(void)
{
	//-------------------------------------------------------------
	iTexture2DDestroy(Bike_Shadow);
	//iTexture2DDestroy(Bike_Shadow_TP);
	//-------------------------------------------------------------
}