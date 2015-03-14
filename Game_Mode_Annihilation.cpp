//-----------------------------------------------------------------
// About:
//
// name: "Game_Mode_Annihilation.cpp:
//
// usage: Updates Elimination Specific GameMode
//
// device input: none.
//
// todo:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Mode_Annihilation.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - MODE - ANNIHILATION - CONSTRUCTORS
///*****************************************************************
Game_Mode_Annihilation::Game_Mode_Annihilation(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Mode_Annihilation::~Game_Mode_Annihilation(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - MODE - ANNIHILATION - ZERODATA
///*****************************************************************
void Game_Mode_Annihilation::ZeroData(void)
{
	//-------------------------------------------------------------
	TimerMax = 10800;//3600 = 1 minute
	float fDifficulty = iFloatInterpolate((float)gAiDifficuty,0.0f,4.0f,5.0f,15.0f);
	KillsRequired = (int)fDifficulty;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - ANNIHILATION - CREATE
///*****************************************************************
void Game_Mode_Annihilation::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
	//Apply Global Timer
	gRaceCountdown = TimerMax;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - ANNIHILATION - UPDATE
///*****************************************************************
void Game_Mode_Annihilation::Update(void)
{
	//-------------------------------------------------------------
	//Update Timer
	if(gRaceCountdown>0 && 
		gBikesGo)
	{
		gRaceCountdown--;
	}
	//-------------------------------------------------------------
}