//-----------------------------------------------------------------
// About:
//
// name: "Game_Texture2D_Sampler.cpp:
//
// included in: "Global_Class_Headers.h" accessed through "Global_Params.h"
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
#include "Game_Texture2D_Sampler.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - TEXTURE - SAMPLER - CONSTRUCTORS
///*****************************************************************
Game_Texture2D_Sampler::Game_Texture2D_Sampler(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}

Game_Texture2D_Sampler::~Game_Texture2D_Sampler(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXTURE - SAMPLER - STYLE - WRAP
///*****************************************************************
void Game_Texture2D_Sampler::WrapSet(TEXTURE2D* Tex2D)
{
	//-------------------------------------------------------------
	if(cGame_Settings.bUse_Anisotrpic_Filter)
    {
		iTexture2DMinMagMipFilterModeSet(Tex2D,D3D11_FILTER_ANISOTROPIC);
		iTexture2DAnisotropicMaxLevelSet(Tex2D,cGame_Settings.Anisotropic_Level);
	}
	else
	{
		iTexture2DMinMagMipFilterModeSet(Tex2D,D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT);//D3D11_FILTER_MIN_MAG_MIP_LINEAR
	}
	iTexture2DModeSet(Tex2D,D3D11_TEXTURE_ADDRESS_WRAP);
	iTexture2DLODSet(Tex2D,0.0F,4.0f,0.0f);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXTURE - SAMPLER - STYLE - CLAMP
///*****************************************************************
void Game_Texture2D_Sampler::ClampSet(TEXTURE2D* Tex2D)
{
	//-------------------------------------------------------------
	if(cGame_Settings.bUse_Anisotrpic_Filter)
    {
		iTexture2DMinMagMipFilterModeSet(Tex2D,D3D11_FILTER_ANISOTROPIC);
		iTexture2DAnisotropicMaxLevelSet(Tex2D,cGame_Settings.Anisotropic_Level);
	}
	else
	{
		iTexture2DMinMagMipFilterModeSet(Tex2D,D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT);
	}
	iTexture2DModeSet(Tex2D,D3D11_TEXTURE_ADDRESS_CLAMP);
	iTexture2DLODSet(Tex2D,0.0F,4.0f,0.0f);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXTURE - SAMPLER - STYLE - LINEAR MIRROR
///*****************************************************************
void Game_Texture2D_Sampler::LinearMirrorSet(TEXTURE2D* Tex2D)
{
	//-------------------------------------------------------------
	iTexture2DMinMagMipFilterModeSet(Tex2D,D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	iTexture2DModeSet(Tex2D,D3D11_TEXTURE_ADDRESS_MIRROR);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXTURE - SAMPLER - STYLE - LINEAR MIRROR ONCE
///*****************************************************************
void Game_Texture2D_Sampler::LinearMirrorOnceSet(TEXTURE2D* Tex2D)
{
	//-------------------------------------------------------------
	iTexture2DMinMagMipFilterModeSet(Tex2D,D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	iTexture2DModeSet(Tex2D,D3D11_TEXTURE_ADDRESS_MIRROR_ONCE);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXTURE - SAMPLER - STYLE - LINEAR BORDER
///*****************************************************************
void Game_Texture2D_Sampler::LinearBorderSet(TEXTURE2D* Tex2D,D3DXVECTOR4* BorderColor)
{
	//-------------------------------------------------------------
	iTexture2DMinMagMipFilterModeSet(Tex2D,D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	iTexture2DModeSet(Tex2D,D3D11_TEXTURE_ADDRESS_BORDER);
	iTexture2DBorderColorSet(Tex2D,BorderColor);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXTURE - SAMPLER - STYLE - ANISOTROPIC MIRROR
///*****************************************************************
void Game_Texture2D_Sampler::AnisotropicMirrorSet(TEXTURE2D* Tex2D)
{
	//-------------------------------------------------------------
	iTexture2DAnisotropicMaxLevelSet(Tex2D,cGame_Settings.Anisotropic_Level);
	iTexture2DMinMagMipFilterModeSet(Tex2D,D3D11_FILTER_ANISOTROPIC);
	iTexture2DModeSet(Tex2D,D3D11_TEXTURE_ADDRESS_MIRROR);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXTURE - SAMPLER - STYLE - ANISOTROPIC MIRROR ONCE
///*****************************************************************
void Game_Texture2D_Sampler::AnisotropicMirrorOnceSet(TEXTURE2D* Tex2D)
{
	//-------------------------------------------------------------
	iTexture2DAnisotropicMaxLevelSet(Tex2D,cGame_Settings.Anisotropic_Level);
	iTexture2DMinMagMipFilterModeSet(Tex2D,D3D11_FILTER_ANISOTROPIC);
	iTexture2DModeSet(Tex2D,D3D11_TEXTURE_ADDRESS_MIRROR_ONCE);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXTURE - SAMPLER - STYLE - ANISOTROPIC BORDER
///*****************************************************************
void Game_Texture2D_Sampler::AnisotropicBorderSet(TEXTURE2D* Tex2D,D3DXVECTOR4* BorderColor)
{
	//-------------------------------------------------------------
	iTexture2DAnisotropicMaxLevelSet(Tex2D,cGame_Settings.Anisotropic_Level);
	iTexture2DMinMagMipFilterModeSet(Tex2D,D3D11_FILTER_ANISOTROPIC);
	iTexture2DModeSet(Tex2D,D3D11_TEXTURE_ADDRESS_BORDER);
	iTexture2DBorderColorSet(Tex2D,BorderColor);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXTURE - SAMPLER - VIDEO - VideoWrapSet
///*****************************************************************
void Game_Texture2D_Sampler::VideoWrapSet(TEXTURE2DVIDEO* Tex2D)
{
	//-------------------------------------------------------------
	//if(cGame_Settings.bUse_Anisotrpic_Filter)
 //   {
	//	iTexture2DVideoMinMagMipFilterModeSet(Tex2D,D3D11_FILTER_ANISOTROPIC);
	//	iTexture2DVideoAnisotropicMaxLevelSet(Tex2D,cGame_Settings.Anisotropic_Level);
	//}
	//else
	//{
	//	iTexture2DVideoMinMagMipFilterModeSet(Tex2D,D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	//}
	//iTexture2DVideoModeSet(Tex2D,D3D11_TEXTURE_ADDRESS_WRAP);
	//iTexture2DVideoLODSet(Tex2D,0.0f,D3D11_FLOAT32_MAX,0.0f);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXTURE - SAMPLER - VIDEO - CubeWrapSet
///*****************************************************************
void Game_Texture2D_Sampler::CubeWrapSet(TEXTURECUBE* Tex2D)
{
	//-------------------------------------------------------------
	if(cGame_Settings.bUse_Anisotrpic_Filter)
    {
		iTextureCubeAnisotropicMaxLevelSet(Tex2D,cGame_Settings.Anisotropic_Level);
		iTextureCubeMinMagMipFilterModeSet(Tex2D,D3D11_FILTER_ANISOTROPIC);
		iTextureCubeModeSet(Tex2D,D3D11_TEXTURE_ADDRESS_CLAMP);
	}
	else
	{
		iTextureCubeMinMagMipFilterModeSet(Tex2D,D3D11_FILTER_MIN_MAG_MIP_LINEAR);
		iTextureCubeModeSet(Tex2D,D3D11_TEXTURE_ADDRESS_CLAMP);
	}
	iTextureCubeLODSet(Tex2D,0.0f,D3D11_FLOAT32_MAX,0.0f);
	//-------------------------------------------------------------
}