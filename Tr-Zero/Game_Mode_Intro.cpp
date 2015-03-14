//-----------------------------------------------------------------
// About:
//
// name: "Game_Mode_Intro.cpp:
//
// usage: Runs intro for a race, then, enables race start
//
// device input: none.
//
// todo:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Mode_Intro.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - MODE - INTRO - CONSTRUCTORS
///*****************************************************************
Game_Mode_Intro::Game_Mode_Intro(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Mode_Intro::~Game_Mode_Intro(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - MODE - INTRO - ZERODATA
///*****************************************************************
void Game_Mode_Intro::ZeroData(void)
{
	//-------------------------------------------------------------
	IntroTimer						= 0;
	IntroTimerMax					= 200;//180
	bBeginTimer						= false;
	PreDelay						= 0;
	PreDelayMax						= 120;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - INTRO - CREATE
///*****************************************************************
void Game_Mode_Intro::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - INTRO - UPDATE
///*****************************************************************
void Game_Mode_Intro::Update(void)
{
	//-------------------------------------------------------------
	//Run preintro cinematic
	if(!bBeginTimer)
	{
		D3DXVECTOR2 vInfo = D3DXVECTOR2(-14.0f,-2.0f);
		D3DXVECTOR4 vColourWhite = D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f);

		iPrint3((char*)"Track :",cGame_Font.f16pt,&vInfo,&vColourWhite,gFont,false);
		vInfo.y -= 0.75f;
		iPrint3((char*)gInfoTrack.c_str(),cGame_Font.f22pt,&vInfo,&gFontWhite,gFont,false);
		vInfo.y -= 1.5f;
		iPrint3((char*)"Mode :",cGame_Font.f16pt,&vInfo,&vColourWhite,gFont,false);
		vInfo.y -= 0.75f;
		iPrint3((char*)gInfoGameMode.c_str(),cGame_Font.f22pt,&vInfo,&gFontWhite,gFont,false);
		vInfo.y -= 1.5f;
		iPrint3((char*)"SpeedClass :",cGame_Font.f16pt,&vInfo,&vColourWhite,gFont,false);
		vInfo.y -= 0.75f;
		iPrint3((char*)gInfoSpeedClass.c_str(),cGame_Font.f22pt,&vInfo,&gFontWhite,gFont,false);
		vInfo.y -= 1.5f;
		iPrint3((char*)"Ai Difficulty :",cGame_Font.f16pt,&vInfo,&vColourWhite,gFont,false);
		vInfo.y -= 0.75f;
		iPrint3((char*)gInfoAiDifficulty.c_str(),cGame_Font.f22pt,&vInfo,&gFontWhite,gFont,false);
		vInfo.y -= 1.5f;

		//Fastest lap info
		vInfo = D3DXVECTOR2(10.0f,-6.0f);
		if(gLapsUpdate)
		{
			cGame_Hud.TimerReadOuts("Personal Best",cGame_PlayerStats.LapRecord[gGameState][gSpeedClass][gTrackReverse],vInfo);
			vInfo.y += -3.0f;
			if(gMasterServerOnline)
			{
				cGame_Hud.TimerReadOuts("World Record",cGame_PlayerStats.OnlineStats_Float_Value_1[0],vInfo);
				vInfo.y += -0.5f;
				vInfo.x += 1.25f;
				iPrint((char*)cGame_PlayerStats.OnlineStats_Name[0].c_str(),cGame_Font.f16pt,&vInfo,&gFontGreyDark,gFont2,true);
			}
		}
	}
	//-------------------------------------------------------------
	//Predelay before user able to start
	if(PreDelay<PreDelayMax)
	{
		PreDelay++;
	}
	//Start race Coundown timer when user pressed start
	else if(!bBeginTimer)
	{
		if(gNumberOfClients>0)//NETWORK START
		{
			gGammaMulti = 0.5f;
			int PlayersNotReady = 0;
			D3DXVECTOR2 vPrint = D3DXVECTOR2(-6.0f,5.0f);
			D3DXVECTOR2 vPrintStatus = D3DXVECTOR2(2.0f,5.0f);
			D3DXVECTOR4 vColour = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);

			//My Status
			vColour = D3DXVECTOR4(cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.x,cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.y,cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.z,1.0f);
			iPrint3(gPlayerName,cGame_Font.f24pt,&vPrint,&vColour,gFont2,false);
			if(gNetMeReady==0)///waiting
			{
				iPrint3((char*)"Not Ready",cGame_Font.f20pt,&vPrintStatus,&D3DXVECTOR4(1.0f,0.3f,0.0f,1.0f),gFont2,false);
				PlayersNotReady++;
			}
			else///ready
			{
				iPrint3((char*)"Ready",cGame_Font.f20pt,&vPrintStatus,&D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f),gFont2,false);

			}
			vPrint.y -= 1.0f;
			vPrintStatus.y -= 1.0f;

			//Network Status
			for(int i=0;i<gNumberOfClients;i++)
			{
				vColour = D3DXVECTOR4(cGame_Bike[i].Colour.vBikeColourTarget.x,cGame_Bike[i].Colour.vBikeColourTarget.y,cGame_Bike[i].Colour.vBikeColourTarget.z,1.0f);
				iPrint3((char*)cGame_Bike[i].Name.c_str(),cGame_Font.f24pt,&vPrint,&vColour,gFont2,false);
				if(gNetPlayerReady[i]==0)///waiting
				{
					iPrint3((char*)"Not Ready",cGame_Font.f20pt,&vPrintStatus,&D3DXVECTOR4(1.0f,0.3f,0.0f,1.0f),gFont2,false);
					PlayersNotReady++;
				}
				else///ready
				{
					iPrint3((char*)"Ready",cGame_Font.f20pt,&vPrintStatus,&D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f),gFont2,false);

				}
				vPrint.y -= 1.0f;
				vPrintStatus.y -= 1.0f;
			}
			///Local Player Info
			if(cGame_Controls.Input_Action_Start()) 
			{
				gNetMeReady++;
				if(gNetMeReady>1)
				{
					gNetMeReady = 0;
				}
			}
			if(gNetMeReady==0)
			{
				iPrint3((char*)"Not Ready - Press Start",cGame_Font.f24pt,&D3DXVECTOR2(0.0f,-8.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,true);
			}
			else
			{
				iPrint3((char*)"Waiting for Players",cGame_Font.f24pt,&D3DXVECTOR2(0.0f,-8.0f),&D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f),gFont,true);
			}
			///Server start game
			if(cGame_Network.Server.State==2 &&
				PlayersNotReady==0)
			{
				gServerState = 1;
				bBeginTimer = true;
			}

		}
		else//OFFLINE START
		{
			iPrint3((char*)"Press Start",cGame_Font.f24pt,&D3DXVECTOR2(0.0f,-8.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,true);
			if(cGame_Controls.Input_Action_Start()) 
			{
				gServerState = 1;
				bBeginTimer = true;
			}
		}

	}
	else if(bBeginTimer)
	{
		if(IntroTimer < IntroTimerMax)
		{
			IntroTimer++;
		}
		else
		{
			gRaceState = 1;
			gBikesGo = true;
		}
	}
	//-------------------------------------------------------------
}