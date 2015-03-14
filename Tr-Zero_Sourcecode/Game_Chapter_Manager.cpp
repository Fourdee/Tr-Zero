//-----------------------------------------------------------------
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Chapter_Manager.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - CHAPTER MANAGER - CONSTRUCTORS
///*****************************************************************
Game_Chapter_Manager::Game_Chapter_Manager(void)
{
	//-------------------------------------------------------------
	//Threaded Load/Destroy States
	tLoadState = 0;
	tDestroyState = 0;
	//-------------------------------------------------------------
}
Game_Chapter_Manager::~Game_Chapter_Manager(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CHAPTER MANAGER - LOADBOOT
///*****************************************************************
void Game_Chapter_Manager::LoadBoot(void)
{
	//-------------------------------------------------------------
	//Settings
	cGame_Settings.Create();
	//-------------------------------------------------------------
	//physx global
	iPhysxGlobalDirectionalLightEnableSet(true,false,false,false);
	//-------------------------------------------------------------
	//camera
	cGame_Camera.Create();
	//-------------------------------------------------------------
	//font
	cGame_Font.Create();
	//-------------------------------------------------------------
	//xbox 360 controller
	cGame_Input_xbox360controller.Create();
	//-------------------------------------------------------------
	//physx materials
	cGame_Physx_Material.Create();
	//-------------------------------------------------------------
	//physx collision masks
	cGame_Physx_Collision_Mask.Create();
	//-------------------------------------------------------------
	//global textures
	cGame_Asset_Global_Texture.Create();
	//-------------------------------------------------------------
	//global Text Descriptions
	cGame_Global_Text_Description.Create();
	//-------------------------------------------------------------
	//Network
	cGame_Network.Create();
	//-------------------------------------------------------------
	//Apply final flags before updating main loop
	gGameState = 0;
	gGameStateChange = gGameState;

	//
	//gGameState = 3;
	//gGameStateChange = gGameState;
	//gGameMode = 2;
	//gGameModeChange = gGameMode;
	//gSpeedClass = 3;
	//gTrackReverse = false;
	//gAi_UserChange = 39;

	///ARENA
	//gGameState = 10;
	//gGameStateChange = gGameState;
	//gGameMode = 5;
	//gGameModeChange = gGameMode;
	//gSpeedClass = 0;
	//gTrackReverse = false;
	//gAi_UserChange = 39;

	gLoad = true;
	gDestroy = false;
	gBootLoadCompleted = true;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CHAPTER MANAGER - Update_CoreGame
///*****************************************************************
void Game_Chapter_Manager::Update_CoreGame(void)
{
	//-------------------------------------------------------------
	//Pre Update
	//-------------------------------------------------------------
	///Update FPS monitor
	gFps = iFrameRate();
	///Reset Gamma multi
	gGammaMulti = 1.0f;
	//-------------------------------------------------------------
	//Update Inputs/Bikes
	//-------------------------------------------------------------
	///Network Recieve (START)
	cThread.Stop(2);
	cThread.Start(2);
	///Player Input
	cGame_Controls.Update();
	///Replay File Stream (WAIT)
	cThread.Stop(1);
	///Network Receieve (WAIT)
	cThread.Stop(2);

	///Process Bikes
	cGame_Bike[gAi_Max_Count].Update();
	for(int i=0;i<gAi_Max_Count;i++)
	{
		cGame_Bike[i].Update();
	}
	//-------------------------------------------------------------
	//Post Update
	//-------------------------------------------------------------
	cGame_Camera.Update();
	cGame_Mesh.Update_Globals();

	///Mesh Audio Systems (START)
	cThread.Start(0);

		cGame_Menu.Update();
		cGame_Hud.Update();
		cGame_RaceTracker.Update();
		cGame_Mode_Controller.Update();

		///Network Send - (START)
		cGame_Network.bThread_Send = true;
		cThread.Start(2);

	///Mesh Audio Systems (WAIT)
	cThread.Stop(0);

	///Replay File Stream - (START)
	cGame_Replay.Update();
	cThread.Start(1);
	//-------------------------------------------------------------
	//End
	//-------------------------------------------------------------
	cGame_Timer.Update();
	cGame_DevMode.Update();
	cGame_Optimiser.Update();

	///Mouse Show-Hide
	iWindowsMouseHide(!gMenu_Active);

	///Hide 2d prints?
	if(gDisable2D)
	{
		iPrintsHide();
	}

	///CHEATS
	if(!gReleaseBuild &&
		iKeyClick(DIK_L) && 
		cGame_PlayerStats.Player_Level < 30)
	{
		cGame_PlayerStats.Player_Level++;
		cGame_PlayerStats.Upgrade_Points_Total += gPointsPerLevel;
		cGame_PlayerStats.Upgrade_Points_Remaining += gPointsPerLevel;
	}

	///NET RESET RECORDS
	//if(gClearOnlineRecords &&
	//	iKeyClick(DIK_E))
	//{
	//	//Save File
	//	//cGame_PlayerStats.Kill_Total++;
	//	//cGame_PlayerStats.Death_Total = 0;
	//	//if(cGame_PlayerStats.Kill_Total>5)
	//	//{
	//	//	cGame_PlayerStats.Kill_Total = 0;
	//	//}
	//	cGame_Ftp.UploadGameStats();
	//}

	///FPS DROP
	if(gFps<50)
	{
		sprintf_s(gCharBuffer,"Fps Drop %d",60 - gFps);
		iPrint(gCharBuffer,cGame_Font.f20pt,&D3DXVECTOR2(10.0f,-5.0f),&D3DXVECTOR4(1.0f,1.0f,0.0f,1.0f),gFont,true);
	}
	//iPrint3((char*)iNetExternalIp().c_str(),cGame_Font.f24pt,&D3DXVECTOR2(0.0f,8.0f),&D3DXVECTOR4(1.0f,1.0f,0.0f,1.0f),gFont,true);
	//iPrint3((char*)cGame_Ftp.IpAddressMine.c_str(),cGame_Font.f24pt,&D3DXVECTOR2(0.0f,6.0f),&D3DXVECTOR4(1.0f,1.0f,0.0f,1.0f),gFont,true);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CHAPTER MANAGER - LOAD
///*****************************************************************
void Game_Chapter_Manager::Load(void)
{
	//-------------------------------------------------------------
	if(tLoadState==0)
	{
		cGame_LoadingScreen.LoadingStageInfo = "Master Server Connect";
	}
	else if(tLoadState==1)
	{
		///Check for MOTD & Master Server Status
		cGame_Ftp.MasterServerMOTD();
		cGame_LoadingScreen.LoadingStageInfo = "Apply New Flags";
	}
	else if(tLoadState==2)
	{
		///GLOBAL PHYSX PAUSE (must be updated here, after 1/2 loops, not in int load section)
		iPhysxPause(gPhysxPause);
		///Player stats
		cGame_PlayerStats.Create();
		///Reset + Apply level data flags
		cGame_Mode_Controller.ApplyNewGlobalFlags();
		///Load upgrade data
		cGame_Upgrades.Create();
		///Reset Network check data
		ZeroData_Global_Net_Packets();
		///Which bike Model?
		gBikeModelType_Player = 0;
		gBikeModelType_Ai = 0;
		if(gGameStateChange==0 && cGame_PlayerStats.Player_Level>=15)///Menu
		{
			gBikeModelType_Player = 1;
			gBikeModelType_Ai = 1;
		}
		else if(gSpeedClass>1)///750-1000cc = Daves bike
		{
			gBikeModelType_Player = 1;
			gBikeModelType_Ai = 1;
		}
		cGame_LoadingScreen.LoadingStageInfo = "Physx & Camera";
	}
	else if(tLoadState==3)
	{
		//-------------------------------------------------------------
		//Track Physx Mesh
		cGame_Track.Physx.Create();
		//-------------------------------------------------------------
		//camera
		cGame_Camera.ZeroData();
		//-------------------------------------------------------------
		cGame_LoadingScreen.LoadingStageInfo = "Creating Bikes";
	}
	else if(tLoadState==4)
	{
		//Spawn
		cGame_Spawn.Create();
		//bikes
		for(int i=0;i<=gAi_Max_Count;i++)
		{
			cGame_Bike[i].Create(i);
		}
		cGame_LoadingScreen.LoadingStageInfo = "Creating Meshes";
	}
	else if(tLoadState==5)
	{
		//-------------------------------------------------------------
		//skybox/skydome
		cGame_SkyDome.Create();
		//-------------------------------------------------------------
		//Track - Mesh
		cGame_Track.Create();
		//-------------------------------------------------------------
		//Mesh Assets
		cGame_Mesh.Create();
		//-------------------------------------------------------------
		//Particle
		cGame_Particle.Create();
		//-------------------------------------------------------------
		//Race Tracker
		cGame_RaceTracker.Create();
		//-------------------------------------------------------------
		cGame_LoadingScreen.LoadingStageInfo = "Creating Interface";
	}
	else if(tLoadState==6)
	{
		//-------------------------------------------------------------
		//menu main
		cGame_Menu.Create();
		//-------------------------------------------------------------
		//Hud
		cGame_Hud.Create();
		//-------------------------------------------------------------
		cGame_LoadingScreen.LoadingStageInfo = "Creating Audio";
	}
	else if(tLoadState==7)
	{
		//-------------------------------------------------------------
		//Audio
		cGame_Audio.Create();
		//-------------------------------------------------------------
		//Game Mode Controller
		cGame_Mode_Controller.Create();
		//-------------------------------------------------------------
		//Game Timer
		cGame_Timer.Create();
		//-------------------------------------------------------------
		//Post Processing
		cGame_PostProcessing.Create();
		//-------------------------------------------------------------
		//Replay
		cGame_Replay.Create();
		//-------------------------------------------------------------
		//Game Optimiser
		cGame_Optimiser.Create();
	}
	else
	{
		gLoad = false;
	}
	//-------------------------------------------------------------
	tLoadState++;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CHAPTER MANAGER - DESTROY
///*****************************************************************
void Game_Chapter_Manager::Destroy(void)
{
	//-------------------------------------------------------------
	if(tDestroyState==0)
	{
		cGame_LoadingScreen.LoadingStageInfo = "Uploading Stats";
	}
	else if(tDestroyState==1)
	{
		///Player stats
		cGame_PlayerStats.Destroy();
		///Upload GameStats to MASTER SERVER WHO)O)O)O!!!!!!
		if(!gExitWin &&
			gGameState>0 &&
			gMasterServerOnline &&
			cGame_Network.Client.State==0)///Dont upload networked clients
		{
			cGame_Ftp.UploadGameStats();
		}
		///Video/Audio
		cGame_Settings.SaveSettings();
		///upgrade data
		cGame_Upgrades.SaveSettings();
		///Update Text Descriptions
		cGame_Global_Text_Description.Create();
		cGame_LoadingScreen.LoadingStageInfo = "Destroying Assets";
	}
	else if(tDestroyState==2)
	{
		//-------------------------------------------------------------
		//Game Timer
		cGame_Timer.Destroy();
		//-------------------------------------------------------------
		//Game Mode Controller
		cGame_Mode_Controller.Destroy();
		//-------------------------------------------------------------
		//Particle
		cGame_Particle.Destroy();
		//-------------------------------------------------------------
		//Audio
		cGame_Audio.Destroy();
		//-------------------------------------------------------------
		//Bikes
		for(int i=0;i<40;i++)
		{
			cGame_Bike[i].Destroy();
		}
		//-------------------------------------------------------------
		//Track - Mesh
		cGame_Track.Destroy();
		//-------------------------------------------------------------
		//skybox/skydome
		cGame_SkyDome.Destroy();
		//-------------------------------------------------------------
		//Hud
		cGame_Hud.Destroy();
		//-------------------------------------------------------------
		//menu main
		cGame_Menu.Destroy();
		//-------------------------------------------------------------
		//Mesh Assets
		cGame_Mesh.Destroy();
	}
	//-------------------------------------------------------------
	//Exit to Windows?
	else if(gExitWin)
	{
		iExit();
	}
	///Apply Loading state
	else
	{
		gLoad = true;
		gDestroy = false;
	}
	//-------------------------------------------------------------
	tDestroyState++;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - CHAPTER MANAGER - UPDATE
///*****************************************************************
void Game_Chapter_Manager::Update(void)
{
	//-------------------------------------------------------------
	//Boot Loader
	if(!gBootLoadCompleted)
	{
		LoadBoot();
		///Create a pretty intro - not using OE2 iVideoPlay which crashes after its finished.
		///gBootLoadState
	}
	//-------------------------------------------------------------
	//Destroy
	else if(gDestroy)
	{
		///Stop all Threads
		cThread.Stop(0);
		cThread.Stop(1);
		cThread.Stop(2);
		///Create Loading Screen
		if(!cGame_LoadingScreen.bLoadingScreen_Created)
		{
			tLoadState = 0;
			tDestroyState = 0;
			cGame_LoadingScreen.Create();
		}
		///Update Loading Screen & Destroy Stage
		else
		{
			Destroy();
			cGame_LoadingScreen.Update();
		}
	}
	//----------------------------------------------------------
	//Loading
	else if(gLoad)
	{
		///Create Loading Screen (needed for boot load)
		if(!cGame_LoadingScreen.bLoadingScreen_Created)
		{
			cGame_LoadingScreen.Create();
		}
		///Update Loading Screen & Destroy Stage
		else
		{
			Load();
			cGame_LoadingScreen.Update();
		}
	}
	//----------------------------------------------------------
	//Game Ready, run it!
	else
	{
		///Destroy our loading screen
		if(cGame_LoadingScreen.bLoadingScreen_Created)
		{
			cGame_LoadingScreen.Destroy();
		}
		///Update Game
		else
		{
			Update_CoreGame();
		}
	}
	//-------------------------------------------------------------
}