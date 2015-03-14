//-----------------------------------------------------------------
// About:
//
// name: "Game_LoadingScreen.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_LoadingScreen.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - LOADINGSCREEN - CONSTRUCTORS
///*****************************************************************
Game_LoadingScreen::Game_LoadingScreen(void)
{
	//-------------------------------------------------------------
	LoadingStageInfo		= "";
	bLoadingScreen_Created	= false;
	Sprite_LoadingScreen	= NULL;
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_LoadingScreen::~Game_LoadingScreen(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - LOADINGSCREEN - ZeroData
///*****************************************************************
void Game_LoadingScreen::ZeroData(void)
{
	//-------------------------------------------------------------
	Tip_To_Display = 0;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - LOADINGSCREEN - CREATE
///*****************************************************************
void Game_LoadingScreen::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
	//Create Sprite
	Sprite_LoadingScreen = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.BG_LoadingScreen,gCamera);
	iSpriteScaleSet(Sprite_LoadingScreen,&D3DXVECTOR2(32.0f,18.0f * gScreenYScale));
	iSpriteShow(Sprite_LoadingScreen);
	//-------------------------------------------------------------
	//Load Fastest lap from file
	if(!gExitWin &&
		gMasterServerOnline)
	{
		cGame_Ftp.LoadRecords(4);
	}
	//-------------------------------------------------------------
	//Generate Random Tip
	const int MAX_TIPS = 15;
	Tip_To_Display = iIntRand(0,MAX_TIPS);
	//-------------------------------------------------------------
	//bLoadingScreen_Created
	bLoadingScreen_Created = true;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - LOADINGSCREEN - Update
///*****************************************************************
void Game_LoadingScreen::Update(void)
{
	//-------------------------------------------------------------
	//Print info
	D3DXVECTOR2 vInfo = D3DXVECTOR2(0.0f,10.0f);
	iPrint((char*)LoadingStageInfo.c_str(),cGame_Font.f32pt,&vInfo,&gMenuFontColour,gFont,true);
	vInfo.y -= 0.65f;
	static int Timer = 0;
	Timer++;
	if(Timer>4)
	{
		Timer = 0;
	}
	vInfo.x = iFloatInterpolateSmooth((float)Timer,0.0f,4.0f,-3.0f,3.0f);
	iPrint((char*)"-",cGame_Font.f32pt,&vInfo,&gMenuFontColour,gFont,true);

	vInfo = D3DXVECTOR2(0.0f,-4.0f);
	if(gGameState>0 && 
		gGameStateChange>0 &&
		!gExitWin)
	{
		iPrint((char*)"Track :",cGame_Font.f16pt,&vInfo,&gFontGreyDark,gFont,true);
		vInfo.y -= 0.75f;
		iPrint((char*)gInfoTrack.c_str(),cGame_Font.f26pt,&vInfo,&gFontGreyLight,gFont,true);
		vInfo.y -= 1.25f;
		iPrint((char*)"Mode :",cGame_Font.f16pt,&vInfo,&gFontGreyDark,gFont,true);
		vInfo.y -= 0.75f;
		iPrint((char*)gInfoGameMode.c_str(),cGame_Font.f26pt,&vInfo,&gFontGreyLight,gFont,true);
		vInfo.y -= 1.25f;
		iPrint((char*)"SpeedClass :",cGame_Font.f16pt,&vInfo,&gFontGreyDark,gFont,true);
		vInfo.y -= 0.75f;
		iPrint((char*)gInfoSpeedClass.c_str(),cGame_Font.f26pt,&vInfo,&gFontGreyLight,gFont,true);
		vInfo.y -= 1.25f;
		iPrint((char*)"Ai Difficulty :",cGame_Font.f16pt,&vInfo,&gFontGreyDark,gFont,true);
		vInfo.y -= 0.75f;
		iPrint((char*)gInfoAiDifficulty.c_str(),cGame_Font.f26pt,&vInfo,&gFontGreyLight,gFont,true);
		//Fastest Laps
		vInfo = D3DXVECTOR2(10.0f,-6.0f);
		if(gGameStateChange<5)
		{
			cGame_Hud.TimerReadOuts("Personal Best",cGame_PlayerStats.LapRecord[gGameStateChange][gSpeedClass][gTrackReverse],vInfo);
			vInfo.y += -3.0f;
			if(gMasterServerOnline)
			{
				cGame_Hud.TimerReadOuts("World Record",cGame_PlayerStats.OnlineStats_Float_Value_1[0],vInfo);
				vInfo.y += -0.5f;
				vInfo.x += 1.25f;
				iPrint((char*)cGame_PlayerStats.OnlineStats_Name[0].c_str(),cGame_Font.f16pt,&vInfo,&gFontGreyDark,gFont2,true);
			}
		}
	}
	//Tip of the day
	TipOfTheDay();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - LOADINGSCREEN - TipOfTheDay
///*****************************************************************
void Game_LoadingScreen::TipOfTheDay(void)
{
	//-------------------------------------------------------------
	string TipLine_1 = "";
	string TipLine_2 = "";
	string TipLine_3 = "";
	//-------------------------------------------------------------
	//Tips list
	if(Tip_To_Display==0)
	{
		TipLine_1 = "Tips - Charging Weapons";
		TipLine_2 = "Some secondary weapons have a charge function.";
		TipLine_3 = "The longer you hold the charge, the more damage output.";
	}
	else if(Tip_To_Display==1)
	{
		TipLine_1 = "Tips - Energy Regen";
		TipLine_2 = "There are more ways to regen bike energy.";
		TipLine_3 = "Try tilting your bike against steep hills.";
	}
	else if(Tip_To_Display==2)
	{
		TipLine_1 = "Tips - Ai Difficulty";
		TipLine_2 = "Whilst playing on Easy is a breeze,";
		TipLine_3 = "Higher Difficulty settings grant more XP!";
	}
	else if(Tip_To_Display==3)
	{
		TipLine_1 = "Tips - Primary Weapon Heat";
		TipLine_2 = "Damage output of the primary weapon is controled by heat";
		TipLine_3 = "The higher the heat, the less damage";
	}
	else if(Tip_To_Display==4)
	{
		TipLine_1 = "Tips - Drifting";
		TipLine_2 = "Allows you gain speed and higher turning circle";
		TipLine_3 = "Tap Break - Steer Left/Right - Hold Accell";
	}
	else if(Tip_To_Display==5)
	{
		TipLine_1 = "Tips - Primary Weapon Flush";
		TipLine_2 = "Energy Pickups also flush the heat on your primary weapon";
		TipLine_3 = "Resulting in mass panic around you!";
	}
	else if(Tip_To_Display==6)
	{
		TipLine_1 = "Tr-Zero - Details - 3DRad";
		TipLine_2 = "The game was originally created and prototyped in 3DRad";
		TipLine_3 = "Now written in C++ and powered by Oddity Engine 2!";
	}
	else if(Tip_To_Display==7)
	{
		TipLine_1 = "Tr-Zero - Details - Physx";
		TipLine_2 = "Rayscans are the only Physx element used in Bike Movement";
		TipLine_3 = "40 Bikes is possible due to custom Vector3 and Quat coding!";
	}
	else if(Tip_To_Display==8)
	{
		TipLine_1 = "Tips - Recommended Upgrades";
		TipLine_2 = "Energy Systems should always be your prioity upgrades.";
		TipLine_3 = "'Bikes gotta have energy to go brum brum ;)'";
	}
	else if(Tip_To_Display==9)
	{
		TipLine_1 = "Tips - Heres a Tip!";
		TipLine_2 = "This Tip is Extra Special, and comes with no frills";
		TipLine_3 = "Either that, or, Random Number Generation loves you :P";
	}
	else if(Tip_To_Display==10)
	{
		TipLine_1 = "Tr-Zero - Details - Jimmy";
		TipLine_2 = "Rumor has it: Dave who made Oddity Engine 2, loves a bottle called Jimmy!";
		TipLine_3 = "And the guy typing this loves a good Cider ;)";
	}
	else if(Tip_To_Display==11)
	{
		TipLine_1 = "Tr-Zero - ScreenShots";
		TipLine_2 = "Press F12 to save a screenshot";
		TipLine_3 = "Screenshots are stored in \\trzero_res\\#screenshots";
	}
	else if(Tip_To_Display==12)
	{
		TipLine_1 = "Tr-Zero - Toggle Interface Shown";
		TipLine_2 = "Press F11 to toggle the 2d interface";
		TipLine_3 = "The interface can be toggled at any time, just remember to turn it back on ;)";
	}
	else if(Tip_To_Display==13)
	{
		TipLine_1 = "Tr-Zero - Details - FTP";
		TipLine_2 = "The game uses an excellent C++ FTP class libary created by Thomas Oswald";
		TipLine_3 = "Its utilized for all master server functions and data sends/pulls";
	}
	else if(Tip_To_Display==14)
	{
		TipLine_1 = "Tr-Zero - Details - Master Server";
		TipLine_2 = "Our master server runs on a 2005 PC and customized distro of Debian Linux";
		TipLine_3 = "Its good to recycle whilst sharing my standard home internet connection!";
	}
	//-------------------------------------------------------------
	//print
	D3DXVECTOR2 vPrint = D3DXVECTOR2(0.0f,9.0f);
	iPrint((char*)TipLine_1.c_str(),cGame_Font.f16pt,&vPrint,&gFontGreyLight,gFont,true);
	vPrint.y -= 1.0f;
	iPrint((char*)TipLine_2.c_str(),cGame_Font.f16pt,&vPrint,&gFontGreyDark,gFont,true);
	vPrint.y -= 0.5f;
	iPrint((char*)TipLine_3.c_str(),cGame_Font.f16pt,&vPrint,&gFontGreyDark,gFont,true);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - LOADINGSCREEN - DESTROY
///*****************************************************************
void Game_LoadingScreen::Destroy(void)
{
	//-------------------------------------------------------------
	iSpriteDestroy(Sprite_LoadingScreen);
	//-------------------------------------------------------------
	//bLoadingScreen_Created
	bLoadingScreen_Created = false;
	//-------------------------------------------------------------
}