//-----------------------------------------------------------------
// About:
//
// name: "Game_Mode_EndRace.cpp:
//
// usage: Finishes the race, calcs scores, displays scores etc etc
//
// device input: none.
//
// todo:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Mode_EndRace.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - MODE - INTRO - CONSTRUCTORS
///*****************************************************************
Game_Mode_EndRace::Game_Mode_EndRace(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Mode_EndRace::~Game_Mode_EndRace(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - MODE - INTRO - ZERODATA
///*****************************************************************
void Game_Mode_EndRace::ZeroData(void)
{
	//-------------------------------------------------------------
	bExit = false;
	bPlayerUseAiControls = false;
	sHuman_Position = "";
	ScoreTimer = 0;
	ExitTimer = 1200;
	bHideResults = false;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - INTRO - CREATE
///*****************************************************************
void Game_Mode_EndRace::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - INTRO - UPDATE
///*****************************************************************
void Game_Mode_EndRace::Update(void)
{
	//-------------------------------------------------------------
	//Switch Player controls to AI
	if(!bPlayerUseAiControls)
	{
		cGame_Bike[gAi_Max_Count].bAiTakeover = true;
		bPlayerUseAiControls = true;
	}
	//-------------------------------------------------------------
	//Update New XP-Level
	else if(!cGame_PlayerStats.bEndRace_Applied)
	{
		cGame_PlayerStats.Update_New_Xp();
		cGame_PlayerStats.bEndRace_Applied = true;
		///Obtain 1st/2nd/3rd string etc
		sHuman_Position = cGame_Global_Text_Description.PositionReadout(cGame_RaceTracker.Position_Current[gAi_Max_Count]);
	}
	//-------------------------------------------------------------
	//Print Results
	else
	{
		if(ScoreTimer<360)
		{
			ScoreTimer++;
			///Reset spectate
			cGame_Camera.bSpectate = false;
			cGame_Camera.SpectateId = gAi_Max_Count;
			///Set endrace camera mode
			cGame_Camera.Mode_InGame = 5;
			///Disable Scoreboards whilst showing player results
			cGame_Hud.bScoreboard = false;
			bHideResults = false;
		}

		if(!cGame_Hud.bScoreboard &&
			!cGame_Camera.bSpectate &&
			!bHideResults)
		{
			gGammaMulti = 0.8f;
			PrintResults();
		}
	}
	//-------------------------------------------------------------
	//Exit
	if(ScoreTimer >= 360 && 
		!bExit)
	{
		//Network Exit
		if(iNetworkIsActive())
		{
			///Network check
			if(gRaceCountdown>0)
			{
				if(!cGame_Camera.bSpectate)
				{
					iPrint3((char*)"Waiting for Race To Finish - Press ] to spectate",cGame_Font.f22pt,&D3DXVECTOR2(0.0f,-10.0f),&gFontWhite,gFont,true);
				}
			}
			///Start Auto Exit countdown
			else if(ExitTimer>0)
			{
				ExitTimer--;
				sprintf_s(gCharBuffer,"Exit in #%i Seconds",ExitTimer / 60);
				iPrint(gCharBuffer,cGame_Font.f22pt,&D3DXVECTOR2(0.0f,-11.0f),&gFontWhite,gFont,true);
				///Reset spectate
				cGame_Camera.bSpectate = false;

				//Print Scoreboards here---------------------------------------------

			}
			///Exit
			else if(cGame_Network.Server.State==2)
			{
				cGame_Audio.Music.MusicStop();
				cGame_Audio.Menu.MenuFx(3);
				gGameStateChange = 0;
				cGame_Gamma_Fade.bFadeOut = true;
				bExit = true;
			}
		}
		//Offline Exit
		else
		{
			iPrint3("<< Press Start to Exit >>",cGame_Font.f24pt,&D3DXVECTOR2(0.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,true);
			if(cGame_Controls.Input_Action_Start())
			{
				cGame_Audio.Music.MusicStop();
				cGame_Audio.Menu.MenuFx(3);
				gGameStateChange = 0;
				cGame_Gamma_Fade.bFadeOut = true;
				bHideResults = false;
				bExit = true;
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - MODE - ENDRACE - PRINTRESULTS
///*****************************************************************
void Game_Mode_EndRace::PrintResults(void)
{
	//-------------------------------------------------------------
	D3DXVECTOR2 vRaceWin = D3DXVECTOR2(0.0f,9.0f);
	D3DXVECTOR2 vPrintInfo = D3DXVECTOR2(-3.0f,-3.0f);
	D3DXVECTOR2 vPrintData = D3DXVECTOR2(3.0f,-3.0f);
	//-------------------------------------------------------------
	//Gamemode
	iPrint3((char*)gInfoGameMode.c_str(),cGame_Font.f24pt,&vRaceWin,&gFontWhite,gFont,true);
	vRaceWin.y -= 1.0f;
	//Race Win/Loss?
	if(gRaceWin)
	{
		iPrint3((char*)"Game Completed",cGame_Font.f36pt,&vRaceWin,&gFontWhite,gFont,true);
	}
	else
	{
		iPrint3((char*)"Game Over",cGame_Font.f36pt,&vRaceWin,&D3DXVECTOR4(1.0f,0.3f,0.0f,1.0f),gFont,true);
	}
	vRaceWin.y -= 2.0f;
	//Position
	if(ScoreTimer > 200)
	{
		iPrint3((char*)sHuman_Position.c_str(),48.0f,&vRaceWin,&gMenuFontColour,gFont,true);
	}
	vRaceWin.y -= 1.0f;
	iPrint((char*)"Position",cGame_Font.f24pt,&vRaceWin,&gFontWhite,gFont,true);
	//-------------------------------------------------------------
	if(ScoreTimer >= 360 &&
		!cGame_Camera.bSpectate)
	{
		//Weapon Stats
		if(gWeaponsTrackEnable)
		{
			if(gGameMode==4)//Annihilation 
			{
				//Kills required
				iPrint3((char*)"Kills Required",cGame_Font.f18pt,&vPrintInfo,&gFontWhite,gFont,false);
				sprintf_s(gCharBuffer,"%i",cGame_Mode_Controller.Annihilation.KillsRequired);
				iPrint3(gCharBuffer,cGame_Font.f24pt,&vPrintData,&gFontWhite,gFont,false);
				vPrintInfo.y -= 0.75f;
				vPrintData.y -= 0.75f;
			}
			//Total Kills
			iPrint3((char*)"Kill Total",cGame_Font.f18pt,&vPrintInfo,&gFontWhite,gFont,false);
			sprintf_s(gCharBuffer,"%i",cGame_Bike[gAi_Max_Count].Weapons.TotalKills);
			iPrint3(gCharBuffer,cGame_Font.f24pt,&vPrintData,&gFontWhite,gFont,false);
			vPrintInfo.y -= 0.75f;
			vPrintData.y -= 0.75f;
			//Damage Done
			iPrint3((char*)"Damage Output",cGame_Font.f18pt,&vPrintInfo,&gFontWhite,gFont,false);
			sprintf_s(gCharBuffer,"%i",cGame_Bike[gAi_Max_Count].Weapons.TotalDamageOutput);
			iPrint3(gCharBuffer,cGame_Font.f24pt,&vPrintData,&gFontWhite,gFont,false);
			vPrintInfo.y -= 1.0f;
			vPrintData.y -= 1.0f;
			//XP - Total Kills
			iPrint3((char*)"XP - Kills",cGame_Font.f18pt,&vPrintInfo,&gFontWhite,gFont,false);
			sprintf_s(gCharBuffer,"%i",cGame_PlayerStats.Info_Xp_Kills);
			iPrint3(gCharBuffer,cGame_Font.f24pt,&vPrintData,&gFontWhite,gFont,false);
			vPrintInfo.y -= 0.75f;
			vPrintData.y -= 0.75f;
		}
		//Position XP
		iPrint3((char*)"XP - Position",cGame_Font.f18pt,&vPrintInfo,&gFontWhite,gFont,false);
		sprintf_s(gCharBuffer,"%i",cGame_PlayerStats.Info_Xp_Position);
		iPrint3(gCharBuffer,cGame_Font.f24pt,&vPrintData,&gFontWhite,gFont,false);
		vPrintInfo.y -= 0.75f;
		vPrintData.y -= 0.75f;
		//Ai Difficulty
		iPrint3((char*)"Ai Difficulty",cGame_Font.f18pt,&vPrintInfo,&gFontWhite,gFont,false);
		iPrint3((char*)gInfoAiDifficulty.c_str(),cGame_Font.f24pt,&vPrintData,&gFontWhite,gFont,false);
		vPrintInfo.y -= 0.75f;
		vPrintData.y -= 0.75f;
		//XP - Difficulty Multi
		iPrint3((char*)"XP - Multiplier",cGame_Font.f18pt,&vPrintInfo,&gFontWhite,gFont,false);
		sprintf_s(gCharBuffer,"x%0.2f",cGame_PlayerStats.fXp_Ai_Multi);
		iPrint3(gCharBuffer,cGame_Font.f24pt,&vPrintData,&gFontWhite,gFont,false);
		vPrintInfo.y -= 1.0f;
		vPrintData.y -= 1.0f;
		//XP - New Total
		iPrint3((char*)"XP - Total",cGame_Font.f18pt,&vPrintInfo,&gFontWhite,gFont,false);
		sprintf_s(gCharBuffer,"%i",cGame_PlayerStats.Info_Xp_Total);
		iPrint3(gCharBuffer,cGame_Font.f24pt,&vPrintData,&gFontWhite,gFont,false);
		vPrintInfo.y -= 0.75f;
		vPrintData.y -= 0.75f;
		//XP - MAX LEVEL
		if(cGame_PlayerStats.Player_Level==gLevelMax)
		{
			vPrintInfo = D3DXVECTOR2(-7.0f,-5.0f);
			vPrintData = vPrintInfo;
			vPrintData.y += 1.5f;
			//XP - New Total
			iPrint3((char*)"Level Max",cGame_Font.f24pt,&vPrintInfo,&gFontWhite,gFont,true);
			sprintf_s(gCharBuffer,"%i",cGame_PlayerStats.Player_Level);
			iPrint3(gCharBuffer,cGame_Font.f30pt,&vPrintData,&gMenuFontColour,gFont,true);
			vPrintInfo.y -= 0.75f;
			vPrintData.y -= 0.75f;
		}
		//XP - Level Up?
		else if(cGame_PlayerStats.bInfo_Xp_LevelUp)
		{
			vPrintInfo = D3DXVECTOR2(-7.0f,-5.0f);
			vPrintData = vPrintInfo;
			vPrintData.y += 1.5f;

			//XP - New Total
			iPrint3((char*)"Level Up!",cGame_Font.f24pt,&vPrintInfo,&gFontWhite,gFont,true);
			sprintf_s(gCharBuffer,"%i",cGame_PlayerStats.Player_Level);
			iPrint3(gCharBuffer,48.0f,&vPrintData,&gMenuFontColour,gFont,true);
			vPrintInfo.y -= 0.75f;
			vPrintData.y -= 0.75f;
		}
		//XP - needed for next Level
		else
		{
			//XP - To level up
			int XpToLevelUp = cGame_PlayerStats.XP_Required_Next_Level - cGame_PlayerStats.Player_XP;
			iPrint3((char*)"XP For Next Level",cGame_Font.f18pt,&vPrintInfo,&gFontWhite,gFont,false);
			sprintf_s(gCharBuffer,"%i",XpToLevelUp);
			iPrint3(gCharBuffer,cGame_Font.f24pt,&vPrintData,&gFontWhite,gFont,false);
			vPrintInfo.y -= 0.75f;
			vPrintData.y -= 0.75f;
		}
		//New Fastest Lap Record?
		if(gLapsUpdate)
		{
			D3DXVECTOR2 vInfo = D3DXVECTOR2(8.0f,-4.0f);
			cGame_Hud.TimerReadOuts("Personal Best",cGame_PlayerStats.LapRecord[gGameState][gSpeedClass][gTrackReverse],vInfo);
			vInfo.y += -3.0f;
			if(gMasterServerOnline)
			{
				//New WR
				if(cGame_PlayerStats.LapRecord[gGameState][gSpeedClass][gTrackReverse]<=cGame_PlayerStats.OnlineStats_Float_Value_1[0])
				{
					cGame_Hud.TimerReadOuts("New World Record!",cGame_PlayerStats.LapRecord[gGameState][gSpeedClass][gTrackReverse],vInfo);
					vInfo.y += -0.5f;
					vInfo.x += 1.25f;
					iPrint(gPlayerName,cGame_Font.f16pt,&vInfo,&gFontGreyDark,gFont2,true);
				}
				//Old WR
				else
				{
					cGame_Hud.TimerReadOuts("World Record",cGame_PlayerStats.OnlineStats_Float_Value_1[0],vInfo);
					vInfo.y += -0.5f;
					vInfo.x += 1.25f;
					iPrint((char*)cGame_PlayerStats.OnlineStats_Name[0].c_str(),cGame_Font.f16pt,&vInfo,&gFontGreyDark,gFont2,true);
				}
			}
		}
	}
	//-------------------------------------------------------------
}
