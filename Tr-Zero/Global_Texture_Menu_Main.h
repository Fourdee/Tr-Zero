#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Global_Texture_Menu_Main
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Hud1
		TEXTURE2D*						Hud1;
		//Targeting
		TEXTURE2D*						Target_Tex[3];
		//BG_TextMain
		TEXTURE2D*						BG_TextMain;
		//BG_TextSetting
		TEXTURE2D*						BG_TextSetting;
		//BG_TextSlider
		TEXTURE2D*						BG_TextSlider;
		//BG_TopBanner
		TEXTURE2D*						BG_TopBanner;
		//BG_Upgrades
		TEXTURE2D*						BG_Upgrades[4];
		//BG_Upgrades_Bottom
		TEXTURE2D*						BG_Upgrades_Bottom;
		//BG_LoadingScreen
		TEXTURE2D*						BG_LoadingScreen;
		//Controls_Xbox
		TEXTURE2D*						Controls_Xbox;
		//Controls_Keyboard
		TEXTURE2D*						Controls_Keyboard;
		//Hud Utility
		TEXTURE2D*						Hud_Utility_0;
		TEXTURE2D*						Hud_Utility_1;
		TEXTURE2D*						Hud_Utility_Icons[4];
		//Hud_Secondary_1
		TEXTURE2D*						Hud_Secondary_0;
		TEXTURE2D*						Hud_Secondary_1;
		TEXTURE2D*						Hud_Secondary_Icons[4];
		//Hud_Scoreboard
		TEXTURE2D*						Hud_Scoreboard;
		//---------------------------------------------------------
		//constructors
		Global_Texture_Menu_Main(void);
		~Global_Texture_Menu_Main(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void SamplerSet(void);
		void Destroy(void);
	//-------------------------------------------------------------
};
