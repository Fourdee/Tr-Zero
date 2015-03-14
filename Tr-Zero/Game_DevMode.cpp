//-----------------------------------------------------------------
// About:
//
// name: "Game_DevMode.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
// usage: Dev Mode/Debug
//
// device input: none.
//
// todo:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_DevMode.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - FONT - CONSTRUCTORS
///*****************************************************************
Game_DevMode::Game_DevMode(void)
{
	//-------------------------------------------------------------
	page = 9;
	bNewSelection = true;
	Current = 0;
	//-------------------------------------------------------------
}

Game_DevMode::~Game_DevMode(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - DEBUG - DEVMODE
///*****************************************************************
void Game_DevMode::Update(void)
{
	//-------------------------------------------------------------
	//Activation - Disable for release builds
	if(gReleaseBuild)
	{
		gDevMode = false;
	}
	else
	{
		cGame_Controls.Input_Action_DevMode();
	}
	//-------------------------------------------------------------
	if(gDevMode)
	{
		//Respawn Bikes
		if(iKeyDown(DIK_R))
		{
			cGame_Bike[gAi_Max_Count].Energy.fEnergy = -1.0f;
			for(int i=0;i<gAi_Max_Count;i++)
			{
				cGame_Bike[i].Energy.fEnergy = -1.0f;
			}
		}
		//Vsync - Multithreading control
		if(iKeyClick(DIK_N))
		{
			gVsync = !gVsync;
			iVsyncEnable(gVsync);
		}
		if(!gVsync)
		{
			iPrint3((char*)"FPS Unlock",cGame_Font.f16pt,&D3DXVECTOR2(11.0f,-1.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,true);
		}
		//Timestep info
		sprintf_s(gCharBuffer,"Delta Timestep %0.4f",gET_DeltaTime);
		iPrint3(gCharBuffer,cGame_Font.f22pt,&D3DXVECTOR2(2.0f,-10.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
		///highest value
		static float DT_H = 0.0f;
		if(gET_DeltaTime>=DT_H)
		{
			DT_H = gET_DeltaTime;
		}
		static int resetDT_H = 0;
		resetDT_H++;
		if(resetDT_H>=360)
		{
			DT_H = 0.0f;
			resetDT_H = 0;
		}
		sprintf_s(gCharBuffer,"Delta Peak %0.3f",DT_H);
		iPrint3(gCharBuffer,cGame_Font.f22pt,&D3DXVECTOR2(2.0f,-11.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);

		//Page ID control
		if(iKeyClick(VK_PRIOR))
		{
			page++;
			bNewSelection = true;
		}
		else if(iKeyClick(VK_NEXT))
		{
			page--;
			bNewSelection = true;
		}

		if(page<0)
		{
			page = 0;
		}
		else if(page==0)
		{
			DevMode_Network();
		}
		else if(page==1)
		{
			DevMode_RaceTracker();
		}
		else if(page==2)
		{
			DevMode_Scanners();
		}
		else if(page==3)
		{
			DevMode_Visuals();
		}
		else if(page==4)
		{
			DevMode_Controls();
		}
		else if(page==5)
		{
			DevMode_Camera();
		}
		else if(page==6)
		{
			DevMode_AudioWeapons();
		}
		else if(page==7)
		{
			DevMode_AudioBikes();
		}
		else if(page==8)
		{
			DevMode_MeshAnimator();
		}
		else if(page==9)
		{
			DevMode_PointLight();
		}
		else if(page==10)
		{
			DevMode_DirectLight();
		}
		else if(page==11)
		{
			DevMode_Culling();
		}
		else if(page==12)
		{
			DevMode_Shadows();
		}
		else
		{
			page = 0;
		}



		//Change Player Bike
		if(iKeyClick(DIK_Y))
		{
			gBikeModelType_Player++;
			if(gBikeModelType_Player>1)
			{
				gBikeModelType_Player = 0;
			}
		}
		//gah humbug
		if(iKeyDown(DIK_E))
		{
			cGame_Bike[gAi_Max_Count].Energy.fEnergy = cGame_Upgrades.fEnergyMax[gAi_Max_Count];
		}
		//-------------------------------------------------------------
		//Start Stop Bikes
		if(iKeyClick(DIK_F1) || iGamepadXbox360ButtonClick(cGame_Input_xbox360controller.Gamepad,GP_BUTTON_BACK))
		{
			gBikesGo = !gBikesGo;
		}
		//-------------------------------------------------------------
		//Player Weapons
		if(iKeyDown(DIK_1) && !cGame_Bike[gAi_Max_Count].Weapons.bSecondaryInUse)
		{
			cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType = 0;
		}
		if(iKeyDown(DIK_2) && !cGame_Bike[gAi_Max_Count].Weapons.bSecondaryInUse)
		{
			cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType = 1;
		}
		if(iKeyDown(DIK_3) && !cGame_Bike[gAi_Max_Count].Weapons.bSecondaryInUse)
		{
			cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType = 2;
		}
		if(iKeyDown(DIK_4) && !cGame_Bike[gAi_Max_Count].Weapons.bSecondaryInUse)
		{
			cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType = 3;
		}
		if(iKeyDown(DIK_5) && !cGame_Bike[gAi_Max_Count].Weapons.bUtilityInUse)
		{
			cGame_Bike[gAi_Max_Count].Weapons.UtilityType = 0;
		}
		if(iKeyDown(DIK_6) && !cGame_Bike[gAi_Max_Count].Weapons.bUtilityInUse)
		{
			cGame_Bike[gAi_Max_Count].Weapons.UtilityType = 1;
		}
		if(iKeyDown(DIK_7) && !cGame_Bike[gAi_Max_Count].Weapons.bUtilityInUse)
		{
			cGame_Bike[gAi_Max_Count].Weapons.UtilityType = 2;
		}
		if(iKeyDown(DIK_8) && !cGame_Bike[gAi_Max_Count].Weapons.bUtilityInUse)
		{
			cGame_Bike[gAi_Max_Count].Weapons.UtilityType = 3;
		}
		//if(iKeyDown(DIK_6) && !bSecondaryInUse)
		//{
		//	SecondaryWeaponType = 2;
		//}
		//if(iKeyDown(DIK_7) && !bUtilityInUse)
		//{
		//	UtilityType = 3;
		//}
		//-------------------------------------------------------------
		//static bool bRender = true;
		//if(iKeyClick(DIK_O)){bRender ^= 1;}
		//if(bRender)
		//{
		//	iRenderEnable();
		//}
		//else
		//{
		//	iRenderDisable();
		//}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - DEBUG - Devmode_Save_Audio
///*****************************************************************
void Game_DevMode::Devmode_Save_Audio(void)
{
	//-------------------------------------------------------------
	HANDLE hFile; 
	DWORD dwDone; 
	char filepath[1024];

	strcpy_s(filepath,gFilePath_Settings_DevMode_Audio);
	iGlobalPathMake(filepath);

	hFile = CreateFile(filepath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		//---------------------------------------------------------
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sPrimaryGun,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sEm_Charge,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sEm_Fire,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sRail_Charge,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sRail_Fire,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sShoxwave_Fire,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sMissile_Fire,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sShield,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sDoubleDamage,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sWarp,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sEm_Charge_Ai,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sEm_Fire_Ai,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sRail_Charge_Ai,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sRail_Fire_Ai,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sShoxwave_Fire_Ai,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sMissile_Fire_Ai,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sShield_Ai,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sDoubleDamage_Ai,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sWarp_Ai,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sPrimaryTravel,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sMissile_Travel,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sMissile_Explosion,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sShoxwave_Travel,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sRail_Travel,sizeof(float),&dwDone,NULL);
	
		//WriteFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sEngine,sizeof(float),&dwDone,NULL);
		//WriteFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sTurbo,sizeof(float),&dwDone,NULL);
		//WriteFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sBoost,sizeof(float),&dwDone,NULL);
		//WriteFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sBreak,sizeof(float),&dwDone,NULL);
		//WriteFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sSlip,sizeof(float),&dwDone,NULL);
		//WriteFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sImpact,sizeof(float),&dwDone,NULL);
		//WriteFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sBoostRelease,sizeof(float),&dwDone,NULL);
		//WriteFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sShield,sizeof(float),&dwDone,NULL);
		//---------------------------------------------------------
		CloseHandle(hFile); 
	}
	bNewSelection = true;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - DEBUG - Devmode_Load_Audio
///*****************************************************************
void Game_DevMode::Devmode_Load_Audio(void)
{
	//-------------------------------------------------------------
	if(iFileExists(gFilePath_Settings_DevMode_Audio))
	{
		HANDLE hFile; 
		DWORD dwDone; 
		char filepath[1024];

		strcpy_s(filepath,gFilePath_Settings_DevMode_Audio);
		iGlobalPathMake(filepath);

		hFile = CreateFile(filepath,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if(hFile != INVALID_HANDLE_VALUE)
		{
			//-----------------------------------------------------
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sPrimaryGun,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sEm_Charge,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sEm_Fire,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sRail_Charge,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sRail_Fire,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sShoxwave_Fire,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sMissile_Fire,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sShield,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sDoubleDamage,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sWarp,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sEm_Charge_Ai,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sEm_Fire_Ai,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sRail_Charge_Ai,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sRail_Fire_Ai,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sShoxwave_Fire_Ai,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sMissile_Fire_Ai,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sShield_Ai,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sDoubleDamage_Ai,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sWarp_Ai,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sPrimaryTravel,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sMissile_Travel,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sMissile_Explosion,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sShoxwave_Travel,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&cGame_Audio.Weapons.fVolumeTarget_sRail_Travel,sizeof(float),&dwDone,NULL);
		
			//ReadFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sEngine,sizeof(float),&dwDone,NULL);
			//ReadFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sTurbo,sizeof(float),&dwDone,NULL);
			//ReadFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sBoost,sizeof(float),&dwDone,NULL);
			//ReadFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sBreak,sizeof(float),&dwDone,NULL);
			//ReadFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sSlip,sizeof(float),&dwDone,NULL);
			//ReadFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sImpact,sizeof(float),&dwDone,NULL);
			//ReadFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sBoostRelease,sizeof(float),&dwDone,NULL);
			//ReadFile(hFile,&cGame_Audio.Bike_Fx.fVolumeTarget_sShield,sizeof(float),&dwDone,NULL);
			//-----------------------------------------------------
			CloseHandle(hFile); 
		}
	}
	bNewSelection = true;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - DEBUG - DEVMODE
///*****************************************************************
void Game_DevMode::DevMode_Scanners(void)
{
	//-------------------------------------------------------------
	//End Race
	//if(iKeyClick(DIK_1))
	//{
	//	gRaceState = 0;
	//}
	//else if(iKeyClick(DIK_2))
	//{
	//	gRaceState = 1;
	//}
	//else if(iKeyClick(DIK_3))
	//{
	//	gRaceState = 2;
	//}

	//-------------------------------------------------------------
	//Print DevModeState
	iPrint((char*)"DevMode",cGame_Font.f32pt,&D3DXVECTOR2(10.0f,-10.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"[            ]",cGame_Font.f32pt,&D3DXVECTOR2(10.0f,-11.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"  Scanners",cGame_Font.f32pt,&D3DXVECTOR2(10.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	sprintf_s(gCharBuffer,"FPS %i",gFps);
	iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(10.0f,-12.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	//Reflection Export
	//if(iKeyClick(DIK_F2))
	//{
	//	if(gGameState==0)///Menu
	//	{
	//		iMeshCubicEnvironmentMapSave(cGame_Track.Mesh_Track[0],"trzero_res\\textures\\env_map\\0_menu.dds");
	//		iMeshCubicEnvironmentMapSave(cGame_Track.Mesh_Track[2],"trzero_res\\textures\\env_map\\2_menu.dds");
	//	}
	//	else if(gGameState==1)///volex
	//	{
	//		iMeshCubicEnvironmentMapSave(cGame_Track.Mesh_Track[0],"trzero_res\\textures\\env_map\\0_volex.dds");
	//		iMeshCubicEnvironmentMapSave(cGame_Track.Mesh_Track[7],"trzero_res\\textures\\env_map\\7_volex.dds");
	//	}
	//}
	//-------------------------------------------------------------
	//Print BIKE DATA
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		D3DXVECTOR2 Ai2dLoc;
		if(i3DLocationToScreen(&Ai2dLoc,&cGame_Bike[i].Manager.vTargetMesh,gCamera))
		{
			sprintf_s(gCharBuffer,"%i",cGame_Bike[i].PlayerID);
			iPrint3(gCharBuffer,cGame_Font.f16pt,&Ai2dLoc,&D3DXVECTOR4(0.0f,0.0f,1.0f,1.0f),gFont,false);
			Ai2dLoc.y -= 0.5f;
			sprintf_s(gCharBuffer,"fScanDown_DistanceCp %0.1f",cGame_Bike[i].Manager.fScanDown_DistanceCp);
			iPrint(gCharBuffer,cGame_Font.f14pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			Ai2dLoc.y -= 0.5f;
			sprintf_s(gCharBuffer,"fSmoothHeight %0.1f",cGame_Bike[i].Manager.fSmoothHeight);
			iPrint(gCharBuffer,cGame_Font.f14pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			Ai2dLoc.y -= 0.5f;
			sprintf_s(gCharBuffer,"State %i",cGame_Bike[i].InputSpeedState);
			iPrint(gCharBuffer,cGame_Font.f14pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,0.0f,1.0f,1.0f),gFont,false);
			Ai2dLoc.y -= 0.5f;
			sprintf_s(gCharBuffer,"Steering %0.2f",cGame_Bike[i].fSteering);
			iPrint(gCharBuffer,cGame_Font.f14pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,0.5f,0.0f,1.0f),gFont,false);
			Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"Lap %i",cGame_Bike[i].LapCounter.CurrentLap);
			//iPrint(gCharBuffer,cGame_Font.f16pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"Out %i",cGame_Bike[i].Weapons.TotalDamageOutput);
			//iPrint(gCharBuffer,cGame_Font.f16pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,0.5f,0.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
		}
	}

	//-------------------------------------------------------------
	//Print Sound Range Info
	//sprintf_s(gCharBuffer,"sCharge - %i",cGame_Audio.Weapons.Charging_ClosestID);
	//iPrint(gCharBuffer,cGame_Font.f16pt,&D3DXVECTOR2(10.0f,4.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//sprintf_s(gCharBuffer,"sMissile - %i",cGame_Audio.Weapons.Missile_ClosestID);
	//iPrint(gCharBuffer,cGame_Font.f16pt,&D3DXVECTOR2(10.0f,3.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//sprintf_s(gCharBuffer,"sShox - %i",cGame_Audio.Weapons.ShoxWave_ClosestID);
	//iPrint(gCharBuffer,cGame_Font.f16pt,&D3DXVECTOR2(10.0f,2.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//sprintf_s(gCharBuffer,"sEm - %i",cGame_Audio.Weapons.EmBurst_ClosestID);
	//iPrint(gCharBuffer,cGame_Font.f16pt,&D3DXVECTOR2(10.0f,1.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//sprintf_s(gCharBuffer,"sRail - %i",cGame_Audio.Weapons.Rail_ClosestID);
	//iPrint(gCharBuffer,cGame_Font.f16pt,&D3DXVECTOR2(10.0f,0.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//sprintf_s(gCharBuffer,"sPrimary - %i",cGame_Audio.Weapons.PrimaryTravel_ClosestID);
	//iPrint(gCharBuffer,cGame_Font.f16pt,&D3DXVECTOR2(10.0f,-1.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//sprintf_s(gCharBuffer,"sPrimaryProjectile - %i",cGame_Audio.Weapons.PrimaryTravel_ClosestProjectileID);
	//iPrint(gCharBuffer,cGame_Font.f16pt,&D3DXVECTOR2(10.0f,-2.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	//Print Camera Data
	//D3DXVECTOR2 vCamInfo = D3DXVECTOR2(0.0f,10.0f);
	/////Origin
	//sprintf_s(gCharBuffer,"vCamOutput.X: %0.1f",cGame_Camera.vCamOutput.x);
	//iPrint(gCharBuffer,cGame_Font.f18pt,&vCamInfo,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//vCamInfo.y -= 1.0f;
	//sprintf_s(gCharBuffer,"vCamOutput.Y: %0.1f",cGame_Camera.vCamOutput.y);
	//iPrint(gCharBuffer,cGame_Font.f18pt,&vCamInfo,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//vCamInfo.y -= 1.0f;
	//sprintf_s(gCharBuffer,"vCamOutput.Z: %0.1f",cGame_Camera.vCamOutput.z);
	//iPrint(gCharBuffer,cGame_Font.f18pt,&vCamInfo,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//vCamInfo.y -= 1.0f;
	/////Offsets
	//sprintf_s(gCharBuffer,"vCamOffset.X - %0.0f",cGame_Camera.vCamOffset.x);
	//iPrint(gCharBuffer,cGame_Font.f16pt,&vCamInfo,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//vCamInfo.y -= 1.0f;
	//sprintf_s(gCharBuffer,"vCamOffset.Y - %0.0f",cGame_Camera.vCamOffset.y);
	//iPrint(gCharBuffer,cGame_Font.f16pt,&vCamInfo,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//vCamInfo.y -= 1.0f;
	//sprintf_s(gCharBuffer,"vCamOffset.Z - %0.0f",cGame_Camera.vCamOffset.z);
	//iPrint(gCharBuffer,cGame_Font.f16pt,&vCamInfo,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//vCamInfo.y -= 1.0f;
	/////LookAt
	//sprintf_s(gCharBuffer,"vCamLookAt.X - %0.0f",cGame_Camera.vCamLookAt.x);
	//iPrint(gCharBuffer,cGame_Font.f16pt,&vCamInfo,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//vCamInfo.y -= 1.0f;
	//sprintf_s(gCharBuffer,"vCamLookAt.Y - %0.0f",cGame_Camera.vCamLookAt.y);
	//iPrint(gCharBuffer,cGame_Font.f16pt,&vCamInfo,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//vCamInfo.y -= 1.0f;
	//sprintf_s(gCharBuffer,"vCamLookAt.Z - %0.0f",cGame_Camera.vCamLookAt.z);
	//iPrint(gCharBuffer,cGame_Font.f16pt,&vCamInfo,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//vCamInfo.y -= 1.0f;
	//-------------------------------------------------------------
	//Audio
	//sprintf_s(gCharBuffer,"sfxfreq - %0.2f",gVolumeFx);
	//iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(-12.0f,0.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	
	//-------------------------------------------------------------
	//Mouse
	D3DXVECTOR2 vMouse = D3DXVECTOR2(0.0f,0.0f);
	MousePositionGet(&vMouse);
	sprintf_s(gCharBuffer,"x: %0.1f",vMouse.x);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vMouse,&D3DXVECTOR4(0.0f,1.0f,1.0f,1.0f),gFont,false);
	vMouse.x += 2.0f;
	sprintf_s(gCharBuffer,"y: %0.1f",vMouse.y);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vMouse,&D3DXVECTOR4(0.0f,1.0f,1.0f,1.0f),gFont,false);
	vMouse.x += 2.0f;
	sprintf_s(gCharBuffer,"Value: %0.3f",cGame_Menu.fMouseValue);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vMouse,&D3DXVECTOR4(0.0f,1.0f,1.0f,1.0f),gFont,false);

	//-------------------------------------------------------------
	//Hud Scale
	//if(iKeyDown(DIK_1)){gFontScale -= 0.05f;}
	//else if(iKeyDown(DIK_2)){gFontScale += 0.05f;}
	sprintf_s(gCharBuffer,"gFontScale: %0.1f",gFontScale);
	iPrint(gCharBuffer,cGame_Font.f16pt,&D3DXVECTOR2(-13.0f,-10.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - DEBUG - DevMode_RaceTracker
///*****************************************************************
void Game_DevMode::DevMode_RaceTracker(void)
{
	//-------------------------------------------------------------
	//Print DevModeState
	iPrint((char*)"DevMode",cGame_Font.f32pt,&D3DXVECTOR2(10.0f,-10.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"[              ]",cGame_Font.f32pt,&D3DXVECTOR2(10.0f,-11.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)" RaceTracker",cGame_Font.f32pt,&D3DXVECTOR2(10.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	sprintf_s(gCharBuffer,"FPS %i",gFps);
	iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(10.0f,-12.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	//Print Player	- BIKE DATA
	D3DXVECTOR2 bike2D;
	if(i3DLocationToScreen(&bike2D,&cGame_Bike[gAi_Max_Count].Manager.vBikeOutput,gCamera))
	{
		bike2D.x += 4.5f;
		sprintf_s(gCharBuffer,"wp %d",cGame_RaceTracker.Waypoint_Current[gAi_Max_Count]);
		iPrint3(gCharBuffer,cGame_Font.f14pt,&bike2D,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
		bike2D.y -= 0.5f;
		//sprintf_s(gCharBuffer,"wp_- %d",cGame_RaceTracker.Waypoint_Previous[gAi_Max_Count]);
		//iPrint3(gCharBuffer,cGame_Font.f14pt,&bike2D,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
		//bike2D.y -= 0.5f;
		sprintf_s(gCharBuffer,"range %0.0f",cGame_RaceTracker.fWaypoint_Current_Distance[gAi_Max_Count]);
		iPrint3(gCharBuffer,cGame_Font.f14pt,&bike2D,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
		bike2D.y -= 0.5f;
		//sprintf_s(gCharBuffer,"range_- %0.0f",cGame_RaceTracker.fWaypoint_Previous_Distance[gAi_Max_Count]);
		//iPrint3(gCharBuffer,cGame_Font.f14pt,&bike2D,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
		//bike2D.y -= 0.5f;
	}
	//-------------------------------------------------------------
	//Print Ai		- BIKE DATA
	for(int i=0;i<gAi_Max_Count;i++)
	{
		D3DXVECTOR2 Ai2dLoc;
		if(i3DLocationToScreen(&Ai2dLoc,&cGame_Bike[i].Manager.vTargetMesh,gCamera))
		{
			sprintf_s(gCharBuffer,"%i",cGame_Bike[i].PlayerID);
			iPrint(gCharBuffer,cGame_Font.f12pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
			Ai2dLoc.y -= 0.5f;
			sprintf_s(gCharBuffer,"wp %d",cGame_RaceTracker.Waypoint_Current[i]);
			iPrint(gCharBuffer,cGame_Font.f12pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"wp_- %d",cGame_RaceTracker.Waypoint_Previous[i]);
			//iPrint(gCharBuffer,cGame_Font.f12pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
			sprintf_s(gCharBuffer,"range %0.0f",cGame_RaceTracker.fWaypoint_Current_Distance[i]);
			iPrint(gCharBuffer,cGame_Font.f12pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"range_- %0.0f",cGame_RaceTracker.fWaypoint_Previous_Distance[i]);
			//iPrint(gCharBuffer,cGame_Font.f12pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
		}
	}
	//-------------------------------------------------------------
	//Waypoints
	bike2D = D3DXVECTOR2(-10.0f,10.0f);
		
	for(int i=0;i<cGame_RaceTracker.ACTIVE_WAYPOINTS;i++)
	{
		bike2D.y = 11.0f;
		sprintf_s(gCharBuffer,"WP%d",i);
		iPrint(gCharBuffer,cGame_Font.f12pt,&bike2D,&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
		bike2D.y = 10.0f;
		for(int j=0;j<=gAi_Max_Count;j++)
		{
			if(cGame_RaceTracker.WaypointSortedClosest[i][j]>=0)
			{
				sprintf_s(gCharBuffer,"%d",cGame_RaceTracker.WaypointSortedClosest[i][j]);
				iPrint3(gCharBuffer,cGame_Font.f12pt,&bike2D,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
				bike2D.y -= 0.5f;
			}
		}
		bike2D.x += 0.75f;
	}

	///debug - Positions
	bike2D = D3DXVECTOR2(9.0f,11.0f);
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		sprintf_s(gCharBuffer,"#%d = %d",i,cGame_RaceTracker.Position_Current[i]);
		iPrint(gCharBuffer,cGame_Font.f14pt,&bike2D,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
		///Wrong way?
		if(cGame_RaceTracker.bWrongWay[i])
		{
			bike2D.x += 1.5f;
			iPrint((char*)"X",cGame_Font.f14pt,&bike2D,&D3DXVECTOR4(1.0f,0.2f,0.0f,1.0f),gFont,false);
			bike2D.x -= 1.5f;
		}
		///Bike Finished?
		if(!cGame_RaceTracker.bBikeRacing[i])
		{
			bike2D.x -= 1.0f;
			iPrint((char*)">>",cGame_Font.f14pt,&bike2D,&D3DXVECTOR4(0.0f,1.0f,1.0f,1.0f),gFont,false);
			bike2D.x += 1.0f;
		}
		bike2D.y -= 0.5f;
	}

	///debug waypoints
	bike2D = D3DXVECTOR2(0.0f,0.0f);
	for(int i=0;i<cGame_RaceTracker.ACTIVE_WAYPOINTS;i++)
	{
		if(i3DLocationToScreen(&bike2D,&cGame_RaceTracker.vWaypoint_Master[i],gCamera))
		{
			sprintf_s(gCharBuffer,"<%d>",i);
			iPrint(gCharBuffer,cGame_Font.f30pt,&bike2D,&D3DXVECTOR4(1.0f,0.5f,0.1f,1.0f),gFont,true);
		}

	}
	//-------------------------------------------------------------
}

///*****************************************************************
///GAME - DEBUG - DevMode_Visuals
///*****************************************************************
void Game_DevMode::DevMode_Visuals(void)
{
	//-------------------------------------------------------------
	D3DXVECTOR2 vPrint = D3DXVECTOR2(-10.0f,10.0f);
	D3DXVECTOR2 vCurrent = D3DXVECTOR2(-11.0f,10.0f);
	//-------------------------------------------------------------
	///Print DevModeState
	iPrint((char*)"DevMode",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-10.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"[                ]",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"  Visuals",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	sprintf_s(gCharBuffer,"FPS %i",gFps);
	iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(10.0f,-12.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	if(iKeyClick(VK_UP))
	{
		Current--;
		if(Current<0)
		{
			Current = 0;
		}
		bNewSelection = true;
	}
	else if(iKeyClick(VK_DOWN))
	{
		Current++;
		bNewSelection = true;
	}
	vCurrent.y = 10.0f - (float)Current;
	iPrint((char*)"->",cGame_Font.f24pt,&vCurrent,&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	///Controls
	static float value = 0.0f;
	static bool bBlend = true;
	static int Render1 = 1;/// 1 5 6 default
	static int Render2 = 7;
	static int Render3 = 2;

	if(iKeyDown(VK_NUMPAD1))
	{
		value -= 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD2))
	{
		value += 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD4))
	{
		value -= 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD5))
	{
		value += 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD7))
	{
		value -= 0.5f;
	}
	else if(iKeyDown(VK_NUMPAD8))
	{
		value += 0.5f;
	}
	//-------------------------------------------------------------
	//Gamma
	if(Current==0)
	{
		if(bNewSelection)
		{
			value = gUserGamma;
			bNewSelection = false;
		}
		iFloatCap(value,0.1f,3.0f);
		gUserGamma = value;
	}
	//Contrast
	else if(Current==1)
	{
		if(bNewSelection)
		{
			value = gColourCorrection.y;
			bNewSelection = false;
		}
		iFloatCap(value,0.1f,5.0f);
		gColourCorrection.y = value;
	}
	//Sat
	else if(Current==2)
	{
		if(bNewSelection)
		{
			value = gColourCorrection.z;
			bNewSelection = false;
		}
		iFloatCap(value,0.1f,5.0f);
		gColourCorrection.z = value;
	}
	//PP GlowRadius 
	else if(Current==3)
	{
		if(bNewSelection)
		{
			value = gGlowValues.x;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,10.0f);
		gGlowValues.x = value;
	}
	//PP GlowAmount 
	else if(Current==4)
	{
		if(bNewSelection)
		{
			value = gGlowValues.y;
			bNewSelection = false;
		}
		iFloatCap(value,0.01f,10.0f);
		gGlowValues.y = value;
	}
	//PP GlowIntensity 
	else if(Current==5)
	{
		if(bNewSelection)
		{
			value = gGlowValues.z;
			bNewSelection = false;
		}
		iFloatCap(value,0.01f,10.0f);
		gGlowValues.z = value;
	}
	//PP GlowTrailFade 
	else if(Current==6)
	{
		if(bNewSelection)
		{
			value = gGlowValues.w;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		gGlowValues.w = value;
	}
	//Blend Mode Enable 
	else if(Current==7)
	{
		if(bNewSelection)
		{

			value = 0.0f;
			if(bBlend)
			{
				value = 1.0f;
			}
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);

		bBlend = true;
		if(value<=0.5f){bBlend = false;}
	}
	//Blend Mode Combine 
	else if(Current==8)
	{
		if(bNewSelection)
		{
			value = (float)Render1;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,5.0f);

		Render1 = (int)value;
	}
	//Blend Mode Pre-Render
	else if(Current==9)
	{
		if(bNewSelection)
		{
			value = (float)Render2;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,19.0f);

		Render2 = (int)value;
	}
	//Blend Mode Render
	else if(Current==10)
	{
		if(bNewSelection)
		{
			value = (float)Render3;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,19.0f);

		Render3 = (int)value;
	}
	//Motion Object Blur
	else if(Current==11)
	{
		if(bNewSelection)
		{
			value = gBlurObject;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,10.0f);
		gBlurObject = value;
	}
	//Bloom
	else if(Current==12)
	{
		if(bNewSelection)
		{
			value = gBloomThreshold;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		gBloomThreshold = value;
	}
	else if(Current==13)
	{
		if(bNewSelection)
		{
			value = gBloomRadius;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1000.0f);
		gBloomRadius = value;
	}
	else if(Current==14)
	{
		if(bNewSelection)
		{
			value = (float)gBloomBlurCount;
			bNewSelection = false;
		}
		iFloatCap(value,1.0f,64.0f);
		gBloomBlurCount = (int)value;
	}
	else
	{
		bNewSelection = true;
		Current = 0;
	}
	sprintf_s(gCharBuffer,"Gamma %0.2f",gUserGamma);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Contrast %0.2f",gColourCorrection.y);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Saturation %0.2f",gColourCorrection.z);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"GlowRadius - %0.2f",gGlowValues.x);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"GlowAmount - %0.2f",gGlowValues.y);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"GlowIntensity - %0.2f",gGlowValues.z);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"GlowTrailFade - %0.2f",gGlowValues.w);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	if(bBlend)
	{
		iPrint((char*)"DX11 Blend - Enabled",cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
		vPrint.y -= 1.0f;
	}
	else
	{
		iPrint((char*)"DX11 Blend - Off",cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
		vPrint.y -= 1.0f;
	}
	sprintf_s(gCharBuffer,"DX11 Blend Combine - %d",Render1);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"DX11 Blend PreRender - %d",Render2);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"DX11 Blend Render - %d",Render3);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Object Blur - %0.2f",gBlurObject);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;

	//Set PP
	iPostProcessGlowSet(gCamera,gGlowValues.x,gGlowValues.y,gGlowValues.z,gGlowValues.w);
	//set blend modes
	//iMeshBlendEnableSet(cGame_Track.Mesh_Track[1],bBlend);
	//iMeshBlendModeSet(cGame_Track.Mesh_Track[1],Render1,Render2,Render3);

	//Bloom
	sprintf_s(gCharBuffer,"gBloomThreshold - %0.2f",gBloomThreshold);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"gBloomRadius - %0.2f",gBloomRadius);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"gBloomBlurCount - %d",gBloomBlurCount);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;

	iPostProcessLuminanceBloomSet(gCamera,gBloomThreshold,gBloomRadius,gBloomBlurCount);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - DEBUG - DevMode_Network
///*****************************************************************
void Game_DevMode::DevMode_Network(void)
{
	//-------------------------------------------------------------
	//Print DevModeState
	iPrint((char*)"DevMode",cGame_Font.f32pt,&D3DXVECTOR2(10.0f,-10.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"[      ]",cGame_Font.f32pt,&D3DXVECTOR2(10.0f,-11.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"  Net",cGame_Font.f32pt,&D3DXVECTOR2(10.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	sprintf_s(gCharBuffer,"FPS %i",gFps);
	iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(10.0f,-12.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	//TickRate Adjust
	if(iKeyDown(VK_NUMPAD1) && gNetworkTickRateMax > 2)
	{
		gNetworkTickRateMax--;
	}
	else if(iKeyDown(VK_NUMPAD2))
	{
		gNetworkTickRateMax++;
	}
	//Player Names
	D3DXVECTOR2 vPlayernames = D3DXVECTOR2(0.0f,9.0f);
	for(int i=0;i<8;i++)
	{
		iPrint((char*)cGame_Bike[i].Name.c_str(),cGame_Font.f24pt,&vPlayernames,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
		vPlayernames.y -= 1.0f;
	}
	//-------------------------------------------------------------
	//Packet Data
	D3DXVECTOR2 vDebug = D3DXVECTOR2(8.0f,0.0f);
	sprintf_s(gCharBuffer,"TickRate - %i",gNetworkTickRateMax);
	iPrint(gCharBuffer,cGame_Font.f24pt,&vDebug,&D3DXVECTOR4(1.0f,0.5f,0.1f,1.0f),gFont,false);
	vDebug.y -= 1.0f;
	if(cGame_Network.Client.State==2)
	{
		if(cGame_Network.Client.bPacketRecieved)
		{
			sprintf_s(gCharBuffer,"%i",cGame_Network.Client.Packet_In);
			iPrint(gCharBuffer,cGame_Font.f24pt,&vDebug,&D3DXVECTOR4(1.0f,0.5f,0.1f,1.0f),gFont,false);
		}
		else
		{
			iPrint((char*)"_____",cGame_Font.f24pt,&vDebug,&D3DXVECTOR4(1.0f,0.5f,0.1f,1.0f),gFont,false);
		}
	}
	else if(cGame_Network.Server.State==2)
	{
		for(int i=0;i<MAX_NETWORK_CONNECTIONS;i++)
		{
			if(cGame_Network.Server.bPacketRecieved[i])
			{
				sprintf_s(gCharBuffer,"%i",cGame_Network.Server.Packet_In[i]);
				iPrint(gCharBuffer,cGame_Font.f24pt,&vDebug,&D3DXVECTOR4(1.0f,0.5f,0.1f,1.0f),gFont,false);
			}
			else
			{
				iPrint((char*)"_____",cGame_Font.f24pt,&vDebug,&D3DXVECTOR4(1.0f,0.5f,0.1f,1.0f),gFont,false);
			}
			vDebug.y -= 1.0f;
		}
	}

	sprintf_s(gCharBuffer,"%i",gDEBUG_Net_ChangedValues);
	iPrint(gCharBuffer,cGame_Font.f36pt,&D3DXVECTOR2(8.0f,6.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	
	//D3DXVECTOR2 vNetRaceState = D3DXVECTOR2(0.0f,0.0f);
	//for(int i=0;i<MAX_NETWORK_CONNECTIONS;i++)
	//{
	//	sprintf_s(gCharBuffer,"%i",cGame_Network.Net_User_Racestate[i]);
	//	iPrint(gCharBuffer,cGame_Font.f32pt,&vNetRaceState,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//	vNetRaceState.y -= 1.0f;
	//}
	//-------------------------------------------------------------
	//Ai Info
	for(int i=0;i<gAi_Max_Count;i++)
	{
		D3DXVECTOR2 Ai2dLoc;
		if(i3DLocationToScreen(&Ai2dLoc,&cGame_Bike[i].Manager.vTargetMesh,gCamera))
		{
			sprintf_s(gCharBuffer,"%i",cGame_Bike[i].PlayerID);
			iPrint(gCharBuffer,cGame_Font.f24pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
			Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"Speed: %0.1f",cGame_Bike[i].Manager.fAcceleration_Speed);
			//iPrint(gCharBuffer,cGame_Font.f16pt,&Ai2dLoc,&D3DXVECTOR4(0.0f,1.0f,1.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"State %i",cGame_Bike[i].InputSpeedState);
			//iPrint(gCharBuffer,cGame_Font.f16pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,0.0f,1.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
			sprintf_s(gCharBuffer,"E %0.0f",cGame_Bike[i].Energy.fEnergy);
			iPrint(gCharBuffer,cGame_Font.f24pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,1.0f,0.0f,1.0f),gFont,false);
			Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"LOCKED %i",cGame_Bike[i].Weapons.NetSecondaryLockedId);
			//iPrint(gCharBuffer,25.0f,&Ai2dLoc,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"1 %i",cGame_Bike[i].Weapons.NetFirePrimary);
			//iPrint(gCharBuffer,cGame_Font.f16pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"2 %i",cGame_Bike[i].Weapons.NetFireSecondary);
			//iPrint(gCharBuffer,cGame_Font.f16pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"3 %i",cGame_Bike[i].Weapons.NetFireUtility);
			//iPrint(gCharBuffer,cGame_Font.f16pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"K %i",cGame_Bike[i].Weapons.TotalKills);
			//iPrint(gCharBuffer,cGame_Font.f16pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,0.5f,0.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"D %i",cGame_Bike[i].Weapons.TotalDeaths);
			//iPrint(gCharBuffer,cGame_Font.f16pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,0.5f,0.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"UPG %i",cGame_Upgrades.uShieldInvConvert[i]);
			//iPrint(gCharBuffer,cGame_Font.f16pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,0.5f,0.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"UPG %0.1f",cGame_Upgrades.fShieldInvConvert[i]);
			//iPrint(gCharBuffer,cGame_Font.f16pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,0.5f,0.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"In  %i",cGame_Bike[i].Weapons.TotalDamageReceived);
			//iPrint(gCharBuffer,cGame_Font.f16pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,0.0f,1.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"%i",cGame_Mesh.Culling.Bike_Closest[i]);
			//iPrint(gCharBuffer,cGame_Font.f30pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,0.1f,0.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
			//sprintf_s(gCharBuffer,"ttbreak %0.0f",cGame_Bike[i].Manager.fAcceleration_TendTo_Break);
			//iPrint(gCharBuffer,cGame_Font.f16pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			//Ai2dLoc.y -= 0.5f;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - DEBUG - DevMode_Controls
///*****************************************************************
void Game_DevMode::DevMode_Controls(void)
{
	//-------------------------------------------------------------
	D3DXVECTOR2 vPrint = D3DXVECTOR2(-10.0f,10.0f);
	D3DXVECTOR2 vCurrent = D3DXVECTOR2(-11.0f,10.0f);
	//-------------------------------------------------------------
	///Print DevModeState
	iPrint((char*)"DevMode",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-10.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"[                ]",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"  Controls",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	sprintf_s(gCharBuffer,"FPS %i",gFps);
	iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(10.0f,-12.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	if(iKeyClick(VK_UP))
	{
		Current--;
		if(Current<0)
		{
			Current = 0;
		}
		bNewSelection = true;
	}
	else if(iKeyClick(VK_DOWN))
	{
		Current++;
		bNewSelection = true;
	}
	vCurrent.y = 10.0f - (float)Current;
	iPrint((char*)"->",cGame_Font.f24pt,&vCurrent,&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	///Controls
	static float value = 0.0f;

	if(iKeyDown(VK_NUMPAD1))
	{
		value -= 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD2))
	{
		value += 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD4))
	{
		value -= 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD5))
	{
		value += 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD7))
	{
		value -= 0.5f;
	}
	else if(iKeyDown(VK_NUMPAD8))
	{
		value += 0.5f;
	}
	//-------------------------------------------------------------
	//Player steering caps
	if(Current==0)
	{
		if(bNewSelection)
		{
			value = gPlayer_Steering_Speed_Min;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,gPlayer_Steering_Speed_Max);
		gPlayer_Steering_Speed_Min = value;
	}
	else if(Current==1)
	{
		if(bNewSelection)
		{
			value = gPlayer_Steering_Speed_Max;
			bNewSelection = false;
		}
		iFloatCap(value,gPlayer_Steering_Speed_Min,10.0f);
		gPlayer_Steering_Speed_Max = value;
	}
	else if(Current==2)
	{
		if(bNewSelection)
		{
			value = gPlayer_Steering_Output_Min;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,gPlayer_Steering_Output_Max);
		gPlayer_Steering_Output_Min = value;
	}
	else if(Current==3)
	{
		if(bNewSelection)
		{
			value = gPlayer_Steering_Output_Max;
			bNewSelection = false;
		}
		iFloatCap(value,gPlayer_Steering_Output_Min,4.0f);
		gPlayer_Steering_Output_Max = value;
	}
	else if(Current==4)
	{
		if(bNewSelection)
		{
			value = gAi_Steering_Speed_Min;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,gAi_Steering_Speed_Max);
		gAi_Steering_Speed_Min = value;
	}
	else if(Current==5)
	{
		if(bNewSelection)
		{
			value = gAi_Steering_Speed_Max;
			bNewSelection = false;
		}
		iFloatCap(value,gAi_Steering_Speed_Min,10.0f);
		gAi_Steering_Speed_Max = value;
	}
	else if(Current==6)
	{
		if(bNewSelection)
		{
			value = gAi_Steering_Output_Min;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,gAi_Steering_Output_Max);
		gAi_Steering_Output_Min = value;
	}
	else if(Current==7)
	{
		if(bNewSelection)
		{
			value = gAi_Steering_Output_Max;
			bNewSelection = false;
		}
		iFloatCap(value,gAi_Steering_Output_Min,6.0f);
		gAi_Steering_Output_Max = value;
	}
	else
	{
		bNewSelection = true;
		Current = 0;
	}
	sprintf_s(gCharBuffer,"Player Steering - SpeedMin %0.2f",gPlayer_Steering_Speed_Min);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Player Steering - SpeedMax %0.2f",gPlayer_Steering_Speed_Max);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Player Steering - OutputMin %0.2f",gPlayer_Steering_Output_Min);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Player Steering - OutputMax %0.2f",gPlayer_Steering_Output_Max);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;

	sprintf_s(gCharBuffer,"Ai Steering - SpeedMin %0.2f",gAi_Steering_Speed_Min);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Ai Steering - SpeedMax %0.2f",gAi_Steering_Speed_Max);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Ai Steering - OutputMin %0.2f",gAi_Steering_Output_Min);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Ai Steering - OutputMax %0.2f",gAi_Steering_Output_Max);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	//Xbox input values
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Input Steering - Xbox %d",gXBox360Controller_ThumbStickLeftX);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;

	//Preset DEFAULT
	if(iKeyClick(DIK_HOME))
	{
		Current = 20;
		gPlayer_Steering_Speed_Min		= 0.5f;
		gPlayer_Steering_Speed_Max		= 7.5f;
		gPlayer_Steering_Output_Min		= 0.625f;
		gPlayer_Steering_Output_Max		= 2.4f;

		gAi_Steering_Speed_Min			= 0.6f;
		gAi_Steering_Speed_Max			= 7.5f;
		gAi_Steering_Output_Min			= 1.8f;
		gAi_Steering_Output_Max			= 5.0f;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - DEBUG - DevMode_Camera
///*****************************************************************
void Game_DevMode::DevMode_Camera(void)
{
	//-------------------------------------------------------------
	D3DXVECTOR2 vPrint = D3DXVECTOR2(-10.0f,10.0f);
	D3DXVECTOR2 vCurrent = D3DXVECTOR2(-11.0f,10.0f);
	//-------------------------------------------------------------
	///Print DevModeState
	iPrint((char*)"DevMode",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-10.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"[                ]",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"  Camera",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	sprintf_s(gCharBuffer,"FPS %i",gFps);
	iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(10.0f,-12.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	if(iKeyClick(VK_UP))
	{
		Current--;
		if(Current<0)
		{
			Current = 0;
		}
		bNewSelection = true;
	}
	else if(iKeyClick(VK_DOWN))
	{
		Current++;
		bNewSelection = true;
	}
	vCurrent.y = 10.0f - (float)Current;
	iPrint((char*)"->",cGame_Font.f24pt,&vCurrent,&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	///Controls
	static float value = 0.0f;

	if(iKeyDown(VK_NUMPAD1))
	{
		value -= 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD2))
	{
		value += 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD4))
	{
		value -= 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD5))
	{
		value += 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD7))
	{
		value -= 0.5f;
	}
	else if(iKeyDown(VK_NUMPAD8))
	{
		value += 0.5f;
	}
	//-------------------------------------------------------------
	const int TargetCamMode = 0;
	//-------------------------------------------------------------
	if(Current==0)
	{
		if(bNewSelection)
		{
			value = cGame_Camera.vPlayerCam[TargetCamMode].x;
			bNewSelection = false;
		}
		iFloatCap(value,-10.0f,10.0f);
		cGame_Camera.vPlayerCam[TargetCamMode].x = value;
	}
	else if(Current==1)
	{
		if(bNewSelection)
		{
			value = cGame_Camera.vPlayerCam[TargetCamMode].y;
			bNewSelection = false;
		}
		iFloatCap(value,-50.0f,50.0f);
		cGame_Camera.vPlayerCam[TargetCamMode].y = value;
	}
	else if(Current==2)
	{
		if(bNewSelection)
		{
			value = cGame_Camera.vPlayerCam[TargetCamMode].z;
			bNewSelection = false;
		}
		iFloatCap(value,-10.0f,10.0f);
		cGame_Camera.vPlayerCam[TargetCamMode].z = value;
	}
	else if(Current==3)
	{
		if(bNewSelection)
		{
			value = cGame_Camera.vPlayerCam[TargetCamMode].w;
			bNewSelection = false;
		}
		iFloatCap(value,1.0f,120.0f);
		cGame_Camera.vPlayerCam[TargetCamMode].w = value;
	}
	else
	{
		bNewSelection = true;
		Current = 0;
	}
	sprintf_s(gCharBuffer,"Height (Y) %0.2f",cGame_Camera.vPlayerCam[TargetCamMode].x);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Depth (Z) %0.2f",cGame_Camera.vPlayerCam[TargetCamMode].y);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Rotation (X) %0.2f",cGame_Camera.vPlayerCam[TargetCamMode].z);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"FoV %0.2f",cGame_Camera.vPlayerCam[TargetCamMode].w);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;

	//Preset DEFAULT
	//if(iKeyClick(DIK_HOME))
	//{
	//	Current = 8;
	//	gCam_Player_Preset_Debug = D3DXVECTOR4(5.72f,-21.97f,-2.07f,50.0f);
	//}
	//if(cGame_Camera.Mode_InGame >= 4)
	//{
		cGame_Camera.Mode_InGame = TargetCamMode;
	//}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - DEBUG - DevMode_AudioWeapons
///*****************************************************************
void Game_DevMode::DevMode_AudioWeapons(void)
{
	//-------------------------------------------------------------
	D3DXVECTOR2 vPrint = D3DXVECTOR2(-10.0f,10.0f);
	D3DXVECTOR2 vCurrent = D3DXVECTOR2(-11.0f,10.0f);
	//-------------------------------------------------------------
	///Print DevModeState
	iPrint((char*)"DevMode",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-10.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"[                   ]",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"  Audio Weapons",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	sprintf_s(gCharBuffer,"FPS %i",gFps);
	iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(10.0f,-12.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	if(iKeyClick(VK_UP))
	{
		Current--;
		if(Current<0)
		{
			Current = 0;
		}
		bNewSelection = true;
	}
	else if(iKeyClick(VK_DOWN))
	{
		Current++;
		bNewSelection = true;
	}
	vCurrent.y = 10.0f - ((float)Current * 0.75f);
	iPrint((char*)"->",cGame_Font.f24pt,&vCurrent,&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	///Controls
	static float value = 0.0f;

	if(iKeyDown(VK_NUMPAD1))
	{
		value -= 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD2))
	{
		value += 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD4))
	{
		value -= 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD5))
	{
		value += 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD7))
	{
		value -= 0.5f;
	}
	else if(iKeyDown(VK_NUMPAD8))
	{
		value += 0.5f;
	}
	//-------------------------------------------------------------
	if(Current==0)
	{
		if(bNewSelection)
		{
			value = gVolumeMusic;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,0.95f);
		gVolumeMusic = value;
	}
	else if(Current==1)
	{
		if(bNewSelection)
		{
			value = gVolumeFx;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		gVolumeFx = value;
	}
	else if(Current==2)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sPrimaryGun;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		cGame_Audio.Weapons.fVolumeTarget_sPrimaryGun = value;
	}
	else if(Current==3)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sEm_Charge;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		cGame_Audio.Weapons.fVolumeTarget_sEm_Charge = value;
	}
	else if(Current==4)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sEm_Fire;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		cGame_Audio.Weapons.fVolumeTarget_sEm_Fire = value;
	}
	else if(Current==5)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sRail_Charge;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		cGame_Audio.Weapons.fVolumeTarget_sRail_Charge = value;
	}
	else if(Current==6)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sRail_Fire;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		cGame_Audio.Weapons.fVolumeTarget_sRail_Fire = value;
	}
	else if(Current==7)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sShoxwave_Fire;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		cGame_Audio.Weapons.fVolumeTarget_sShoxwave_Fire = value;
	}
	else if(Current==8)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sMissile_Fire;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		cGame_Audio.Weapons.fVolumeTarget_sMissile_Fire = value;
	}
	else if(Current==9)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sShield;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		cGame_Audio.Weapons.fVolumeTarget_sShield = value;
	}
	else if(Current==10)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sDoubleDamage;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		cGame_Audio.Weapons.fVolumeTarget_sDoubleDamage = value;
	}
	else if(Current==11)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sWarp;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		cGame_Audio.Weapons.fVolumeTarget_sWarp = value;
	}
	else if(Current==12)//ai's
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sEm_Charge_Ai;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.5f);
		cGame_Audio.Weapons.fVolumeTarget_sEm_Charge_Ai = value;
	}
	else if(Current==13)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sEm_Fire_Ai;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.5f);
		cGame_Audio.Weapons.fVolumeTarget_sEm_Fire_Ai = value;
	}
	else if(Current==14)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sRail_Charge_Ai;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.5f);
		cGame_Audio.Weapons.fVolumeTarget_sRail_Charge_Ai = value;
	}
	else if(Current==15)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sRail_Fire_Ai;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.5f);
		cGame_Audio.Weapons.fVolumeTarget_sRail_Fire_Ai = value;
	}
	else if(Current==16)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sShoxwave_Fire_Ai;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.5f);
		cGame_Audio.Weapons.fVolumeTarget_sShoxwave_Fire_Ai = value;
	}
	else if(Current==17)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sMissile_Fire_Ai;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.5f);
		cGame_Audio.Weapons.fVolumeTarget_sMissile_Fire_Ai = value;
	}
	else if(Current==18)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sShield_Ai;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.5f);
		cGame_Audio.Weapons.fVolumeTarget_sShield_Ai = value;
	}
	else if(Current==19)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sDoubleDamage_Ai;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.5f);
		cGame_Audio.Weapons.fVolumeTarget_sDoubleDamage_Ai = value;
	}
	else if(Current==20)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sWarp_Ai;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.5f);
		cGame_Audio.Weapons.fVolumeTarget_sWarp_Ai = value;
	}
	else if(Current==21)//Travel
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sPrimaryTravel;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.5f);
		cGame_Audio.Weapons.fVolumeTarget_sPrimaryTravel = value;
	}
	else if(Current==22)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sMissile_Travel;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.5f);
		cGame_Audio.Weapons.fVolumeTarget_sMissile_Travel = value;
	}
	else if(Current==23)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sMissile_Explosion;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.5f);
		cGame_Audio.Weapons.fVolumeTarget_sMissile_Explosion = value;
	}
	else if(Current==24)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sShoxwave_Travel;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.5f);
		cGame_Audio.Weapons.fVolumeTarget_sShoxwave_Travel = value;
	}
	else if(Current==25)
	{
		if(bNewSelection)
		{
			value = cGame_Audio.Weapons.fVolumeTarget_sRail_Travel;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.5f);
		cGame_Audio.Weapons.fVolumeTarget_sRail_Travel = value;
	}
	else
	{
		bNewSelection = true;
		Current = 0;
	}
	sprintf_s(gCharBuffer,"Master Volume - Music %0.2f",gVolumeMusic);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Master Volume - SFX %0.2f",gVolumeFx);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;

	sprintf_s(gCharBuffer,"Player - Primary Gun %0.2f",cGame_Audio.Weapons.fVolumeTarget_sPrimaryGun);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Player - EM Charge %0.2f",cGame_Audio.Weapons.fVolumeTarget_sEm_Charge);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Player - EM Fire %0.2f",cGame_Audio.Weapons.fVolumeTarget_sEm_Fire);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Player - Rail Charge %0.2f",cGame_Audio.Weapons.fVolumeTarget_sRail_Charge);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Player - Rail Fire %0.2f",cGame_Audio.Weapons.fVolumeTarget_sRail_Fire);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Player - ShoxWave Fire %0.2f",cGame_Audio.Weapons.fVolumeTarget_sShoxwave_Fire);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Player - Missile Fire %0.2f",cGame_Audio.Weapons.fVolumeTarget_sMissile_Fire);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Player - Shield %0.2f",cGame_Audio.Weapons.fVolumeTarget_sShield);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Player - DoubleDamage %0.2f",cGame_Audio.Weapons.fVolumeTarget_sDoubleDamage);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Player - Warp %0.2f",cGame_Audio.Weapons.fVolumeTarget_sWarp);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;


	sprintf_s(gCharBuffer,"Ai - EM Charge %0.2f",cGame_Audio.Weapons.fVolumeTarget_sEm_Charge_Ai);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Ai - EM Fire %0.2f",cGame_Audio.Weapons.fVolumeTarget_sEm_Fire_Ai);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Ai - Rail Charge %0.2f",cGame_Audio.Weapons.fVolumeTarget_sRail_Charge_Ai);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Ai - Rail Fire %0.2f",cGame_Audio.Weapons.fVolumeTarget_sRail_Fire_Ai);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Ai - ShoxWave Fire %0.2f",cGame_Audio.Weapons.fVolumeTarget_sShoxwave_Fire_Ai);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Ai - Missile Fire %0.2f",cGame_Audio.Weapons.fVolumeTarget_sMissile_Fire_Ai);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Ai - Shield %0.2f",cGame_Audio.Weapons.fVolumeTarget_sShield_Ai);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Ai - DoubleDamage %0.2f",cGame_Audio.Weapons.fVolumeTarget_sDoubleDamage_Ai);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Ai - Warp %0.2f",cGame_Audio.Weapons.fVolumeTarget_sWarp_Ai);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;

	sprintf_s(gCharBuffer,"Travel - Primary %0.2f",cGame_Audio.Weapons.fVolumeTarget_sPrimaryTravel);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Travel - Missile %0.2f",cGame_Audio.Weapons.fVolumeTarget_sMissile_Travel);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Travel - Missile Explosion %0.2f",cGame_Audio.Weapons.fVolumeTarget_sMissile_Explosion);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Travel - ShoxWave %0.2f",cGame_Audio.Weapons.fVolumeTarget_sShoxwave_Travel);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Travel - Rail %0.2f",cGame_Audio.Weapons.fVolumeTarget_sRail_Travel);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;



	//SAVE
	iPrint((char*)"F8 = Load",cGame_Font.f20pt,&D3DXVECTOR2(9.0f,-6.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"F9 = Save",cGame_Font.f20pt,&D3DXVECTOR2(9.0f,-7.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	if(iKeyClick(DIK_F8))
	{
		Devmode_Load_Audio();
	}
	else if(iKeyClick(DIK_F9))
	{
		Devmode_Save_Audio();
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - DEBUG - DevMode_AudioBikes
///*****************************************************************
void Game_DevMode::DevMode_AudioBikes(void)
{
	//-------------------------------------------------------------
	D3DXVECTOR2 vPrint = D3DXVECTOR2(-10.0f,10.0f);
	D3DXVECTOR2 vCurrent = D3DXVECTOR2(-11.0f,10.0f);
	//-------------------------------------------------------------
	///Print DevModeState
	iPrint((char*)"DevMode",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-10.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"[                   ]",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"  Audio Bike",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	sprintf_s(gCharBuffer,"FPS %i",gFps);
	iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(10.0f,-12.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	if(iKeyClick(VK_UP))
	{
		Current--;
		if(Current<0)
		{
			Current = 0;
		}
		bNewSelection = true;
	}
	else if(iKeyClick(VK_DOWN))
	{
		Current++;
		bNewSelection = true;
	}
	vCurrent.y = 10.0f - ((float)Current * 0.75f);
	iPrint((char*)"->",cGame_Font.f24pt,&vCurrent,&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	///Controls
	static float value = 0.0f;

	if(iKeyDown(VK_NUMPAD1))
	{
		value -= 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD2))
	{
		value += 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD4))
	{
		value -= 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD5))
	{
		value += 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD7))
	{
		value -= 0.5f;
	}
	else if(iKeyDown(VK_NUMPAD8))
	{
		value += 0.5f;
	}
	//-------------------------------------------------------------
	if(Current==0)
	{
		if(bNewSelection)
		{
			value = gVolumeMusic;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,0.95f);
		gVolumeMusic = value;
	}
	//else if(Current==1)
	//{
	//	if(bNewSelection)
	//	{
	//		value = gVolumeFx;
	//		bNewSelection = false;
	//	}
	//	iFloatCap(value,0.0f,1.0f);
	//	gVolumeFx = value;
	//}
	//else if(Current==2)
	//{
	//	if(bNewSelection)
	//	{
	//		value = cGame_Audio.Bike_Fx.fVolumeTarget_sEngine;
	//		bNewSelection = false;
	//	}
	//	iFloatCap(value,0.0f,3.5f);
	//	cGame_Audio.Bike_Fx.fVolumeTarget_sEngine = value;
	//}
	//else if(Current==3)
	//{
	//	if(bNewSelection)
	//	{
	//		value = cGame_Audio.Bike_Fx.fVolumeTarget_sTurbo;
	//		bNewSelection = false;
	//	}
	//	iFloatCap(value,0.0f,3.5f);
	//	cGame_Audio.Bike_Fx.fVolumeTarget_sTurbo = value;
	//}
	//else if(Current==4)
	//{
	//	if(bNewSelection)
	//	{
	//		value = cGame_Audio.Bike_Fx.fVolumeTarget_sBoost;
	//		bNewSelection = false;
	//	}
	//	iFloatCap(value,0.0f,3.5f);
	//	cGame_Audio.Bike_Fx.fVolumeTarget_sBoost = value;
	//}
	//else if(Current==5)
	//{
	//	if(bNewSelection)
	//	{
	//		value = cGame_Audio.Bike_Fx.fVolumeTarget_sBreak;
	//		bNewSelection = false;
	//	}
	//	iFloatCap(value,0.0f,3.5f);
	//	cGame_Audio.Bike_Fx.fVolumeTarget_sBreak = value;
	//}
	//else if(Current==6)
	//{
	//	if(bNewSelection)
	//	{
	//		value = cGame_Audio.Bike_Fx.fVolumeTarget_sSlip;
	//		bNewSelection = false;
	//	}
	//	iFloatCap(value,0.0f,3.5f);
	//	cGame_Audio.Bike_Fx.fVolumeTarget_sSlip = value;
	//}
	//else if(Current==7)
	//{
	//	if(bNewSelection)
	//	{
	//		value = cGame_Audio.Bike_Fx.fVolumeTarget_sImpact;
	//		bNewSelection = false;
	//	}
	//	iFloatCap(value,0.0f,3.5f);
	//	cGame_Audio.Bike_Fx.fVolumeTarget_sImpact = value;
	//}
	//else if(Current==8)
	//{
	//	if(bNewSelection)
	//	{
	//		value = cGame_Audio.Bike_Fx.fVolumeTarget_sBoostRelease;
	//		bNewSelection = false;
	//	}
	//	iFloatCap(value,0.0f,3.5f);
	//	cGame_Audio.Bike_Fx.fVolumeTarget_sBoostRelease = value;
	//}
	//else if(Current==9)
	//{
	//	if(bNewSelection)
	//	{
	//		value = cGame_Audio.Bike_Fx.fVolumeTarget_sShield;
	//		bNewSelection = false;
	//	}
	//	iFloatCap(value,0.0f,3.5f);
	//	cGame_Audio.Bike_Fx.fVolumeTarget_sShield = value;
	//}
	else
	{
		bNewSelection = true;
		Current = 0;
	}
	sprintf_s(gCharBuffer,"Master Volume - Music %0.2f",gVolumeMusic);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Master Volume - SFX %0.2f",gVolumeFx);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;

	//sprintf_s(gCharBuffer,"Engine - Main %0.2f",cGame_Audio.Bike_Fx.fVolumeTarget_sEngine);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	//sprintf_s(gCharBuffer,"Engine - Turbo %0.2f",cGame_Audio.Bike_Fx.fVolumeTarget_sTurbo);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	//sprintf_s(gCharBuffer,"Engine - Boost %0.2f",cGame_Audio.Bike_Fx.fVolumeTarget_sBoost);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	//sprintf_s(gCharBuffer,"Breaks - %0.2f",cGame_Audio.Bike_Fx.fVolumeTarget_sBreak);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	//sprintf_s(gCharBuffer,"Slip - %0.2f",cGame_Audio.Bike_Fx.fVolumeTarget_sSlip);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	//sprintf_s(gCharBuffer,"Impact %0.2f",cGame_Audio.Bike_Fx.fVolumeTarget_sImpact);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	//sprintf_s(gCharBuffer,"Boost Release %0.2f",cGame_Audio.Bike_Fx.fVolumeTarget_sBoostRelease);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	//sprintf_s(gCharBuffer,"Shield Regen %0.2f",cGame_Audio.Bike_Fx.fVolumeTarget_sShield);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
		
	//sprintf_s(gCharBuffer,"Reverb %d",cGame_Audio.Bike_Fx.fVolumeTarget_sShield);iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);vPrint.y -= 0.75f;
	//iListenerReverbSet();

	//print Id's
	//D3DXVECTOR2 vLoc = D3DXVECTOR2(0.0f,8.0f);
	//for(int i=0;i<MAX_SOUND_GROUPS;i++)
	//{
	//	sprintf_s(gCharBuffer,"Prev %d",cGame_Audio.Bike_Fx.Previous_Id[i]);
	//	iPrint(gCharBuffer,cGame_Font.f16pt,&vLoc,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//	vLoc.x += 2.0f;
	//	sprintf_s(gCharBuffer,"curr %d",cGame_Audio.Bike_Fx.Current_Id[i]);
	//	iPrint(gCharBuffer,cGame_Font.f16pt,&vLoc,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//	
	//	vLoc.y -= 0.75f;
	//	vLoc.x = 0.0f;
	//}

	//SAVE
	iPrint((char*)"F8 = Load",cGame_Font.f20pt,&D3DXVECTOR2(9.0f,-6.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"F9 = Save",cGame_Font.f20pt,&D3DXVECTOR2(9.0f,-7.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	if(iKeyClick(DIK_F8))
	{
		Devmode_Load_Audio();
	}
	else if(iKeyClick(DIK_F9))
	{
		Devmode_Save_Audio();
	}
	////-------------------------------------------------------------
}
///*****************************************************************
///GAME - DEBUG - DevMode_MeshAnimator
///*****************************************************************
void Game_DevMode::DevMode_MeshAnimator(void)
{
	//-------------------------------------------------------------
	D3DXVECTOR2 vPrint = D3DXVECTOR2(-10.0f,10.0f);
	D3DXVECTOR2 vCurrent = D3DXVECTOR2(-11.0f,10.0f);
	//-------------------------------------------------------------
	///Print DevModeState
	iPrint((char*)"DevMode",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-10.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"[                ]",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"  Animator",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	sprintf_s(gCharBuffer,"FPS %i",gFps);
	iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(10.0f,-12.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	if(iKeyClick(VK_UP))
	{
		Current--;
		if(Current<0)
		{
			Current = 0;
		}
		bNewSelection = true;
	}
	else if(iKeyClick(VK_DOWN))
	{
		Current++;
		bNewSelection = true;
	}
	vCurrent.y = 10.0f - (float)Current;
	iPrint((char*)"->",cGame_Font.f24pt,&vCurrent,&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	///Controls
	static float value = 0.0f;

	if(iKeyDown(VK_NUMPAD1))
	{
		value -= 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD2))
	{
		value += 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD4))
	{
		value -= 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD5))
	{
		value += 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD7))
	{
		value -= 0.5f;
	}
	else if(iKeyDown(VK_NUMPAD8))
	{
		value += 0.5f;
	}
	//-------------------------------------------------------------
	if(Current==0)//Segment ID
	{
		if(bNewSelection)
		{
			value = (float)cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count];
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,19.0f);
		cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count] = (int)value;
	}
	else if(Current==1)//TIMER MAX
	{
		if(bNewSelection)
		{
			value = (float)cGame_Mesh.Animator.Timer_Creator_MAX[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]];
			bNewSelection = false;
		}
		iFloatCap(value,1.0f,100.0f);
		cGame_Mesh.Animator.Timer_Creator_MAX[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]] = (int)value;
	}
	else if(Current==2)//Vector X
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Animator.vTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].x;
			bNewSelection = false;
		}
		iFloatCap(value,-10.0f,10.0f);
		cGame_Mesh.Animator.vTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].x = value;
	}
	else if(Current==3)//Vector Y
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Animator.vTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].y;
			bNewSelection = false;
		}
		iFloatCap(value,-10.0f,10.0f);
		cGame_Mesh.Animator.vTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].y = value;
	}
	else if(Current==4)//Vector Z
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Animator.vTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].z;
			bNewSelection = false;
		}
		iFloatCap(value,-10.0f,10.0f);
		cGame_Mesh.Animator.vTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].z = value;
	}
	else if(Current==5)//Quat X
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Animator.qTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].x;
			bNewSelection = false;
		}
		iFloatCap(value,-3600.0f,3600.0f);
		cGame_Mesh.Animator.qTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].x = value;
	}
	else if(Current==6)//Quat Y
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Animator.qTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].y;
			bNewSelection = false;
		}
		iFloatCap(value,-3600.0f,3600.0f);
		cGame_Mesh.Animator.qTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].y = value;
	}
	else if(Current==7)//Quat Z
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Animator.qTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].z;
			bNewSelection = false;
		}
		iFloatCap(value,-3600.0f,3600.0f);
		cGame_Mesh.Animator.qTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].z = value;
	}
	else
	{
		bNewSelection = true;
		Current = 0;
	}
	sprintf_s(gCharBuffer,"Segment  %d",cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"TimerMax  %d",cGame_Mesh.Animator.Timer_Creator_MAX[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]]);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Vector X  %0.0f",cGame_Mesh.Animator.vTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].x);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Vector Y  %0.0f",cGame_Mesh.Animator.vTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].y);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Vector Z  %0.0f",cGame_Mesh.Animator.vTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].z);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;

	sprintf_s(gCharBuffer,"Quat X  %0.0f",cGame_Mesh.Animator.qTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].x);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Quat Y  %0.0f",cGame_Mesh.Animator.qTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].y);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	sprintf_s(gCharBuffer,"Quat Z  %0.0f",cGame_Mesh.Animator.qTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]].z);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 1.0f;
	//-------------------------------------------------------------
	//Copy last frame
	if(iKeyClick(DIK_F3))
	{
		if(cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]>0)
		{
			cGame_Mesh.Animator.vTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]] = cGame_Mesh.Animator.vTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]-1];
			cGame_Mesh.Animator.qTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]] = cGame_Mesh.Animator.qTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]-1];
		}
		bNewSelection = true;
	}

	//-------------------------------------------------------------
	//Clear Frame
	if(iKeyClick(DIK_F4))
	{
		cGame_Mesh.Animator.vTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		cGame_Mesh.Animator.qTarget_Creator[cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]] = D3DXVECTOR3(0.0f,0.0f,0.0f); 
		bNewSelection = true;
	}

	//-------------------------------------------------------------
	//Play
	static int Previous_Segment = 0;
	static bool bReturn_to_previous = false;
	if(iKeyClick(DIK_F5))
	{
		cGame_Mesh.Animator.bPlay = true;
		///Grab current segment
		Previous_Segment = cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count]; 
		bReturn_to_previous = true;
		///play from 1st segment
		for(int i=0;i<=gAi_Max_Count;i++)
		{
			cGame_Mesh.Animator.Mode_Segment[i] = 0;
			cGame_Mesh.Animator.Timer[i] = 0;
		}
	}
	if(cGame_Mesh.Animator.bPlay)
	{
		bNewSelection = true;
	}
	else if(bReturn_to_previous)
	{
		bNewSelection = true;
		bReturn_to_previous = false;
		cGame_Mesh.Animator.Mode_Segment[gAi_Max_Count] = Previous_Segment;
	}
	//-------------------------------------------------------------
	//Load
	if(iKeyClick(DIK_F8))
	{
		cGame_Mesh.Animator.Load();
		bNewSelection = true;
	}
	//-------------------------------------------------------------
	//Save
	else if(iKeyClick(DIK_F9))
	{
		cGame_Mesh.Animator.Save();
		bNewSelection = true;
	}
	//-------------------------------------------------------------
	//Activate
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		cGame_Mesh.Animator.Mode[i] = -1;
	}
	//-------------------------------------------------------------
	//Exit
	if(iKeyClick(DIK_F2))
	{
		for(int i=0;i<=gAi_Max_Count;i++)
		{
			cGame_Mesh.Animator.Mode[i] = 0;
			gDevMode = false;
		}
	}
	//-------------------------------------------------------------
	//PRINT INFO
	sprintf_s(gCharBuffer,"Timer %d",cGame_Mesh.Animator.Timer[gAi_Max_Count]);
	iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(9.0f,4.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);

	iPrint((char*)"F2 = Exit",cGame_Font.f20pt,&D3DXVECTOR2(9.0f,-2.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"F3 = Copy Previous Segment",cGame_Font.f20pt,&D3DXVECTOR2(9.0f,-3.0f),&D3DXVECTOR4(1.0f,0.5f,0.0f,1.0f),gFont,false);
	iPrint((char*)"F4 = Clear Segment",cGame_Font.f20pt,&D3DXVECTOR2(9.0f,-4.0f),&D3DXVECTOR4(1.0f,0.5f,0.0f,1.0f),gFont,false);
	iPrint((char*)"F5 = Play",cGame_Font.f20pt,&D3DXVECTOR2(9.0f,-5.0f),&D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"F8 = Load",cGame_Font.f20pt,&D3DXVECTOR2(9.0f,-6.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"F9 = Save",cGame_Font.f20pt,&D3DXVECTOR2(9.0f,-7.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - DEBUG - DevMode_PointLight
///*****************************************************************
void Game_DevMode::DevMode_PointLight(void)
{
	//-------------------------------------------------------------
	D3DXVECTOR2 vPrint = D3DXVECTOR2(-10.0f,10.0f);
	D3DXVECTOR2 vCurrent = D3DXVECTOR2(-11.0f,10.0f);
	//-------------------------------------------------------------
	///Print DevModeState
	iPrint((char*)"DevMode",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-10.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"[                   ]",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"  PointLight",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	sprintf_s(gCharBuffer,"FPS %i",gFps);
	iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(10.0f,-12.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	if(iKeyClick(VK_UP))
	{
		Current--;
		if(Current<0)
		{
			Current = 0;
		}
		bNewSelection = true;
	}
	else if(iKeyClick(VK_DOWN))
	{
		Current++;
		bNewSelection = true;
	}
	vCurrent.y = 10.0f - ((float)Current * 0.75f);
	iPrint((char*)"->",cGame_Font.f24pt,&vCurrent,&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	///Controls
	static float value = 0.0f;

	if(iKeyDown(VK_NUMPAD1))
	{
		value -= 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD2))
	{
		value += 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD4))
	{
		value -= 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD5))
	{
		value += 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD7))
	{
		value -= 0.5f;
	}
	else if(iKeyDown(VK_NUMPAD8))
	{
		value += 0.5f;
	}
	//-------------------------------------------------------------
	if(Current==0)
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Light_Point.PointLight_HeadLight_Alpha;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		cGame_Mesh.Light_Point.PointLight_HeadLight_Alpha = value;
	}
	else if(Current==1)
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Light_Point.PointLight_HeadLight_Range;
			bNewSelection = false;
		}
		iFloatCap(value,1.0f,500.0f);
		cGame_Mesh.Light_Point.PointLight_HeadLight_Range = value;
	}
	else if(Current==2)
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Light_Point.PointLight_HeadLight_Falloff;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,500.0f);
		cGame_Mesh.Light_Point.PointLight_HeadLight_Falloff = value;
	}
	else if(Current==3)
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Light_Point.PointLight_HeadLight_Multi;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,10.0f);
		cGame_Mesh.Light_Point.PointLight_HeadLight_Multi = value;
	}
	else if(Current==4)
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Light_Point.PointLight_HeadLight_Offset.x;
			bNewSelection = false;
		}
		iFloatCap(value,-10.0f,10.0f);
		cGame_Mesh.Light_Point.PointLight_HeadLight_Offset.x = value;
	}
	else if(Current==5)
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Light_Point.PointLight_HeadLight_Offset.y;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,50.0f);
		cGame_Mesh.Light_Point.PointLight_HeadLight_Offset.y = value;
	}
	else if(Current==6)
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Light_Point.PointLight_HeadLight_Offset.z;
			bNewSelection = false;
		}
		iFloatCap(value,-50.0f,50.0f);
		cGame_Mesh.Light_Point.PointLight_HeadLight_Offset.z = value;
	}
	else if(Current==7)
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Light_Point.PointLight_Shield_Alpha;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		cGame_Mesh.Light_Point.PointLight_Shield_Alpha = value;
	}
	else if(Current==8)
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Light_Point.PointLight_Shield_Range;
			bNewSelection = false;
		}
		iFloatCap(value,1.0f,500.0f);
		cGame_Mesh.Light_Point.PointLight_Shield_Range = value;
	}
	else if(Current==9)
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Light_Point.PointLight_Shield_Falloff;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,500.0f);
		cGame_Mesh.Light_Point.PointLight_Shield_Falloff = value;
	}
	else if(Current==10)
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Light_Point.PointLight_Shield_Multi;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,10.0f);
		cGame_Mesh.Light_Point.PointLight_Shield_Multi = value;
	}
	else if(Current==11)
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Light_Point.PointLight_Shield_Offset.x;
			bNewSelection = false;
		}
		iFloatCap(value,-10.0f,10.0f);
		cGame_Mesh.Light_Point.PointLight_Shield_Offset.x = value;
	}
	else if(Current==12)
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Light_Point.PointLight_Shield_Offset.y;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,50.0f);
		cGame_Mesh.Light_Point.PointLight_Shield_Offset.y = value;
	}
	else if(Current==13)
	{
		if(bNewSelection)
		{
			value = cGame_Mesh.Light_Point.PointLight_Shield_Offset.z;
			bNewSelection = false;
		}
		iFloatCap(value,-50.0f,50.0f);
		cGame_Mesh.Light_Point.PointLight_Shield_Offset.z = value;
	}
	else
	{
		bNewSelection = true;
		Current = 0;
	}
	sprintf_s(gCharBuffer,"Headlight_Alpha %0.2f",cGame_Mesh.Light_Point.PointLight_HeadLight_Alpha);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Headlight_Range %0.1f",cGame_Mesh.Light_Point.PointLight_HeadLight_Range);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Headlight_Falloff %0.1f",cGame_Mesh.Light_Point.PointLight_HeadLight_Falloff);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Headlight_ColourMulti %0.1f",cGame_Mesh.Light_Point.PointLight_HeadLight_Multi);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;

	sprintf_s(gCharBuffer,"Headlight_Offset X %0.1f",cGame_Mesh.Light_Point.PointLight_HeadLight_Offset.x);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Headlight_Offset Y %0.1f",cGame_Mesh.Light_Point.PointLight_HeadLight_Offset.y);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Headlight_Offset Z %0.1f",cGame_Mesh.Light_Point.PointLight_HeadLight_Offset.z);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;


	sprintf_s(gCharBuffer,"Shield_Alpha %0.2f",cGame_Mesh.Light_Point.PointLight_Shield_Alpha);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Shield_Range %0.1f",cGame_Mesh.Light_Point.PointLight_Shield_Range);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Shield_Falloff %0.1f",cGame_Mesh.Light_Point.PointLight_Shield_Falloff);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Shield_ColourMulti %0.1f",cGame_Mesh.Light_Point.PointLight_Shield_Multi);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;

	sprintf_s(gCharBuffer,"Shield_Offset X %0.1f",cGame_Mesh.Light_Point.PointLight_Shield_Offset.x);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Shield_Offset Y %0.1f",cGame_Mesh.Light_Point.PointLight_Shield_Offset.y);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Shield_Offset Z %0.1f",cGame_Mesh.Light_Point.PointLight_Shield_Offset.z);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;

	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - DEBUG - DevMode_DirectLight
