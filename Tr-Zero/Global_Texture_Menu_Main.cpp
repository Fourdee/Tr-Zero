//-----------------------------------------------------------------
// About:
//
// name: "Global_Texture_Menu_Main.cpp:
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
#include "Global_Texture_Menu_Main.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - GLOBAL - TEXTURES - MENU MAIN - CONSTRUCTORS
///*****************************************************************
Global_Texture_Menu_Main::Global_Texture_Menu_Main(void)
{
	//-------------------------------------------------------------
	Hud1							= NULL;
	//Targeting
	for(int i=0;i<3;i++)
	{
		Target_Tex[i]				= NULL;
	}
	BG_TextMain						= NULL;
	BG_TextSetting					= NULL;
	BG_TextSlider					= NULL;
	BG_TopBanner					= NULL;

	for(int i=0;i<4;i++)
	{
		BG_Upgrades[i]				= NULL;
	}
	BG_Upgrades_Bottom				= NULL;
	BG_LoadingScreen				= NULL;
	//Controls
	Controls_Xbox					= NULL;
	Controls_Keyboard				= NULL;
	//Hud Utility
	Hud_Utility_0					= NULL;
	Hud_Utility_1					= NULL;
	//Hud_Secondary_1
	Hud_Secondary_0					= NULL;
	Hud_Secondary_1					= NULL;
	//Weapon icons
	for(int i=0;i<4;i++)
	{
		Hud_Utility_Icons[i] = NULL;
		Hud_Secondary_Icons[i] = NULL;
	}
	//Hud_Scoreboard
	Hud_Scoreboard = NULL;
	//-------------------------------------------------------------
}

