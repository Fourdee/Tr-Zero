//-----------------------------------------------------------------
// About:
//
// name: "Global_Texture_Track_Pickups.cpp:
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
#include "Global_Texture_Track_Pickups.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - GLOBAL - TEXTURES - TRACK - PICKUPS - CONSTRUCTORS
///*****************************************************************
Global_Texture_Track_Pickups::Global_Texture_Track_Pickups(void)
{
	//-------------------------------------------------------------
	Pickup_Energy					= NULL;
	//-------------------------------------------------------------
}

Global_Texture_Track_Pickups::~Global_Texture_Track_Pickups(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - TRACK - PICKUPS - CREATE
///*****************************************************************
void Global_Texture_Track_Pickups::Create(void)
{
	//-------------------------------------------------------------
	Pickup_Energy = iTexture2DCreate("trzero_res\\textures\\emissive_map\\pickups\\energy.dds");
	//-------------------------------------------------------------
	//apply samplers
	SamplerSet();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - TRACK - PICKUPS - SAMPLER SET
///*****************************************************************
void Global_Texture_Track_Pickups::SamplerSet(void)
{
	//-------------------------------------------------------------
	cGame_Texture2D_Sampler.WrapSet(Pickup_Energy);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - TRACK - PICKUPS - DESTROY
///*****************************************************************
void Global_Texture_Track_Pickups::Destroy(void)
{
	//-------------------------------------------------------------
	iTexture2DDestroy(Pickup_Energy);
	//-------------------------------------------------------------
}