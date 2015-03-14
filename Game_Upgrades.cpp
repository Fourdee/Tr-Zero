//-----------------------------------------------------------------
// About:
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Upgrades.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - UPGRADES - CONSTRUCTORS
///*****************************************************************
Game_Upgrades::Game_Upgrades(void)
{
	//-------------------------------------------------------------
	//Player data init (loads from file after this)
	uPrimaryDamagePlayer = 0;
	uPrimaryTravelPlayer = 0;

	uMissileLockTimePlayer = 0;
	uMissileDamagePlayer = 0;
	uMissileRadiusPlayer = 0;
	uMissileTravelPlayer = 0;

	uShoxwaveDamagePlayer = 0;
	uShoxwaveReductionPlayer = 0;

	uEmBurstDamagePlayer = 0;
	uEmBurstRadiusPlayer = 0;
	uEmBurstReductionPlayer = 0;

	uRailDamagePlayer = 0;
	uRailTravelPlayer = 0;

	uShieldInvTimePlayer = 0;
	uShieldInvConvertPlayer = 0;
	uAutoPilotTimePlayer = 0;
	uDoubleDamageTimePlayer = 0;
	uDoubleDamageConvPlayer = 0;
	uWarpDamageReducePlayer = 0;

	uEnergyMaxPlayer = 0;
	uEnergyPickupPlayer = 0;
	uSpeedClassUnlockPlayer = 0;
	uEnergyTickRegenPlayer = 0;
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Upgrades::~Game_Upgrades(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - UPGRADES - ZeroData
///*****************************************************************
void Game_Upgrades::ZeroData(void)
{
	//-------------------------------------------------------------
	//Info flags
	///PRimary Weapons
	Info_PrimaryDamage[0] = 0;
	Info_PrimaryDamage[1] = 25;
	Info_PrimaryDamage[2] = 50;
	Info_PrimaryDamage[3] = 75;

	Info_PrimaryTravel[0] = 0;
	Info_PrimaryTravel[1] = 10;
	Info_PrimaryTravel[2] = 20;
	Info_PrimaryTravel[3] = 30;

	///Secondary Weapons
	Info_MissileLockTime[0] = 0;
	Info_MissileLockTime[1] = 16;
	Info_MissileLockTime[2] = 33;
	Info_MissileLockTime[3] = 50;

	Info_MissileDamage[0] = 0;
	Info_MissileDamage[1] = 33;
	Info_MissileDamage[2] = 66;
	Info_MissileDamage[3] = 100;

	Info_MissileRadius[0] = 0;
	Info_MissileRadius[1] = 33;
	Info_MissileRadius[2] = 66;
	Info_MissileRadius[3] = 100;
	
	Info_MissileTravel[0] = 0;
	Info_MissileTravel[1] = 15;
	Info_MissileTravel[2] = 30;
	Info_MissileTravel[3] = 45;

	Info_ShoxwaveDamage[0] = 0;
	Info_ShoxwaveDamage[1] = 50;
	Info_ShoxwaveDamage[2] = 100;
	Info_ShoxwaveDamage[3] = 150;

	Info_ShoxwaveTravel[0] = 0;
	Info_ShoxwaveTravel[1] = 10;
	Info_ShoxwaveTravel[2] = 20;
	Info_ShoxwaveTravel[3] = 30;
	
	Info_ShoxwaveReduction[0] = 0;
	Info_ShoxwaveReduction[1] = 50;
	Info_ShoxwaveReduction[2] = 100;
	Info_ShoxwaveReduction[3] = 150;

	Info_EmBurstDamage[0] = 0;
	Info_EmBurstDamage[1] = 50;
	Info_EmBurstDamage[2] = 100;
	Info_EmBurstDamage[3] = 150;

	Info_EmBurstRadius[0] = 0;
	Info_EmBurstRadius[1] = 16;
	Info_EmBurstRadius[2] = 33;
	Info_EmBurstRadius[3] = 50;

	Info_EmBurstReduction[0] = 0;
	Info_EmBurstReduction[1] = 25;
	Info_EmBurstReduction[2] = 50;
	Info_EmBurstReduction[3] = 75;

	Info_RailDamage[0] = 0;
	Info_RailDamage[1] = 33;
	Info_RailDamage[2] = 66;
	Info_RailDamage[3] = 100;

	Info_RailTravel[0] = 0;
	Info_RailTravel[1] = 12;
	Info_RailTravel[2] = 25;
	Info_RailTravel[3] = 40;

	///Utility
	Info_ShieldInvTime[0] = 5;
	Info_ShieldInvTime[1] = 7;
	Info_ShieldInvTime[2] = 8;
	Info_ShieldInvTime[3] = 10;

	Info_ShieldInvConvert[0] = 0;
	Info_ShieldInvConvert[1] = 25;
	Info_ShieldInvConvert[2] = 50;
	Info_ShieldInvConvert[3] = 75;

	Info_AutoPilotTime[0] = 5;
	Info_AutoPilotTime[1] = 7;
	Info_AutoPilotTime[2] = 8;
	Info_AutoPilotTime[3] = 10;

	Info_DoubleDamageTime[0] = 5;
	Info_DoubleDamageTime[1] = 7;
	Info_DoubleDamageTime[2] = 8;
	Info_DoubleDamageTime[3] = 10;

	Info_DoubleDamageConv[0] = 0;
	Info_DoubleDamageConv[1] = 8;
	Info_DoubleDamageConv[2] = 16;
	Info_DoubleDamageConv[3] = 25;

	Info_WarpDamageReduce[0] = 20;
	Info_WarpDamageReduce[1] = 40;
	Info_WarpDamageReduce[2] = 60;
	Info_WarpDamageReduce[3] = 80;

	///Energy
	Info_SpeedClassUnlock[0] = 250;
	Info_SpeedClassUnlock[1] = 500;
	Info_SpeedClassUnlock[2] = 750;
	Info_SpeedClassUnlock[3] = 1000;

	Info_EnergyMax[0] = 250;
	Info_EnergyMax[1] = 300;
	Info_EnergyMax[2] = 350;
	Info_EnergyMax[3] = 400;

	Info_EnergyPickup[0] = 30;
	Info_EnergyPickup[1] = 40;
	Info_EnergyPickup[2] = 50;
	Info_EnergyPickup[3] = 60;

	Info_EnergyTickRegen[0] = 1;
	Info_EnergyTickRegen[1] = 2;
	Info_EnergyTickRegen[2] = 3;
	Info_EnergyTickRegen[3] = 4;
	//-------------------------------------------------------------
	int AiUpgradeLevel = 0;
	if(gAiDifficuty>=1)
	{
		AiUpgradeLevel = gAiDifficuty - 1;
	}
	for(int i=0;i<40;i++)
	{
		//Zero all upgrades
		//Dont reset active networked players
		//apply ai difficulty to remaning Ai bikes
		if(i>=gNumberOfClients)
		{
			//Primary Weapon Upgrades
			///Primary Damage
			uPrimaryDamage[i] = AiUpgradeLevel;
			fPrimaryDamageMin[i] = 0.0f;
			fPrimaryDamageMax[i] = 0.0f;
			///Primary Travel Speed
			uPrimaryTravel[i] = AiUpgradeLevel;
			fPrimaryTravel[i] = 0.0f;
			//Secondary Weapon Upgrades
			///Missile Lock Time
			uMissileLockTime[i] = AiUpgradeLevel;
			MissileLockTime[i] = 0;
			///Missile Damage
			uMissileDamage[i] = AiUpgradeLevel;
			fMissileDamage[i] = 0.0f;
			///Missile Radius
			uMissileRadius[i] = AiUpgradeLevel;
			fMissileRadius[i] = 0.0f;
			///Missile Travel Speed
			uMissileTravel[i] = AiUpgradeLevel;
			fMissileTravel[i] = 0.0f;
			///Shoxwave Damage
			uShoxwaveDamage[i] = AiUpgradeLevel;
			fShoxwaveDamage[i] = 0.0f;
			///Shoxwave Travel Speed
			uShoxwaveTravel[i] = AiUpgradeLevel;
			fShoxwaveTravel[i] = 0.0f;
			///Shoxwave Speed Reduction
			uShoxwaveReduction[i] = AiUpgradeLevel;
			fShoxwaveReduction[i] = 0.0f;
			///Em Burst Damage
			uEmBurstDamage[i] = AiUpgradeLevel;
			fEmBurstDamageMin[i] = 0.0f;
			fEmBurstDamageMax[i] = 0.0f;
			///Em Burst Radius
			uEmBurstRadius[i] = AiUpgradeLevel;
			fEmBurstRadius[i] = 0.0f;
			///Em Burst Speed Reduction
			uEmBurstReduction[i] = AiUpgradeLevel;
			fEmBurstReduction[i] = 0.0f;
			///Rail Damage
			uRailDamage[i] = AiUpgradeLevel;
			fRailDamageMin[i] = 0.0f;
			fRailDamageMax[i] = 0.0f;
			///Rail Travel Speed
			uRailTravel[i] = AiUpgradeLevel;
			fRailTravel[i] = 0.0f;
			//Utility Weapon Upgrades
			///ShieldInv Time
			uShieldInvTime[i] = AiUpgradeLevel;
			ShieldInvTime[i] = 0;
			///ShieldInv Convert
			uShieldInvConvert[i] = AiUpgradeLevel;
			fShieldInvConvert[i] = 0.0f;
			///AutoPilot Time
			uAutoPilotTime[i] = AiUpgradeLevel;
			AutoPilotTime[i] = 0;
			///DoubleDamage Time
			uDoubleDamageTime[i] = AiUpgradeLevel;
			DoubleDamageTime[i] = 0;
			///DoubleDamageConv
			uDoubleDamageConv[i] = AiUpgradeLevel;
			fDoubleDamageConv[i] = 0.0f;
			///Warp Damage Reduce
			uWarpDamageReduce[i] = AiUpgradeLevel;
			fWarpDamageReduce[i] = 0.0f;
			//Energy Upgrades
			///EnergyMax
			uEnergyMax[i] = AiUpgradeLevel;
			fEnergyMax[i] = 0.0f;
			///EnergyPickup
			uEnergyPickup[i] = AiUpgradeLevel;
			fEnergyPickup[i] = 0.0f;
			///PlayerLevel
			uPlayerLevel[i] = AiUpgradeLevel;
			///EnergyTickRegen
			uEnergyTickRegen[i] = AiUpgradeLevel;
			fEnergyTickRegen[i] = 0.0f;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - UPGRADES - CREATE
///*****************************************************************
void Game_Upgrades::Create(void)
{
	//-------------------------------------------------------------
	float fMin = 0.0f;
	float fMax = 0.0f;
	//-------------------------------------------------------------
	//Flush to defaults
	ZeroData();
	//-------------------------------------------------------------
	//Load Player Data
	LoadSettings();
	//-------------------------------------------------------------
	//Apply upgraded states to floats/int values we use
	for(int i=0;i<40;i++)
	{
		//Load player data
		if(i==gAi_Max_Count)
		{
			uPrimaryDamage[i] = uPrimaryDamagePlayer;
			uPrimaryTravel[i] = uPrimaryTravelPlayer;
			uMissileLockTime[i] = uMissileLockTimePlayer;
			uMissileDamage[i] = uMissileDamagePlayer;
			uMissileRadius[i] = uMissileRadiusPlayer;
			uMissileTravel[i] = uMissileTravelPlayer;
			uShoxwaveDamage[i] = uShoxwaveDamagePlayer;
			uShoxwaveTravel[i] = uShoxwaveTravelPlayer;
			uShoxwaveReduction[i] = uShoxwaveReductionPlayer;
			uEmBurstDamage[i] = uEmBurstDamagePlayer;
			uEmBurstRadius[i] = uEmBurstRadiusPlayer;
			uEmBurstReduction[i] = uEmBurstReductionPlayer;
			uRailDamage[i] = uRailDamagePlayer;
			uRailTravel[i] = uRailTravelPlayer;
			uShieldInvTime[i] = uShieldInvTimePlayer;
			uShieldInvConvert[i] = uShieldInvConvertPlayer;
			uAutoPilotTime[i] = uAutoPilotTimePlayer;
			uDoubleDamageTime[i] = uDoubleDamageTimePlayer;
			uDoubleDamageConv[i] = uDoubleDamageConvPlayer;
			uWarpDamageReduce[i] = uWarpDamageReducePlayer;
			uEnergyMax[i] = uEnergyMaxPlayer;
			uEnergyPickup[i] = uEnergyPickupPlayer;
			uPlayerLevel[i] = cGame_PlayerStats.Player_Level;
			uEnergyTickRegen[i] = uEnergyTickRegenPlayer;
		}
		//Offline - match Ai energy upgrades to player
		else if(cGame_Network.Client.State==0 && 
			cGame_Network.Server.State==0)
		{
			//Energy Upgrades
			///EnergyMax
			uEnergyMax[i] = uEnergyMaxPlayer;
			///EnergyPickup
			uEnergyPickup[i] = uEnergyPickupPlayer;
			///PlayerLevel
			uPlayerLevel[i] = uSpeedClassUnlockPlayer;
			///EnergyTickRegen
			uEnergyTickRegen[i] = uEnergyTickRegenPlayer;
		}

		//Primary Weapon Upgrades
		///Primary Damage
		fMin = 10.0f;
		fMax = 20.0f;
		fPrimaryDamageMin[i] = iFloatInterpolate((float)uPrimaryDamage[i],0.0f,3.0f,fMin,fMax);
		fMin = 15.0f;
		fMax = 35.0f;
		fPrimaryDamageMax[i] = iFloatInterpolate((float)uPrimaryDamage[i],0.0f,3.0f,fMin,fMax);
		///Primary Travel Speed
		fMin = 5.5f;
		fMax = 6.75f;
		fPrimaryTravel[i] = iFloatInterpolate((float)uPrimaryTravel[i],0.0f,3.0f,fMin,fMax);
		//Secondary Weapon Upgrades
		///Missile Lock Time
		fMin = 90.0f;
		fMax = 45.0f;
		MissileLockTime[i] = (int)iFloatInterpolate((float)uMissileLockTime[i],0.0f,3.0f,fMin,fMax);
		///Missile Damage
		fMin = 100.0f;
		fMax = 200.0f;
		fMissileDamage[i] = iFloatInterpolate((float)uMissileDamage[i],0.0f,3.0f,fMin,fMax);
		///Missile Radius
		fMin = 40.0f;
		fMax = 80.0f;
		fMissileRadius[i] = iFloatInterpolate((float)uMissileRadius[i],0.0f,3.0f,fMin,fMax);
		///Missile Travel Speed
		fMin = 0.045f;
		fMax = 0.06f;
		fMissileTravel[i] = iFloatInterpolate((float)uMissileTravel[i],0.0f,3.0f,fMin,fMax);
		///Shoxwave Damage
		fMin = 2.0f;
		fMax = 5.0f;
		fShoxwaveDamage[i] = iFloatInterpolate((float)uShoxwaveDamage[i],0.0f,3.0f,fMin,fMax);
		///Shoxwave Travel Speed
		fMin = 0.0075f;
		fMax = 0.01f;
		fShoxwaveTravel[i] = iFloatInterpolate((float)uShoxwaveTravel[i],0.0f,3.0f,fMin,fMax);
		///Shoxwave Speed Reduction
		fMin = 0.02f;
		fMax = 0.03f;
		fShoxwaveReduction[i] = iFloatInterpolate((float)uShoxwaveReduction[i],0.0f,3.0f,fMin,fMax);
		///Em Burst Damage
		fMin = 1.0f;
		fMax = 2.0f;
		fEmBurstDamageMin[i] = iFloatInterpolate((float)uEmBurstDamage[i],0.0f,3.0f,fMin,fMax);
		fMin = 2.0f;
		fMax = 4.0f;
		fEmBurstDamageMax[i] = iFloatInterpolate((float)uEmBurstDamage[i],0.0f,3.0f,fMin,fMax);
		///Em Burst Radius
		fMin = 60.0f;
		fMax = 120.0f;
		fEmBurstRadius[i] = iFloatInterpolate((float)uEmBurstRadius[i],0.0f,3.0f,fMin,fMax);
		///Em Burst Speed Reduction
		fMin = 0.05f;
		fMax = 0.08f;
		fEmBurstReduction[i] = iFloatInterpolate((float)uEmBurstReduction[i],0.0f,3.0f,fMin,fMax);
		///Rail Damage
		fMin = 15.0f;
		fMax = 100.0f;
		fRailDamageMin[i] = iFloatInterpolate((float)uRailDamage[i],0.0f,3.0f,fMin,fMax);
		fMin = 65.0f;
		fMax = 200.0f;
		fRailDamageMax[i] = iFloatInterpolate((float)uRailDamage[i],0.0f,3.0f,fMin,fMax);
		///Rail Travel Speed
		fMin = 10.0f;
		fMax = 14.0f;
		fRailTravel[i] = iFloatInterpolate((float)uRailTravel[i],0.0f,3.0f,fMin,fMax);
		//Utility Weapon Upgrades
		///ShieldInv Time
		fMin = 300.0f;
		fMax = 600.0f;
		ShieldInvTime[i] = (int)iFloatInterpolate((float)uShieldInvTime[i],0.0f,3.0f,fMin,fMax);
		///ShieldInv Convert
		fMin = 0.0f;
		fMax = 0.75f;
		fShieldInvConvert[i] = iFloatInterpolate((float)uShieldInvConvert[i],0.0f,3.0f,fMin,fMax);
		///AutoPilot Time
		fMin = 300.0f;
		fMax = 600.0f;
		AutoPilotTime[i] = (int)iFloatInterpolate((float)uAutoPilotTime[i],0.0f,3.0f,fMin,fMax);
		///DoubleDamage Time
		fMin = 300.0f;
		fMax = 600.0f;
		DoubleDamageTime[i] = (int)iFloatInterpolate((float)uDoubleDamageTime[i],0.0f,3.0f,fMin,fMax);
		///DoubleDamage Convert
		fMin = 0.0f;
		fMax = 0.24f;
		fDoubleDamageConv[i] = iFloatInterpolate((float)uDoubleDamageConv[i],0.0f,3.0f,fMin,fMax);
		///Warp Damage Reduce
		fMin = 0.8f;
		fMax = 0.2f;
		fWarpDamageReduce[i] = iFloatInterpolate((float)uWarpDamageReduce[i],0.0f,3.0f,fMin,fMax);
		//Energy Upgrades
		///EnergyMax
		fMin = 250.0f;
		fMax = 400.0f;
		fEnergyMax[i] = iFloatInterpolate((float)uEnergyMax[i],0.0f,3.0f,fMin,fMax);
		///EnergyPickup
		fMin = 30.0f;
		fMax = 60.0f;
		fEnergyPickup[i] = iFloatInterpolate((float)uEnergyPickup[i],0.0f,3.0f,fMin,fMax);
		///EnergyTickRegen
		fMin = 1.0f;
		fMax = 4.0f;
		fEnergyTickRegen[i] = iFloatInterpolate((float)uEnergyTickRegen[i],0.0f,3.0f,fMin,fMax);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - UPGRADES - LOAD SETTINGS
///*****************************************************************
void Game_Upgrades::LoadSettings(void)
{
	//-------------------------------------------------------------
	if(iFileExists(gFilePath_Settings_Upgrades))
	{
		HANDLE hFile; 
		DWORD dwDone; 
		char filepath[1024];

		strcpy_s(filepath,gFilePath_Settings_Upgrades);
		iGlobalPathMake(filepath);

		hFile = CreateFile(filepath,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			//-----------------------------------------------------
			ReadFile(hFile,&uPrimaryDamagePlayer,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&uPrimaryTravelPlayer,sizeof(int),&dwDone,NULL);

			ReadFile(hFile,&uMissileLockTimePlayer,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&uMissileDamagePlayer,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&uMissileRadiusPlayer,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&uMissileTravelPlayer,sizeof(int),&dwDone,NULL);

			ReadFile(hFile,&uShoxwaveDamagePlayer,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&uShoxwaveTravelPlayer,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&uShoxwaveReductionPlayer,sizeof(int),&dwDone,NULL);

			ReadFile(hFile,&uEmBurstDamagePlayer,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&uEmBurstRadiusPlayer,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&uEmBurstReductionPlayer,sizeof(int),&dwDone,NULL);

			ReadFile(hFile,&uRailDamagePlayer,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&uRailTravelPlayer,sizeof(int),&dwDone,NULL);

			ReadFile(hFile,&uShieldInvTimePlayer,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&uShieldInvConvertPlayer,sizeof(int),&dwDone,NULL);

			ReadFile(hFile,&uAutoPilotTimePlayer,sizeof(int),&dwDone,NULL);

			ReadFile(hFile,&uDoubleDamageTimePlayer,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&uDoubleDamageConvPlayer,sizeof(int),&dwDone,NULL);

			ReadFile(hFile,&uWarpDamageReducePlayer,sizeof(int),&dwDone,NULL);

			ReadFile(hFile,&uEnergyMaxPlayer,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&uEnergyPickupPlayer,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&uSpeedClassUnlockPlayer,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&uEnergyTickRegenPlayer,sizeof(int),&dwDone,NULL);
			//---------------------------------------------------------
			CloseHandle(hFile); 
		}
	}
	else
	{
		SaveSettings();
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - UPGRADES - SAVE SETTINGS
///*****************************************************************
void Game_Upgrades::SaveSettings(void)
{
	//-------------------------------------------------------------
	HANDLE hFile; 
	DWORD dwDone; 
	char filepath[1024];

	strcpy_s(filepath,gFilePath_Settings_Upgrades);
	iGlobalPathMake(filepath);

	hFile = CreateFile(filepath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		//---------------------------------------------------------
		WriteFile(hFile,&uPrimaryDamagePlayer,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&uPrimaryTravelPlayer,sizeof(int),&dwDone,NULL);

		WriteFile(hFile,&uMissileLockTimePlayer,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&uMissileDamagePlayer,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&uMissileRadiusPlayer,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&uMissileTravelPlayer,sizeof(int),&dwDone,NULL);

		WriteFile(hFile,&uShoxwaveDamagePlayer,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&uShoxwaveTravelPlayer,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&uShoxwaveReductionPlayer,sizeof(int),&dwDone,NULL);

		WriteFile(hFile,&uEmBurstDamagePlayer,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&uEmBurstRadiusPlayer,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&uEmBurstReductionPlayer,sizeof(int),&dwDone,NULL);

		WriteFile(hFile,&uRailDamagePlayer,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&uRailTravelPlayer,sizeof(int),&dwDone,NULL);

		WriteFile(hFile,&uShieldInvTimePlayer,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&uShieldInvConvertPlayer,sizeof(int),&dwDone,NULL);

		WriteFile(hFile,&uAutoPilotTimePlayer,sizeof(int),&dwDone,NULL);

		WriteFile(hFile,&uDoubleDamageTimePlayer,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&uDoubleDamageConvPlayer,sizeof(int),&dwDone,NULL);

		WriteFile(hFile,&uWarpDamageReducePlayer,sizeof(int),&dwDone,NULL);

		WriteFile(hFile,&uEnergyMaxPlayer,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&uEnergyPickupPlayer,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&uSpeedClassUnlockPlayer,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&uEnergyTickRegenPlayer,sizeof(int),&dwDone,NULL);
		//---------------------------------------------------------
		CloseHandle(hFile); 
	}
	//-------------------------------------------------------------
}