///*****************************************************************
void Game_DevMode::DevMode_DirectLight(void)
{
	//-------------------------------------------------------------
	D3DXVECTOR2 vPrint = D3DXVECTOR2(-10.0f,10.0f);
	D3DXVECTOR2 vCurrent = D3DXVECTOR2(-11.0f,10.0f);
	//-------------------------------------------------------------
	///Print DevModeState
	iPrint((char*)"DevMode",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-10.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"[                   ]",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"  DirectLight",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	sprintf_s(gCharBuffer,"FPS %i",gFps);
	iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(10.0f,-12.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	if(iKeyClick(VK_UP))
	{
		Current--;
		if(Current<0)
		{
			Current = 0;
		}
		bNewSelection = true;
	}
	else if(iKeyClick(VK_DOWN))
	{
		Current++;
		bNewSelection = true;
	}
	vCurrent.y = 10.0f - ((float)Current * 0.75f);
	iPrint((char*)"->",cGame_Font.f24pt,&vCurrent,&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	///Controls
	static float value = 0.0f;

	if(iKeyDown(VK_NUMPAD1))
	{
		value -= 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD2))
	{
		value += 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD4))
	{
		value -= 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD5))
	{
		value += 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD7))
	{
		value -= 0.5f;
	}
	else if(iKeyDown(VK_NUMPAD8))
	{
		value += 0.5f;
	}
	//-------------------------------------------------------------
	//Light world
	if(Current==0)
	{
		if(bNewSelection)
		{
			value = gDirectLight1.x;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.0f);
		gDirectLight1.x = value;
		gDirectLight1.y = value;
		gDirectLight1.z = value;
	}
	//Light Ambient
	else if(Current==1)
	{
		if(bNewSelection)
		{
			value = gDirectLight1.w;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,2.0f);
		gDirectLight1.w = value;
	}
	//Light world
	else if(Current==2)
	{
		if(bNewSelection)
		{
			value = gDirectLight2.x;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.0f);
		gDirectLight2.x = value;
		gDirectLight2.y = value;
		gDirectLight2.z = value;
	}
	//Light Ambient
	else if(Current==3)
	{
		if(bNewSelection)
		{
			value = gDirectLight2.w;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,2.0f);
		gDirectLight2.w = value;
	}
	//Light world
	else if(Current==4)
	{
		if(bNewSelection)
		{
			value = gDirectLight3.x;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.0f);
		gDirectLight3.x = value;
		gDirectLight3.y = value;
		gDirectLight3.z = value;
	}
	//Light Ambient
	else if(Current==5)
	{
		if(bNewSelection)
		{
			value = gDirectLight3.w;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,2.0f);
		gDirectLight3.w = value;
	}
	//Light4
	else if(Current==6)
	{
		if(bNewSelection)
		{
			value = gDirectLight4.x;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.0f);
		gDirectLight4.x = value;
	}
	else if(Current==7)
	{
		if(bNewSelection)
		{
			value = gDirectLight4.y;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.0f);
		gDirectLight4.y = value;
	}
	else if(Current==8)
	{
		if(bNewSelection)
		{
			value = gDirectLight4.z;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,3.0f);
		gDirectLight4.z = value;
	}
	//Light Ambient
	else if(Current==9)
	{
		if(bNewSelection)
		{
			value = gDirectLight4.w;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,2.0f);
		gDirectLight4.w = value;
	}
	else if(Current==10)
	{
		if(bNewSelection)
		{
			value = gHsvMin;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,2.0f);
		gHsvMin = value;
	}
	else if(Current==11)
	{
		if(bNewSelection)
		{
			value = gHsvMax;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,5.0f);
		gHsvMax = value;
	}
	else
	{
		bNewSelection = true;
		Current = 0;
	}
	sprintf_s(gCharBuffer,"Light1_Emit %0.2f",gDirectLight1.x);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Light1_Ambient %0.2f",gDirectLight1.w);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;

	sprintf_s(gCharBuffer,"Light2_Emit %0.2f",gDirectLight2.x);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Light2_Ambient %0.2f",gDirectLight2.w);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;

	sprintf_s(gCharBuffer,"Light3_Emit %0.2f",gDirectLight3.x);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Light3_Ambient %0.2f",gDirectLight3.w);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;

	sprintf_s(gCharBuffer,"Light4_R %0.2f",gDirectLight4.x);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Light4_G %0.2f",gDirectLight4.y);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Light4_B %0.2f",gDirectLight4.z);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Light4_Ambient %0.2f",gDirectLight4.w);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;

	//HSV stuff
	sprintf_s(gCharBuffer,"gHsvMin %0.2f",gHsvMin);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"gHsvMax %0.2f",gHsvMax);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - DEBUG - DevMode_Culling
