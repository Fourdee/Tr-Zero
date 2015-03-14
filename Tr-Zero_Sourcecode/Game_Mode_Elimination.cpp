//-----------------------------------------------------------------
// About:
//
// name: "Game_Mode_Elimination.cpp:
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
#include "Game_Mode_Elimination.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - MODE - ELIMINATION - CONSTRUCTORS
///*****************************************************************
Game_Mode_Elimination::Game_Mode_Elimination(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Mode_Elimination::~Game_Mode_Elimination(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - MODE - ELIMINATION - ZERODATA
///*****************************************************************
void Game_Mode_Elimination::ZeroData(void)
{
	//-------------------------------------------------------------
	EliminationApplied = false;
	CurrentLapCheck = 2;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - ELIMINATION - CREATE
///*****************************************************************
void Game_Mode_Elimination::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - ELIMINATION - UPDATE
///*****************************************************************
void Game_Mode_Elimination::Update(void)
{
	//-------------------------------------------------------------
	int EliminateId = -1;
	int LapAheadTotal = 0;

	//Begin
	if(cGame_RaceTracker.Total_AliveBikes>1)
	{
		//Find the x who needs eliminating
		for(int i=0;i<=gAi_Max_Count;i++)
		{
			if(cGame_RaceTracker.Position_Current[i] == cGame_RaceTracker.Total_AliveBikes)
			{
				EliminateId = i;
			}
		}
		//Check how many are a lap ahead
		for(int i=0;i<=gAi_Max_Count;i++)
		{
			if(i!=EliminateId &&
				cGame_RaceTracker.Lap_Current[i] >= CurrentLapCheck)
			{
				LapAheadTotal++;
			}
		}
		//When number of bikes on next lap matches alive, eliminiate
		if(LapAheadTotal==cGame_RaceTracker.Total_AliveBikes-1)
		{
			EliminationApplied = true;
		}

		//Eliminate
		if(EliminationApplied)
		{
			if(EliminateId==gAi_Max_Count)
			{
				cGame_Bike[gAi_Max_Count].Energy.fEnergy = -1.0f;
				cGame_Bike[gAi_Max_Count].Energy.bAlive = false;
			}
			else
			{
				cGame_Bike[EliminateId].Energy.fEnergy = -1.0f;
				cGame_Bike[EliminateId].Energy.bAlive = false;
			}
			CurrentLapCheck++;
			EliminationApplied = false;
		}
	}
	//-------------------------------------------------------------
}