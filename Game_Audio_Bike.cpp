//-----------------------------------------------------------------
// About:
//
// name: "Game_Audio.h:
//
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
#include "Game_Audio_Bike.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - AUDIO - BIKE - CONSTRUCTORS
///*****************************************************************
Game_Audio_Bike::Game_Audio_Bike(void)
{
	//-------------------------------------------------------------
	//Player Bike Engine Layer
	for(int i=0;i<3;i++)
	{
		sEngine_Player[i] = NULL;
		sTurbo_Player[i] = NULL;
		sBoost_Player[i] = NULL;
	}
	//Break Player
	sBreak_Player = NULL;
	//Slip
	sSlip_Player = NULL;
	//Impact
	sImpact_Player = NULL;
	//Backfires
	sBoostRelease_Player = NULL;
	//Shield
	sShield_Player = NULL;
	//---------------------------------------------------------
	//AI Bikes
	for(int i=0;i<2;i++)
	{
		sEngine_Ai[i] = NULL;
	}
	//---------------------------------------------------------
	//Volumes Target (eg fVolume = THIS * internal * gsoundfx)
	///Volumes - Player
	fVolumeTarget_sEngine_Player = 1.6f;
	fVolumeTarget_sTurbo_Player = 2.25f;
	fVolumeTarget_sBoost_Player = 0.77f;

	fVolumeTarget_sBreak_Player = 0.95f;
	fVolumeTarget_sSlip_Player = 2.09f;
	fVolumeTarget_sImpact_Player = 0.5f;
	fVolumeTarget_sBoostRelease_Player = 0.7f;
	fVolumeTarget_sShield_Player = 0.85f;
	///Volumes Ai
	fVolumeTarget_sEngine_Ai = 0.62f;
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}
Game_Audio_Bike::~Game_Audio_Bike(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - BIKE - ZeroData
///*****************************************************************
void Game_Audio_Bike::ZeroData(void)
{
	//-------------------------------------------------------------
	//Internal Volumes
	fInternalVol = 1.0f;
	///Max Ranges
	fPlayer_MaxRange = 250.0f;
	fAi_MaxRange = 150.0f;
	///Volume Ramping
	fVolumeRamp = 0.0f;
	Timer_VolumeRamp = 0;
	//---------------------------------------------------------
	//Player Bike Engine Layer
	fEngine_Player_VolMax = 0.0f;
	fTurbo_Player_VolMax = 0.0f;
	fBoost_Player_VolMax = 0.0f;
	for(int i=0;i<3;i++)
	{
		fEngine_Player_Vol[i] = 0.0f;
		fEngine_Player_Freq[i] = 0.0f;

		fTurbo_Player_Vol[i] = 0.0f;
		fTurbo_Player_Freq[i] = 0.0f;

		fBoost_Player_Vol[i] = 0.0f;
		fBoost_Player_Freq[i] = 0.0f;
	}
	//Break Player
	fBreak_Player_Vol = 0.0f;
	//Shield
	fShield_Player_VolMax = 0.7f;
	//Slip
	fSlip_Player_Vol = 0.0f;
	//BoostRelease
	Timer_BoostRelease_Player = 0;
	//Shield
	fShield_Player_Vol = 0.0f;
	//-------------------------------------------------------------
	//AI Bikes
	for(int i=0;i<2;i++)
	{
		fEngine_Ai_Vol[i] = 0.0f;
		fEngine_Ai_Freq[i] = 1.0f;
		iSoundVolumeSet(sEngine_Ai[i],fEngine_Ai_Vol[i]);
		Engine_Ai_Closest[i] = -1;
		fEngine_Ai_PreviousRange[i] = fAi_MaxRange;
	}
	Timer_Ai_Tickrate = 0;
	//-------------------------------------------------------------
}

///*****************************************************************
//GAME - AUDIO - BIKE - CREATE
///*****************************************************************
void Game_Audio_Bike::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
	//Player Bike Engine Layer
	sEngine_Player[0] = iSoundCreate("trzero_res\\sound\\bike\\engine_main_low_mono.wav",true);
	sEngine_Player[1] = iSoundCreate("trzero_res\\sound\\bike\\engine_main_med_mono.wav",true);
	sEngine_Player[2] = iSoundCreate("trzero_res\\sound\\bike\\engine_main_high_mono.wav",true);
	iSoundDopplerEffectSet(sEngine_Player[0],0.0f);
	iSoundDopplerEffectSet(sEngine_Player[1],0.0f);
	iSoundDopplerEffectSet(sEngine_Player[2],0.0f);
	iSoundVolumeSet(sEngine_Player[0],0.0f);
	iSoundVolumeSet(sEngine_Player[1],0.0f);
	iSoundVolumeSet(sEngine_Player[2],0.0f);

	sTurbo_Player[0] = iSoundCreate("trzero_res\\sound\\bike\\engine_top_low_mono.wav",true);
	sTurbo_Player[1] = iSoundCreate("trzero_res\\sound\\bike\\engine_top_med_mono.wav",true);
	sTurbo_Player[2] = iSoundCreate("trzero_res\\sound\\bike\\engine_top_high_mono.wav",true);
	iSoundDopplerEffectSet(sTurbo_Player[0],0.0f);
	iSoundDopplerEffectSet(sTurbo_Player[1],0.0f);
	iSoundDopplerEffectSet(sTurbo_Player[2],0.0f);
	iSoundVolumeSet(sTurbo_Player[0],0.0f);
	iSoundVolumeSet(sTurbo_Player[1],0.0f);
	iSoundVolumeSet(sTurbo_Player[2],0.0f);

	sBoost_Player[0] = iSoundCreate("trzero_res\\sound\\bike\\engine_boost_low_stereo.wav",false);
	sBoost_Player[1] = iSoundCreate("trzero_res\\sound\\bike\\engine_boost_med_stereo.wav",false);
	sBoost_Player[2] = iSoundCreate("trzero_res\\sound\\bike\\engine_boost_high_stereo.wav",false);
	iSoundVolumeSet(sBoost_Player[0],0.0f);
	iSoundVolumeSet(sBoost_Player[1],0.0f);
	iSoundVolumeSet(sBoost_Player[2],0.0f);
	//Break Player
	sBreak_Player = iSoundCreate("trzero_res\\sound\\bike\\brake_stereo.wav",false);
	iSoundVolumeSet(sBreak_Player,0.0f);
	//Slip
	sSlip_Player = iSoundCreate("trzero_res\\sound\\bike\\tire_slip_mono.wav",true);
	iSoundVolumeSet(sSlip_Player,0.0f);
	iSoundDopplerEffectSet(sSlip_Player,0.0f);
	//Impact
	sImpact_Player = iSoundCreate("trzero_res\\sound\\bike\\wall_collision_stereo.wav",false);
	iSoundVolumeSet(sImpact_Player,0.0f);
	//Backfires
	sBoostRelease_Player = iSoundCreate("trzero_res\\sound\\bike\\boost_release_stereo.wav",false);
	iSoundVolumeSet(sBoostRelease_Player,0.0f);
	//Shield
	sShield_Player = iSoundCreate("trzero_res\\sound\\bike\\energy_regen_stereo.wav",false);
	iSoundVolumeSet(sShield_Player,0.0f);
	//-------------------------------------------------------------
	//AI Bikes
	for(int i=0;i<2;i++)
	{
		sEngine_Ai[i] = iSoundCreate("trzero_res\\sound\\bike\\engine_ai_mono.ogg",true);
		iSoundVolumeSet(sEngine_Ai[i],0.0f);
		iSoundDopplerEffectSet(sEngine_Ai[i],0.0f);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - BIKE - UPDATE
///*****************************************************************
void Game_Audio_Bike::Update(void)
{
	//-------------------------------------------------------------
	//Internal Volume (for menu etc, control all bike fx volumes)
	if(gPaused || cGame_Gamma_Fade.bFadeOut)
	{
		iFloatTendTo2(fInternalVol,0.0f,40.0f);
	}
	else
	{
		///Sound Barrier
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
	//Audio Functions
	UpdateVolumeRamp();
	//-------------------------------------------------------------
	//Player Bike
	UpdatePlayer();
	//-------------------------------------------------------------
	//Ai Bike
	UpdateAi();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - BIKE - UPDATE VOLUME RAMPING
///*****************************************************************
void Game_Audio_Bike::UpdateVolumeRamp(void)
{
	//-------------------------------------------------------------
	Timer_VolumeRamp++;
	int off = 5;
	int cap = off * 2;
	if(Timer_VolumeRamp < off)
	{
		iFloatTendTo2(fVolumeRamp,0.3f,1.6f);
	}
	else if(Timer_VolumeRamp >= off && Timer_VolumeRamp < cap)
	{
		iFloatTendTo2(fVolumeRamp,1.0f,1.6f);
	}
	else
	{
		Timer_VolumeRamp = 0;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - AUDIO - BIKE - UPDATE PLAYER
///*****************************************************************
void Game_Audio_Bike::UpdatePlayer(void)
{
	//-------------------------------------------------------------
	//Input Data
	float Speed = abs(cGame_Bike[gAi_Max_Count].Manager.fAcceleration_Speed);
	float SpeedMax = cGame_Bike[gAi_Max_Count].Manager.fAcceleration_Max * 2.1f;
	//-------------------------------------------------------------
	//Volume Control
	if(cGame_Bike[gAi_Max_Count].Energy.bEnergyRegenActive)
	{
		iFloatTendTo2(fShield_Player_Vol,fVolumeTarget_sShield_Player,7.0f);
		fBreak_Player_Vol = 0.0f;		
		fEngine_Player_VolMax = fVolumeTarget_sEngine_Player / 1.8f;
		fBoost_Player_VolMax = 0.0f;
		fTurbo_Player_VolMax = fVolumeTarget_sTurbo_Player / 2.0f;
	}
	else if(cGame_Bike[gAi_Max_Count].InputSpeedState==-1)
	{
		iFloatTendTo2(fShield_Player_Vol,0.0f,40.0f);

		float fBreak_Vol_Stop_Multi = iFloatInterpolate(Speed,0.5f,1.5f,0.0f,1.0f);
		iFloatTendTo2(fBreak_Player_Vol,fVolumeTarget_sBreak_Player * fBreak_Vol_Stop_Multi,25.0f);

		fEngine_Player_VolMax = fVolumeTarget_sEngine_Player / 4.0f;
		fBoost_Player_VolMax = 0.0f;
		fTurbo_Player_VolMax = fVolumeTarget_sTurbo_Player / 2.0f;
	}
	else if(cGame_Bike[gAi_Max_Count].InputSpeedState==0)
	{
		iFloatTendTo2(fShield_Player_Vol,0.0f,40.0f);
		iFloatTendTo2(fBreak_Player_Vol,0.0f,25.0f);

		fEngine_Player_VolMax = fVolumeTarget_sEngine_Player / 1.75f;
		fBoost_Player_VolMax = 0.0f;
		fTurbo_Player_VolMax = fVolumeTarget_sTurbo_Player / 2.0f;
	}
	else if(cGame_Bike[gAi_Max_Count].InputSpeedState==1)
	{
		iFloatTendTo2(fShield_Player_Vol,0.0f,40.0f);
		iFloatTendTo2(fBreak_Player_Vol,0.0f,25.0f);
		fEngine_Player_VolMax = fVolumeTarget_sEngine_Player;
		fBoost_Player_VolMax = 0.0f;
		fTurbo_Player_VolMax = fVolumeTarget_sTurbo_Player;
	}
	else if(cGame_Bike[gAi_Max_Count].InputSpeedState==2)
	{
		iFloatTendTo2(fShield_Player_Vol,0.0f,40.0f);
		iFloatTendTo2(fBreak_Player_Vol,0.0f,25.0f);
		fEngine_Player_VolMax = fVolumeTarget_sEngine_Player / 1.1f;
		fBoost_Player_VolMax = fVolumeTarget_sBoost_Player;
		fTurbo_Player_VolMax = fVolumeTarget_sTurbo_Player;
		Timer_BoostRelease_Player++;
	}
	//-------------------------------------------------------------
	//Engine Layers
	float fTargetEngineVol0 = 0.0f;
	float fTargetEngineVol1 = 0.0f;
	float fTargetEngineVol2 = 0.0f;

	float fTargetTurboVol0 = 0.0f;
	float fTargetTurboVol1 = 0.0f;
	float fTargetTurboVol2 = 0.0f;

	float fTargetBoostVol0 = 0.0f;
	float fTargetBoostVol1 = 0.0f;
	float fTargetBoostVol2 = 0.0f;

	float SpeedSection_0 = SpeedMax / 2.8f;
	float SpeedSection_1 = SpeedMax / 1.5f;
	///Sections
	if(Speed <= SpeedSection_0)
	{
		fTargetEngineVol0 = fEngine_Player_VolMax;
		fTargetTurboVol0 = fTurbo_Player_VolMax;
		fTargetBoostVol0 = fBoost_Player_VolMax;
	}
	else if(Speed <= SpeedSection_1)
	{
		fTargetEngineVol1 = fEngine_Player_VolMax;
		fTargetTurboVol1 = fTurbo_Player_VolMax;
		fTargetBoostVol1 = fBoost_Player_VolMax;
	}
	else 
	{
		fTargetEngineVol2 = fEngine_Player_VolMax;
		fTargetTurboVol2 = fTurbo_Player_VolMax;
		fTargetBoostVol2 = fBoost_Player_VolMax;
	}
	fEngine_Player_Freq[0] = iFloatInterpolate(Speed,0.0f,SpeedSection_0,0.95f,1.35f); 
	fEngine_Player_Freq[1] = iFloatInterpolate(Speed,SpeedSection_0,SpeedSection_1,0.9f,1.35f); 
	fEngine_Player_Freq[2] = iFloatInterpolate(Speed,SpeedSection_1,SpeedMax,0.8f,1.3f); 

	fTurbo_Player_Freq[0] = iFloatInterpolate(Speed,0.0f,SpeedSection_0,0.95f,1.35f); 
	fTurbo_Player_Freq[1] = iFloatInterpolate(Speed,SpeedSection_0,SpeedSection_1,0.9f,1.35f); 
	fTurbo_Player_Freq[2] = iFloatInterpolate(Speed,SpeedSection_1,SpeedMax,0.8f,1.3f); 

	fBoost_Player_Freq[0] = iFloatInterpolate(Speed,0.0f,SpeedSection_0,0.95f,1.35f); 
	fBoost_Player_Freq[1] = iFloatInterpolate(Speed,SpeedSection_0,SpeedSection_1,0.9f,1.35f); 
	fBoost_Player_Freq[2] = iFloatInterpolate(Speed,SpeedSection_1,SpeedMax,0.8f,1.3f); 

	iFloatTendTo2(fEngine_Player_Vol[0],fTargetEngineVol0,12.0f);
	iFloatTendTo2(fEngine_Player_Vol[1],fTargetEngineVol1,12.0f);
	iFloatTendTo2(fEngine_Player_Vol[2],fTargetEngineVol2,12.0f);

	iFloatTendTo2(fTurbo_Player_Vol[0],fTargetTurboVol0,12.0f);
	iFloatTendTo2(fTurbo_Player_Vol[1],fTargetTurboVol1,12.0f);
	iFloatTendTo2(fTurbo_Player_Vol[2],fTargetTurboVol2,12.0f);

	iFloatTendTo2(fBoost_Player_Vol[0],fTargetBoostVol0,12.0f);
	iFloatTendTo2(fBoost_Player_Vol[1],fTargetBoostVol1,12.0f);
	iFloatTendTo2(fBoost_Player_Vol[2],fTargetBoostVol2,12.0f);
	//Apply
	for(int i=0;i<3;i++)
	{
		///Main
		iSoundVolumeSet(sEngine_Player[i],((fEngine_Player_Vol[i] * fInternalVol) * gVolumeFx));
		iSoundFrequencyRatioSet(sEngine_Player[i],fEngine_Player_Freq[i]);
		iSoundLocationSet(sEngine_Player[i],&cGame_Mesh.Animator.vBike[gAi_Max_Count]);
		///Turbo
		iSoundVolumeSet(sTurbo_Player[i],((fTurbo_Player_Vol[i] * fInternalVol) * gVolumeFx));
		iSoundFrequencyRatioSet(sTurbo_Player[i],fTurbo_Player_Freq[i]);
		iSoundLocationSet(sTurbo_Player[i],&cGame_Mesh.Animator.vBike[gAi_Max_Count]);
		///Boost
		iSoundVolumeSet(sBoost_Player[i],((fBoost_Player_Vol[i] * fInternalVol) * gVolumeFx));
		iSoundFrequencyRatioSet(sBoost_Player[i],fBoost_Player_Freq[i]);
	}
	//Play
	if(!iSoundPlaying(sEngine_Player[0]))
	{
		for(int i=0;i<3;i++)
		{
			iSoundRadiusSet(sEngine_Player[i],fPlayer_MaxRange);
			iSoundRadiusSet(sTurbo_Player[i],fPlayer_MaxRange);
			iSoundPlay(sEngine_Player[i],0,true);
			iSoundPlay(sTurbo_Player[i],0,true);
			iSoundPlay(sBoost_Player[i],0,true);
		}
	}
	//-------------------------------------------------------------
	//Break
	float Break_Freq = iFloatInterpolate(Speed,1.0f,SpeedMax,1.0f,1.5f); 
	iSoundFrequencyRatioSet(sBreak_Player,Break_Freq);
	iSoundVolumeSet(sBreak_Player,(fBreak_Player_Vol * fInternalVol) * gVolumeFx);
	//-------------------------------------------------------------
	//Slip
	fSlip_Player_Vol = iFloatInterpolate(abs(cGame_Bike[gAi_Max_Count].Manager.fLean),6.0f,20.0f,0.0f,fVolumeTarget_sSlip_Player);
	iSoundVolumeSet(sSlip_Player,((fSlip_Player_Vol * fInternalVol) * gVolumeFx));
	float Slip_Freq = iFloatInterpolate(abs(cGame_Bike[gAi_Max_Count].Manager.fLean),16.0f,28.0f,0.7f,1.2f);
	iSoundFrequencyRatioSet(sSlip_Player,Slip_Freq);
	iSoundLocationSet(sSlip_Player,&cGame_Mesh.Animator.vBike[gAi_Max_Count]);
	//-------------------------------------------------------------
	//Impact
	if(abs(cGame_Bike[gAi_Max_Count].Manager.fCollision_px) > 1.0f && !iSoundPlaying(sImpact_Player))
	{
		iSoundVolumeSet(sImpact_Player,(fVolumeTarget_sImpact_Player * fInternalVol * gVolumeFx));
		iSoundPlay(sImpact_Player,0,false);
	}
	//-------------------------------------------------------------
	//BoostRelease
	if(Timer_BoostRelease_Player >= 60 && 
		cGame_Bike[gAi_Max_Count].InputSpeedState!=2)
	{
		iSoundVolumeSet(sBoostRelease_Player,((fVolumeTarget_sBoostRelease_Player * fInternalVol) * gVolumeFx));
		iSoundPlay(sBoostRelease_Player,0,false);
		Timer_BoostRelease_Player = 0;
	}
	//-------------------------------------------------------------
	//Shield
	float Shield_Freq = iFloatInterpolateSmooth(cGame_Bike[gAi_Max_Count].Energy.fEnergy,25.0f,cGame_Upgrades.fEnergyMax[gAi_Max_Count],0.95f,1.3f); 
	iSoundFrequencyRatioSet(sShield_Player,Shield_Freq);
	iSoundVolumeSet(sShield_Player,(fShield_Player_Vol * fVolumeRamp) * fInternalVol * gVolumeFx);
	//-------------------------------------------------------------
	//Play All Looping Sounds
	if(!iSoundPlaying(sBreak_Player))
	{
		iSoundPlay(sSlip_Player,0,true);
		iSoundPlay(sShield_Player,0,true);
		iSoundPlay(sBreak_Player,0,true);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - AUDIO - BIKE - UPDATE Ai
///*****************************************************************
void Game_Audio_Bike::UpdateAi(void)
{
	//-------------------------------------------------------------
	//Ai Bike
	// find x closest to camera
	//-------------------------------------------------------------
	//Begin range check against all bikes
	Timer_Ai_Tickrate++;
	if(Timer_Ai_Tickrate==5)
	{
		fEngine_Ai_PreviousRange[0] = fAi_MaxRange;
		fEngine_Ai_PreviousRange[1] = fAi_MaxRange;

		for(int i=0;i<gAi_Max_Count;i++)
		{
			if(cGame_Bike[i].fDistanceToCam < fEngine_Ai_PreviousRange[0] && 
				i!= Engine_Ai_Closest[1])
			{
				fEngine_Ai_PreviousRange[0] = cGame_Bike[i].fDistanceToCam;
				Engine_Ai_Closest[0] = i;
			}
			else if(cGame_Bike[i].fDistanceToCam < fEngine_Ai_PreviousRange[1] && 
					i!= Engine_Ai_Closest[0])
			{
				fEngine_Ai_PreviousRange[1] = cGame_Bike[i].fDistanceToCam;
				Engine_Ai_Closest[1] = i;
			}
		}
		//Reset timer for next tick
		Timer_Ai_Tickrate = 0;
	}
	//-------------------------------------------------------------
	//Output
	for(int i=0;i<2;i++)
	{
		//out of range, disable
		if(Engine_Ai_Closest[i]==-1)
		{
			if(iSoundPlaying(sEngine_Ai[i]))
			{
				fEngine_Ai_Vol[i] = 0.0f;
				iSoundStop(sEngine_Ai[i]);
			}
		}
		//Grab the 2 closest bikes, define the sounds
		else
		{
			//Start sound if not playing
			if(!iSoundPlaying(sEngine_Ai[i]))
			{
				///Radius
				iSoundRadiusSet(sEngine_Ai[i],fAi_MaxRange);
				iSoundPlay(sEngine_Ai[i],0,true);
			}
			//Define Volume to SpeedState
			if(cGame_Bike[Engine_Ai_Closest[i]].InputSpeedState==-1)
			{
				iFloatTendTo2(fEngine_Ai_Vol[i],(fVolumeTarget_sEngine_Ai / 4.0f),20.0f);
			}
			else if(cGame_Bike[Engine_Ai_Closest[i]].InputSpeedState==0)
			{
				iFloatTendTo2(fEngine_Ai_Vol[i],(fVolumeTarget_sEngine_Ai / 3.0f),20.0f);
			}
			else
			{
				iFloatTendTo2(fEngine_Ai_Vol[i],fVolumeTarget_sEngine_Ai,20.0f);
			}
			//else if(cGame_Bike[Engine_Ai_Closest[i]].InputSpeedState==2)
			//{
			//	iFloatTendTo2(fEngine_Ai_Vol[i],fVolumeTarget_sEngine_Ai,5.0f);
			//}
			//Volume
			iSoundVolumeSet(sEngine_Ai[i],(fEngine_Ai_Vol[i] * fInternalVol) * gVolumeFx);
			//Freq
			float fDoppler = iFloatInterpolateSmooth(fEngine_Ai_PreviousRange[i] - cGame_Bike[Engine_Ai_Closest[i]].fDistanceToCam,-20.0f,20.0f,-0.35f,0.55f);
			float Speed = abs(cGame_Bike[Engine_Ai_Closest[i]].Manager.fAcceleration_Speed);
			float SpeedMax = cGame_Bike[Engine_Ai_Closest[i]].Manager.fAcceleration_Max * 2.0f;

			float fTargetFreq = iFloatInterpolateSmooth(Speed,0.0f,SpeedMax,0.8f + ((float)i * 0.1f),1.9f);
			fTargetFreq += fDoppler;
			iFloatCap(fTargetFreq,0.8f,2.0f);

			iFloatTendTo2(fEngine_Ai_Freq[i],fTargetFreq,8.0f);
			iSoundFrequencyRatioSet(sEngine_Ai[i],fEngine_Ai_Freq[i]);
			//Location
			iSoundLocationSet(sEngine_Ai[i],&cGame_Mesh.Animator.vBike[Engine_Ai_Closest[i]]);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - BIKE - DESTROY
///*****************************************************************
void Game_Audio_Bike::Destroy(void)
{
	//-------------------------------------------------------------
	//Player Bike Engine
	for(int i=0;i<3;i++)
	{
		iSoundDestroy(sEngine_Player[i]);
		iSoundDestroy(sTurbo_Player[i]);
		iSoundDestroy(sBoost_Player[i]);
	}
	//Break Player
	iSoundDestroy(sBreak_Player);
	//Slip
	iSoundDestroy(sSlip_Player);
	//Impact
	iSoundDestroy(sImpact_Player);
	//Backfire
	iSoundDestroy(sBoostRelease_Player);
	//Shield
	iSoundDestroy(sShield_Player);
	//-------------------------------------------------------------
	//Ai
	for(int i=0;i<2;i++)
	{
		iSoundDestroy(sEngine_Ai[i]);
	}
	//-------------------------------------------------------------
}