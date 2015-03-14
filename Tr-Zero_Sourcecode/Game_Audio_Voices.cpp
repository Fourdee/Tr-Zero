//-----------------------------------------------------------------
// About:
//
// name: "Game_Audio_Voices.cpp:
//
// included in: "Game_Audio_Voices.h"
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
#include "Game_Audio_Voices.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - AUDIO - VOICES - CONSTRUCTORS
///*****************************************************************
Game_Audio_Voices::Game_Audio_Voices(void)
{
	//-------------------------------------------------------------
	//Data
	ZeroData();
	//---------------------------------------------------------
	//Utility
	ShieldInv = NULL;
	AutoPilot = NULL;
	DoubleDamage = NULL;
	Warp = NULL;
	//-------------------------------------------------------------
	//Weapons
	WeaponsOnline = NULL;
	Shockwave = NULL;
	EMBurst = NULL;
	FusionMissile = NULL;
	LancerRail = NULL;
	//BoostEnabled
	BoostEnabled = NULL;
	//Energy
	EnergyCrit = NULL;
	//Countdown
	Countdown = NULL;
	//End Game Alerts
	GameComplete = NULL;
	GameOver = NULL;
	//Final Lap
	FinalLap = NULL;
	//---------------------------------------------------------
	//Position Placed
	PositionPlaced = NULL;
	//Position Human
	PositionHuman = NULL;
	//-------------------------------------------------------------
}

