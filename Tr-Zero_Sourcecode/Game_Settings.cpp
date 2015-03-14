//-----------------------------------------------------------------
// About:
//
// User Video/Audio/user Settings
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Settings.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - SETTINGS  - CONSTRUCTORS
///*****************************************************************
Game_Settings::Game_Settings(void)
{
	//-------------------------------------------------------------
	DeviceRes = NULL;
	strcpy_s(DeviceName,"NULL");
	DeviceResolutionsCount = 0;
	DisplayWidth = NULL;
	DisplayHeight = NULL;
	ResIndex = 0;
	//-------------------------------------------------------------
	//texture filter
	bUse_Anisotrpic_Filter = false;
	Anisotropic_Level = 1;
	Anisotropic_Max_Level = 16;
	//-------------------------------------------------------------
}

Game_Settings::~Game_Settings(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - SETTINGS  - CREATE
///*****************************************************************
void Game_Settings::Create(void)
{
	//-------------------------------------------------------------
	//load settings
	LoadSettings();
	//-------------------------------------------------------------
	//create the device and gather info
	DeviceRes = iDeviceResolutionCreate();
	iDeviceName(DeviceRes,DeviceName);
	DeviceResolutionsCount = iDeviceResolutionCount(DeviceRes);
	if(DeviceResolutionsCount==0){iMessageBox("");}
	DisplayWidth = new int[DeviceResolutionsCount];
	DisplayHeight = new int[DeviceResolutionsCount];
	for(int i=0;i<DeviceResolutionsCount;i++)
	{
		iDeviceResolution(DeviceRes,DisplayWidth[i],DisplayHeight[i],i);
	}
	//-------------------------------------------------------------
	//find current resolution of the oddity engine window...
	int CX = iDisplayWidth();
	int CY = iDisplayHeight();
	for(int i=0;i<DeviceResolutionsCount;i++)
	{
		if((DisplayWidth[i]==CX) && (DisplayHeight[i]==CY))
		{
			ResIndex = i;
			break;
		}
	}
	//-------------------------------------------------------------
	ScaleFixer();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - SETTINGS  - RESOLUTION APPLY
///*****************************************************************
void Game_Settings::ResolutionApply(void)
{
	//-------------------------------------------------------------
	//apply resolution
	if(iDeviceWindowIsFullscreen())
	{
		iDeviceWindowFullScreenResizeSet(DisplayWidth[ResIndex],DisplayHeight[ResIndex]);
		ScaleFixer();
		iDeviceSettingApply();
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - SETTINGS  - SCALE FIXER
///*****************************************************************
void Game_Settings::ScaleFixer(void)
{
	//-------------------------------------------------------------
	//Apply global font scale against res
	gFontScale = iFloatInterpolate((float)DisplayHeight[ResIndex],480.0f,1080.0f,0.6f,1.4f);
	//Apply Font scales for font class
	cGame_Font.ApplyFontScale();
	//-------------------------------------------------------------
	//Apply Sprite Y Scale Resolution Fix
	const float AR_Default = 1.7777f;
	float AR_New = ((float)DisplayWidth[ResIndex] / (float)DisplayHeight[ResIndex]);
	gScreenYScale = (AR_Default - AR_New) + 1.0f;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - SETTINGS  - LOAD SETTINGS
///*****************************************************************
void Game_Settings::LoadSettings(void)
{
	//-------------------------------------------------------------
	if(iFileExists(gFilePath_Settings_Settings))
	{
		HANDLE hFile; 
		DWORD dwDone; 
		char filepath[1024];

		strcpy_s(filepath,gFilePath_Settings_Settings);
		iGlobalPathMake(filepath);

		hFile = CreateFile(filepath,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if(hFile != INVALID_HANDLE_VALUE)
		{
			//-----------------------------------------------------
			//Gfx
			ReadFile(hFile,&bUse_Anisotrpic_Filter,sizeof(bool),&dwDone,NULL);
			ReadFile(hFile,&Anisotropic_Level,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&gUserGamma,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&gGlowEnable,sizeof(bool),&dwDone,NULL);
			ReadFile(hFile,&gDoFEnable,sizeof(bool),&dwDone,NULL);
			ReadFile(hFile,&gDoFQuality,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&gBlurEnable,sizeof(bool),&dwDone,NULL);
			ReadFile(hFile,&gFxaaEnable,sizeof(bool),&dwDone,NULL);
			ReadFile(hFile,&gFxaaQuality,sizeof(int),&dwDone,NULL);
			bool bNothing = false;
			ReadFile(hFile,&bNothing,sizeof(bool),&dwDone,NULL);
			///Optimiser Bypass
			ReadFile(hFile,&cGame_Optimiser.bOptimiseBypass,sizeof(bool),&dwDone,NULL);
			///Bike Draw Limits
			ReadFile(hFile,&gMax_Culling_Bikes_Shown,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&gMax_Culling_Bikes_Low_Detail,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&gMax_Culling_Bikes_High_Detail,sizeof(int),&dwDone,NULL);
			///1st run
			ReadFile(hFile,&gFirstRun,sizeof(bool),&dwDone,NULL);
			//Audio
			ReadFile(hFile,&gVolumeFx,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&gVolumeMusic,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&gVolumeHitsound,sizeof(float),&dwDone,NULL);
			//Colours
			///User bike colour
			ReadFile(hFile,&gBikeColourUserHSV,sizeof(float),&dwDone,NULL);
			gBikeColourUser = HSVtoRGB(gBikeColourUserHSV);
			///Menu Colour
			ReadFile(hFile,&gMenuColour,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&gMenuFontColour,sizeof(D3DXVECTOR4),&dwDone,NULL);
			ReadFile(hFile,&gMenuTrackColour,sizeof(D3DXVECTOR3),&dwDone,NULL);
			//MISC
			///Ai Difficulty
			ReadFile(hFile,&gAiDifficuty,sizeof(int),&dwDone,NULL);
			///Player Name
			ReadFile(hFile,&gPlayerName,sizeof(gPlayerName),&dwDone,NULL);
			///Last IP address
			ReadFile(hFile,&gIpAddress,sizeof(gIpAddress),&dwDone,NULL);
			///CONTROLS
			ReadFile(hFile,&gXbox360Controller_Vibrate,sizeof(bool),&dwDone,NULL);
			///CAMERA
			ReadFile(hFile,&gCam_PlayerPreset,sizeof(int),&dwDone,NULL);
			///Network Game Region
			ReadFile(hFile,&gGameRegion,sizeof(int),&dwDone,NULL);
			//-----------------------------------------------------
			CloseHandle(hFile); 
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - SETTINGS  - SAVE SETTINGS
///*****************************************************************
void Game_Settings::SaveSettings(void)
{
	//-------------------------------------------------------------
	HANDLE hFile; 
	DWORD dwDone; 
	char filepath[1024];

	strcpy_s(filepath,gFilePath_Settings_Settings);
	iGlobalPathMake(filepath);

	hFile = CreateFile(filepath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		//---------------------------------------------------------
		//Gfx
		WriteFile(hFile,&bUse_Anisotrpic_Filter,sizeof(bool),&dwDone,NULL);
		WriteFile(hFile,&Anisotropic_Level,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&gUserGamma,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&gGlowEnable,sizeof(bool),&dwDone,NULL);
		WriteFile(hFile,&gDoFEnable,sizeof(bool),&dwDone,NULL);
		WriteFile(hFile,&gDoFQuality,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&gBlurEnable,sizeof(bool),&dwDone,NULL);
		WriteFile(hFile,&gFxaaEnable,sizeof(bool),&dwDone,NULL);
		WriteFile(hFile,&gFxaaQuality,sizeof(int),&dwDone,NULL);
		bool bNothing = false;
		WriteFile(hFile,&bNothing,sizeof(bool),&dwDone,NULL);
		///Optimiser Bypass
		WriteFile(hFile,&cGame_Optimiser.bOptimiseBypass,sizeof(bool),&dwDone,NULL);
		///Bike Draw Limits
		WriteFile(hFile,&gMax_Culling_Bikes_Shown,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&gMax_Culling_Bikes_Low_Detail,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&gMax_Culling_Bikes_High_Detail,sizeof(int),&dwDone,NULL);
		///1st run
		WriteFile(hFile,&gFirstRun,sizeof(bool),&dwDone,NULL);
		//Audio
		WriteFile(hFile,&gVolumeFx,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&gVolumeMusic,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&gVolumeHitsound,sizeof(float),&dwDone,NULL);
		///User bike colour
		WriteFile(hFile,&gBikeColourUserHSV,sizeof(float),&dwDone,NULL);	
		///Menu Colour
		WriteFile(hFile,&gMenuColour,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&gMenuFontColour,sizeof(D3DXVECTOR4),&dwDone,NULL);
		WriteFile(hFile,&gMenuTrackColour,sizeof(D3DXVECTOR3),&dwDone,NULL);
		///Ai Difficulty
		WriteFile(hFile,&gAiDifficuty,sizeof(int),&dwDone,NULL);
		///Player Name
		WriteFile(hFile,&gPlayerName,sizeof(gPlayerName),&dwDone,NULL);
		///Last IP address
		WriteFile(hFile,&gIpAddress,sizeof(gIpAddress),&dwDone,NULL);
		///CONTROLS
		WriteFile(hFile,&gXbox360Controller_Vibrate,sizeof(bool),&dwDone,NULL);
		///CAMERA
		WriteFile(hFile,&gCam_PlayerPreset,sizeof(int),&dwDone,NULL);
		///Network Game Region
		WriteFile(hFile,&gGameRegion,sizeof(int),&dwDone,NULL);
		//---------------------------------------------------------
		CloseHandle(hFile); 
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - SETTINGS  - DESTROY
///*****************************************************************
void Game_Settings::Destroy(void)
{
	//-------------------------------------------------------------
	//free memory - see stdafx.h for these methods
	SAFE_DELETE_ARRAY(DisplayWidth);
	SAFE_DELETE_ARRAY(DisplayHeight);
	//-------------------------------------------------------------
}