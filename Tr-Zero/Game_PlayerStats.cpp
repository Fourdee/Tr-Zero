//-----------------------------------------------------------------
// About:
//
// name: "Game_PlayerStats.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
// Complete save file for player
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_PlayerStats.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - PLAYERSTATS - CONSTRUCTORS
///*****************************************************************
Game_PlayerStats::Game_PlayerStats(void)
{
	//-------------------------------------------------------------
	//NETWORK RECORDS
	for(int i=0;i<MAX_RECORDS+1;i++)
	{
		OnlineStats_Int_Value_1[i] = 0;
		OnlineStats_Int_Value_2[i] = 0;
		OnlineStats_Name[i] = "";

		OnlineStats_Float_Value_1[i] = 817.0f;
	}
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_PlayerStats::~Game_PlayerStats(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PLAYERSTATS - ZeroData
///*****************************************************************
void Game_PlayerStats::ZeroData(void)
{
	//-------------------------------------------------------------
	//bEndRace_Applied state
	bEndRace_Applied	= false;
	//End race XP info
	Info_Xp_Kills		= 0;
	Info_Xp_Position	= 0;
	bInfo_Xp_LevelUp	= false;
	//Stats
	PlayTime_Total		= 0;
	Kill_Total			= 0;
	Death_Total			= 0;
	Win_Total			= 0;
	Loss_Total			= 0;

	//upgrade points
	Upgrade_Points_Total		= 0;
	Upgrade_Points_Remaining	= 0;
	Upgrade_Points_Used			= 0;
	//Player Level
	Player_Level				= 0;
	Player_XP					= 0;
	XP_Required_Next_Level		= XpForNextLevel();
	fXp_Ai_Multi				= Ai_Difficulty_Multiplier(); 

	//-------------------------------------------------------------
	//Lap Records
	for(int i=0;i<MAX_RECORDS_CHAPTERS;i++)
	{
		for(int j=0;j<MAX_RECORDS_SPEEDCLASS;j++)
		{
			for(int k=0;k<MAX_RECORDS_REVERSE;k++)
			{
				LapRecord[i][j][k] = 817.123f;
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - PLAYERSTATS - CREATE
///*****************************************************************
void Game_PlayerStats::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
	//Load Saved Data
	LoadSettings();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - PLAYERSTATS - DESTROY
///*****************************************************************
void Game_PlayerStats::Destroy(void)
{
	//-------------------------------------------------------------
	//Apply new stats
	///Player Total Playtime
	PlayTime_Total		+= cGame_Timer.SessionTime;
	///kd
	Kill_Total			+= cGame_Bike[gAi_Max_Count].Weapons.TotalKills;
	Death_Total			+= cGame_Bike[gAi_Max_Count].Weapons.TotalDeaths;
	///Race win/loss
	if(gGameState>0)
	{
		if(gRaceWin)
		{
			Win_Total++;
		}
		else
		{
			Loss_Total++;
		}
	}
	//-------------------------------------------------------------
	//Save user data
	SaveSettings();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - PLAYERSTATS - Update_New_Xp
///*****************************************************************
void Game_PlayerStats::Update_New_Xp(void)
{
	//-------------------------------------------------------------
	//Global
	///Xp to add float
	const float fKill_Xp_Multi = 25.0f;
	float newXP = 0.0f;
	float Position = 0.0f;
	//-------------------------------------------------------------
	//Race Specific
	if(gGameMode==1)//Normal Race
	{
		///Add race win
		if(gRaceWin)
		{
			///add Position
			Position = iFloatInterpolate((float)cGame_RaceTracker.Position_Current[gAi_Max_Count],1.0f,40.0f,400.0f,0.0f);
			newXP += Position;
		}
	}
	else if(gGameMode==2)//Normal Weapon Race
	{
		///Add race win
		if(gRaceWin)
		{
			///add Position
			Position = iFloatInterpolate((float)cGame_RaceTracker.Position_Current[gAi_Max_Count],1.0f,40.0f,300.0f,0.0f);
			newXP += Position;
		}
		///add Kills
		newXP += (float)cGame_Bike[gAi_Max_Count].Weapons.TotalKills * fKill_Xp_Multi;
	}
	else if(gGameMode==3)//Elimination
	{
		///add Position
		Position = iFloatInterpolate((float)cGame_RaceTracker.Position_Current[gAi_Max_Count],1.0f,6.0f,250.0f,0.0f);
		newXP += Position;
	}
	else if(gGameMode==4)//Annihilation
	{
		///Add race win
		if(gRaceWin)
		{
			///add Position
			Position = iFloatInterpolate((float)cGame_RaceTracker.Position_Current[gAi_Max_Count],1.0f,40.0f,150.0f,0.0f);
			newXP += Position;
		}
		///add Kills
		newXP += (float)cGame_Bike[gAi_Max_Count].Weapons.TotalKills * fKill_Xp_Multi;
	}
	else if(gGameMode==5)//Arena
	{
		///add Position
		Position = iFloatInterpolate((float)cGame_RaceTracker.Position_Current[gAi_Max_Count],1.0f,40.0f,150.0f,0.0f);
		newXP += Position;
		///add Kills
		newXP += (float)cGame_Bike[gAi_Max_Count].Weapons.TotalKills * fKill_Xp_Multi;
	}
	//-------------------------------------------------------------
	//Multiply New XP by Ai difficulty
	newXP *= fXp_Ai_Multi;
	//-------------------------------------------------------------
	//Update info for print
	Info_Xp_Position = (int)Position;
	Info_Xp_Total = (int)newXP;
	if(gWeaponsTrackEnable)
	{
		Info_Xp_Kills = cGame_Bike[gAi_Max_Count].Weapons.TotalKills * (int)fKill_Xp_Multi;
	}
	//-------------------------------------------------------------
	//Update XP/Apply Levels
	///Apply XP
	Player_XP += (int)newXP;
	///Obtain XP required to level
	XP_Required_Next_Level = XpForNextLevel();
	///Cap player level
	if(Player_Level >= gLevelMax)
	{
		Player_XP = 1337; // ;)
	}
	///Check for level up, apply
	while(Player_XP >= XP_Required_Next_Level)
	{
		Player_XP -= XP_Required_Next_Level;
		Player_Level++;
		bInfo_Xp_LevelUp = true;
		///Apply new upgrade points
		Upgrade_Points_Total += gPointsPerLevel;
		Upgrade_Points_Remaining += gPointsPerLevel;
		///Check again for multiple level ups
		XP_Required_Next_Level = XpForNextLevel();
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PLAYERSTATS - XpForNextLevel
///*****************************************************************
int Game_PlayerStats::XpForNextLevel(void)
{
	//-------------------------------------------------------------
	float fXpRequired = iFloatInterpolate((float)Player_Level,0.0f,(float)gLevelMax,50.0f,2000.0f);
	return (int)fXpRequired;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PLAYERSTATS - Ai_Difficulty_Multiplier
///*****************************************************************
float Game_PlayerStats::Ai_Difficulty_Multiplier(void)
{
	//-------------------------------------------------------------
	///Multiply by AI difficulty
	float DifficultyMulti = iFloatInterpolate((float)gAiDifficuty,0.0f,4.0f,0.5f,2.0f);
	return DifficultyMulti;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PLAYERSTATS - LoadSettings
///*****************************************************************
void Game_PlayerStats::LoadSettings(void)
{
	//-------------------------------------------------------------
	if(iFileExists(gFilePath_Settings_PlayerStats))
	{
		HANDLE hFile; 
		DWORD dwDone; 
		char filepath[1024];

		strcpy_s(filepath,gFilePath_Settings_PlayerStats);
		iGlobalPathMake(filepath);

		hFile = CreateFile(filepath,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if(hFile != INVALID_HANDLE_VALUE)
		{
			//-----------------------------------------------------
			ReadFile(hFile,&PlayTime_Total,sizeof(unsigned long),&dwDone,NULL);
			ReadFile(hFile,&Kill_Total,sizeof(unsigned long),&dwDone,NULL);
			ReadFile(hFile,&Death_Total,sizeof(unsigned long),&dwDone,NULL);
			ReadFile(hFile,&Win_Total,sizeof(unsigned long),&dwDone,NULL);
			ReadFile(hFile,&Loss_Total,sizeof(unsigned long),&dwDone,NULL);
			//upgrade points
			ReadFile(hFile,&Upgrade_Points_Total,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&Upgrade_Points_Remaining,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&Upgrade_Points_Used,sizeof(int),&dwDone,NULL);
			//Player_Level
			ReadFile(hFile,&Player_Level,sizeof(int),&dwDone,NULL);
			ReadFile(hFile,&Player_XP,sizeof(unsigned int),&dwDone,NULL);
			ReadFile(hFile,&XP_Required_Next_Level,sizeof(unsigned int),&dwDone,NULL);
			//---------------------------------------------------------
			CloseHandle(hFile); 
		}
	}
	//-------------------------------------------------------------
	//Lap Records
	LoadSettings_LapRecords();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PLAYERSTATS - SaveSettings
///*****************************************************************
void Game_PlayerStats::SaveSettings(void)
{
	//-------------------------------------------------------------
	HANDLE hFile; 
	DWORD dwDone; 
	char filepath[1024];

	strcpy_s(filepath,gFilePath_Settings_PlayerStats);
	iGlobalPathMake(filepath);

	hFile = CreateFile(filepath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		//---------------------------------------------------------
		WriteFile(hFile,&PlayTime_Total,sizeof(unsigned long),&dwDone,NULL);
		WriteFile(hFile,&Kill_Total,sizeof(unsigned long),&dwDone,NULL);
		WriteFile(hFile,&Death_Total,sizeof(unsigned long),&dwDone,NULL);
		WriteFile(hFile,&Win_Total,sizeof(unsigned long),&dwDone,NULL);
		WriteFile(hFile,&Loss_Total,sizeof(unsigned long),&dwDone,NULL);
		//upgrade points
		WriteFile(hFile,&Upgrade_Points_Total,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&Upgrade_Points_Remaining,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&Upgrade_Points_Used,sizeof(int),&dwDone,NULL);
		//Player_Level
		WriteFile(hFile,&Player_Level,sizeof(int),&dwDone,NULL);
		WriteFile(hFile,&Player_XP,sizeof(unsigned int),&dwDone,NULL);
		WriteFile(hFile,&XP_Required_Next_Level,sizeof(unsigned int),&dwDone,NULL);
		//---------------------------------------------------------
		CloseHandle(hFile); 
	}
	//-------------------------------------------------------------
	//Lap Records
	SaveSettings_LapRecords();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PLAYERSTATS - LoadSettings_LapRecords
///*****************************************************************
void Game_PlayerStats::LoadSettings_LapRecords(void)
{
	//-------------------------------------------------------------
	if(iFileExists(gFilePath_Settings_LapRecords))
	{
		HANDLE hFile; 
		DWORD dwDone; 
		char filepath[1024];

		strcpy_s(filepath,gFilePath_Settings_LapRecords);
		iGlobalPathMake(filepath);

		hFile = CreateFile(filepath,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if(hFile != INVALID_HANDLE_VALUE)
		{
			//-----------------------------------------------------
			for(int i=0;i<MAX_RECORDS_CHAPTERS;i++)
			{
				for(int j=0;j<MAX_RECORDS_SPEEDCLASS;j++)
				{
					for(int k=0;k<MAX_RECORDS_REVERSE;k++)
					{
						ReadFile(hFile,&LapRecord[i][j][k],sizeof(float),&dwDone,NULL);
					}
				}
			}
			//---------------------------------------------------------
			CloseHandle(hFile); 
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PLAYERSTATS - SaveSettings_LapRecords
///*****************************************************************
void Game_PlayerStats::SaveSettings_LapRecords(void)
{
	//-------------------------------------------------------------
	HANDLE hFile; 
	DWORD dwDone; 
	char filepath[1024];

	strcpy_s(filepath,gFilePath_Settings_LapRecords);
	iGlobalPathMake(filepath);

	hFile = CreateFile(filepath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		//---------------------------------------------------------
		for(int i=0;i<MAX_RECORDS_CHAPTERS;i++)
		{
			for(int j=0;j<MAX_RECORDS_SPEEDCLASS;j++)
			{
				for(int k=0;k<MAX_RECORDS_REVERSE;k++)
				{
					WriteFile(hFile,&LapRecord[i][j][k],sizeof(float),&dwDone,NULL);
				}
			}
		}
		//---------------------------------------------------------
		CloseHandle(hFile); 
	}
	//-------------------------------------------------------------
}