//-----------------------------------------------------------------
// About:
//
// name: "Game_Audio_SoundBarrier.cpp:
//
// included in: "Game_Audio.h"
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
#include "Game_Audio_SoundBarrier.h"
//-----------------------------------------------------------------
///*****************************************************************
///GAME - AUDIO - MUSIC - CONSTRUCTORS
///*****************************************************************
Game_Audio_SoundBarrier::Game_Audio_SoundBarrier(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<3;i++)
	{
		s_SoundBarrier[i] = NULL;
	}
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Audio_SoundBarrier::~Game_Audio_SoundBarrier(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - AUDIO - MUSIC - ZeroData
///*****************************************************************
void Game_Audio_SoundBarrier::ZeroData(void)
{
	//-------------------------------------------------------------
	fInternalVolume			= 0.0f;
	for(int i=0;i<3;i++)
	{
		fVolumeTarget[i]	= 0.5f;
		fVolume[i]			= 0.5f;
	}
	CurrentState			= 0;
	TimeInBarrier			= 0;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - MUSIC - CREATE
///*****************************************************************
void Game_Audio_SoundBarrier::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
	//Create Sounds
	s_SoundBarrier[0] = iSoundCreate("trzero_res\\sound\\bike\\sound_barrier\\sound_barrier_enter_stereo.wav",false);
	s_SoundBarrier[1] = iSoundCreate("trzero_res\\sound\\bike\\sound_barrier\\sound_barrier_travel_stereo.wav",false);
	s_SoundBarrier[2] = iSoundCreate("trzero_res\\sound\\bike\\sound_barrier\\sound_barrier_exit_stereo.wav",false);
	iSoundVolumeSet(s_SoundBarrier[0],0.0f);
	iSoundVolumeSet(s_SoundBarrier[1],0.0f);
	iSoundVolumeSet(s_SoundBarrier[2],0.0f);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - MUSIC - UPDATE
///*****************************************************************
void Game_Audio_SoundBarrier::Update(void)
{
	//-------------------------------------------------------------
	//Internal Volume
	if(gPaused || cGame_Gamma_Fade.bFadeOut)
	{
		iFloatTendTo2(fInternalVolume,0.0f,40.0f);
	}
	else
	{
		iFloatTendTo2(fInternalVolume,1.0f,gSoundBarrierTendTo_Out);
	}
	//-------------------------------------------------------------
	//Sound Barrier - activator
	gSoundBarrier = false;
	if(cGame_Camera.bSpectate)
	{
		if(cGame_Bike[cGame_Camera.SpectateId].Manager.fAcceleration_Speed >= gSoundBarrierSpeedActivation)
		{
			gSoundBarrier = true;
		}
	}
	else if(cGame_Bike[gAi_Max_Count].Manager.fAcceleration_Speed >= gSoundBarrierSpeedActivation)
	{
		gSoundBarrier = true;
	}
	//-------------------------------------------------------------
	//Play Sound Barrier FX
	if(gSoundBarrier)
	{
		///Update time spent in barrier
		TimeInBarrier++;
		///stop previous sound
		iSoundStop(s_SoundBarrier[2]);
		if(CurrentState==0)///Play intro sound
		{
			iSoundPlay(s_SoundBarrier[0],0,false);
			CurrentState++;
		}
		else if(CurrentState==1)///Play loop
		{
			if(!iSoundPlaying(s_SoundBarrier[1]) &&
				!iSoundPlaying(s_SoundBarrier[0]))
			{
				iSoundPlay(s_SoundBarrier[1],0,true);
			}
		}
	}
	else if(CurrentState==1)///Play outro sound
	{
		///stop other sounds
		iSoundStop(s_SoundBarrier[0]);
		iSoundStop(s_SoundBarrier[1]);
		///play outtro
		if(TimeInBarrier>=30)
		{
			iSoundPlay(s_SoundBarrier[2],0,false);
		}
		///reset
		TimeInBarrier = 0;
		CurrentState = 0;
	}
	///Volume runtime
	iSoundVolumeSet(s_SoundBarrier[0],(fVolume[0] * fInternalVolume) * gVolumeFx);
	iSoundVolumeSet(s_SoundBarrier[1],(fVolume[1] * fInternalVolume) * gVolumeFx);
	iSoundVolumeSet(s_SoundBarrier[2],(fVolume[2] * fInternalVolume) * gVolumeFx);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - MUSIC - DESTROY
///*****************************************************************
void Game_Audio_SoundBarrier::Destroy(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<3;i++)
	{
		iSoundDestroy(s_SoundBarrier[i]);
	}
	//-------------------------------------------------------------
}