///*****************************************************************
void Game_DevMode::DevMode_Culling(void)
{
	//-------------------------------------------------------------
	D3DXVECTOR2 vPrint = D3DXVECTOR2(-10.0f,10.0f);
	D3DXVECTOR2 vCurrent = D3DXVECTOR2(-11.0f,10.0f);
	//-------------------------------------------------------------
	///Print DevModeState
	iPrint((char*)"DevMode",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-10.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"[                       ]",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"  Ai Render Limits",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	sprintf_s(gCharBuffer,"FPS %i",gFps);
	iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(10.0f,-12.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	if(iKeyClick(VK_UP))
	{
		Current--;
		if(Current<0)
		{
			Current = 0;
		}
		bNewSelection = true;
	}
	else if(iKeyClick(VK_DOWN))
	{
		Current++;
		bNewSelection = true;
	}
	vCurrent.y = 10.0f - ((float)Current * 0.75f);
	iPrint((char*)"->",cGame_Font.f24pt,&vCurrent,&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	///Controls
	static float value = 0.0f;

	if(iKeyDown(VK_NUMPAD1))
	{
		value -= 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD2))
	{
		value += 0.01f;
	}
	else if(iKeyDown(VK_NUMPAD4))
	{
		value -= 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD5))
	{
		value += 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD7))
	{
		value -= 0.5f;
	}
	else if(iKeyDown(VK_NUMPAD8))
	{
		value += 0.5f;
	}
	//-------------------------------------------------------------
	//
	if(Current==0)
	{
		if(bNewSelection)
		{
			value = (float)gMax_Culling_Bikes_Shown;
			bNewSelection = false;
		}
		iFloatCap(value,1.0f,(float)MAX_BIKE_AI_COUNT);
		gMax_Culling_Bikes_Shown = (int)value;
	}
	//
	else if(Current==1)
	{
		if(bNewSelection)
		{
			value = (float)gMax_Culling_Bikes_Low_Detail;
			bNewSelection = false;
		}
		iFloatCap(value,1.0f,(float)MAX_BIKE_AI_COUNT);
		gMax_Culling_Bikes_Low_Detail = (int)value;
	}
	else if(Current==2)
	{
		if(bNewSelection)
		{
			value = (float)gMax_Culling_Bikes_High_Detail;
			bNewSelection = false;
		}
		iFloatCap(value,1.0f,(float)MAX_BIKE_AI_COUNT);
		gMax_Culling_Bikes_High_Detail = (int)value;
	}
	else
	{
		bNewSelection = true;
		Current = 0;
	}

	sprintf_s(gCharBuffer,"Total Draw %d",gMax_Culling_Bikes_Shown);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"Low Detail %d",gMax_Culling_Bikes_Low_Detail);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"High Detail %d",gMax_Culling_Bikes_High_Detail);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - DEBUG - DevMode_Shadows
