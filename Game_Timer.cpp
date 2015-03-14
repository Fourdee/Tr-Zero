//-----------------------------------------------------------------
// About:
//
// name: "Game_Timer.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
// All Global timer functions/vars
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Timer.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - TIMER - CONSTRUCTORS
///*****************************************************************
Game_Timer::Game_Timer(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Timer::~Game_Timer(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - TIMER - ZeroData
///*****************************************************************
void Game_Timer::ZeroData(void)
{
	//-------------------------------------------------------------
	OneSecond			= 0;
	bOneSecond			= false;

	bRegenTimer			= false;

	SessionTime			= 0;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TIMER - CREATE
///*****************************************************************
void Game_Timer::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TIMER - UPDATE
///*****************************************************************
void Game_Timer::Update(void)
{
	//-------------------------------------------------------------
	//Core Timer - always active (one second / assuming 60fps)
	bOneSecond = false;
	OneSecond++;
	///Regen
	bRegenTimer = false;

	if(OneSecond==60)
	{
		///Regen Timer - Active inrace
		if(gBikesGo && gRaceState >= 1)
		{
			bRegenTimer = true;
		}
		///Total Play Time
		SessionTime++;
		//Core Timer - always active (one second)
		bOneSecond = true;
		OneSecond = 0;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TIMER - DESTROY
///*****************************************************************
void Game_Timer::Destroy(void)
{
	//-------------------------------------------------------------
	//Null
	//-------------------------------------------------------------
}