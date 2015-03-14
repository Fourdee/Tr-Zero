//-----------------------------------------------------------------
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Replay.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - REPLAY - CONSTRUCTORS
///*****************************************************************
Game_Replay::Game_Replay(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Replay::~Game_Replay(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - REPLAY - ZERODATA
///*****************************************************************
void Game_Replay::ZeroData(void)
{
	//-------------------------------------------------------------
	CurrentFrame_Timer = 0;
	State = 0; //1 = record, 2 = playback
	Seek = 0;
	File_Length = 0;
	bReplaySystemActive = false;
	//Thread Triggers
	bThread_Record = false;
	bThread_Play = false;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - REPLAY - CREATE
///*****************************************************************
void Game_Replay::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	DeleteFile("trzero_res\\settings\\replay.bin");
	//-------------------------------------------------------------
	//Use replay system?
	if(!iNetworkIsActive() &&			///Not a networked game
		gGameMode>0 &&					///Not TimeTrial
		gGameState>0)					///Not Menu
	{
		bReplaySystemActive = true;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - REPLAY - UPDATE
///*****************************************************************
void Game_Replay::Update(void)
{
	//-------------------------------------------------------------
	//Run Replay System
	if(bReplaySystemActive)
	{
		//Record 1
		if(gRaceState==1)
		{
			State = 1;///a trigger we can use
			//Record();
		}
		//Playback 2
		else if(gRaceState==2)
		{
			State = 2;///a trigger we can use
			User_ControlsInfo();
			//Playback();
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - REPLAY - RECORD
///*****************************************************************
void Game_Replay::Record(void)
{
	//-------------------------------------------------------------
	//STATE 1
	//-------------------------------------------------------------
	//FileStream
	if(gBikesGo)
	{
		//Save Bike Data Stream
		ofstream myfile("trzero_res\\settings\\replay.bin",ios::app | ios::binary);

		myfile.write((char*)&CurrentFrame_Timer,sizeof(unsigned long));
		File_Length += sizeof(unsigned long);

		myfile.write((char*)&gWeaponsEnable,sizeof(bool));
		File_Length += sizeof(bool);

		for(int i=0;i<=gAi_Max_Count;i++)
		{
			///Bike Data
			myfile.write((char*)&cGame_Bike[i].InputSpeedState,sizeof(int));
			File_Length += sizeof(int);
			myfile.write((char*)&cGame_Bike[i].fSteering,sizeof(float));
			File_Length += sizeof(float);
			myfile.write((char*)&cGame_Bike[i].bDrift,sizeof(bool));
			File_Length += sizeof(bool);
			myfile.write((char*)&cGame_Bike[i].Manager.fAcceleration_Speed,sizeof(float));
			File_Length += sizeof(float);
			myfile.write((char*)&cGame_Bike[i].Energy.fEnergy,sizeof(float));
			File_Length += sizeof(float);
			myfile.write((char*)&cGame_Bike[i].Manager.vBikeOrigin,sizeof(D3DXVECTOR3));
			File_Length += sizeof(D3DXVECTOR3);
			myfile.write((char*)&cGame_Bike[i].Manager.qBikeOrigin,sizeof(D3DXQUATERNION));
			File_Length += sizeof(D3DXQUATERNION);

			///Weapon Data
			myfile.write((char*)&cGame_Bike[i].Weapons.NetFirePrimary,sizeof(int));
			File_Length += sizeof(int);
			myfile.write((char*)&cGame_Bike[i].Weapons.NetFireSecondary,sizeof(int));
			File_Length += sizeof(int);
			myfile.write((char*)&cGame_Bike[i].Weapons.NetFireUtility,sizeof(int));
			File_Length += sizeof(int);
			myfile.write((char*)&cGame_Bike[i].Weapons.NetSecondaryLockedId,sizeof(int));
			File_Length += sizeof(int);
		}
		myfile.close();
		///update frame
		CurrentFrame_Timer++;
		///Put Seek to Max Length (so we can use it to reset to 0 on 1st playback, and, use it to reset bikes)
		Seek = File_Length;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - REPLAY - PLAYBACK
///*****************************************************************
void Game_Replay::Playback(void)
{
	//-------------------------------------------------------------
	//STATE 2
	//-------------------------------------------------------------
	//FileStream
	if(gBikesGo)
	{
		//EoF - Restart
		if(Seek>=File_Length)
		{
			///Reset "non-saved" Bike System data
			for(int i=0;i<=gAi_Max_Count;i++)
			{
				cGame_Bike[i].Weapons.Reset_Replay();
				cGame_Mesh.Animator.Mode[i] = 0;
				cGame_Bike[i].RespawnTimer = 0;
				cGame_Bike[i].bRespawning = false;
				cGame_Bike[i].RespawnTimer = 0;
				cGame_RaceTracker.bBikeRacing[i] = false;
			}
			///Seek back to start of file
			Seek = 0;
		}

		//Load Data Stream
		ifstream myfile("trzero_res\\settings\\replay.bin",ios::in | ios::binary);

		myfile.seekg(Seek);
		myfile.read((char*)&CurrentFrame_Timer,sizeof(unsigned long));
		Seek += sizeof(unsigned long);

		myfile.seekg(Seek);
		myfile.read((char*)&gWeaponsEnable,sizeof(bool));
		Seek += sizeof(bool);

		for(int i=0;i<=gAi_Max_Count;i++)
		{
			///Bike Data
			myfile.seekg(Seek);
			myfile.read((char*)&cGame_Bike[i].InputSpeedState,sizeof(int));
			Seek += sizeof(int);

			myfile.seekg(Seek);
			myfile.read((char*)&cGame_Bike[i].fSteering,sizeof(float));
			Seek += sizeof(float);

			myfile.seekg(Seek);
			myfile.read((char*)&cGame_Bike[i].bDrift,sizeof(bool));
			Seek += sizeof(bool);

			myfile.seekg(Seek);
			myfile.read((char*)&cGame_Bike[i].Manager.fAcceleration_Speed,sizeof(float));
			Seek += sizeof(float);

			myfile.seekg(Seek);
			myfile.read((char*)&cGame_Bike[i].Energy.fEnergy,sizeof(float));
			Seek += sizeof(float);

			myfile.seekg(Seek);
			myfile.read((char*)&cGame_Bike[i].Manager.vBikeOrigin,sizeof(D3DXVECTOR3));
			Seek += sizeof(D3DXVECTOR3);

			myfile.seekg(Seek);
			myfile.read((char*)&cGame_Bike[i].Manager.qBikeOrigin,sizeof(D3DXQUATERNION));
			Seek += sizeof(D3DXQUATERNION);

			///Weapons
			myfile.seekg(Seek);
			myfile.read((char*)&cGame_Bike[i].Weapons.NetFirePrimary,sizeof(int));
			Seek += sizeof(int);

			myfile.seekg(Seek);
			myfile.read((char*)&cGame_Bike[i].Weapons.NetFireSecondary,sizeof(int));
			Seek += sizeof(int);

			myfile.seekg(Seek);
			myfile.read((char*)&cGame_Bike[i].Weapons.NetFireUtility,sizeof(int));
			Seek += sizeof(int);

			myfile.seekg(Seek);
			myfile.read((char*)&cGame_Bike[i].Weapons.NetSecondaryLockedId,sizeof(int));
			Seek += sizeof(int);
		}
		myfile.close();
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - REPLAY - User_ControlsInfo
///*****************************************************************
void Game_Replay::User_ControlsInfo(void)
{
	//-------------------------------------------------------------
	//User Controls+Info
	D3DXVECTOR2 vLocation = D3DXVECTOR2(9.0f,10.0f);
	iPrint3((char*)">>",cGame_Font.f30pt,&vLocation,&gMenuFontColour,gFont,false);
	vLocation.x += 1.0f;
	iPrint3((char*)"Replay",cGame_Font.f36pt,&vLocation,&gFontWhite,gFont,false);

	vLocation.y -= 1.2f;
	float fPlaybackPercent = 0.0f;
	if(Seek>0)
	{
		fPlaybackPercent = (float)Seek / (float)File_Length * 100.0f;
	}
	sprintf_s(gCharBuffer,"%0.1f%%",fPlaybackPercent);
	iPrint3(gCharBuffer,cGame_Font.f30pt,&vLocation,&gMenuFontColour,gFont,false);
	
	vLocation.y -= 0.75f;
	iPrint3((char*)"( F1 ) - Toggle Scoreboard",cGame_Font.f16pt,&vLocation,&gFontGreyDark,gFont,false);
	vLocation.y -= 0.5f;


	iPrint3((char*)"( F2 ) - Toggle Results",cGame_Font.f16pt,&vLocation,&gFontGreyDark,gFont,false);
	if(iKeyClick(DIK_F2))
	{
		cGame_Mode_Controller.EndRace.bHideResults = !cGame_Mode_Controller.EndRace.bHideResults;
	}

	vLocation.y -= 0.5f;
	iPrint3((char*)"( F5 ) - Restart Replay",cGame_Font.f16pt,&vLocation,&gFontGreyDark,gFont,false);
	if(iKeyClick(DIK_F5))
	{
		Seek = File_Length;
	}

	vLocation.y -= 0.5f;
	iPrint3((char*)"( C ) - Change Camera",cGame_Font.f16pt,&vLocation,&gFontGreyDark,gFont,false);
	//-------------------------------------------------------------
}