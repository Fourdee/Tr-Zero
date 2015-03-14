//-----------------------------------------------------------------
// About:
//
// name: "Game_Audio.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
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
#include "Game_Audio.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - AUDIO - CONSTRUCTORS
///*****************************************************************
Game_Audio::Game_Audio(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}

Game_Audio::~Game_Audio(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - CREATE
///*****************************************************************
void Game_Audio::Create(void)
{
	//-------------------------------------------------------------
	//set listener
	iListenerCameraSet(gCamera);
	//set reverb
	//iListenerReverbSet(0);//27
	//-------------------------------------------------------------
	//SoundBarrier
	SoundBarrier.Create();
	//Music
	Music.Create();
	//Menu Fx
	Menu.Create();
	//Bike Fx
	if(gGameState>0)
	{
		Bike_Fx.Create();
	}
	//Weapons
	if(gWeaponsTrackEnable)
	{
		Weapons.Create();
	}
	//Voice
	Voice.Create();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - UPDATE
///*****************************************************************
void Game_Audio::Update(void)
{
	//-------------------------------------------------------------
	//Voices
	Voice.Update();
	//-------------------------------------------------------------
	//SoundBarrier
	SoundBarrier.Update();
	//Music
	Music.Update();
	//Bike FX
	Bike_Fx.Update();
	//Weapons
	if(gWeaponsTrackEnable)
	{
		Weapons.Update();
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - DESTROY
///*****************************************************************
void Game_Audio::Destroy(void)
{
	//-------------------------------------------------------------
	SoundBarrier.Destroy();
	Music.Destroy();
	Menu.Destroy();
	if(gGameState>0)
	{
		Bike_Fx.Destroy();
	}
	//Weapons
	if(gWeaponsTrackEnable)
	{
		Weapons.Destroy();
	}
	Voice.Destroy();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - AUDIO - WEAPONS - Freq_Doppler
///*****************************************************************
float Game_Audio::Freq_Doppler(D3DXVECTOR3 vInput)
{
	//-------------------------------------------------------------
	float fDopplerRange = iVectorLength(&(vInput - cGame_Camera.vCamOutput));
	float fFreq = iFloatInterpolateSmooth(fDopplerRange,0.0f,200.0f,1.25f,0.75f);
	return fFreq;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - AUDIO - WEAPONS - Freq_Doppler2
///*****************************************************************
float Game_Audio::Freq_Doppler2(D3DXVECTOR3 vInput,float fMaxRange)
{
	//-------------------------------------------------------------
	//Infront or behind?
	float fDopplerRange = iVectorLength(&(vInput - cGame_Camera.vCamOutput));
	float fFreq = iFloatInterpolateSmooth(fDopplerRange,0.0f,fMaxRange,1.15f,0.85f);
	return fFreq;
	//-------------------------------------------------------------
}