Global_Texture_Menu_Main::~Global_Texture_Menu_Main(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - MENU MAIN - CREATE
///*****************************************************************
void Global_Texture_Menu_Main::Create(void)
{
	//-------------------------------------------------------------
	Hud1 = iTexture2DCreate("trzero_res\\sprites\\hud\\hud1.dds");
	//Targeting
	Target_Tex[0] = iTexture2DCreate("trzero_res\\sprites\\hud\\Target_1.dds");
	Target_Tex[1] = iTexture2DCreate("trzero_res\\sprites\\hud\\Target_2.dds");
	Target_Tex[2] = iTexture2DCreate("trzero_res\\sprites\\hud\\Target_3.dds");
	BG_TextMain = iTexture2DCreate("trzero_res\\sprites\\menu\\text_main.dds");
	BG_TextSetting = iTexture2DCreate("trzero_res\\sprites\\menu\\text_setting_test.dds");
	BG_TextSlider = iTexture2DCreate("trzero_res\\sprites\\menu\\text_slider.dds");
	BG_TopBanner = iTexture2DCreate("trzero_res\\sprites\\menu\\top_banner_highlight.dds");
	BG_Upgrades[0] = iTexture2DCreate("trzero_res\\sprites\\menu\\upgrade0.dds");
	BG_Upgrades[1] = iTexture2DCreate("trzero_res\\sprites\\menu\\upgrade1.dds");
	BG_Upgrades[2] = iTexture2DCreate("trzero_res\\sprites\\menu\\upgrade2.dds");
	BG_Upgrades[3] = iTexture2DCreate("trzero_res\\sprites\\menu\\upgrade3.dds");
	BG_Upgrades_Bottom = iTexture2DCreate("trzero_res\\sprites\\menu\\upgrade_bottom.dds");
	BG_LoadingScreen = iTexture2DCreate("trzero_res\\sprites\\loading\\loadingscreen.dds");
	//Controls
	Controls_Xbox = iTexture2DCreate("trzero_res\\sprites\\menu\\controls_xbox.dds");
	Controls_Keyboard = iTexture2DCreate("trzero_res\\sprites\\menu\\controls_keyboard.dds");
	//Hud Utility
	Hud_Utility_0 = iTexture2DCreate("trzero_res\\sprites\\hud\\utility_0.dds");
	Hud_Utility_1 = iTexture2DCreate("trzero_res\\sprites\\hud\\utility_1.dds");
	Hud_Secondary_0 = iTexture2DCreate("trzero_res\\sprites\\hud\\secondary_0.dds");
	Hud_Secondary_1 = iTexture2DCreate("trzero_res\\sprites\\hud\\secondary_1.dds");
	//icons
	Hud_Utility_Icons[0]	= iTexture2DCreate("trzero_res\\sprites\\hud\\weapon_icon\\utility_shield.dds");
	Hud_Utility_Icons[1]	= iTexture2DCreate("trzero_res\\sprites\\hud\\weapon_icon\\utility_autopilot.dds");
	Hud_Utility_Icons[2]	= iTexture2DCreate("trzero_res\\sprites\\hud\\weapon_icon\\utility_doubledamage.dds");
	Hud_Utility_Icons[3]	= iTexture2DCreate("trzero_res\\sprites\\hud\\weapon_icon\\utility_warp.dds");

	Hud_Secondary_Icons[0] 	= iTexture2DCreate("trzero_res\\sprites\\hud\\weapon_icon\\secondary_missile.dds");
	Hud_Secondary_Icons[1] 	= iTexture2DCreate("trzero_res\\sprites\\hud\\weapon_icon\\secondary_shoxwave.dds");
	Hud_Secondary_Icons[2] 	= iTexture2DCreate("trzero_res\\sprites\\hud\\weapon_icon\\secondary_emburst.dds");
	Hud_Secondary_Icons[3] 	= iTexture2DCreate("trzero_res\\sprites\\hud\\weapon_icon\\secondary_rail.dds");
	//Hud_Scoreboard
	Hud_Scoreboard = iTexture2DCreate("trzero_res\\sprites\\hud\\scoreboard.dds");
	//-------------------------------------------------------------
	//apply samplers
	SamplerSet();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - MENU MAIN - SAMPLER SET
///*****************************************************************
void Global_Texture_Menu_Main::SamplerSet(void)
{
	//-------------------------------------------------------------
	if(cGame_Settings.bUse_Anisotrpic_Filter)
	{
		cGame_Texture2D_Sampler.AnisotropicBorderSet(Hud1,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.AnisotropicBorderSet(Target_Tex[0],&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.AnisotropicBorderSet(Target_Tex[1],&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.AnisotropicBorderSet(Target_Tex[2],&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.AnisotropicBorderSet(BG_TextMain,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.AnisotropicBorderSet(BG_TextSetting,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.AnisotropicBorderSet(BG_TextSlider,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.AnisotropicBorderSet(BG_TopBanner,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		for(int i=0;i<4;i++)
		{
			cGame_Texture2D_Sampler.AnisotropicBorderSet(BG_Upgrades[i],&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		}
		cGame_Texture2D_Sampler.AnisotropicBorderSet(BG_Upgrades_Bottom,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.AnisotropicBorderSet(BG_LoadingScreen,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.AnisotropicBorderSet(Controls_Xbox,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.AnisotropicBorderSet(Controls_Keyboard,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.AnisotropicBorderSet(Hud_Utility_0,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.AnisotropicBorderSet(Hud_Utility_1,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.AnisotropicBorderSet(Hud_Secondary_0,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.AnisotropicBorderSet(Hud_Secondary_1,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		//Weapon icons
		for(int i=0;i<4;i++)
		{
			cGame_Texture2D_Sampler.AnisotropicBorderSet(Hud_Utility_Icons[i],&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
			cGame_Texture2D_Sampler.AnisotropicBorderSet(Hud_Secondary_Icons[i],&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		}
		//Hud_Scoreboard
		cGame_Texture2D_Sampler.AnisotropicBorderSet(Hud_Scoreboard,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
	}
	else
	{
		cGame_Texture2D_Sampler.LinearBorderSet(Hud1,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.LinearBorderSet(Target_Tex[0],&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.LinearBorderSet(Target_Tex[1],&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.LinearBorderSet(Target_Tex[2],&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.LinearBorderSet(BG_TextMain,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.LinearBorderSet(BG_TextSetting,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.LinearBorderSet(BG_TextSlider,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.LinearBorderSet(BG_TopBanner,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		for(int i=0;i<4;i++)
		{
			cGame_Texture2D_Sampler.LinearBorderSet(BG_Upgrades[i],&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		}
		cGame_Texture2D_Sampler.LinearBorderSet(BG_Upgrades_Bottom,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.LinearBorderSet(BG_LoadingScreen,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.LinearBorderSet(Controls_Xbox,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.LinearBorderSet(Controls_Keyboard,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.LinearBorderSet(Hud_Utility_0,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.LinearBorderSet(Hud_Utility_1,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.LinearBorderSet(Hud_Secondary_0,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		cGame_Texture2D_Sampler.LinearBorderSet(Hud_Secondary_1,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		//Weapon icons
		for(int i=0;i<4;i++)
		{
			cGame_Texture2D_Sampler.LinearBorderSet(Hud_Utility_Icons[i],&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
			cGame_Texture2D_Sampler.LinearBorderSet(Hud_Secondary_Icons[i],&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
		}
		//Hud_Scoreboard
		cGame_Texture2D_Sampler.LinearBorderSet(Hud_Scoreboard,&D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f));
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - MENU MAIN - DESTROY
///*****************************************************************
void Global_Texture_Menu_Main::Destroy(void)
{
	//-------------------------------------------------------------
	iTexture2DDestroy(Hud1);
	//Targeting
	for(int i=0;i<3;i++)
	{
		iTexture2DDestroy(Target_Tex[i]);
	}
	iTexture2DDestroy(BG_TextMain);
	iTexture2DDestroy(BG_TextSetting);
	iTexture2DDestroy(BG_TextSlider);
	iTexture2DDestroy(BG_TopBanner);
	for(int i=0;i<4;i++)
	{
		iTexture2DDestroy(BG_Upgrades[i]);
	}
	iTexture2DDestroy(BG_Upgrades_Bottom);
	iTexture2DDestroy(BG_LoadingScreen);
	iTexture2DDestroy(Controls_Xbox);
	iTexture2DDestroy(Controls_Keyboard);
	//Hud Utility
	iTexture2DDestroy(Hud_Utility_0);
	iTexture2DDestroy(Hud_Utility_1);
	iTexture2DDestroy(Hud_Secondary_0);
	iTexture2DDestroy(Hud_Secondary_1);
	//Weapon icons
	for(int i=0;i<4;i++)
	{
		iTexture2DDestroy(Hud_Utility_Icons[i]);
		iTexture2DDestroy(Hud_Secondary_Icons[i]);
	}
	//Hud_Scoreboard
	iTexture2DDestroy(Hud_Scoreboard);
	//-------------------------------------------------------------
}