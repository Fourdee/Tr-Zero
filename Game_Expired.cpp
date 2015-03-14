//-----------------------------------------------------------------
// About:
//
// name: "Game_Expired.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
// Checks if build has expired
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Expired.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - EXPIRED - CONSTRUCTORS
///*****************************************************************
Game_Expired::Game_Expired(void)
{
	//-------------------------------------------------------------
	Year				= 0;
	Month				= 0;
	Day					= 0;
	Year_Max			= 0;
	Month_Max			= 0;
	Day_Max				= 0;
	//-------------------------------------------------------------
}

Game_Expired::~Game_Expired(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - EXPIRED - CREATE
///*****************************************************************
void Game_Expired::Create(void)
{
	//-------------------------------------------------------------
	//Build Expire Check
	Year				= iSystemTime(0);
	Month				= iSystemTime(1);
	Day					= iSystemTime(3);
	Year_Max			= 2014;
	Month_Max			= 4;
	Day_Max				= 20;

	if(Year > Year_Max)
	{
		gBuildExpired = true;
	}
	else if(Year==Year_Max && Month > Month_Max)
	{
		gBuildExpired = true;
	}
	else if(Year==Year_Max && Month==Month_Max && Day >= Day_Max)
	{
		gBuildExpired = true;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - EXPIRED - UPDATE
///*****************************************************************
void Game_Expired::Update(void)
{
	//-------------------------------------------------------------
	iPrint((char*)"Build Expired",cGame_Font.f32pt,&D3DXVECTOR2(0.0f,0.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,true);
	static int timer = 0;
	timer++;
	if(timer >= 120)
	{
		gExitWin = true;
		cGame_Gamma_Fade.bFadeOut = true;
	}
	//-------------------------------------------------------------
}