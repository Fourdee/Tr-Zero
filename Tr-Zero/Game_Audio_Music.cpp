//-----------------------------------------------------------------
// About:
//
// name: "Game_Audio_Music.cpp:
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
#include "Game_Audio_Music.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - AUDIO - MUSIC - CONSTRUCTORS
///*****************************************************************
Game_Audio_Music::Game_Audio_Music(void)
{
	//-------------------------------------------------------------
	//music
	BG_Music = NULL;
	Showroom_Music = NULL;
	bShowroom = false;
	fInternal_Vol = 0.0f;
	//-------------------------------------------------------------
}

Game_Audio_Music::~Game_Audio_Music(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - MUSIC - CREATE
///*****************************************************************
void Game_Audio_Music::Create(void)
{
	//-------------------------------------------------------------
	//music
	if(gGameState==0)//Menu
	{
		BG_Music = iSoundCreate("trzero_res\\sound\\music\\ghales_empire.ogg",false);
		Showroom_Music = iSoundCreate("trzero_res\\sound\\music\\jb_nullvoid.ogg",false);
	}
	else if(gGameState==1)//Volex
	{
		BG_Music = iSoundCreate("trzero_res\\sound\\music\\ghales_neighb.ogg",false);
	}
	else if(gGameState==2)//Silence
	{
		BG_Music = iSoundCreate("trzero_res\\sound\\music\\jb_level1.ogg",false);
	}
	else if(gGameState==3)//Phantom
	{
		BG_Music = iSoundCreate("trzero_res\\sound\\music\\dk_terraform.ogg",false);
	}
	else if(gGameState==10)//Rez
	{
		BG_Music = iSoundCreate("trzero_res\\sound\\music\\dknight_electrov3.ogg",false);
	}
	//Apply
	iSoundVolumeSet(BG_Music,fInternal_Vol * gVolumeMusic);
	//Apply volume + start
	MusicStart();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - MUSIC - AOUNDS APPLY
///*****************************************************************
void Game_Audio_Music::MusicStart(void)
{
	//-------------------------------------------------------------
	//play background music
	iSoundPlay(BG_Music,0,true);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - MUSIC - AOUNDS STOP
///*****************************************************************
void Game_Audio_Music::MusicStop(void)
{
	//-------------------------------------------------------------
	//music
	iSoundStop(BG_Music);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - MUSIC - UPDATE
///*****************************************************************
void Game_Audio_Music::Update(void)
{
	//-------------------------------------------------------------
	//Sound Barrier
	if(gSoundBarrier)
	{
		iFloatTendTo2(fInternal_Vol,gSoundBarrierVolumeMin,gSoundBarrierTendTo_In);
	}
	else
	{
		iFloatTendTo2(fInternal_Vol,1.0f,gSoundBarrierTendTo_Out);
	}
	//Apply
	iSoundVolumeSet(BG_Music,fInternal_Vol * gVolumeMusic);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - MUSIC - DESTROY
///*****************************************************************
void Game_Audio_Music::Destroy(void)
{
	//-------------------------------------------------------------
	//stop all sounds
	MusicStop();
	//-------------------------------------------------------------
	//music
	iSoundDestroy(BG_Music);
	//Showroom
	if(gGameState==0)
	{
		iSoundDestroy(Showroom_Music);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - AUDIO - MUSIC - Showroom_Start
///*****************************************************************
void Game_Audio_Music::Showroom_Start(void)
{
	//-------------------------------------------------------------
	if(!bShowroom)
	{
		iSoundStop(BG_Music);
		iSoundVolumeSet(Showroom_Music,gVolumeMusic * 0.9f);
		iSoundPlay(Showroom_Music,0,true);

		bShowroom = true;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - AUDIO - MUSIC - Showroom_Stop
///*****************************************************************
void Game_Audio_Music::Showroom_Stop(void)
{
	//-------------------------------------------------------------
	if(bShowroom)
	{
		iSoundStop(Showroom_Music);
		iSoundPlay(BG_Music,0,true);

		bShowroom = false;
	}
	//-------------------------------------------------------------
}