Game_Audio_Voices::~Game_Audio_Voices(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - VOICES - ZERODATA
///*****************************************************************
void Game_Audio_Voices::ZeroData(void)
{
	//-------------------------------------------------------------
	//Data
	fVoiceVolume = 1.1f;
	PlayTimerMax = 120;
	PlayTimer = PlayTimerMax;
	//-------------------------------------------------------------
	//Utility
	bShieldInv = false;
	bAutoPilot = false;
	bDoubleDamage = false;
	bWarp = false;
	//Weapons
	bWeaponsOnline = false;
	bShockwave = false;
	bEMBurst = false;
	bFusionMissile = false;
	bLancerRail = false;
	//BoostEnabled
	bBoostEnabled = false;
	//Energy
	bEnergyCrit = false;
	//Countdown
	bCountdown = false;
	//End Game Alerts
	bGameComplete = false;
	//Final Lap
	bFinalLap = false;
	//---------------------------------------------------------
	//Position Placed
	bPositionPlaced = false;
	//PositionHuman
	bPositionHuman = false;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - VOICES - CREATE
///*****************************************************************
void Game_Audio_Voices::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
	ShieldInv = iSoundCreate("trzero_res\\sound\\voice_ryan\\shield_inv.wav",false);
	AutoPilot = iSoundCreate("trzero_res\\sound\\voice_ryan\\autopilot.wav",false);
	DoubleDamage = iSoundCreate("trzero_res\\sound\\voice_ryan\\double_damage.wav",false);
	Warp = iSoundCreate("trzero_res\\sound\\voice_ryan\\warp.wav",false);
	WeaponsOnline = iSoundCreate("trzero_res\\sound\\voice_ryan\\weapons_online.wav",false);
	Shockwave = iSoundCreate("trzero_res\\sound\\voice_ryan\\shox_wave.wav",false);
	EMBurst = iSoundCreate("trzero_res\\sound\\voice_ryan\\emburst.wav",false);
	FusionMissile = iSoundCreate("trzero_res\\sound\\voice_ryan\\fusionmissile.wav",false);
	LancerRail = iSoundCreate("trzero_res\\sound\\voice_ryan\\lancer_rail.wav",false);
	BoostEnabled = iSoundCreate("trzero_res\\sound\\voice_ryan\\boost_online.wav",false);
	EnergyCrit = iSoundCreate("trzero_res\\sound\\voice_ryan\\energy_crit.wav",false);
	Countdown = iSoundCreate("trzero_res\\sound\\voice_ryan\\321.wav",false);
	GameComplete = iSoundCreate("trzero_res\\sound\\voice_ryan\\game_completed.wav",false);
	GameOver = iSoundCreate("trzero_res\\sound\\voice_ryan\\game_over.wav",false);
	FinalLap = iSoundCreate("trzero_res\\sound\\voice_ryan\\final_lap.wav",false);
	PositionPlaced = iSoundCreate("trzero_res\\sound\\voice_ryan\\position_placed.wav",false);
	//PositionHuman = iSoundCreate("trzero_res\\sound\\voice\\position_id.ogg",false); //Created when needed
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - VOICES - UPDATE
///*****************************************************************
void Game_Audio_Voices::Update(void)
{
	//-------------------------------------------------------------
	//Play End Game Voices
	if(gRaceState==2)
	{
		//End Game Alerts
		if(!bGameComplete)
		{
			iSoundVolumeSet(GameComplete,fVoiceVolume * gVolumeFx);
			iSoundVolumeSet(GameOver,fVoiceVolume * gVolumeFx);
			//Win
			if(gRaceWin)
			{
				iSoundPlay(GameComplete,0,false);
			}
			//Loss
			else
			{
				iSoundPlay(GameOver,0,false);
			}
			bGameComplete = true;
			PlayTimer = 0;
		}
		else if(!bPositionPlaced && cGame_Mode_Controller.EndRace.ScoreTimer==120)
		{
			iSoundVolumeSet(PositionPlaced,fVoiceVolume * gVolumeFx);
			iSoundPlay(PositionPlaced,0,false);
			bPositionPlaced = true;
		}
		else if(!bPositionHuman && cGame_Mode_Controller.EndRace.ScoreTimer==200)
		{
			char PlayId[1024] = { '\0' };
			sprintf_s(PlayId,"trzero_res\\sound\\voice_ryan\\HumanPosition\\%d.wav",cGame_RaceTracker.Position_Current[gAi_Max_Count]);
			PositionHuman = iSoundCreate(PlayId,false);

			iSoundVolumeSet(PositionHuman,fVoiceVolume * gVolumeFx);
			iSoundPlay(PositionHuman,0,false);
			bPositionHuman = true;
		}
	}
	//-------------------------------------------------------------
	//Update Play Timer
	else if(PlayTimer < PlayTimerMax)
	{
		PlayTimer++;
	}
	//-------------------------------------------------------------
	//Play InGame Voices
	else if(gGameState>0)
	{
		//-------------------------------------------------------------
		//Shield Inv
		if(!bShieldInv && cGame_Bike[gAi_Max_Count].Weapons.UtilityType==0)
		{
			if(cGame_Bike[gAi_Max_Count].Weapons.UtilityAliveTimeMax!=gRespawnShieldTimeMax)///Skip sound for respawn shield
			{
				iSoundVolumeSet(ShieldInv,fVoiceVolume * gVolumeFx);
				iSoundPlay(ShieldInv,0,false);
				PlayTimer = 0;
				bShieldInv = true;
			}
		}
		else if(cGame_Bike[gAi_Max_Count].Weapons.UtilityType==-1)
		{
			bShieldInv = false;
		}
		//Auto Pilot
		if(!bAutoPilot && cGame_Bike[gAi_Max_Count].Weapons.UtilityType==1)
		{
			iSoundVolumeSet(AutoPilot,fVoiceVolume * gVolumeFx);
			iSoundPlay(AutoPilot,0,false);
			bAutoPilot = true;
			PlayTimer = 0;
		}
		else if(cGame_Bike[gAi_Max_Count].Weapons.UtilityType==-1)
		{
			bAutoPilot = false;
		}
		//Double Damage
		if(!bDoubleDamage && cGame_Bike[gAi_Max_Count].Weapons.UtilityType==2)
		{
			iSoundVolumeSet(DoubleDamage,fVoiceVolume * gVolumeFx);
			iSoundPlay(DoubleDamage,0,false);
			bDoubleDamage = true;
			PlayTimer = 0;
		}
		else if(cGame_Bike[gAi_Max_Count].Weapons.UtilityType==-1)
		{
			bDoubleDamage = false;
		}
		//Warp
		if(!bWarp && cGame_Bike[gAi_Max_Count].Weapons.UtilityType==3)
		{
			iSoundVolumeSet(Warp,fVoiceVolume * gVolumeFx);
			iSoundPlay(Warp,0,false);
			bWarp = true;
			PlayTimer = 0;
		}
		else if(cGame_Bike[gAi_Max_Count].Weapons.UtilityType==-1)
		{
			bWarp = false;
		}
		//-------------------------------------------------------------
		//EnergyCrit
		if(!bEnergyCrit && 
			cGame_Bike[gAi_Max_Count].Energy.fEnergy <= gEnergyWarningLimit &&
			cGame_Bike[gAi_Max_Count].Energy.bAlive)
		{
			iSoundVolumeSet(EnergyCrit,fVoiceVolume * gVolumeFx);
			iSoundPlay(EnergyCrit,0,false);
			bEnergyCrit = true;
			PlayTimer = 0;
		}
		else if(cGame_Bike[gAi_Max_Count].Energy.fEnergy > gEnergyWarningLimit * 1.5f)
		{
			bEnergyCrit = false;
		}
		//-------------------------------------------------------------
		//BoostEnabled
		if(!bBoostEnabled && gBoostEnable)
		{
			iSoundVolumeSet(BoostEnabled,fVoiceVolume * gVolumeFx);
			iSoundPlay(BoostEnabled,0,false);
			bBoostEnabled = true;
			PlayTimer = 0;
		}
		//-------------------------------------------------------------
		//Weapons Online
		if(!bWeaponsOnline && gWeaponsEnable)
		{
			iSoundVolumeSet(WeaponsOnline,fVoiceVolume * gVolumeFx);
			iSoundPlay(WeaponsOnline,0,false);
			bWeaponsOnline = true;
			PlayTimer = 0;
		}
		//-------------------------------------------------------------
		//Countdown
		int RespawnTime = gRespawnTimerMax - cGame_Bike[gAi_Max_Count].RespawnTimer;
		int CountdownTime = cGame_Mode_Controller.Intro.IntroTimerMax - cGame_Mode_Controller.Intro.IntroTimer;
		if(!bCountdown && 
			cGame_Mode_Controller.Intro.bBeginTimer && 
			CountdownTime==180)
		{
			iSoundVolumeSet(Countdown,fVoiceVolume * gVolumeFx);
			iSoundPlay(Countdown,0,false);
			bCountdown = true;
			PlayTimer = 0;
		}
		//Respawn
		else if(RespawnTime==180 &&
			gRespawnEnable)
		{
			iSoundVolumeSet(Countdown,fVoiceVolume * gVolumeFx);
			iSoundPlay(Countdown,0,false);
			PlayTimer = 0;
		}
		//-------------------------------------------------------------
		//Final Lap
		if(!bFinalLap && 
			cGame_RaceTracker.Lap_Current[gAi_Max_Count]==gLapMax)
		{
			iSoundVolumeSet(FinalLap,fVoiceVolume * gVolumeFx);
			iSoundPlay(FinalLap,0,false);
			bFinalLap = true;
			PlayTimer = 0;
		}
		//-------------------------------------------------------------
		//FusionMissile
		if(!bFusionMissile && cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType==0)
		{
			iSoundVolumeSet(FusionMissile,fVoiceVolume * gVolumeFx);
			iSoundPlay(FusionMissile,0,false);
			bFusionMissile = true;
			PlayTimer = 0;
		}
		else if(cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType==-1)
		{
			bFusionMissile = false;
		}
		//Shockwave
		if(!bShockwave && cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType==1)
		{
			iSoundVolumeSet(Shockwave,fVoiceVolume * gVolumeFx);
			iSoundPlay(Shockwave,0,false);
			bShockwave = true;
			PlayTimer = 0;
		}
		else if(cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType==-1)
		{
			bShockwave = false;
		}
		//EMBurst
		if(!bEMBurst && cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType==2)
		{
			iSoundVolumeSet(EMBurst,fVoiceVolume * gVolumeFx);
			iSoundPlay(EMBurst,0,false);
			bEMBurst = true;
			PlayTimer = 0;
		}
		else if(cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType==-1)
		{
			bEMBurst = false;
		}
		//LancerRail
		if(!bLancerRail && cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType==3)
		{
			iSoundVolumeSet(LancerRail,fVoiceVolume * gVolumeFx);
			iSoundPlay(LancerRail,0,false);
			bLancerRail = true;
			PlayTimer = 0;
		}
		else if(cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType==-1)
		{
			bLancerRail = false;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - VOICES - DESTROY
///*****************************************************************
void Game_Audio_Voices::Destroy(void)
{
	//-------------------------------------------------------------
	//Utility
	iSoundDestroy(ShieldInv);
	iSoundDestroy(AutoPilot);
	iSoundDestroy(DoubleDamage);
	iSoundDestroy(Warp);
	//Weapons
	iSoundDestroy(WeaponsOnline);
	iSoundDestroy(Shockwave);
	iSoundDestroy(EMBurst);
	iSoundDestroy(FusionMissile);
	iSoundDestroy(LancerRail);
	//Boost Enabled
	iSoundDestroy(BoostEnabled);
	//Energy
	iSoundDestroy(EnergyCrit);
	//Countdown
	iSoundDestroy(Countdown);
	//FinalLap 
	iSoundDestroy(FinalLap);
	//End Game Alerts
	iSoundDestroy(GameComplete);
	iSoundDestroy(GameOver);
	//Position
	iSoundDestroy(PositionPlaced);
	///Only destroy if it was played
	if(bPositionHuman)
	{
		iSoundDestroy(PositionHuman);
	}
	//-------------------------------------------------------------
}

