//-----------------------------------------------------------------
// About:
//
// name: "Game_Global_Text_Description.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
// usage: Updates/Provides a Text description to Global Values
//
// device input: none.
//
// todo:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Global_Text_Description.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - TEXT - CONSTRUCTORS
///*****************************************************************
Game_Global_Text_Description::Game_Global_Text_Description(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}

Game_Global_Text_Description::~Game_Global_Text_Description(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXT - CREATE
///*****************************************************************
void Game_Global_Text_Description::Create(void)
{
	//-------------------------------------------------------------
	Update();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXT - UPDATE
///*****************************************************************
void Game_Global_Text_Description::Update(void)
{
	//-------------------------------------------------------------
	//AI DIFFICULTY
	if(gAiDifficuty <= 0){gInfoAiDifficulty = "Easy";}
	else if(gAiDifficuty==1){gInfoAiDifficulty = "Normal";}
	else if(gAiDifficuty==2){gInfoAiDifficulty = "Hard";}
	else if(gAiDifficuty==3){gInfoAiDifficulty = "Extreme";}
	else if(gAiDifficuty==4){gInfoAiDifficulty = "@-'-,--";}

	//SPEED CLASS
	if(gSpeedClass <= 0){gInfoSpeedClass = "250cc - Sapphire";}
	else if(gSpeedClass==1){gInfoSpeedClass = "500cc - Eclipse";}
	else if(gSpeedClass==2){gInfoSpeedClass = "750cc - Fusion";}
	else if(gSpeedClass==3){gInfoSpeedClass = "1000cc - Infinity";}

	//GAME MODE
	if(gGameModeChange<=0){gInfoGameMode = "Time Trial";}
	else if(gGameModeChange==1){gInfoGameMode = "Pure Race";}
	else if(gGameModeChange==2){gInfoGameMode = "Weapon Race";}
	else if(gGameModeChange==3){gInfoGameMode = "Elimination";}
	else if(gGameModeChange==4){gInfoGameMode = "Annihilation";}
	else if(gGameModeChange==5){gInfoGameMode = "DM Arena";}

	//TRACK NAME
	if(gGameStateChange<=1){gInfoTrack = "Volex Peaks";}
	else if(gGameStateChange==2){gInfoTrack = "Silence";}
	else if(gGameStateChange==3){gInfoTrack = "Phantom";}
	else if(gGameStateChange==10){gInfoTrack = "Arena - Rez";}

	//TRACK REVERSE SETTING
	gInfoTrackReverse = "Reversed";
	if(gTrackReverse==0){gInfoTrackReverse = "Normal";}

	//PLAYER PREFERED CAMERA
	gInfoPlayerCam = "Tr-Zero";
	if(gCam_PlayerPreset==1){gInfoPlayerCam = "Tr-Zero High";}
	else if(gCam_PlayerPreset==2){gInfoPlayerCam = "Vintage";}
	else if(gCam_PlayerPreset==3){gInfoPlayerCam = "Internal";}

	//Game Region
	if(gGameRegion==0)
	{
		//gGameRegionInfo = "America";
		gGameRegionInfo = "Global Test";
	}
	else if(gGameRegion==1)
	{
		gGameRegionInfo = "Europe";
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXT - PositionReadout
///*****************************************************************
string Game_Global_Text_Description::PositionReadout(int position)
{
	//-------------------------------------------------------------
	char Output[16];
	//-------------------------------------------------------------

	if(position==1)		{sprintf_s(Output,"%dst",position);}
	else if(position==2){sprintf_s(Output,"%dnd",position);}
	else if(position==3){sprintf_s(Output,"%drd",position);}
	else if(position<21){sprintf_s(Output,"%dth",position);}
	else if(position==21){sprintf_s(Output,"%dst",position);}
	else if(position==22){sprintf_s(Output,"%dnd",position);}
	else if(position==23){sprintf_s(Output,"%drd",position);}
	else if(position<31){sprintf_s(Output,"%dth",position);}
	else if(position==31){sprintf_s(Output,"%dst",position);}
	else if(position==32){sprintf_s(Output,"%dnd",position);}
	else if(position==33){sprintf_s(Output,"%drd",position);}
	else				{sprintf_s(Output,"%dth",position);}

	return (string)Output;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXT - Weapon_Secondary_Name
///*****************************************************************
string Game_Global_Text_Description::Weapon_Secondary_Name(int Value)
{
	//-------------------------------------------------------------
	string Output = "";
	//-------------------------------------------------------------
	if(Value==0)
	{
		Output = "Fusion Missile";
	}
	else if(Value==1)
	{
		Output = "Shoxwave";
	}
	else if(Value==2)
	{
		Output = "EM Burst";
	}
	else if(Value==3)
	{
		Output = "Lancer Rail";
	}

	return Output;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXT - Weapon_Utility_Name
///*****************************************************************
string Game_Global_Text_Description::Weapon_Utility_Name(int Value)
{
	//-------------------------------------------------------------
	string Output = "";
	//-------------------------------------------------------------
	if(Value==0)
	{
		Output = "Shield Invunrability";
	}
	else if(Value==1)
	{
		Output = "AutoPilot";
	}
	else if(Value==2)
	{
		Output = "Double Damage";
	}
	else if(Value==3)
	{
		Output = "Warp";
	}

	return Output;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TEXT - Weapon_KilledBy_Name
///*****************************************************************
string Game_Global_Text_Description::Weapon_KilledBy_Name(int Value)
{
	//-------------------------------------------------------------
	string Output = "";
	//-------------------------------------------------------------
	if(Value==0)
	{
		Output = "Primary";
	}
	else if(Value>0)
	{
		Value -= 1; ///remove primary and use the standard function
		Output = Weapon_Secondary_Name(Value);
	}

	return Output;
	//-------------------------------------------------------------
}