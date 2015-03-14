//-----------------------------------------------------------------
// About:
//
// name: "Game_Ftp.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Ftp.h"
#include "FTPClient.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - FTP - CONSTRUCTORS
///*****************************************************************
Game_Ftp::Game_Ftp(void)
{
	//-------------------------------------------------------------
	//Obtain My IP ADDRESS (Only needs to run once at launch)
	//IpAddressMine = iNetExternalIp();
	//Host Nat status - Activated when client deletes my game.
	bHostNatFailed = false;
	bHostNatFailed_NoGamesInform = false;
	//-------------------------------------------------------------
	//Server File Paths
	///MOTD
	Server_MOTD					= "/trzero_masterserver/#MOTD.ini";
	Local_MOTD					= "trzero_res\\settings\\#Network\\#MOTD.ini";

	///Feedback
	Server_FEEDBACK				= "/trzero_masterserver/#feedback/debug";
	if(gReleaseBuild)
	{
		Server_FEEDBACK			= "/trzero_masterserver/#feedback/live";
	}
	Local_FEEDBACK				= "trzero_res\\settings\\#Network\\feedback.ini";

	///Stats
	Server_STATS				= "/trzero_masterserver/#teststats/debug";
	if(gReleaseBuild)
	{
		Server_STATS			= "/trzero_masterserver/#teststats/live";
	}
	Local_STATS					= "trzero_res\\settings\\#Network\\stats.txt";

	///Games
	Server_GAME					= "/trzero_masterserver/#games/debug";
	if(gReleaseBuild)
	{
		Server_GAME				= "/trzero_masterserver/#games/live";
	}
	Local_GAME					= "trzero_res\\settings\\#Network\\game.bin";

	//RECORDS
	///Kills and Deaths
	Server_RECORDS_KD				= "/trzero_masterserver/#records/debug/Records_KD.bin";
	if(gReleaseBuild)
	{
		Server_RECORDS_KD			= "/trzero_masterserver/#records/live/Records_KD.bin";
	}
	Local_RECORDS_KD				= "trzero_res\\settings\\#Network\\Records_KD.bin";

	///Wins and Losses
	Server_RECORDS_WL				= "/trzero_masterserver/#records/debug/Records_WL.bin";
	if(gReleaseBuild)
	{
		Server_RECORDS_WL			= "/trzero_masterserver/#records/live/Records_WL.bin";
	}
	Local_RECORDS_WL				= "trzero_res\\settings\\#Network\\Records_WL.bin";

	///Time Played
	Server_RECORDS_PLAYTIME			= "/trzero_masterserver/#records/debug/Records_PLAYTIME.bin";
	if(gReleaseBuild)
	{
		Server_RECORDS_PLAYTIME		= "/trzero_masterserver/#records/live/Records_PLAYTIME.bin";
	}
	Local_RECORDS_PLAYTIME			= "trzero_res\\settings\\#Network\\Records_PLAYTIME.bin";

	///Lap Records
	for(int i=0;i<MAX_RECORDS_CHAPTERS;i++)
	{
		for(int j=0;j<MAX_RECORDS_SPEEDCLASS;j++)
		{
			for(int k=0;k<MAX_RECORDS_REVERSE;k++)
			{
				sprintf_s(gCharBuffer,"/trzero_masterserver/#records/debug/Records_LAPS_%d_%d_%d.bin",i,j,k);
				Server_RECORDS_LAPS[i][j][k] = (string)gCharBuffer;

				if(gReleaseBuild)
				{
					sprintf_s(gCharBuffer,"/trzero_masterserver/#records/live/Records_LAPS_%d_%d_%d.bin",i,j,k);
					Server_RECORDS_LAPS[i][j][k] = (string)gCharBuffer;
				}
				sprintf_s(gCharBuffer,"trzero_res\\settings\\#Network\\Records_LAPS_%d_%d_%d.bin",i,j,k);
				Local_RECORDS_LAPS[i][j][k] = (string)gCharBuffer;
			}
		}
	}
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Ftp::~Game_Ftp(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - FTP - MasterServerMOTD (Check Server status, grab MOTD & Records)
///*****************************************************************
void Game_Ftp::MasterServerMOTD(void)
{
	////-------------------------------------------------------------
	//DeleteFile(Local_MOTD);
	//DeleteFile(Local_RECORDS_KD);
	//DeleteFile(Local_RECORDS_WL);
	//DeleteFile(Local_RECORDS_PLAYTIME);
	//for(int i=0;i<MAX_RECORDS_CHAPTERS;i++)
	//{
	//	for(int j=0;j<MAX_RECORDS_SPEEDCLASS;j++)
	//	{
	//		for(int k=0;k<MAX_RECORDS_REVERSE;k++)
	//		{
	//			DeleteFile((char*)Local_RECORDS_LAPS[i][j][k].c_str());
	//		}
	//	}
	//}
	//gMasterServerOnline = false;
	////-------------------------------------------------------------
	////FTP - Grab MOTD
	//nsFTP::CFTPClient ftpClient;
	//nsFTP::CLogonInfo logonInfo(_T(FTP_ADDRESS),FTP_PORT,_T(FTP_USER),_T(FTP_PW));

	///// connect to server
	//ftpClient.Login(logonInfo);
	//
	/////Check connection Status
	//bFtpOnline = ftpClient.IsConnected();
	//if(bFtpOnline)
	//{
	//	//Apply server status
	//	gMasterServerOnline = true;	
	//	/// get directory listing
	//	nsFTP::TFTPFileStatusShPtrVec list;
	//	//Download MOTD
	//	ftpClient.List(_T("/trzero_masterserver"), list);
	//	ftpClient.DownloadFile(_T(Server_MOTD), _T(Local_MOTD));
	//	if(iFileExists(Local_MOTD))
	//	{
	//		char TempString[1024];

	//		if(gReleaseBuild)
	//		{
	//			GetPrivateProfileString("MOTD","release","File Error release MOTD",TempString,_MAX_PATH,Local_MOTD);
	//			gMasterServerMOTD = (string)TempString;
	//			GetPrivateProfileString("VERSION","release","File Error debug VERSION",TempString,_MAX_PATH,Local_MOTD);
	//			gMasterServerBuildVersion = (string)TempString;
	//		}
	//		else
	//		{
	//			GetPrivateProfileString("MOTD","debug","File Error debug MOTD",TempString,_MAX_PATH,Local_MOTD);
	//			gMasterServerMOTD = (string)TempString;
	//			GetPrivateProfileString("VERSION","debug","File Error debug VERSION",TempString,_MAX_PATH,Local_MOTD);
	//			gMasterServerBuildVersion = (string)TempString;
	//		}
	//		///Check version against client - mismatch
	//		if(gMasterServerBuildVersion!=gBuildVersion)
	//		{
	//			gMasterServerOnline = false;
	//		}
	//	}
	//	//-------------------------------------------------------------
	//	//Download Records
	//	if(gMasterServerOnline)///Requires same version
	//	{
	//		//1 KD RECORDS
	//		ftpClient.DownloadFile(_T(Server_RECORDS_KD), _T(Local_RECORDS_KD));
	//		//LoadRecords(1);

	//		//2 WL RECORDS
	//		ftpClient.DownloadFile(_T(Server_RECORDS_WL), _T(Local_RECORDS_WL));
	//		//LoadRecords(2);

	//		//3 PLAYTIME RECORDS
	//		ftpClient.DownloadFile(_T(Server_RECORDS_PLAYTIME), _T(Local_RECORDS_PLAYTIME));
	//		//LoadRecords(3);

	//		//4 Lap Records
	//		for(int i=0;i<MAX_RECORDS_CHAPTERS;i++)
	//		{
	//			if(i>0)///Skip menu chapter
	//			{
	//				for(int j=0;j<MAX_RECORDS_SPEEDCLASS;j++)
	//				{
	//					for(int k=0;k<MAX_RECORDS_REVERSE;k++)
	//					{
	//						ftpClient.DownloadFile(_T((char*)Server_RECORDS_LAPS[i][j][k].c_str()), _T((char*)Local_RECORDS_LAPS[i][j][k].c_str()));
	//					}
	//				}
	//			}
	//		}
	//	}
	//	// disconnect
	//	ftpClient.Logout();
	//}
	//-------------------------------------------------------------
	///Obtain Master Server Final Flag
	if(!gMasterServerOnline)
	{
		gMasterServerMOTD = "Master Server Offline";
		if(gMasterServerBuildVersion!=gBuildVersion)
		{
			if(gReleaseBuild)
			{
				gMasterServerMOTD = "This version of Tr-Zero is out of Date. Please update http://www.indiedb.com/games/tr-zero";
			}
			else
			{
				gMasterServerMOTD = "Debug Internal Version out of date. Please update from dropbox";
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - FTP - CreateGame
///*****************************************************************
void Game_Ftp::CreateGame(void)
{
	//-------------------------------------------------------------
	//Create the game - Add FTP file
	if(!bGameCreated)
	{
		//Save IP
		HANDLE hFile; 
		DWORD dwDone; 
		char filepath[1024];

		strcpy_s(filepath,Local_GAME);
		iGlobalPathMake(filepath);

		hFile = CreateFile(filepath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		if(hFile != INVALID_HANDLE_VALUE)
		{
			//---------------------------------------------------------
			WriteFile(hFile,&IpAddressMine,sizeof(string),&dwDone,NULL);
			//---------------------------------------------------------
			CloseHandle(hFile); 
		}
		//-------------------------------------------------------------
		//FTP - Upload IP File
		nsFTP::CFTPClient ftpClient;
		nsFTP::CLogonInfo logonInfo(_T(FTP_ADDRESS),FTP_PORT,_T(FTP_USER),_T(FTP_PW));

		/// connect to server
		ftpClient.Login(logonInfo);
		
		///Check connection Status
		bFtpOnline = ftpClient.IsConnected();

		/// get directory listing
		nsFTP::TFTPFileStatusShPtrVec list;
		ftpClient.List(_T(Server_GAME), list);

		///Upload File
		char outbuffer[1024];
		sprintf_s(outbuffer,"%s/game_%i.bin",Server_GAME,gGameRegion);
		ftpClient.UploadFile(_T(Local_GAME), _T(outbuffer));

		/// disconnect
		ftpClient.Logout();
		bGameCreated = true;
	}
	//-------------------------------------------------------------
	//Check file exists (failed connect clients will delete file - EG: NO PORT FORWARDING)
	Timer_HostCheckGameExists++;
	if(Timer_HostCheckGameExists>=Timer_HostCheckGameExistsMAX)
	{
		Timer_HostCheckGameExists = 0;

		nsFTP::CFTPClient ftpClient;
		nsFTP::CLogonInfo logonInfo(_T(FTP_ADDRESS),FTP_PORT,_T(FTP_USER),_T(FTP_PW));

		/// connect to server
		ftpClient.Login(logonInfo);
		
		///Check connection Status
		bFtpOnline = ftpClient.IsConnected();

		/// get directory listing
		nsFTP::TFTPFileStatusShPtrVec list;
		ftpClient.List(_T(Server_GAME), list);

		char inbuffer[1024];
		sprintf_s(inbuffer,"%s/game_%i.bin",Server_GAME,gGameRegion);

		///Delete Local File
		DeleteFile(Local_GAME);

		///Download File
		ftpClient.DownloadFile(_T(inbuffer), _T(Local_GAME));

		/// disconnect
		ftpClient.Logout();
		//-------------------------------------------------------------
		//Check If File Exists (eg: Game exists)
		if(iFileExists(Local_GAME))
		{
			//Check IP matches my IP (Clients will delete my game that fail on port forwarding)
			HANDLE hFile; 
			DWORD dwDone; 
			char filepath[1024];

			strcpy_s(filepath,Local_GAME);
			iGlobalPathMake(filepath);

			hFile = CreateFile(filepath,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if(hFile != INVALID_HANDLE_VALUE)
			{
				//---------------------------------------------------------
				ReadFile(hFile,&IpAddressRecieved,sizeof(string),&dwDone,NULL);
				//---------------------------------------------------------
				
				CloseHandle(hFile); 
			}
			//File IP does not match mine - Game has been deleted due to NAT
			if(IpAddressRecieved!=IpAddressMine)
			{
				bHostNatFailed = true;
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - FTP - DeleteGame (Clear game from server)
///*****************************************************************
void Game_Ftp::DeleteGame(void)
{
	//-------------------------------------------------------------
	if(!bGameDeleted)
	{
		//FTP - Delete IP File
		nsFTP::CFTPClient ftpClient;
		nsFTP::CLogonInfo logonInfo(_T(FTP_ADDRESS),FTP_PORT,_T(FTP_USER),_T(FTP_PW));

		/// connect to server
		ftpClient.Login(logonInfo);
		
		///Check connection Status
		bFtpOnline = ftpClient.IsConnected();

		/// get directory listing
		nsFTP::TFTPFileStatusShPtrVec list;
		ftpClient.List(_T(Server_GAME), list);

		char outbuffer[1024];
		sprintf_s(outbuffer,"%s/game_%i.bin",Server_GAME,gGameRegion);
		ftpClient.Delete(_T(outbuffer));

		/// disconnect
		ftpClient.Logout();
		//Game deleted
		bGameDeleted = true;
		bGameCreated = false;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - FTP - ClientUnableToConnect (Clear game from server - Due to NAT issue)
///*****************************************************************
void Game_Ftp::ClientUnableToConnect(void)
{
	//-------------------------------------------------------------
	if(!bGameDeleted)
	{
		//FTP - Delete IP File
		nsFTP::CFTPClient ftpClient;
		nsFTP::CLogonInfo logonInfo(_T(FTP_ADDRESS),FTP_PORT,_T(FTP_USER),_T(FTP_PW));

		/// connect to server
		ftpClient.Login(logonInfo);
		
		///Check connection Status
		bFtpOnline = ftpClient.IsConnected();

		/// get directory listing
		nsFTP::TFTPFileStatusShPtrVec list;
		ftpClient.List(_T(Server_GAME), list);

		///Delete file
		char outbuffer[1024];
		sprintf_s(outbuffer,"%s/game_%i.bin",Server_GAME,gGameRegion);
		ftpClient.Delete(_T(outbuffer));

		/// disconnect
		ftpClient.Logout();
		bGameDeleted = true;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - FTP - GameFound (Are there any active games on the server?)
///*****************************************************************
bool Game_Ftp::GameFound(void)
{
	//-------------------------------------------------------------
	ZeroData();
	bool bGameFound = false;
	DeleteFile(Local_GAME);
	//-------------------------------------------------------------
	//FTP
	nsFTP::CFTPClient ftpClient;
	nsFTP::CLogonInfo logonInfo(_T(FTP_ADDRESS),FTP_PORT,_T(FTP_USER),_T(FTP_PW));

	/// connect to server
	ftpClient.Login(logonInfo);
	
	///Check connection Status
	bFtpOnline = ftpClient.IsConnected();

	/// get directory listing
	nsFTP::TFTPFileStatusShPtrVec list;
	ftpClient.List(_T(Server_GAME), list);
	///Download File
	char inbuffer[1024];
	sprintf_s(inbuffer,"%s/game_%i.bin",Server_GAME,gGameRegion);
	ftpClient.DownloadFile(_T(inbuffer), _T(Local_GAME));
	/// disconnect
	ftpClient.Logout();
	//-------------------------------------------------------------
	//Check If File Exists (eg: Game exists)
	if(iFileExists(Local_GAME))
	{
		//Grab IP from file
		HANDLE hFile; 
		DWORD dwDone; 
		char filepath[1024];

		strcpy_s(filepath,Local_GAME);
		iGlobalPathMake(filepath);

		hFile = CreateFile(filepath,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if(hFile != INVALID_HANDLE_VALUE)
		{
			//---------------------------------------------------------
			//GetFileSize(
			ReadFile(hFile,&IpAddressRecieved,sizeof(string),&dwDone,NULL);
			//---------------------------------------------------------
			
			CloseHandle(hFile); 
		}
		if(IpAddressRecieved!="")
		{
			bGameFound = true;
		}
	}
	//-------------------------------------------------------------
	return bGameFound;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - FTP - UploadGameStats (End of each completed rate - Stats for ME! :D)
///*****************************************************************
void Game_Ftp::UploadGameStats(void)
{
	//-------------------------------------------------------------
	DeleteFile(Local_STATS);
	DeleteFile(Local_RECORDS_KD);
	DeleteFile(Local_RECORDS_WL);
	DeleteFile(Local_RECORDS_PLAYTIME);
	for(int i=0;i<MAX_RECORDS_CHAPTERS;i++)
	{
		for(int j=0;j<MAX_RECORDS_SPEEDCLASS;j++)
		{
			for(int k=0;k<MAX_RECORDS_REVERSE;k++)
			{
				DeleteFile((char*)Local_RECORDS_LAPS[i][j][k].c_str());
			}
		}
	}
	//-------------------------------------------------------------
	//FTP - Upload Finished Game Stats
	nsFTP::CFTPClient ftpClient;
	nsFTP::CLogonInfo logonInfo(_T(FTP_ADDRESS),FTP_PORT,_T(FTP_USER),_T(FTP_PW));

	/// connect to server
	ftpClient.Login(logonInfo);
	
	///Check connection Status
	bFtpOnline = ftpClient.IsConnected();
	if(bFtpOnline)
	{
		//Create Stat File for upload
		char TempString[1024];
		///Network
		sprintf_s(TempString,"%s",(char*)cGame_Ftp.IpAddressMine.c_str());
		WritePrivateProfileString("NETWORK","MyIp",TempString,Local_STATS);

		sprintf_s(TempString,"%s",(char*)cGame_Ftp.IpAddressRecieved.c_str());
		WritePrivateProfileString("NETWORK","TargetIp",TempString,Local_STATS);

		sprintf_s(TempString,"%d",gNumberOfClients);
		WritePrivateProfileString("NETWORK","TotalClients",TempString,Local_STATS);

		///GameType
		sprintf_s(TempString,"%s",(char*)gInfoGameMode.c_str());
		WritePrivateProfileString("GAMETYPE","GameMode",TempString,Local_STATS);

		sprintf_s(TempString,"%s",(char*)gInfoTrack.c_str());
		WritePrivateProfileString("GAMETYPE","TrackName",TempString,Local_STATS);

		sprintf_s(TempString,"%s",(char*)gInfoTrackReverse.c_str());
		WritePrivateProfileString("GAMETYPE","TrackReverse",TempString,Local_STATS);

		sprintf_s(TempString,"%s",(char*)gInfoSpeedClass.c_str());
		WritePrivateProfileString("GAMETYPE","SpeedClass",TempString,Local_STATS);

		///Ai
		sprintf_s(TempString,"%s",(char*)gInfoAiDifficulty.c_str());
		WritePrivateProfileString("AI","Difficulty",TempString,Local_STATS);

		sprintf_s(TempString,"%d",gAi_Max_Count);
		WritePrivateProfileString("AI","Total",TempString,Local_STATS);

		///Player
		sprintf_s(TempString,"%s",gPlayerName);
		WritePrivateProfileString("PLAYER","PlayerName",TempString,Local_STATS);

		sprintf_s(TempString,"%d",cGame_PlayerStats.Player_Level);
		WritePrivateProfileString("PLAYER","PlayerLevel",TempString,Local_STATS);

		sprintf_s(TempString,"%s",(char*)gInfoPlayerCam.c_str());
		WritePrivateProfileString("PLAYER","CameraPreference",TempString,Local_STATS);

		///Stats
		sprintf_s(TempString,"%d",cGame_PlayerStats.PlayTime_Total);
		WritePrivateProfileString("STATS","TotalPlayTime",TempString,Local_STATS);

		sprintf_s(TempString,"%d",cGame_PlayerStats.Kill_Total);
		WritePrivateProfileString("STATS","TotalKills",TempString,Local_STATS);

		sprintf_s(TempString,"%d",cGame_PlayerStats.Death_Total);
		WritePrivateProfileString("STATS","TotalDeaths",TempString,Local_STATS);

		sprintf_s(TempString,"%0.0f",gBikeColourUserHSV);
		WritePrivateProfileString("STATS","BikeColour",TempString,Local_STATS);

		sprintf_s(TempString,"%d",gMenuColour);
		WritePrivateProfileString("STATS","MenuColour",TempString,Local_STATS);
		
		///GFX
		sprintf_s(TempString,"%d x %d",iDisplayWidth(),iDisplayHeight());
		WritePrivateProfileString("GFX","Resolution",TempString,Local_STATS);

		sprintf_s(TempString,"%s",(gGlowEnable)?"true":"false");
		WritePrivateProfileString("GFX","gGlowEnable",TempString,Local_STATS);

		sprintf_s(TempString,"%s",(gDoFEnable)?"true":"false");
		WritePrivateProfileString("GFX","gDoFEnable",TempString,Local_STATS);

		sprintf_s(TempString,"%s",(gBlurEnable)?"true":"false");
		WritePrivateProfileString("GFX","gBlurEnable",TempString,Local_STATS);

		sprintf_s(TempString,"%s",(gFxaaEnable)?"true":"false");
		WritePrivateProfileString("GFX","gFxaaEnable",TempString,Local_STATS);

		sprintf_s(TempString,"%s",(cGame_Optimiser.bOptimiseBypass)?"true":"false");
		WritePrivateProfileString("GFX","OptimiserBypass",TempString,Local_STATS);

		///SOUND
		sprintf_s(TempString,"%0.2f",gVolumeFx);
		WritePrivateProfileString("SOUND","gVolumeFx",TempString,Local_STATS);
		
		sprintf_s(TempString,"%0.2f",gVolumeMusic);
		WritePrivateProfileString("SOUND","gVolumeMusic",TempString,Local_STATS);

		/// get directory listing
		nsFTP::TFTPFileStatusShPtrVec list;
		ftpClient.List(_T(Server_STATS), list);

		/// do file operations
		char outbuffer[1024];
		if(iNetworkIsActive())
		{
			sprintf_s(outbuffer,"%s/mp_%s.txt",Server_STATS,gPlayerName);
		}
		else
		{
			sprintf_s(outbuffer,"%s/sp_%s.txt",Server_STATS,gPlayerName);
		}
		///Delete
		ftpClient.Delete(_T(outbuffer));
		///Upload File
		ftpClient.UploadFile(_T(Local_STATS), _T(outbuffer));

		//-------------------------------------------------------------
		//Records (download/process/upload)
		if(gMasterServerOnline) ///Requires same version
		{
			//1 - KD RECORDS
			ftpClient.DownloadFile(_T(Server_RECORDS_KD), _T(Local_RECORDS_KD));
			LoadRecords(1);
			DeleteFile(Local_RECORDS_KD);

			SaveRecords(1);
			ftpClient.Delete(_T(Server_RECORDS_KD));
			ftpClient.UploadFile(_T(Local_RECORDS_KD), _T(Server_RECORDS_KD));

			//2 - WL RECORDS
			ftpClient.DownloadFile(_T(Server_RECORDS_WL), _T(Local_RECORDS_WL));
			LoadRecords(2);
			DeleteFile(Local_RECORDS_WL);

			SaveRecords(2);
			ftpClient.Delete(_T(Server_RECORDS_WL));
			ftpClient.UploadFile(_T(Local_RECORDS_WL), _T(Server_RECORDS_WL));

			//3 PLAYTIME RECORDS
			ftpClient.DownloadFile(_T(Server_RECORDS_PLAYTIME), _T(Local_RECORDS_PLAYTIME));
			LoadRecords(3);
			DeleteFile(Local_RECORDS_PLAYTIME);

			SaveRecords(3);
			ftpClient.Delete(_T(Server_RECORDS_PLAYTIME));
			ftpClient.UploadFile(_T(Local_RECORDS_PLAYTIME), _T(Server_RECORDS_PLAYTIME));

			//4 LAP RECORDS
			if(gClearOnlineRecords)
			{
				for(int i=0;i<MAX_RECORDS_CHAPTERS;i++)
				{
					for(int j=0;j<MAX_RECORDS_SPEEDCLASS;j++)
					{
						for(int k=0;k<MAX_RECORDS_REVERSE;k++)
						{
							DeleteFile((char*)Local_RECORDS_LAPS[i][j][k].c_str());

							ProcessRecords_Float(cGame_PlayerStats.LapRecord[i][j][k],(char*)Local_RECORDS_LAPS[i][j][k].c_str());
							ftpClient.Delete(_T((char*)Server_RECORDS_LAPS[i][j][k].c_str()));
							ftpClient.UploadFile(_T((char*)Local_RECORDS_LAPS[i][j][k].c_str()), _T((char*)Server_RECORDS_LAPS[i][j][k].c_str()));
						}
					}
				}
			}
			else if(gLapsUpdate)
			{
				ftpClient.DownloadFile(_T((char*)Server_RECORDS_LAPS[gGameState][gSpeedClass][gTrackReverse].c_str()), _T((char*)Local_RECORDS_LAPS[gGameState][gSpeedClass][gTrackReverse].c_str()));
				LoadRecords(4);
				DeleteFile((char*)Local_RECORDS_LAPS[gGameState][gSpeedClass][gTrackReverse].c_str());

				SaveRecords(4);
				ftpClient.Delete(_T((char*)Server_RECORDS_LAPS[gGameState][gSpeedClass][gTrackReverse].c_str()));
				ftpClient.UploadFile(_T((char*)Local_RECORDS_LAPS[gGameState][gSpeedClass][gTrackReverse].c_str()), _T((char*)Server_RECORDS_LAPS[gGameState][gSpeedClass][gTrackReverse].c_str()));
			}
		}
		// disconnect
		ftpClient.Logout();
	}
	//-------------------------------------------------------------
	//We dont want people to see the stats upload - delete it
	DeleteFile(Local_STATS);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - FTP - UploadFeedback (Feedback for the team!)
///*****************************************************************
void Game_Ftp::UploadFeedback(void)
{
	//-------------------------------------------------------------
	DeleteFile(Local_FEEDBACK);
	//-------------------------------------------------------------
	//FTP - Upload Finished Game Stats
	nsFTP::CFTPClient ftpClient;
	nsFTP::CLogonInfo logonInfo(_T(FTP_ADDRESS),FTP_PORT,_T(FTP_USER),_T(FTP_PW));

	/// connect to server
	ftpClient.Login(logonInfo);
	
	///Check connection Status
	bFtpOnline = ftpClient.IsConnected();
	if(bFtpOnline)
	{
		//Create Stat File for upload
		char TempString[1024];
		sprintf_s(TempString,"%d",gFeedback_Overall);
		WritePrivateProfileString("FEEDBACK","gFeedback_Overall",TempString,Local_FEEDBACK);
		sprintf_s(TempString,"%d",gFeedback_Gameplay);
		WritePrivateProfileString("FEEDBACK","gFeedback_Gameplay",TempString,Local_FEEDBACK);
		sprintf_s(TempString,"%d",gFeedback_Performance);
		WritePrivateProfileString("FEEDBACK","gFeedback_Performance",TempString,Local_FEEDBACK);
		sprintf_s(TempString,"%d",gFeedback_Visuals);
		WritePrivateProfileString("FEEDBACK","gFeedback_Visuals",TempString,Local_FEEDBACK);
		sprintf_s(TempString,"%d",gFeedback_Sound);
		WritePrivateProfileString("FEEDBACK","gFeedback_Sound",TempString,Local_FEEDBACK);
		sprintf_s(TempString,"%d",gFeedback_Music);
		WritePrivateProfileString("FEEDBACK","gFeedback_Music",TempString,Local_FEEDBACK);
		sprintf_s(TempString,"%d",gFeedback_Difficulty);
		WritePrivateProfileString("FEEDBACK","gFeedback_Difficulty",TempString,Local_FEEDBACK);

		/// get directory listing
		nsFTP::TFTPFileStatusShPtrVec list;
		ftpClient.List(_T(Server_FEEDBACK), list);

		/// do file operations
		char outbuffer[1024];
		sprintf_s(outbuffer,"%s/%s.txt",Server_FEEDBACK,gPlayerName);
		///Delete
		ftpClient.Delete(_T(outbuffer));
		///Upload File
		ftpClient.UploadFile(_T(Local_FEEDBACK), _T(outbuffer));
		/// disconnect
		ftpClient.Logout();
	}
	//-------------------------------------------------------------
	DeleteFile(Local_FEEDBACK);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - FTP - LoadRecords
///*****************************************************************
void Game_Ftp::LoadRecords(int RecordToLoad)
{
	//-------------------------------------------------------------
	CurrentRecord_Loaded = -1;
	//-------------------------------------------------------------
	//1 = Kills
	if(RecordToLoad==1)
	{
		if(iFileExists(Local_RECORDS_KD))
		{
			HANDLE hFile; 
			DWORD dwDone; 
			char filepath[1024];

			strcpy_s(filepath,Local_RECORDS_KD);
			iGlobalPathMake(filepath);

			hFile = CreateFile(filepath,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if(hFile != INVALID_HANDLE_VALUE)
			{
				for(int i=0;i<MAX_RECORDS;i++)
				{
					ReadFile(hFile,&cGame_PlayerStats.OnlineStats_Int_Value_1[i],sizeof(unsigned long),&dwDone,NULL);
					ReadFile(hFile,&cGame_PlayerStats.OnlineStats_Int_Value_2[i],sizeof(unsigned long),&dwDone,NULL);
					ReadFile(hFile,&cGame_PlayerStats.OnlineStats_Name[i],sizeof(string),&dwDone,NULL);
				}
				CloseHandle(hFile); 
			}
			CurrentRecord_Loaded = RecordToLoad;
		}
	}
	//2 = Wins Losses
	else if(RecordToLoad==2)
	{
		if(iFileExists(Local_RECORDS_WL))
		{
			HANDLE hFile; 
			DWORD dwDone; 
			char filepath[1024];

			strcpy_s(filepath,Local_RECORDS_WL);
			iGlobalPathMake(filepath);

			hFile = CreateFile(filepath,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if(hFile != INVALID_HANDLE_VALUE)
			{
				for(int i=0;i<MAX_RECORDS;i++)
				{
					ReadFile(hFile,&cGame_PlayerStats.OnlineStats_Int_Value_1[i],sizeof(unsigned long),&dwDone,NULL);
					ReadFile(hFile,&cGame_PlayerStats.OnlineStats_Int_Value_2[i],sizeof(unsigned long),&dwDone,NULL);
					ReadFile(hFile,&cGame_PlayerStats.OnlineStats_Name[i],sizeof(string),&dwDone,NULL);
				}
				CloseHandle(hFile); 
			}
			CurrentRecord_Loaded = RecordToLoad;
		}
	}
	//3 = Playtime Total
	else if(RecordToLoad==3)
	{
		if(iFileExists(Local_RECORDS_PLAYTIME))
		{
			HANDLE hFile; 
			DWORD dwDone; 
			char filepath[1024];

			strcpy_s(filepath,Local_RECORDS_PLAYTIME);
			iGlobalPathMake(filepath);

			hFile = CreateFile(filepath,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if(hFile != INVALID_HANDLE_VALUE)
			{
				for(int i=0;i<MAX_RECORDS;i++)
				{
					ReadFile(hFile,&cGame_PlayerStats.OnlineStats_Int_Value_1[i],sizeof(unsigned long),&dwDone,NULL);
					ReadFile(hFile,&cGame_PlayerStats.OnlineStats_Int_Value_2[i],sizeof(unsigned long),&dwDone,NULL);
					ReadFile(hFile,&cGame_PlayerStats.OnlineStats_Name[i],sizeof(string),&dwDone,NULL);
				}
				CloseHandle(hFile); 
			}
			CurrentRecord_Loaded = RecordToLoad;
		}
	}
	//4 = Lap Records
	else if(RecordToLoad==4)
	{
		int Index = gGameState;
		if(gGameState==0)//Menu
		{
			Index = gGameStateChange;
		}
		
		if(iFileExists((char*)Local_RECORDS_LAPS[Index][gSpeedClass][gTrackReverse].c_str()))
		{
			HANDLE hFile; 
			DWORD dwDone; 
			char filepath[1024];

			strcpy_s(filepath,(char*)Local_RECORDS_LAPS[Index][gSpeedClass][gTrackReverse].c_str());
			iGlobalPathMake(filepath);

			hFile = CreateFile(filepath,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if(hFile != INVALID_HANDLE_VALUE)
			{
				for(int i=0;i<MAX_RECORDS;i++)
				{
					ReadFile(hFile,&cGame_PlayerStats.OnlineStats_Float_Value_1[i],sizeof(float),&dwDone,NULL);
					ReadFile(hFile,&cGame_PlayerStats.OnlineStats_Name[i],sizeof(string),&dwDone,NULL);
				}
				CloseHandle(hFile); 
			}
			CurrentRecord_Loaded = RecordToLoad;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - FTP - SaveRecords
///*****************************************************************
void Game_Ftp::SaveRecords(int RecordToSave)
{
	//-------------------------------------------------------------
	//Reset Current Loaded Record
	CurrentRecord_Loaded = -1;
	//-------------------------------------------------------------
	//1 = KILLS & DEATHS
	if(RecordToSave==1)
	{
		ProcessRecords_Int(cGame_PlayerStats.Kill_Total,cGame_PlayerStats.Death_Total,Local_RECORDS_KD);
	}
	//2 = WINS & LOSSES
	else if(RecordToSave==2)
	{
		ProcessRecords_Int(cGame_PlayerStats.Win_Total,cGame_PlayerStats.Loss_Total,Local_RECORDS_WL);
	}
	//3 = Playtime Total
	else if(RecordToSave==3)
	{
		unsigned long PlayerLevel = cGame_PlayerStats.Player_Level;///Conversion
		ProcessRecords_Int(cGame_PlayerStats.PlayTime_Total,PlayerLevel,Local_RECORDS_PLAYTIME);
	}
	//4 = Lap Records
	else if(RecordToSave==4)
	{
		ProcessRecords_Float(cGame_PlayerStats.LapRecord[gGameState][gSpeedClass][gTrackReverse],(char*)Local_RECORDS_LAPS[gGameState][gSpeedClass][gTrackReverse].c_str());
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - FTP - ProcessRecords_Int
///*****************************************************************
void Game_Ftp::ProcessRecords_Int(unsigned long &in_value_1,
									unsigned long &in_value_2,
									char* Local_File)
{
	//-------------------------------------------------------------
	//sorting arrays
	unsigned long* SORT_Int_Value_1 = new unsigned long[MAX_RECORDS+1];
	unsigned long* SORT_Int_Value_2 = new unsigned long[MAX_RECORDS+1];
	string* SORT_Name = new string[MAX_RECORDS+1];
	bool* SORT_bAvailable = new bool[MAX_RECORDS+1];///Bool, used in sorting, stops matching data being used.
	//-------------------------------------------------------------

	for(int i=0;i<MAX_RECORDS+1;i++)
	{
		SORT_bAvailable[i] = true;
	}

	//Define Data to use
	string in_name = (string)gPlayerName;

	//Use last record for player data (temp record)
	cGame_PlayerStats.OnlineStats_Int_Value_1[MAX_RECORDS] = in_value_1;		
	cGame_PlayerStats.OnlineStats_Int_Value_2[MAX_RECORDS] = in_value_2;		
	cGame_PlayerStats.OnlineStats_Name[MAX_RECORDS] = in_name;			

	for(int i=0;i<MAX_RECORDS;i++)
	{
		///Check if i already exist in the actual list
		if(cGame_PlayerStats.OnlineStats_Name[MAX_RECORDS]==cGame_PlayerStats.OnlineStats_Name[i])
		{
			///Update my record
			if(in_value_1 >= cGame_PlayerStats.OnlineStats_Int_Value_1[i])
			{
				cGame_PlayerStats.OnlineStats_Int_Value_1[i] = in_value_1;
				cGame_PlayerStats.OnlineStats_Int_Value_2[i] = in_value_2;
			}
			///Null last record (no longer needed)
			cGame_PlayerStats.OnlineStats_Int_Value_1[MAX_RECORDS] = 0;
			cGame_PlayerStats.OnlineStats_Int_Value_2[MAX_RECORDS] = 0;
			cGame_PlayerStats.OnlineStats_Name[MAX_RECORDS] = "";			
			break;
		}
	}

	//sort all temp data
	///Apply temp records with current data
	for(int i=0;i<MAX_RECORDS+1;i++)
	{
		SORT_Int_Value_1[i] = cGame_PlayerStats.OnlineStats_Int_Value_1[i];	
		SORT_Int_Value_2[i] = cGame_PlayerStats.OnlineStats_Int_Value_2[i];	
		SORT_Name[i] = cGame_PlayerStats.OnlineStats_Name[i];			
	}
	sort(SORT_Int_Value_1, SORT_Int_Value_1 + (MAX_RECORDS+1));

	//Match names & deaths to new data
	for(int i=0;i<MAX_RECORDS+1;i++)
	{
		for(int j=0;j<MAX_RECORDS+1;j++)
		{
			if(SORT_bAvailable[j] &&
				SORT_Int_Value_1[i]==cGame_PlayerStats.OnlineStats_Int_Value_1[j])
			{
				SORT_Name[i] = cGame_PlayerStats.OnlineStats_Name[j];
				SORT_Int_Value_2[i] = cGame_PlayerStats.OnlineStats_Int_Value_2[j];
				SORT_bAvailable[j] = false;
				break;
			}
		}
	}

	//Apply to local records
	int Index = 0;
	for(int i=0;i<MAX_RECORDS;i++)
	{
		Index = MAX_RECORDS - i;///using +1 temp record
		cGame_PlayerStats.OnlineStats_Int_Value_1[i] = SORT_Int_Value_1[Index];			
		cGame_PlayerStats.OnlineStats_Int_Value_2[i] = SORT_Int_Value_2[Index];			
		cGame_PlayerStats.OnlineStats_Name[i] = SORT_Name[Index];			
	}

	//Save File
	HANDLE hFile; 
	DWORD dwDone; 
	char filepath[1024];

	strcpy_s(filepath,Local_File);
	iGlobalPathMake(filepath);

	hFile = CreateFile(filepath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		for(int i=0;i<MAX_RECORDS;i++)
		{
			///CLEAR
			if(gClearOnlineRecords)
			{
				cGame_PlayerStats.OnlineStats_Int_Value_1[i] = 0;
				cGame_PlayerStats.OnlineStats_Int_Value_2[i] = 0;
				cGame_PlayerStats.OnlineStats_Name[i] = "";
			}
			WriteFile(hFile,&cGame_PlayerStats.OnlineStats_Int_Value_1[i],sizeof(unsigned long),&dwDone,NULL);
			WriteFile(hFile,&cGame_PlayerStats.OnlineStats_Int_Value_2[i],sizeof(unsigned long),&dwDone,NULL);
			WriteFile(hFile,&cGame_PlayerStats.OnlineStats_Name[i],sizeof(string),&dwDone,NULL);
		}
		CloseHandle(hFile); 
	}
	//-------------------------------------------------------------
	//Delete temp arrays
	SAFE_DELETE_ARRAY(SORT_Int_Value_1);
	SAFE_DELETE_ARRAY(SORT_Int_Value_2);
	SAFE_DELETE_ARRAY(SORT_Name);
	SAFE_DELETE_ARRAY(SORT_bAvailable);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - FTP - ProcessRecords_Float
///*****************************************************************
void Game_Ftp::ProcessRecords_Float(float &in_value_1,
							        char* Local_File)
{
	//-------------------------------------------------------------
	//sorting arrays
	float* SORT_Float_Value_1 = new float[MAX_RECORDS+1];
	string* SORT_Name = new string[MAX_RECORDS+1];
	bool* SORT_bAvailable = new bool[MAX_RECORDS+1];///Bool, used in sorting, stops matching data being used.
	//-------------------------------------------------------------

	for(int i=0;i<MAX_RECORDS+1;i++)
	{
		SORT_bAvailable[i] = true;
	}

	//Define Data to use
	string in_name = (string)gPlayerName;

	//Use last record for player data (temp record)
	cGame_PlayerStats.OnlineStats_Float_Value_1[MAX_RECORDS] = in_value_1;		
	cGame_PlayerStats.OnlineStats_Name[MAX_RECORDS] = in_name;			

	for(int i=0;i<MAX_RECORDS;i++)
	{
		///Check if i already exist in the actual list
		if(cGame_PlayerStats.OnlineStats_Name[MAX_RECORDS]==cGame_PlayerStats.OnlineStats_Name[i])
		{
			///Update my record
			if(in_value_1 <= cGame_PlayerStats.OnlineStats_Float_Value_1[i])
			{
				cGame_PlayerStats.OnlineStats_Float_Value_1[i] = in_value_1;
			}
			///Null last record (no longer needed)
			cGame_PlayerStats.OnlineStats_Float_Value_1[MAX_RECORDS] = 817.0f;
			cGame_PlayerStats.OnlineStats_Name[MAX_RECORDS] = "";			
			break;
		}
	}

	//sort all temp data
	///Apply temp records with current data
	for(int i=0;i<MAX_RECORDS+1;i++)
	{
		SORT_Float_Value_1[i] = cGame_PlayerStats.OnlineStats_Float_Value_1[i];	
		SORT_Name[i] = cGame_PlayerStats.OnlineStats_Name[i];			
	}
	sort(SORT_Float_Value_1, SORT_Float_Value_1 + (MAX_RECORDS+1));

	//Match names & deaths to new data
	for(int i=0;i<MAX_RECORDS+1;i++)
	{
		for(int j=0;j<MAX_RECORDS+1;j++)
		{
			if(SORT_bAvailable[j] &&
				SORT_Float_Value_1[i]==cGame_PlayerStats.OnlineStats_Float_Value_1[j])
			{
				SORT_Name[i] = cGame_PlayerStats.OnlineStats_Name[j];
				SORT_bAvailable[j] = false;
				break;
			}
		}
	}

	//Apply to local records
	for(int i=0;i<MAX_RECORDS;i++)
	{
		cGame_PlayerStats.OnlineStats_Float_Value_1[i] = SORT_Float_Value_1[i];			
		cGame_PlayerStats.OnlineStats_Name[i] = SORT_Name[i];			
	}

	//Save File
	HANDLE hFile; 
	DWORD dwDone; 
	char filepath[1024];

	strcpy_s(filepath,Local_File);
	iGlobalPathMake(filepath);

	hFile = CreateFile(filepath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		for(int i=0;i<MAX_RECORDS;i++)
		{
			///CLEAR
			if(gClearOnlineRecords)
			{
				cGame_PlayerStats.OnlineStats_Float_Value_1[i] = 817.0f;
				cGame_PlayerStats.OnlineStats_Name[i] = "";
			}
			WriteFile(hFile,&cGame_PlayerStats.OnlineStats_Float_Value_1[i],sizeof(float),&dwDone,NULL);
			WriteFile(hFile,&cGame_PlayerStats.OnlineStats_Name[i],sizeof(string),&dwDone,NULL);
		}
		CloseHandle(hFile); 
	}
	//-------------------------------------------------------------
	//Delete temp arrays
	SAFE_DELETE_ARRAY(SORT_Float_Value_1);
	SAFE_DELETE_ARRAY(SORT_Name);
	SAFE_DELETE_ARRAY(SORT_bAvailable);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - FTP - ZeroData
///*****************************************************************
void Game_Ftp::ZeroData(void)
{
	//-------------------------------------------------------------
	IpAddressRecieved						= "";
	bFtpOnline								= true;

	Timer_HostCheckGameExistsMAX			= 600;
	Timer_HostCheckGameExists				= 0;
	bGameCreated							= false;
	bGameDeleted							= false;
	CurrentRecord_Loaded					= -1;
	//-------------------------------------------------------------
	//Clear network game files
	char outbuffer[1024];
	for(int i=0;i<gGameRegionMAX;i++)
	{
		sprintf_s(outbuffer,"trzero_res\\settings\\#Network\\game_%i.bin",i);
		DeleteFile(outbuffer);
	}
	//-------------------------------------------------------------
}