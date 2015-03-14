//-----------------------------------------------------------------
// About:
//
// name: "Game_SkyDome.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
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
#include "Game_SkyDome.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - SKYDOME - CONSTRUCTORS
///*****************************************************************
Game_SkyDome::Game_SkyDome(void)
{
	//-------------------------------------------------------------
	Tex2D = NULL;
	SkyDome = NULL;
	//-------------------------------------------------------------
}

Game_SkyDome::~Game_SkyDome(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - SKYDOME - CHAPTER - 000 - CREATE
///*****************************************************************
void Game_SkyDome::Create(void)
{
	//-------------------------------------------------------------
	//create texture
	TexturesCreate(1);
	//create skydome
	SkyDome = iSkyDomeCreate(Tex2D);
	iSkyDomeShow(SkyDome);	
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - SKYDOME - TEXTURES CREATE
///*****************************************************************
void Game_SkyDome::TexturesCreate(int index)
{
	//-------------------------------------------------------------
	Tex2D = iTexture2DCreate("trzero_res\\textures\\skydome_map\\sky_dome_Blue_Sky_Clouded.dds");
	iTexture2DMinMagMipFilterModeSet(Tex2D,D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	iTexture2DModeSet(Tex2D,D3D11_TEXTURE_ADDRESS_WRAP);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - SKYDOME - DESTROY
///*****************************************************************
void Game_SkyDome::Destroy(void)
{
	//-------------------------------------------------------------
	iSkyDomeDestroy(SkyDome);
	iTexture2DDestroy(Tex2D);
	//-------------------------------------------------------------
}