///*****************************************************************
void Game_DevMode::DevMode_Shadows(void)
{
	//-------------------------------------------------------------
	D3DXVECTOR2 vPrint = D3DXVECTOR2(-10.0f,10.0f);
	D3DXVECTOR2 vCurrent = D3DXVECTOR2(-11.0f,10.0f);
	//-------------------------------------------------------------
	///Print DevModeState
	iPrint((char*)"DevMode",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-10.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"[                       ]",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"  Shadows",cGame_Font.f32pt,&D3DXVECTOR2(9.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	sprintf_s(gCharBuffer,"FPS %i",gFps);
	iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(10.0f,-12.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	if(iKeyClick(VK_UP))
	{
		Current--;
		if(Current<0)
		{
			Current = 0;
		}
		bNewSelection = true;
	}
	else if(iKeyClick(VK_DOWN))
	{
		Current++;
		bNewSelection = true;
	}
	vCurrent.y = 10.0f - ((float)Current * 0.75f);
	iPrint((char*)"->",cGame_Font.f24pt,&vCurrent,&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
	///Controls
	static float value = 0.0f;

	if(iKeyDown(VK_NUMPAD1))
	{
		value -= 0.001f;
	}
	else if(iKeyDown(VK_NUMPAD2))
	{
		value += 0.001f;
	}
	else if(iKeyDown(VK_NUMPAD4))
	{
		value -= 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD5))
	{
		value += 0.1f;
	}
	else if(iKeyDown(VK_NUMPAD7))
	{
		value -= 5.0f;
	}
	else if(iKeyDown(VK_NUMPAD8))
	{
		value += 5.0f;
	}
	//-------------------------------------------------------------
	//
	if(Current==0)
	{
		if(bNewSelection)
		{
			value = (float)gShadowsResolution;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,6.0f);
		gShadowsResolution = (int)value;
	}
	//
	else if(Current==1)
	{
		if(bNewSelection)
		{
			value = gShadowBlur;
			bNewSelection = false;
		}
		iFloatCap(value,1.0f,1000.0f);
		gShadowBlur = value;
	}
	else if(Current==2)
	{
		if(bNewSelection)
		{
			value = gShadowBias;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		gShadowBias = value;
	}
	else if(Current==3)
	{
		if(bNewSelection)
		{
			value = gShadowDensity;
			bNewSelection = false;
		}
		iFloatCap(value,0.0f,1.0f);
		gShadowDensity = value;
	}
	//Location
	else if(Current==4)
	{
		if(bNewSelection)
		{
			value = gShadowsLocation.x;
			bNewSelection = false;
		}
		iFloatCap(value,-2000.0f,2000.0f);
		gShadowsLocation.x = value;
	}
	else if(Current==5)
	{
		if(bNewSelection)
		{
			value = gShadowsLocation.y;
			bNewSelection = false;
		}
		iFloatCap(value,-2000.0f,2000.0f);
		gShadowsLocation.y = value;
	}
	else if(Current==6)
	{
		if(bNewSelection)
		{
			value = gShadowsLocation.z;
			bNewSelection = false;
		}
		iFloatCap(value,-2000.0f,2000.0f);
		gShadowsLocation.z = value;
	}
	//Orientation
	else if(Current==7)
	{
		if(bNewSelection)
		{
			value = gShadowsOrientation.x;
			bNewSelection = false;
		}
		iFloatCap(value,-360.0f,360.0f);
		gShadowsOrientation.x = value;
	}
	else if(Current==8)
	{
		if(bNewSelection)
		{
			value = gShadowsOrientation.y;
			bNewSelection = false;
		}
		iFloatCap(value,-360.0f,360.0f);
		gShadowsOrientation.y = value;
	}
	else if(Current==9)
	{
		if(bNewSelection)
		{
			value = gShadowsOrientation.z;
			bNewSelection = false;
		}
		iFloatCap(value,-360.0f,360.0f);
		gShadowsOrientation.z = value;
	}
	//Size
	else if(Current==10)
	{
		if(bNewSelection)
		{
			value = gShadowsSize.x;
			bNewSelection = false;
		}
		iFloatCap(value,1.0f,5000.0f);
		gShadowsSize.x = value;
	}
	else if(Current==11)
	{
		if(bNewSelection)
		{
			value = gShadowsSize.y;
			bNewSelection = false;
		}
		iFloatCap(value,1.0f,5000.0f);
		gShadowsSize.y = value;
	}
	else
	{
		bNewSelection = true;
		Current = 0;
	}

	sprintf_s(gCharBuffer,"gShadowsResolution %d",gShadowsResolution);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"gShadowBlur %0.2f",gShadowBlur);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"gShadowBias %0.4f",gShadowBias);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"gShadowDensity %0.2f",gShadowDensity);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	
	sprintf_s(gCharBuffer,"gShadowsLocation.x %0.0f",gShadowsLocation.x);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"gShadowsLocation.y %0.0f",gShadowsLocation.y);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"gShadowsLocation.z %0.0f",gShadowsLocation.z);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;

	sprintf_s(gCharBuffer,"gShadowsOrientation.x %0.0f",gShadowsOrientation.x);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"gShadowsOrientation.y %0.0f",gShadowsOrientation.y);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"gShadowsOrientation.z %0.0f",gShadowsOrientation.z);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;

	sprintf_s(gCharBuffer,"gShadowsSize.x %0.0f",gShadowsSize.x);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;
	sprintf_s(gCharBuffer,"gShadowsSize.y %0.0f",gShadowsSize.y);
	iPrint(gCharBuffer,cGame_Font.f16pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	vPrint.y -= 0.75f;

	//Apply Shadow updates
	D3DXQUATERNION qDown = D3DXQUATERNION(0.0f,0.0f,0.0,1.0f);
	iQuaternionFromEulerAngles(&qDown,gShadowsOrientation.x,gShadowsOrientation.y,gShadowsOrientation.z);
	iShadowMapCascadeFocusSet(gCamera,0,&gShadowsLocation,&qDown);

	iShadowMapCascadeConfigureSet(gCamera,0,gShadowsSize.x,gShadowsSize.y);//side/depth

	iCameraShadowMapCascadeDensitySet(gCamera,gShadowDensity);
	iCameraShadowMapBlurSet(gCamera,1,gShadowBlur);
	iCameraShadowMapCascadeBiasSet(gCamera,0,gShadowBias);
	iShadowMapCascadeDebugVisualShow();

	//SAVE
	iPrint((char*)"F8 = Load",cGame_Font.f20pt,&D3DXVECTOR2(9.0f,-6.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	iPrint((char*)"F9 = Save",cGame_Font.f20pt,&D3DXVECTOR2(9.0f,-7.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	if(iKeyClick(DIK_F8))
	{
		cGame_PostProcessing.Create();
		bNewSelection = true;
	}
	else if(iKeyClick(DIK_F9))
	{
		cGame_PostProcessing.Save_ShadowSettings();
		cGame_PostProcessing.Create();
		bNewSelection = true;
	}

	//re-apply stack on resolution change
	static int resolutioncheck = gShadowsResolution;
	if(resolutioncheck!=gShadowsResolution)
	{
		cGame_PostProcessing.Create();
		resolutioncheck = gShadowsResolution;
	}
	//-------------------------------------------------------------
}