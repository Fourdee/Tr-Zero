//-----------------------------------------------------------------
// About:
//
// name: "Game_Audio_Weapons.h:
//
// Included in "Game_Audio.h":
// usage: 
//
// device input: none.
//
// todo:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Audio_Weapons.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - AUDIO - WEAPONS - CONSTRUCTORS
///*****************************************************************
Game_Audio_Weapons::Game_Audio_Weapons(void)
{
	//-------------------------------------------------------------
	//HITSOUND
	sHitSound = NULL;
	//Player Weapon Sounds
	sPrimaryGun = NULL;
	sEm_Charge = NULL;
	sEm_Fire = NULL;
	sRail_Charge = NULL;
	sRail_Fire = NULL;
	sMissile_Fire = NULL;
	sShield = NULL;
	sDoubleDamage = NULL;
	for(int i=0;i<2;i++)
	{
		sWarp[i] = NULL;
	}
	//Ai
	sEm_Charge_Ai = NULL;
	sEm_Fire_Ai = NULL;
	sRail_Charge_Ai = NULL;
	sRail_Fire_Ai = NULL;
	sMissile_Fire_Ai = NULL;
	sShield_Ai = NULL;
	sDoubleDamage_Ai = NULL;
	for(int i=0;i<2;i++)
	{
		sWarp_Ai[i] = NULL;
	}
	//-------------------------------------------------------------
	//Global Travel Sound
	///Primary Travel Sound
	sPrimaryTravel = NULL;
	///Fusion Missile Travel Sound
	sMissile_Travel = NULL;
	///Fusion Missile Explosion
	sMissile_Explosion = NULL;
	///ShoxWave Travel Sound
	sShoxwave_Travel = NULL;
	///Rail Travel Sound
	sRail_Travel = NULL;
	//---------------------------------------------------------
	//Global Impacts
	for(int i=0;i<3;i++)
	{
		sPrimary_Impact[i] = NULL;
		sShield_Impact[i] = NULL;
	}
	//-------------------------------------------------------------
	//Volumes Target (eg fVolume = THIS * internal * gsoundfx)
	///Volumes - Player
	fVolumeTarget_sPrimaryGun = 0.72f;
	fVolumeTarget_sEm_Charge = 0.58f;
	fVolumeTarget_sEm_Fire = 0.62f;
	fVolumeTarget_sRail_Charge = 0.95f;
	fVolumeTarget_sRail_Fire = 0.79f;
	fVolumeTarget_sShoxwave_Fire = 0.65f;
	fVolumeTarget_sMissile_Fire = 0.7f;
	fVolumeTarget_sShield = 0.62f;
	fVolumeTarget_sDoubleDamage = 0.62f;
	fVolumeTarget_sWarp = 0.84f;
	///Volumes - Ai
	fVolumeTarget_sEm_Charge_Ai = 2.0f;
	fVolumeTarget_sEm_Fire_Ai = 1.81f;
	fVolumeTarget_sRail_Charge_Ai = 2.2f;
	fVolumeTarget_sRail_Fire_Ai = 1.38f;
	fVolumeTarget_sShoxwave_Fire_Ai = 1.88f;
	fVolumeTarget_sMissile_Fire_Ai = 1.88f;
	fVolumeTarget_sShield_Ai = 1.4f;
	fVolumeTarget_sDoubleDamage_Ai = 1.4f;
	fVolumeTarget_sWarp_Ai = 2.68f;
	///Volumes - Travel
	fVolumeTarget_sPrimaryTravel = 1.75f;
	fVolumeTarget_sMissile_Travel = 2.4f;
	fVolumeTarget_sMissile_Explosion = 1.6f;
	fVolumeTarget_sShoxwave_Travel = 3.4f;
	fVolumeTarget_sRail_Travel = 3.2f;
	///Volumes - Impact
	fVolumeTarget_sPrimary_Impact = 1.35f;
	fVolumeTarget_sShield_Impact = 1.35f;
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}
Game_Audio_Weapons::~Game_Audio_Weapons(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - AUDIO - WEAPONS - ZeroData
///*****************************************************************
void Game_Audio_Weapons::ZeroData(void)
{
	//-------------------------------------------------------------
	//Internal Volume
	fInternalVol = 1.0f;
	///Ranges
	fImpact_MaxRange = 250.0f;
	fAi_MaxRange = 400.0f;
	fTravel_MaxRange = 55.0f;
	//-------------------------------------------------------------
	//Volumes ACTUAL
	///Volumes - Player
	fVolume_sPrimaryGun = 0.0f;
	fVolume_sEm_Charge = 0.0f;
	fVolume_sEm_Fire = 0.0f;
	fVolume_sRail_Charge = 0.0f;
	fVolume_sRail_Fire = 0.0f;
	fVolume_sShoxwave_Fire = 0.0f;
	fVolume_sMissile_Fire = 0.0f;
	fVolume_sShield = 0.0f;
	fVolume_sDoubleDamage = 0.0f;
	fVolume_sWarp = 0.0f;
	///Volumes - Ai
	fVolume_sEm_Charge_Ai = 0.0f;
	fVolume_sEm_Fire_Ai = 0.0f;
	fVolume_sRail_Charge_Ai = 0.0f;
	fVolume_sRail_Fire_Ai = 0.0f;
	fVolume_sShoxwave_Fire_Ai = 0.0f;
	fVolume_sMissile_Fire_Ai = 0.0f;
	fVolume_sShield_Ai = 0.0f;
	fVolume_sDoubleDamage_Ai = 0.0f;
	fVolume_sWarp_Ai = 0.0f;
	///Volumes - Travel
	fVolume_sPrimaryTravel = 0.0f;
	fVolume_sMissile_Travel = 0.0f;
	fVolume_sMissile_Explosion = 0.0f;
	fVolume_sShoxwave_Travel = 0.0f;
	fVolume_sRail_Travel = 0.0f;
	///Volumes - Impact
	fVolume_sPrimary_Impact = 0.0f;
	fVolume_sShield_Impact = 0.0f;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - WEAPONS - CREATE
///*****************************************************************
void Game_Audio_Weapons::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
	//HITSOUND
	sHitSound = iSoundCreate("trzero_res\\sound\\weapons\\hitsound_mono.wav",false);
	iSoundVolumeSet(sHitSound,0.5f);
	//Player
	///primary
	sPrimaryGun = iSoundCreate("trzero_res\\sound\\weapons\\primary_fire_stereo.wav",false);
	iSoundVolumeSet(sPrimaryGun,0.0f);
	///Em_Charge
	sEm_Charge = iSoundCreate("trzero_res\\sound\\weapons\\em_charge_stereo2.wav",false);
	iSoundVolumeSet(sEm_Charge,0.0f);
	///Em_Fire
	sEm_Fire = iSoundCreate("trzero_res\\sound\\weapons\\em_fire_stereo.wav",false);
	iSoundVolumeSet(sEm_Fire,0.0f);
	///Rail_Charge
	sRail_Charge = iSoundCreate("trzero_res\\sound\\weapons\\rail_charge_stereo.wav",false);
	iSoundVolumeSet(sRail_Charge,0.0f);
	///Rail_Fire
	sRail_Fire = iSoundCreate("trzero_res\\sound\\weapons\\rail_fire_stereo.wav",false);
	iSoundVolumeSet(sRail_Fire,0.0f);
	///Shoxwave_Fire
	sShoxwave_Fire = iSoundCreate("trzero_res\\sound\\weapons\\shoxwave_fire_stereo.wav",false);
	iSoundVolumeSet(sShoxwave_Fire,0.0f);
	///sMissile_Fire
	sMissile_Fire = iSoundCreate("trzero_res\\sound\\weapons\\missile_fire_stereo.wav",false);
	iSoundVolumeSet(sMissile_Fire,0.0f);
	///sShield
	sShield = iSoundCreate("trzero_res\\sound\\weapons\\shield_stereo.wav",false);
	iSoundVolumeSet(sShield,0.0f);
	///sDoubleDamage
	sDoubleDamage = iSoundCreate("trzero_res\\sound\\weapons\\double_damage_stereo.wav",false);
	iSoundVolumeSet(sDoubleDamage,0.0f);
	///sWarp
	sWarp[0] = iSoundCreate("trzero_res\\sound\\weapons\\warp_1_stereo.wav",false);
	sWarp[1] = iSoundCreate("trzero_res\\sound\\weapons\\warp_2_stereo.wav",false);
	for(int i=0;i<2;i++)
	{
		iSoundVolumeSet(sWarp[i],0.0f);
	}
	//Ai
	///Em_Charge
	sEm_Charge_Ai = iSoundCreate("trzero_res\\sound\\weapons\\em_charge_mono.wav",true);
	iSoundRadiusSet(sEm_Charge_Ai,fAi_MaxRange);
	iSoundDopplerEffectSet(sEm_Charge_Ai,0.0f);
	iSoundVolumeSet(sEm_Charge_Ai,0.0f);
	///Em_Fire
	sEm_Fire_Ai = iSoundCreate("trzero_res\\sound\\weapons\\em_fire_mono.wav",true);
	iSoundRadiusSet(sEm_Fire_Ai,fAi_MaxRange);
	iSoundDopplerEffectSet(sEm_Fire_Ai,0.0f);
	iSoundVolumeSet(sEm_Fire_Ai,0.0f);
	///Rail_Charge
	sRail_Charge_Ai = iSoundCreate("trzero_res\\sound\\weapons\\rail_charge_mono.wav",true);
	iSoundRadiusSet(sRail_Charge_Ai,fAi_MaxRange);
	iSoundDopplerEffectSet(sRail_Charge_Ai,0.0f);
	iSoundVolumeSet(sRail_Charge_Ai,0.0f);
	///Rail_Fire
	sRail_Fire_Ai = iSoundCreate("trzero_res\\sound\\weapons\\rail_fire_mono.wav",true);
	iSoundRadiusSet(sRail_Fire_Ai,fAi_MaxRange);
	iSoundDopplerEffectSet(sRail_Fire_Ai,0.0f);
	iSoundVolumeSet(sRail_Fire_Ai,0.0f);
	///Shoxwave_Fire
	sShoxwave_Fire_Ai = iSoundCreate("trzero_res\\sound\\weapons\\shoxwave_fire_mono.wav",true);
	iSoundRadiusSet(sShoxwave_Fire_Ai,fAi_MaxRange);
	iSoundDopplerEffectSet(sShoxwave_Fire_Ai,0.0f);
	iSoundVolumeSet(sShoxwave_Fire_Ai,0.0f);
	///sMissile_Fire_Ai
	sMissile_Fire_Ai = iSoundCreate("trzero_res\\sound\\weapons\\missile_fire_mono.wav",true);
	iSoundRadiusSet(sMissile_Fire_Ai,fAi_MaxRange);
	iSoundDopplerEffectSet(sMissile_Fire_Ai,0.0f);
	iSoundVolumeSet(sMissile_Fire_Ai,0.0f);
	///sShield_Ai
	sShield_Ai = iSoundCreate("trzero_res\\sound\\weapons\\shield_mono.wav",true);
	iSoundRadiusSet(sShield_Ai,fAi_MaxRange);
	iSoundDopplerEffectSet(sShield_Ai,0.0f);
	iSoundVolumeSet(sShield_Ai,0.0f);
	///sDoubleDamage_Ai
	sDoubleDamage_Ai = iSoundCreate("trzero_res\\sound\\weapons\\double_damage_mono.wav",true);
	iSoundRadiusSet(sDoubleDamage_Ai,fAi_MaxRange);
	iSoundDopplerEffectSet(sDoubleDamage_Ai,0.0f);
	iSoundVolumeSet(sDoubleDamage_Ai,0.0f);
	///sWarp_Ai
	sWarp_Ai[0] = iSoundCreate("trzero_res\\sound\\weapons\\warp_1_mono.wav",true);
	sWarp_Ai[1] = iSoundCreate("trzero_res\\sound\\weapons\\warp_2_mono.wav",true);
	for(int i=0;i<2;i++)
	{
		iSoundRadiusSet(sWarp_Ai[i],fAi_MaxRange);
		iSoundDopplerEffectSet(sWarp_Ai[i],0.0f);
		iSoundVolumeSet(sWarp_Ai[i],0.0f);
	}
	//-------------------------------------------------------------
	//Global Travel Sounds
	///Primary Travel Sound
	sPrimaryTravel = iSoundCreate("trzero_res\\sound\\weapons\\primary_travel_mono.wav",true);
	iSoundRadiusSet(sPrimaryTravel,fTravel_MaxRange);
	iSoundDopplerEffectSet(sPrimaryTravel,0.0f);
	iSoundVolumeSet(sPrimaryTravel,0.0f);
	///Fusion Missile Travel Sound
	sMissile_Travel = iSoundCreate("trzero_res\\sound\\weapons\\missile_travel_mono.wav",true);
	iSoundRadiusSet(sMissile_Travel,fAi_MaxRange);
	iSoundDopplerEffectSet(sMissile_Travel,0.0f);
	iSoundVolumeSet(sMissile_Travel,0.0f);
	///Fusion Missile Explosion
	sMissile_Explosion = iSoundCreate("trzero_res\\sound\\weapons\\missile_explosion_mono.wav",true);
	iSoundRadiusSet(sMissile_Explosion,fAi_MaxRange);
	iSoundDopplerEffectSet(sMissile_Explosion,0.0f);
	iSoundVolumeSet(sMissile_Explosion,0.0f);
	///ShoxWave Travel Sound
	sShoxwave_Travel = iSoundCreate("trzero_res\\sound\\weapons\\shoxwave_travel_mono.wav",true);
	iSoundRadiusSet(sShoxwave_Travel,fAi_MaxRange);
	iSoundDopplerEffectSet(sShoxwave_Travel,0.0f);
	iSoundVolumeSet(sShoxwave_Travel,0.0f);
	///Rail Travel Sound
	sRail_Travel = iSoundCreate("trzero_res\\sound\\weapons\\rail_travel_mono.wav",true);
	iSoundRadiusSet(sRail_Travel,fAi_MaxRange);
	iSoundDopplerEffectSet(sRail_Travel,0.0f);
	iSoundVolumeSet(sRail_Travel,0.0f);
	//-------------------------------------------------------------
	//Global Impacts
	sPrimary_Impact[0] = iSoundCreate("trzero_res\\sound\\weapons\\primary_impact_one_mono.wav",true);
	sPrimary_Impact[1] = iSoundCreate("trzero_res\\sound\\weapons\\primary_impact_two_mono.wav",true);
	sPrimary_Impact[2] = iSoundCreate("trzero_res\\sound\\weapons\\primary_impact_three_mono.wav",true);
	sShield_Impact[0] = iSoundCreate("trzero_res\\sound\\weapons\\unity_shield_impact_one_mono.wav",true);
	sShield_Impact[1] = iSoundCreate("trzero_res\\sound\\weapons\\unity_shield_impact_two_mono.wav",true);
	sShield_Impact[2] = iSoundCreate("trzero_res\\sound\\weapons\\unity_shield_impact_three_mono.wav",true);
	for(int i=0;i<3;i++)
	{
		iSoundRadiusSet(sPrimary_Impact[i],fImpact_MaxRange);
		iSoundDopplerEffectSet(sPrimary_Impact[i],0.0f);
		iSoundVolumeSet(sPrimary_Impact[i],0.0f);

		iSoundRadiusSet(sShield_Impact[i],fImpact_MaxRange);
		iSoundDopplerEffectSet(sShield_Impact[i],0.0f);
		iSoundVolumeSet(sShield_Impact[i],0.0f);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - WEAPONS - Play_Hitsound
///*****************************************************************
void Game_Audio_Weapons::Play_Hitsound(float in_damage)
{
	//-------------------------------------------------------------
	//HITSOUND
	if(in_damage >= 1.0f)
	{
		iSoundStop(sHitSound);
		float fFreq = 1.1f;
		float fTargetVolume = 0.7f;
		if(in_damage > 50.0f)
		{
			fFreq = 0.8f;
			fTargetVolume = 1.0f;
		}
		iSoundFrequencyRatioSet(sHitSound,fFreq);
		iSoundVolumeSet(sHitSound,((gVolumeHitsound * fTargetVolume) * gVolumeFx));
		iSoundPlay(sHitSound,0,false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - WEAPONS - UPDATE
///*****************************************************************
void Game_Audio_Weapons::Update(void)
{
	//-------------------------------------------------------------
	//Update Internal Volume - menu etc
	if(gPaused || cGame_Gamma_Fade.bFadeOut)
	{
		iFloatTendTo2(fInternalVol,0.0f,40.0f);
	}
	else
	{
		//Sound Barrier
		if(gSoundBarrier)
		{
			iFloatTendTo2(fInternalVol,gSoundBarrierVolumeMin,gSoundBarrierTendTo_In);
		}
		else
		{
			///Ryan Speaking
			if(cGame_Audio.Voice.PlayTimer<=60 && fInternalVol > 0.7f)
			{
				fInternalVol = 0.7f;
			}
			iFloatTendTo2(fInternalVol,1.0f,gSoundBarrierTendTo_Out);
		}
	}
	//-------------------------------------------------------------
	//Volumes ACTUAL - Update
	///Volumes - Player
	fVolume_sPrimaryGun = (fVolumeTarget_sPrimaryGun * fInternalVol) * gVolumeFx;
	fVolume_sEm_Charge = (fVolumeTarget_sEm_Charge * fInternalVol) * gVolumeFx;
	fVolume_sEm_Fire = (fVolumeTarget_sEm_Fire * fInternalVol) * gVolumeFx;
	fVolume_sRail_Charge = (fVolumeTarget_sRail_Charge * fInternalVol) * gVolumeFx;
	fVolume_sRail_Fire = (fVolumeTarget_sRail_Fire * fInternalVol) * gVolumeFx;
	fVolume_sShoxwave_Fire = (fVolumeTarget_sShoxwave_Fire * fInternalVol) * gVolumeFx;
	fVolume_sMissile_Fire = (fVolumeTarget_sMissile_Fire * fInternalVol) * gVolumeFx;
	fVolume_sShield = (fVolumeTarget_sShield * fInternalVol) * gVolumeFx;
	fVolume_sDoubleDamage = (fVolumeTarget_sDoubleDamage * fInternalVol) * gVolumeFx;
	fVolume_sWarp = (fVolumeTarget_sWarp * fInternalVol) * gVolumeFx;
	///Volumes - Ai
	fVolume_sEm_Charge_Ai = (fVolumeTarget_sEm_Charge_Ai * fInternalVol) * gVolumeFx;
	fVolume_sEm_Fire_Ai = (fVolumeTarget_sEm_Fire_Ai * fInternalVol) * gVolumeFx;
	fVolume_sRail_Charge_Ai = (fVolumeTarget_sRail_Charge_Ai * fInternalVol) * gVolumeFx;
	fVolume_sRail_Fire_Ai = (fVolumeTarget_sRail_Fire_Ai * fInternalVol) * gVolumeFx;
	fVolume_sShoxwave_Fire_Ai = (fVolumeTarget_sShoxwave_Fire_Ai * fInternalVol) * gVolumeFx;
	fVolume_sMissile_Fire_Ai = (fVolumeTarget_sMissile_Fire_Ai * fInternalVol) * gVolumeFx;
	fVolume_sShield_Ai = (fVolumeTarget_sShield_Ai * fInternalVol) * gVolumeFx;
	fVolume_sMissile_Fire_Ai = (fVolumeTarget_sMissile_Fire_Ai * fInternalVol) * gVolumeFx;
	fVolume_sDoubleDamage_Ai = (fVolumeTarget_sDoubleDamage_Ai * fInternalVol) * gVolumeFx;
	fVolume_sWarp_Ai = (fVolumeTarget_sWarp_Ai * fInternalVol) * gVolumeFx;
	///Volumes - Travel
	fVolume_sPrimaryTravel = (fVolumeTarget_sPrimaryTravel * fInternalVol) * gVolumeFx;
	fVolume_sMissile_Travel = (fVolumeTarget_sMissile_Travel * fInternalVol) * gVolumeFx;
	fVolume_sMissile_Explosion = (fVolumeTarget_sMissile_Explosion * fInternalVol) * gVolumeFx;
	fVolume_sShoxwave_Travel = (fVolumeTarget_sShoxwave_Travel * fInternalVol) * gVolumeFx;
	fVolume_sRail_Travel = (fVolumeTarget_sRail_Travel * fInternalVol) * gVolumeFx;
	///Volumes - Impact
	fVolume_sPrimary_Impact = (fVolumeTarget_sPrimary_Impact * fInternalVol) * gVolumeFx;
	fVolume_sShield_Impact = (fVolumeTarget_sShield_Impact * fInternalVol) * gVolumeFx;
	//-------------------------------------------------------------
	//Player
	Player_Update();
	//Ai
	Ai_Update();
	//-------------------------------------------------------------
	//Travel
	Travel_Update();
	//-------------------------------------------------------------
	//Impact
	if(gBikesGo)
	{
		Impact_Update();
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - AUDIO - WEAPONS - Player_Update
///*****************************************************************
void Game_Audio_Weapons::Player_Update(void)
{
	//-------------------------------------------------------------
	//Primary
	if(cGame_Bike[gAi_Max_Count].Weapons.bPrimaryFired)
	{
		iSoundVolumeSet(sPrimaryGun,fVolume_sPrimaryGun);
		float PrimaryGun_Freq = iFloatInterpolateSmooth((float)cGame_Bike[gAi_Max_Count].Weapons.PrimaryHeat,0.0f,100.0f,0.75f,1.25f); 
		iSoundFrequencyRatioSet(sPrimaryGun,PrimaryGun_Freq);
		if(iSoundPlaying(sPrimaryGun))
		{
			iSoundStop(sPrimaryGun);
		}
		iSoundPlay(sPrimaryGun,0,false);
	}
	//-------------------------------------------------------------
	//Shoxwave fire
	if(cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType==1)
	{
		//Fire
		if(cGame_Bike[gAi_Max_Count].Weapons.SecondaryProjectileAliveTime==1)
		{
			///play fire
			///iSoundStop(sShoxwave_Fire);
			///
			iSoundVolumeSet(sShoxwave_Fire,fVolume_sShoxwave_Fire);
			iSoundPlay(sShoxwave_Fire,0,false);
		}
	}
	//-------------------------------------------------------------
	//Em Burst fire
	if(cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType==2)
	{
		//Charge
		if(cGame_Bike[gAi_Max_Count].Weapons.bSecondaryWeaponCharging)
		{
			iSoundVolumeSet(sEm_Charge,fVolume_sEm_Charge);
			//iSoundFrequencyRatioSet(sEm_Charge,Freq_Charge((float)cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponChargeTime,(float)cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponChargeTimeMax));
			if(!iSoundPlaying(sEm_Charge))
			{
				iSoundPlay(sEm_Charge,0,false);
			}
		}
		//Release fire
		else if(cGame_Bike[gAi_Max_Count].Weapons.SecondaryProjectileAliveTime==1)
		{
			///Stop charge - play fire
			if(iSoundPlaying(sEm_Charge))
			{
				iSoundStop(sEm_Charge);
				///
				iSoundVolumeSet(sEm_Fire,fVolume_sEm_Fire);
				iSoundPlay(sEm_Fire,0,false);
			}
		}
	}
	//-------------------------------------------------------------
	//Rail fire
	if(cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType==3)
	{
		//Charge
		if(cGame_Bike[gAi_Max_Count].Weapons.bSecondaryWeaponCharging)
		{
			iSoundVolumeSet(sRail_Charge,fVolume_sRail_Charge);
			iSoundFrequencyRatioSet(sRail_Charge,Freq_Charge((float)cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponChargeTime,(float)cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponChargeTimeMax));
			if(!iSoundPlaying(sRail_Charge))
			{
				iSoundPlay(sRail_Charge,0,true);
			}
		}
		//Release fire
		else if(cGame_Bike[gAi_Max_Count].Weapons.SecondaryProjectileAliveTime==1)
		{
			///Stop charge - play fire
			if(iSoundPlaying(sRail_Charge))
			{
				iSoundStop(sRail_Charge);
				///
				iSoundVolumeSet(sRail_Fire,fVolume_sRail_Fire);
				iSoundPlay(sRail_Fire,0,false);
			}
		}
	}
	//-------------------------------------------------------------
	//Missile fire
	if(cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponType==0)
	{
		//Fire
		if(cGame_Bike[gAi_Max_Count].Weapons.SecondaryProjectileAliveTime==1)
		{
			///play fire
			iSoundVolumeSet(sMissile_Fire,fVolume_sMissile_Fire);
			iSoundPlay(sMissile_Fire,0,false);
		}
	}
	//-------------------------------------------------------------
	//Shield
	if(cGame_Bike[gAi_Max_Count].Weapons.UtilityType==0 &&
		cGame_Bike[gAi_Max_Count].Weapons.bUtilityProjectileSetup)
	{
		///play
		iSoundVolumeSet(sShield,fVolume_sShield);
		if(!iSoundPlaying(sShield))
		{
			iSoundPlay(sShield,0,true);
		}
	}
	else if(iSoundPlaying(sShield))
	{
		iSoundStop(sShield);
	}
	//-------------------------------------------------------------
	//DoubleDamage
	if(cGame_Bike[gAi_Max_Count].Weapons.UtilityType==2 &&
		cGame_Bike[gAi_Max_Count].Weapons.bUtilityProjectileSetup)
	{
		///play
		iSoundVolumeSet(sDoubleDamage,fVolume_sDoubleDamage);
		if(!iSoundPlaying(sDoubleDamage))
		{
			iSoundPlay(sDoubleDamage,0,true);
		}
	}
	else if(iSoundPlaying(sDoubleDamage))
	{
		iSoundStop(sDoubleDamage);
	}
	//-------------------------------------------------------------
	//Warp
	if(cGame_Bike[gAi_Max_Count].Weapons.UtilityType==3)
	{
		///Stage 1
		if(cGame_Bike[gAi_Max_Count].Weapons.UtilityAliveTime==1)
		{
			///play
			iSoundVolumeSet(sWarp[0],fVolume_sWarp);
			iSoundPlay(sWarp[0],0,false);
		}
		else if(cGame_Bike[gAi_Max_Count].Weapons.UtilityAliveTime==26)
		{
			///Stop previous
			if(iSoundPlaying(sWarp[0]))
			{
				iSoundStop(sWarp[0]);
			}
			///play
			iSoundVolumeSet(sWarp[1],fVolume_sWarp);
			iSoundPlay(sWarp[1],0,false);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - AUDIO - WEAPONS - Ai_Update
///*****************************************************************
void Game_Audio_Weapons::Ai_Update(void)
{
	//-------------------------------------------------------------
	//Data
	///Em Fire
	float fClosest_Em_Charge = fAi_MaxRange;
	float fClosest_Em_Fire = fAi_MaxRange;
	int Em_Charge_Ai_Current = -1;
	int Em_Fire_Ai_Current = -1;
	///Rail Fire
	float fClosest_Rail_Charge = fAi_MaxRange;
	float fClosest_Rail_Fire = fAi_MaxRange;
	int Rail_Charge_Ai_Current = -1;
	int Rail_Fire_Ai_Current = -1;
	///Shoxwave Fire
	float fClosest_Shoxwave_Fire = fAi_MaxRange;
	int Shoxwave_Fire_Ai_Current = -1;
	///Missile Fire
	float fClosest_Missile_Fire = fAi_MaxRange;
	int Missile_Fire_Ai_Current = -1;
	///Shield
	float fClosest_Shield = fAi_MaxRange;
	int Shield_Ai_Current = -1;
	///DoubleDamage
	float fClosest_DoubleDamage = fAi_MaxRange;
	int DoubleDamage_Ai_Current = -1;
	///Warp
	float fClosest_Warp0 = fAi_MaxRange;
	int Warp0_Ai_Current = -1;
	float fClosest_Warp1 = fAi_MaxRange;
	int Warp1_Ai_Current = -1;
	//-------------------------------------------------------------
	//Find
	float fDistance = 0.0f;
	for(int i=0;i<gAi_Max_Count;i++)
	{
		///Check in range 1st
		///fDistance = iVectorLength(&(cGame_Bike[i].Manager.vTargetMesh-cGame_Bike[gAi_Max_Count].Manager.vTargetMesh));
		fDistance = cGame_Bike[i].fDistanceToCam;
		if(fDistance<fAi_MaxRange)
		{
			//Missile Fire
			if(cGame_Bike[i].Weapons.SecondaryWeaponType==0)
			{
				///Check fire
				if(cGame_Bike[i].Weapons.SecondaryProjectileAliveTime==1 &&
					fDistance < fClosest_Missile_Fire)
				{
					fClosest_Missile_Fire = fDistance;
					Missile_Fire_Ai_Current = i;
				}
			}
			//Shoxwave
			else if(cGame_Bike[i].Weapons.SecondaryWeaponType==1)
			{
				///Check fire
				if(cGame_Bike[i].Weapons.SecondaryProjectileAliveTime==1 &&
					fDistance < fClosest_Shoxwave_Fire)
				{
					fClosest_Shoxwave_Fire = fDistance;
					Shoxwave_Fire_Ai_Current = i;
				}
			}
			//Em Burst
			else if(cGame_Bike[i].Weapons.SecondaryWeaponType==2)
			{
				///Check charging
				if(cGame_Bike[i].Weapons.bSecondaryWeaponCharging &&
					fDistance < fClosest_Em_Charge)
				{
					///Work out closest
					fClosest_Em_Charge = fDistance;
					Em_Charge_Ai_Current = i;
				}
				///Check fire
				else if(cGame_Bike[i].Weapons.SecondaryProjectileAliveTime==1 &&
					fDistance < fClosest_Em_Fire)
				{
					fClosest_Em_Fire = fDistance;
					Em_Fire_Ai_Current = i;
				}
			}
			//Rail
			else if(cGame_Bike[i].Weapons.SecondaryWeaponType==3)
			{
				///Check charging
				if(cGame_Bike[i].Weapons.bSecondaryWeaponCharging &&
					fDistance < fClosest_Rail_Charge)
				{
					///Work out closest
					fClosest_Rail_Charge = fDistance;
					Rail_Charge_Ai_Current = i;
				}
				///Check fire
				else if(cGame_Bike[i].Weapons.SecondaryProjectileAliveTime==1 &&
					fDistance < fClosest_Rail_Fire)
				{
					fClosest_Rail_Fire = fDistance;
					Rail_Fire_Ai_Current = i;
				}
			}
			//Shield
			if(cGame_Bike[i].Weapons.UtilityType==0)
			{
				///Check in use
				if(cGame_Bike[i].Weapons.bUtilityProjectileSetup &&
					fDistance < fClosest_Shield)
				{
					///Work out closest
					fClosest_Shield = fDistance;
					Shield_Ai_Current = i;
				}
			}
			//DoubleDamage
			else if(cGame_Bike[i].Weapons.UtilityType==2)
			{
				///Check in use
				if(cGame_Bike[i].Weapons.bUtilityProjectileSetup &&
					fDistance < fClosest_DoubleDamage)
				{
					///Work out closest
					fClosest_DoubleDamage = fDistance;
					DoubleDamage_Ai_Current = i;
				}
			}
			//Warp
			else if(cGame_Bike[i].Weapons.UtilityType==3)
			{
				///Check in use Stage 1
				if(cGame_Bike[i].Weapons.UtilityAliveTime==1 &&
					fDistance < fClosest_Warp0)
				{
					///Work out closest
					fClosest_Warp0 = fDistance;
					Warp0_Ai_Current = i;
				}
				///Check in use Stage 2
				else if(cGame_Bike[i].Weapons.UtilityAliveTime==26 &&
						fDistance < fClosest_Warp1)
				{
					///Work out closest
					fClosest_Warp1 = fDistance;
					Warp1_Ai_Current = i;
				}
			}
		}
	}
	//-------------------------------------------------------------
	//Play Sounds
	///Missile Fire
	if(Missile_Fire_Ai_Current>=0)
	{
		///Update new ID (Stop/Process/Start)
		if(iSoundPlaying(sMissile_Fire_Ai))
		{
			iSoundStop(sMissile_Fire_Ai);
		}
		iSoundVolumeSet(sMissile_Fire_Ai,fVolume_sMissile_Fire_Ai);
		iSoundLocationSet(sMissile_Fire_Ai,&cGame_Mesh.Animator.vBike[Missile_Fire_Ai_Current]);
		iSoundPlay(sMissile_Fire_Ai,0,false);
	}

	///Shoxwave Fire
	if(Shoxwave_Fire_Ai_Current>=0)
	{
		///Update new ID (Stop/Process/Start)
		if(iSoundPlaying(sShoxwave_Fire_Ai))
		{
			iSoundStop(sShoxwave_Fire_Ai);
		}
		iSoundVolumeSet(sShoxwave_Fire_Ai,fVolume_sShoxwave_Fire_Ai);
		iSoundLocationSet(sShoxwave_Fire_Ai,&cGame_Mesh.Animator.vBike[Shoxwave_Fire_Ai_Current]);
		iSoundPlay(sShoxwave_Fire_Ai,0,false);
	}

	///Em Charge
	if(Em_Charge_Ai_Current>=0)
	{
		///Update new ID
		iSoundVolumeSet(sEm_Charge_Ai,fVolume_sEm_Charge_Ai);
		iSoundLocationSet(sEm_Charge_Ai,&cGame_Mesh.Animator.vBike[Em_Charge_Ai_Current]);
		iSoundFrequencyRatioSet(sEm_Charge_Ai,Freq_Charge((float)cGame_Bike[Em_Charge_Ai_Current].Weapons.SecondaryWeaponChargeTime,(float)cGame_Bike[Em_Charge_Ai_Current].Weapons.SecondaryWeaponChargeTimeMax));
		if(!iSoundPlaying(sEm_Charge_Ai))
		{
			iSoundPlay(sEm_Charge_Ai,0,true);
		}
	}
	else if(iSoundPlaying(sEm_Charge_Ai))
	{
		///Stop
		iSoundStop(sEm_Charge_Ai);
	}
	///Em Fire
	if(Em_Fire_Ai_Current>=0)
	{
		///Update new ID (Stop/Process/Start)
		if(iSoundPlaying(sEm_Fire_Ai))
		{
			iSoundStop(sEm_Fire_Ai);
		}
		iSoundVolumeSet(sEm_Fire_Ai,fVolume_sEm_Fire_Ai);
		iSoundLocationSet(sEm_Fire_Ai,&cGame_Mesh.Animator.vBike[Em_Fire_Ai_Current]);
		iSoundPlay(sEm_Fire_Ai,0,false);
	}

	///Rail Charge
	if(Rail_Charge_Ai_Current>=0)
	{
		///Update new ID
		iSoundVolumeSet(sRail_Charge_Ai,fVolume_sRail_Charge_Ai);
		iSoundLocationSet(sRail_Charge_Ai,&cGame_Mesh.Animator.vBike[Rail_Charge_Ai_Current]);
		iSoundFrequencyRatioSet(sRail_Charge_Ai,Freq_Charge((float)cGame_Bike[Rail_Charge_Ai_Current].Weapons.SecondaryWeaponChargeTime,(float)cGame_Bike[Rail_Charge_Ai_Current].Weapons.SecondaryWeaponChargeTimeMax));
		if(!iSoundPlaying(sRail_Charge_Ai))
		{
			iSoundPlay(sRail_Charge_Ai,0,true);
		}
	}
	else if(iSoundPlaying(sRail_Charge_Ai))
	{
		///Stop
		iSoundStop(sRail_Charge_Ai);
	}
	///Rail Fire
	if(Rail_Fire_Ai_Current>=0)
	{
		///Update new ID (Stop/Process/Start)
		if(iSoundPlaying(sRail_Fire_Ai))
		{
			iSoundStop(sRail_Fire_Ai);
		}
		iSoundVolumeSet(sRail_Fire_Ai,fVolume_sRail_Fire_Ai);
		iSoundLocationSet(sRail_Fire_Ai,&cGame_Mesh.Animator.vBike[Rail_Fire_Ai_Current]);
		iSoundPlay(sRail_Fire_Ai,0,false);
	}

	///sShield_Ai
	if(Shield_Ai_Current>=0)
	{
		///Update new ID
		iSoundVolumeSet(sShield_Ai,fVolume_sShield_Ai);
		iSoundLocationSet(sShield_Ai,&cGame_Mesh.Animator.vBike[Shield_Ai_Current]);
		if(!iSoundPlaying(sShield_Ai))
		{
			iSoundPlay(sShield_Ai,0,true);
		}
	}
	else if(iSoundPlaying(sShield_Ai))
	{
		///Stop
		iSoundStop(sShield_Ai);
	}

	///sDoubleDamage_Ai
	if(DoubleDamage_Ai_Current>=0)
	{
		///Update new ID
		iSoundVolumeSet(sDoubleDamage_Ai,fVolume_sDoubleDamage_Ai);
		iSoundLocationSet(sDoubleDamage_Ai,&cGame_Mesh.Animator.vBike[DoubleDamage_Ai_Current]);
		if(!iSoundPlaying(sDoubleDamage_Ai))
		{
			iSoundPlay(sDoubleDamage_Ai,0,true);
		}
	}
	else if(iSoundPlaying(sDoubleDamage_Ai))
	{
		///Stop
		iSoundStop(sDoubleDamage_Ai);
	}

	///Warp - Stage 1
	if(Warp0_Ai_Current>=0)
	{
		///Update new ID (Stop/Process/Start)
		if(iSoundPlaying(sWarp_Ai[0]))
		{
			iSoundStop(sWarp_Ai[0]);
		}
		iSoundVolumeSet(sWarp_Ai[0],fVolume_sWarp_Ai);
		iSoundLocationSet(sWarp_Ai[0],&cGame_Mesh.Animator.vBike[Warp0_Ai_Current]);
		iSoundPlay(sWarp_Ai[0],0,false);
	}
	///Warp - Stage 2
	if(Warp1_Ai_Current>=0)
	{
		///Update new ID (Stop/Process/Start)
		if(iSoundPlaying(sWarp_Ai[1]))
		{
			iSoundStop(sWarp_Ai[1]);
		}
		iSoundVolumeSet(sWarp_Ai[1],fVolume_sWarp_Ai);
		iSoundLocationSet(sWarp_Ai[1],&cGame_Mesh.Animator.vBike[Warp1_Ai_Current]);
		iSoundPlay(sWarp_Ai[1],0,false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - AUDIO - WEAPONS - Travel_Update
///*****************************************************************
void Game_Audio_Weapons::Travel_Update(void)
{
	//-------------------------------------------------------------
	///Null vars
	float fDistance = 0.0f;
	float fNearest = 0.0f;
	int Nearest = -1;
	D3DXVECTOR3 vIn = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 vOut = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//-------------------------------------------------------------
	//primary projectile in the world
	fDistance = 0.0f;
	fNearest = fTravel_MaxRange;
	Nearest = -1;
	vIn = D3DXVECTOR3(0.0f,0.0f,0.0f);
	vOut = D3DXVECTOR3(0.0f,0.0f,0.0f);

	for(int i=0;i<cGame_Mesh.Bike_Weapons.TOTAL_CREATE_PRIMARY_PROJECTILE;i++)
	{
		if(iMeshImposterIsShown(cGame_Mesh.Bike_Weapons.P_Primary_Glow,i))///Before auto culling render? Yes it is!!!!
		{
			iMeshImposterLocation(cGame_Mesh.Bike_Weapons.P_Primary_Glow,i,&vIn);
			fDistance = iVectorLength(&(vIn-cGame_Camera.vCamOutput));
			if(fDistance<fNearest)
			{
				fNearest = fDistance;
				Nearest = i;
				vOut = vIn;
			}
		}
	}
	//Apply Sound
	if(Nearest>=0)
	{
		//Doppler
		iSoundFrequencyRatioSet(sPrimaryTravel,cGame_Audio.Freq_Doppler(vOut) + 0.1f);
		//Ai
		iSoundLocationSet(sPrimaryTravel,&vOut);
		iSoundVolumeSet(sPrimaryTravel,fVolume_sPrimaryTravel);
		if(!iSoundPlaying(sPrimaryTravel))
		{
			iSoundPlay(sPrimaryTravel,0,true);
		}
	}
	//Stop sounds when done
	else if(iSoundPlaying(sPrimaryTravel))
	{
		iSoundStop(sPrimaryTravel);
	}
	//-------------------------------------------------------------
	//Missile projectile in the world
	fDistance = 0.0f;
	fNearest = fAi_MaxRange;
	Nearest = -1;
	vIn = D3DXVECTOR3(0.0f,0.0f,0.0f);
	vOut = D3DXVECTOR3(0.0f,0.0f,0.0f);

	for(int i=0;i<cGame_Mesh.Bike_Weapons.TOTAL_CREATE_ALL;i++)
	{
		if(iMeshImposterIsShown(cGame_Mesh.Bike_Weapons.P_Missile_Projectile[0],i))
		{
			iMeshImposterLocation(cGame_Mesh.Bike_Weapons.P_Missile_Projectile[0],i,&vIn);
			fDistance = iVectorLength(&(vIn-cGame_Camera.vCamOutput));
			if(fDistance<fNearest)
			{
				fNearest = fDistance;
				Nearest = i;
				vOut = vIn;
			}
		}
	}
	//Apply Sound
	if(Nearest>=0)
	{
		//Doppler
		iSoundFrequencyRatioSet(sMissile_Travel,cGame_Audio.Freq_Doppler(vOut) + 0.2f);
		iSoundLocationSet(sMissile_Travel,&vOut);
		iSoundVolumeSet(sMissile_Travel,fVolume_sMissile_Travel);
		if(!iSoundPlaying(sMissile_Travel))
		{
			iSoundPlay(sMissile_Travel,0,true);
		}
	}
	//Stop sounds when done
	else if(iSoundPlaying(sMissile_Travel))
	{
		iSoundStop(sMissile_Travel);
	}
	//-------------------------------------------------------------
	//Fusion Missile Explosion
	fDistance = 0.0f;
	fNearest = fAi_MaxRange;
	Nearest = -1;
	vIn = D3DXVECTOR3(0.0f,0.0f,0.0f);
	vOut = D3DXVECTOR3(0.0f,0.0f,0.0f);

	for(int i=0;i<cGame_Mesh.Bike_Weapons.TOTAL_CREATE_ALL;i++)
	{
		if(iMeshImposterIsShown(cGame_Mesh.Bike_Weapons.P_Missile_Explosion[0],i) &&
			cGame_Mesh.Bike_Weapons.ExplosionTimer[i]==1)
		{
			iMeshImposterLocation(cGame_Mesh.Bike_Weapons.P_Missile_Explosion[0],i,&vIn);
			fDistance = iVectorLength(&(vIn-cGame_Camera.vCamOutput));
			if(fDistance<fNearest)
			{
				fNearest = fDistance;
				Nearest = i;
				vOut = vIn;
			}
		}
	}
	//Apply Sound
	if(Nearest>=0)
	{
		//Doppler
		//iSoundFrequencyRatioSet(sMissile_Explosion,cGame_Audio.Freq_Doppler(vOut) + 0.2f);
		if(iSoundPlaying(sMissile_Explosion))
		{
			iSoundStop(sMissile_Explosion);
		}
		iSoundLocationSet(sMissile_Explosion,&vOut);
		iSoundVolumeSet(sMissile_Explosion,fVolume_sMissile_Explosion);
		iSoundPlay(sMissile_Explosion,0,false);
	}
	//-------------------------------------------------------------
	//Shoxwave projectile in the world
	fDistance = 0.0f;
	fNearest = fAi_MaxRange;
	Nearest = -1;
	vIn = D3DXVECTOR3(0.0f,0.0f,0.0f);
	vOut = D3DXVECTOR3(0.0f,0.0f,0.0f);

	for(int i=0;i<cGame_Mesh.Bike_Weapons.TOTAL_CREATE_ALL;i++)
	{
		if(iMeshImposterIsShown(cGame_Mesh.Bike_Weapons.P_Shockwave_Projectile,i))
		{
			iMeshImposterLocation(cGame_Mesh.Bike_Weapons.P_Shockwave_Projectile,i,&vIn);
			fDistance = iVectorLength(&(vIn-cGame_Camera.vCamOutput));
			if(fDistance<fNearest)
			{
				fNearest = fDistance;
				Nearest = i;
				vOut = vIn;
			}
		}
	}
	//Apply Sound
	if(Nearest>=0)
	{
		//Doppler
		iSoundFrequencyRatioSet(sShoxwave_Travel,cGame_Audio.Freq_Doppler(vOut) + 0.2f);
		iSoundLocationSet(sShoxwave_Travel,&vOut);
		iSoundVolumeSet(sShoxwave_Travel,fVolume_sShoxwave_Travel);
		if(!iSoundPlaying(sShoxwave_Travel))
		{
			iSoundPlay(sShoxwave_Travel,0,true);
		}
	}
	//Stop sounds when done
	else if(iSoundPlaying(sShoxwave_Travel))
	{
		iSoundStop(sShoxwave_Travel);
	}
	//-------------------------------------------------------------
	//Rail Travel Sound in the world
	fDistance = 0.0f;
	fNearest = fAi_MaxRange;
	Nearest = -1;
	vIn = D3DXVECTOR3(0.0f,0.0f,0.0f);
	vOut = D3DXVECTOR3(0.0f,0.0f,0.0f);

	for(int i=0;i<cGame_Mesh.Bike_Weapons.TOTAL_CREATE_ALL;i++)
	{
		if(iMeshImposterIsShown(cGame_Mesh.Bike_Weapons.Rail_Projectile,i))
		{
			iMeshImposterLocation(cGame_Mesh.Bike_Weapons.Rail_Projectile,i,&vIn);
			fDistance = iVectorLength(&(vIn-cGame_Camera.vCamOutput));
			if(fDistance<fNearest)
			{
				fNearest = fDistance;
				Nearest = i;
				vOut = vIn;
			}
		}
	}
	//Apply Sound
	if(Nearest>=0)
	{
		//Doppler
		iSoundFrequencyRatioSet(sRail_Travel,cGame_Audio.Freq_Doppler(vOut));
		//Ai
		iSoundLocationSet(sRail_Travel,&vOut);
		iSoundVolumeSet(sRail_Travel,fVolume_sRail_Travel);
		if(!iSoundPlaying(sRail_Travel))
		{
			iSoundPlay(sRail_Travel,0,true);
		}
	}
	//Stop sounds when done
	else if(iSoundPlaying(sRail_Travel))
	{
		iSoundStop(sRail_Travel);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - AUDIO - WEAPONS - Impact_Update
///*****************************************************************
void Game_Audio_Weapons::Impact_Update(void)
{
	//-------------------------------------------------------------
    D3DXVECTOR3* vLoc = new D3DXVECTOR3[gAi_Max_Count+1];
    float* fRange = new float[gAi_Max_Count+1];
    float* fRange_Sorted = new float[gAi_Max_Count+1];
    int* Id = new int[gAi_Max_Count+1];
	//-------------------------------------------------------------
	//Primary Impacts
	int Total = 0;
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		///Reset
		vLoc[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		fRange[i] = -1.0f;
		fRange_Sorted[i] = 10000.0f;
		Id[i] = -1;
		///Find Ai
		if(cGame_Bike[i].fDistanceToCam < fImpact_MaxRange &&
			cGame_Bike[i].Weapons.WeaponId_Out==0)
		{
			vLoc[i] = cGame_Bike[i].Manager.vTargetMesh;
			fRange[i] = cGame_Bike[i].fDistanceToCam;
			fRange_Sorted[Total] = cGame_Bike[i].fDistanceToCam;
			Total++;
		}
	}

	//sort
	iFloatQsort(fRange_Sorted,Total);

	//Match up
	for(int i=0;i<Total;i++)
	{
		for(int j=0;j<=gAi_Max_Count;j++)
		{
			if(fRange_Sorted[i]==fRange[j])
			{
				Id[i] = j;
				///Remove this from pool and future loops
				fRange[j] = -1.0f;
				break;
			}
		}
	}

	//Play Sound
	for(int i=0;i<3;i++)
	{
		if(Id[i]>-1)
		{
			///Shield Hit - find a sound out of the 3 to play
			if(cGame_Bike[Id[i]].Weapons.UtilityType==0 && 
				cGame_Bike[Id[i]].Weapons.bUtilityProjectileSetup)
			{
				bool bSoundAllocated = false;
				for(int j=0;j<3;j++)
				{
					if(!iSoundPlaying(sShield_Impact[j]))
					{
						///Found it, play it
						iSoundLocationSet(sShield_Impact[j],&vLoc[Id[i]]);
						iSoundVolumeSet(sShield_Impact[j],fVolume_sShield_Impact);
						iSoundPlay(sShield_Impact[j],0,false);
						//iSoundFrequencyRatioSet(sShield_Impact[j],cGame_Audio.Freq_Doppler(vLoc[Id[i]]));
						bSoundAllocated = true;
						break;
					}
				}
				if(!bSoundAllocated)
				{
					int Random = 0;//iIntRand(0,3);
					iSoundStop(sShield_Impact[Random]);
					iSoundLocationSet(sShield_Impact[Random],&vLoc[Id[i]]);
					iSoundVolumeSet(sShield_Impact[Random],fVolume_sShield_Impact);
					iSoundPlay(sShield_Impact[Random],0,false);
					//iSoundFrequencyRatioSet(sShield_Impact[Random],cGame_Audio.Freq_Doppler(vLoc[Id[i]]));
				}
			}
			///Primary Hit - find a sound out of the 3 to play
			else
			{
				bool bSoundAllocated = false;
				for(int j=0;j<3;j++)
				{
					if(!iSoundPlaying(sPrimary_Impact[j]))
					{
						///Found it, play it
						iSoundLocationSet(sPrimary_Impact[j],&vLoc[Id[i]]);
						iSoundVolumeSet(sPrimary_Impact[j],fVolume_sPrimary_Impact);
						iSoundPlay(sPrimary_Impact[j],0,false);
						//iSoundFrequencyRatioSet(sPrimary_Impact[j],cGame_Audio.Freq_Doppler(vLoc[Id[i]]));
						bSoundAllocated = true;
						break;
					}
				}
				if(!bSoundAllocated)
				{
					int Random = 0;//iIntRand(0,3);
					iSoundStop(sPrimary_Impact[Random]);
					iSoundLocationSet(sPrimary_Impact[Random],&vLoc[Id[i]]);
					iSoundVolumeSet(sPrimary_Impact[Random],fVolume_sPrimary_Impact);
					iSoundPlay(sPrimary_Impact[Random],0,false);
					//iSoundFrequencyRatioSet(sPrimary_Impact[Random],cGame_Audio.Freq_Doppler(vLoc[Id[i]]));
				}
			}
		}
	}
	//-------------------------------------------------------------
	SAFE_DELETE_ARRAY(vLoc);
    SAFE_DELETE_ARRAY(fRange);
    SAFE_DELETE_ARRAY(fRange_Sorted);
    SAFE_DELETE_ARRAY(Id);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - AUDIO - WEAPONS - Freq_Charge
///*****************************************************************
float Game_Audio_Weapons::Freq_Charge(float input,float max)
{
	//-------------------------------------------------------------
	float fFreq = iFloatInterpolateSmooth(input,0.0f,max,0.75f,1.35f);
	return fFreq;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - WEAPONS - DESTROY
///*****************************************************************
void Game_Audio_Weapons::Destroy(void)
{
	//-------------------------------------------------------------
	//HITSOUND
	iSoundDestroy(sHitSound);
	//Player Weapons
	///primary
	iSoundDestroy(sPrimaryGun);
	///Em_Charge
	iSoundDestroy(sEm_Charge);
	///Em_Fire
	iSoundDestroy(sEm_Fire);
	///Rail_Charge
	iSoundDestroy(sRail_Charge);
	///Rail_Fire
	iSoundDestroy(sRail_Fire);
	///Shoxwave_Fire
	iSoundDestroy(sShoxwave_Fire);
	///sMissile_Fire
	iSoundDestroy(sMissile_Fire);
	///sShield
	iSoundDestroy(sShield);
	///sDoubleDamage
	iSoundDestroy(sDoubleDamage);
	///sWarp
	for(int i=0;i<2;i++)
	{
		iSoundDestroy(sWarp[i]);
	}
	//Ai
	///Em_Charge
	iSoundDestroy(sEm_Charge_Ai);
	///Em_Fire
	iSoundDestroy(sEm_Fire_Ai);
	///Rail_Charge
	iSoundDestroy(sRail_Charge_Ai);
	///Rail_Fire
	iSoundDestroy(sRail_Fire_Ai);
	///Shoxwave_Fire
	iSoundDestroy(sShoxwave_Fire_Ai);
	///sMissile_Fire_Ai
	iSoundDestroy(sMissile_Fire_Ai);
	///sShield_Ai
	iSoundDestroy(sShield_Ai);
	///sDoubleDamage_Ai
	iSoundDestroy(sDoubleDamage_Ai);
	///sWarp_Ai
	for(int i=0;i<2;i++)
	{
		iSoundDestroy(sWarp_Ai[i]);
	}
	//-------------------------------------------------------------
	//Globals Travel Sounds
	///Primary Travel Sound
	iSoundDestroy(sPrimaryTravel);
	///Fusion Missile Travel Sound
	iSoundDestroy(sMissile_Travel);
	///Fusion Missile Explosion
	iSoundDestroy(sMissile_Explosion);
	///ShoxWave Travel Sound
	iSoundDestroy(sShoxwave_Travel);
	///ShoxWave Travel Sound
	iSoundDestroy(sRail_Travel);
	//---------------------------------------------------------
	//Global Impacts
	for(int i=0;i<3;i++)
	{
		iSoundDestroy(sPrimary_Impact[i]);
		iSoundDestroy(sShield_Impact[i]);
	}
	//-------------------------------------------------------------
}