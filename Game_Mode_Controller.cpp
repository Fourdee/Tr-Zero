//-----------------------------------------------------------------
// About:
//
// name: "Game_Mode_Controller.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
// usage: Contols game specific modes, loads required data and updates systems
// eg: weapons enabler etc
//
// device input: none.
//
// todo: 
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Mode_Controller.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - MODECONTROLLER - CONSTRUCTORS
///*****************************************************************
Game_Mode_Controller::Game_Mode_Controller(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
Game_Mode_Controller::~Game_Mode_Controller(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - MODECONTROLLER - GlobalMonitor
///*****************************************************************
void Game_Mode_Controller::GlobalMonitor(void)
{
	//-------------------------------------------------------------
	//Player finished race
	if(!cGame_RaceTracker.bBikeRacing[gAi_Max_Count])
	{
		///End it
		gRaceState = 2;
		///Apply failures
		if(gGameMode==3)///Elimiation
		{
			if(cGame_RaceTracker.Position_Current[gAi_Max_Count]>1)
			{
				gRaceWin = false;
			}
		}
		if(gGameMode==4)///Anhinilation
		{
			if(cGame_Bike[gAi_Max_Count].Weapons.TotalKills<Annihilation.KillsRequired)
			{
				gRaceWin = false;
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODECONTROLLER - ApplyNewGlobalFlags
///*****************************************************************
void Game_Mode_Controller::ApplyNewGlobalFlags(void)
{
	//-------------------------------------------------------------
	//Reset "per level change" flags
	///Menu state
	gMenuId = 0;
	gMenuSubId = 0;
	gMenu_Active = false;
	///Others
	gRaceWin = true;///Only apply Failures
	gRaceState = 0; //Not started
	gGameState = gGameStateChange;
	gGameMode = gGameModeChange;
	gPaused = false;
	gResetLevel = false;
	gBikesGo = false;
	gWeaponsEnable = false;
	gBoostEnable = false;
	gLapsUpdate = false;
	gKillBasedPositions = false;
	gRaceCountdown = 3600;///Net limit
	gRaceCountdown_Net_Use = false;
	///Network State reset
	gServerState = 0;
	cGame_Network.ZeroData();
	//-------------------------------------------------------------
	//Setup Flags
	if(gGameState==0)//Menu
	{
		gLapMax = 10;
		//gAi_Max_Count = MAX_BIKE_AI_COUNT;
		gAi_Max_Count = 29;
		gWeaponsTrackEnable = false;
		gBoostTrackEnable = false;
		gRespawnEnable = false;
		gTrackReverse = 0;
		gMenuId = 2;
		//Gfx optimizer check
		if(gFirstRun)
		{
			gGfxOptimiserState = 2;
			gMenuId = 3;
		}
		//Bring network players back to network menu
		if(cGame_Network.Client.State==2){gMenuId = 13;}
		else if(cGame_Network.Server.State==2){gMenuId = 12;}
		gMenuSubId = 0;
		gMenu_Active = true;
		//Prevent Menu from being next track
		gGameStateChange = 1;
	}
	else if(gGameMode==0)//TimeTrial
	{
		gLapMax = 99;
		gAi_Max_Count = gNumberOfClients;
		gWeaponsTrackEnable = false;
		gBoostTrackEnable = true;
		gRespawnEnable = true;
		gLapsUpdate = true;
	}
	else if(gGameMode==1)//Normal Race
	{
		gLapMax = TotalLaps();///Track + speedclass specfic
		gAi_Max_Count = gAi_UserChange;
		gWeaponsTrackEnable = false;
		gBoostTrackEnable = true;
		gRespawnEnable = true;
		gLapsUpdate = true;
		gRaceCountdown_Net_Use = true;
	}
	else if(gGameMode==2)//Normal Weapon Race
	{
		gLapMax = TotalLaps();///Track + speedclass specfic
		gAi_Max_Count = gAi_UserChange;
		gWeaponsTrackEnable = true;
		gBoostTrackEnable = true;
		gRespawnEnable = true;
		gLapsUpdate = true;
		gRaceCountdown_Net_Use = true;
	}
	else if(gGameMode==3)//Elimination
	{
		gAi_Max_Count = 5;
		//Network add
		if(gNumberOfClients>gAi_Max_Count)
		{
			gAi_Max_Count = gNumberOfClients;
		}
		gLapMax = gAi_Max_Count;
		gWeaponsTrackEnable = false;
		gBoostTrackEnable = true;
		gRespawnEnable = false;
		gLapsUpdate = true;
	}
	else if(gGameMode==4)//Annihilation
	{
		gLapMax = 999;
		gAi_Max_Count = gAi_UserChange;
		gWeaponsTrackEnable = true;
		gBoostTrackEnable = true;
		gRespawnEnable = true;
		gLapsUpdate = true;
		gKillBasedPositions = true;
	}
	else if(gGameMode==5)//Arena
	{
		gLapMax = 999;
		gAi_Max_Count = gAi_UserChange;
		gWeaponsTrackEnable = true;
		gBoostTrackEnable = true;
		gRespawnEnable = true;
		gKillBasedPositions = true;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODECONTROLLER - CREATE
///*****************************************************************
void Game_Mode_Controller::Create(void)
{
	//-------------------------------------------------------------
	//Setup Flags
	if(gGameState==0)//Menu
	{
		//ApplyNewGlobalFlags() Only Changes
	}
	else if(gGameMode==0)//TimeTrial
	{
		//ApplyNewGlobalFlags() Only Changes
	}
	else if(gGameMode==1)//Normal Race
	{
		//ApplyNewGlobalFlags() Only Changes
	}
	else if(gGameMode==2)//Normal Weapon Race
	{
		//ApplyNewGlobalFlags() Only Changes
	}
	else if(gGameMode==3)//Elimination
	{
		Elimination.Create();
	}
	else if(gGameMode==4)//Annihilation
	{
		Annihilation.Create();
	}
	else if(gGameMode==5)//Arena
	{
		Arena.Create();
	}
	//-------------------------------------------------------------
	//Setup Intro
	Intro.Create();
	//Setup EndRace
	EndRace.Create();
	//-------------------------------------------------------------
	//Weapons Systems
	if(gWeaponsTrackEnable)
	{
		WeaponsEnabler.Create();
		WeaponsPickup.Create();
		//Utility Additions
		UtilityPickup.Create();
	}
	//-------------------------------------------------------------
	//Boost Systems
	if(gBoostTrackEnable)
	{
		BoostEnabler.Create();
		EnergyPickup.Create();
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODECONTROLLER - UPDATE
///*****************************************************************
void Game_Mode_Controller::Update(void)
{
	//-------------------------------------------------------------
	if(gGameState>0)//Not for menu
	{
		//-------------------------------------------------------------
		//Network monitor - checks other players/counts down when one has finished
		NetworkMonitor();
		//Global monitor - Checks when player bike has stopped racing, applies gRaceWin and gRaceState==2
		GlobalMonitor();
		//GameMode Specfic Scenario Updates
		if(gGameMode==3)///Elimination
		{
			Elimination.Update();
		}
		//-------------------------------------------------------------
		//intro seq
		if(gRaceState==0)
		{
			Intro.Update();
		}
		//Run Race
		else if(gRaceState==1 && 
			gBikesGo)
		{
			if(gGameMode==4)///Annihilation
			{
				Annihilation.Update();
			}
			else if(gGameMode==5)///Arena DM
			{
				Arena.Update();
			}
			//Weapons Systems
			if(gWeaponsTrackEnable)
			{
				WeaponsEnabler.Update();
				WeaponsPickup.Update();
				UtilityPickup.Update();
			}
			//Boost Systems
			if(gBoostTrackEnable)
			{
				BoostEnabler.Update();
				EnergyPickup.Update();
			}
		}
		//End race seq
		else if(gRaceState==2)
		{
			//Update Endrace
			EndRace.Update();
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - MODECONTROLLER - NetworkMonitor
///*****************************************************************
void Game_Mode_Controller::NetworkMonitor(void)
{
	//-------------------------------------------------------------
	//Network wait for rest to finish
	///Network game - put timer to 60 seconds - wait
	bool bCountDownRunning = false;
	if(iNetworkIsActive())
	{
		///Check if other bikes have finished
		int TotalCheck = 0;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(!cGame_RaceTracker.bBikeRacing[i])
			{
				TotalCheck++;
			}
		}
		if(!cGame_RaceTracker.bBikeRacing[gAi_Max_Count])
		{
			TotalCheck++;
		}

		///All Bikes have finished, end game
		if(TotalCheck==gNumberOfClients + 1)
		{
			cGame_Camera.bSpectate = false;
			gRaceCountdown = 0;
			gRaceState = 2;
		}
		///One+ bike has finished, begin countdown?
		else if(gRaceCountdown_Net_Use &&
				TotalCheck>0 &&
				gRaceCountdown>0)
		{
			bCountDownRunning = true;
			if(cGame_Network.Server.State==2)
			{
				if(gRaceCountdown>3600)
				{
					///Nudge timer down to 60 seconds
					gRaceCountdown = 3600;
				}
				else
				{
					gRaceCountdown--;
				}
			}
		}
		///debug
		//sprintf_s(gCharBuffer,"Total Finished #%i",TotalCheck);
		//iPrint(gCharBuffer,cGame_Font.f28pt,&D3DXVECTOR2(0.0f,4.0f),&gFontWhite,gFont,true);

		//Print Countdown info for all players
		if(bCountDownRunning)
		{
			sprintf_s(gCharBuffer,"Time Remaning #%i",gRaceCountdown / 60);
			iPrint(gCharBuffer,cGame_Font.f22pt,&D3DXVECTOR2(0.0f,-11.0f),&gFontWhite,gFont,true);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - MODECONTROLLER - TotalLaps
///*****************************************************************
int Game_Mode_Controller::TotalLaps(void)
{
	//-------------------------------------------------------------
	int TotalLaps = 808;///== add a track
	//-------------------------------------------------------------
	//Volex
	if(gGameState==1)
	{
		if(gSpeedClass==0)///250cc
		{
			TotalLaps = 3;
		}
		else if(gSpeedClass==1)///500cc
		{
			TotalLaps = 4;
		}
		else if(gSpeedClass==2)///750cc
		{
			TotalLaps = 5;
		}
		else if(gSpeedClass==3)///1000cc
		{
			TotalLaps = 6;
		}
	}
	//Silence
	else if(gGameState==2)
	{
		if(gSpeedClass==0)///250cc
		{
			TotalLaps = 5;
		}
		else if(gSpeedClass==1)///500cc
		{
			TotalLaps = 6;
		}
		else if(gSpeedClass==2)///750cc
		{
			TotalLaps = 8;
		}
		else if(gSpeedClass==3)///1000cc
		{
			TotalLaps = 10;
		}
	}
	//Phantom
	else if(gGameState==3)
	{
		if(gSpeedClass==0)///250cc
		{
			TotalLaps = 2;
		}
		else if(gSpeedClass==1)///500cc
		{
			TotalLaps = 3;
		}
		else if(gSpeedClass==2)///750cc
		{
			TotalLaps = 4;
		}
		else if(gSpeedClass==3)///1000cc
		{
			TotalLaps = 5;
		}
	}
	//-------------------------------------------------------------
	return TotalLaps;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODECONTROLLER - DESTROY
///*****************************************************************
void Game_Mode_Controller::Destroy(void)
{
	//-------------------------------------------------------------
	//Weapons Systems
	if(gWeaponsTrackEnable)
	{
		WeaponsEnabler.Destroy();
		WeaponsPickup.Destroy();
		//Utility Additions
		UtilityPickup.Destroy();
	}
	//-------------------------------------------------------------
	//Boost System
	if(gBoostTrackEnable)
	{
		BoostEnabler.Destroy();
		EnergyPickup.Destroy();
	}
	//-------------------------------------------------------------
}