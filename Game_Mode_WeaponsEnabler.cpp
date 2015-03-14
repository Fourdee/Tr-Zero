//-----------------------------------------------------------------
// About:
//
// name: "Game_WeaponsEnabler.cpp:
//
// usage: Actives Weapons for track/game type
//
// device input: none.
//
// todo:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Mode_WeaponsEnabler.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - MODE - WEAPONSENABLER - CONSTRUCTORS
///*****************************************************************
Game_Mode_WeaponsEnabler::Game_Mode_WeaponsEnabler(void)
{
	//-------------------------------------------------------------
	EnableTimer = 0;
	EnableTimerMax = 0;
	//-------------------------------------------------------------
}

Game_Mode_WeaponsEnabler::~Game_Mode_WeaponsEnabler(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - WEAPONSENABLER - CREATE
///*****************************************************************
void Game_Mode_WeaponsEnabler::Create(void)
{
	//-------------------------------------------------------------
	EnableTimer = 0;
	//EnableTimerMax = 600; //10seconds
	EnableTimerMax = 600; 
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - WEAPONSENABLER - UPDATE
///*****************************************************************
void Game_Mode_WeaponsEnabler::Update(void)
{
	//-------------------------------------------------------------
	if(!gWeaponsEnable && gBikesGo)
	{
		if(EnableTimer<EnableTimerMax)
		{
			EnableTimer++;
		}
		else
		{
			gWeaponsEnable = true;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - WEAPONSENABLER - DESTROY
///*****************************************************************
void Game_Mode_WeaponsEnabler::Destroy(void)
{
	//-------------------------------------------------------------
	EnableTimer = 0;
	EnableTimerMax = 0;
	//-------------------------------------------------------------
}