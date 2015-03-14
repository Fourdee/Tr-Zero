#pragma once
//-----------------------------------------------------------------
#define _WINSOCK_DEPRECATED_NO_WARNINGS
//Defines
#define FTP_ADDRESS "fuzon-uk.no-ip.biz"
#define FTP_USER "root"
#define FTP_PW "trigger01"
#define FTP_PORT 21

///RECORDS
#define MAX_RECORDS 50

#define MAX_RECORDS_CHAPTERS 4
#define MAX_RECORDS_SPEEDCLASS 4
#define MAX_RECORDS_REVERSE 2
//-----------------------------------------------------------------
class Game_Ftp
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//FTP STATUS
		bool						bFtpOnline;

		//Incomming String
		string						IpAddressRecieved;
		string						IpAddressMine;
		//Host Nat Status (eg: client deleted game due to connection failure)
		bool						bHostNatFailed;
		bool						bHostNatFailed_NoGamesInform;
		//RECORDS
		int							CurrentRecord_Loaded;
		///Kills and Deaths
		char*						Server_RECORDS_KD;
		char*						Local_RECORDS_KD;
		///Wins and Losses
		char*						Server_RECORDS_WL;
		char*						Local_RECORDS_WL;
		///Time Played
		char*						Server_RECORDS_PLAYTIME;
		char*						Local_RECORDS_PLAYTIME;
		///Lap Records
		string						Server_RECORDS_LAPS[MAX_RECORDS_CHAPTERS][MAX_RECORDS_SPEEDCLASS][MAX_RECORDS_REVERSE];
		string						Local_RECORDS_LAPS[MAX_RECORDS_CHAPTERS][MAX_RECORDS_SPEEDCLASS][MAX_RECORDS_REVERSE];
		//---------------------------------------------------------
		//constructors
		Game_Ftp(void);
		~Game_Ftp(void);
		//---------------------------------------------------------
		//functions
		void MasterServerMOTD(void);
		bool GameFound(void);
		void CreateGame(void);
		void DeleteGame(void);
		void ClientUnableToConnect(void);
		///Stats for me!
		void UploadGameStats(void);
		void UploadFeedback(void);
		///NET RECORDS
		void LoadRecords(int RecordToLoad);
		void SaveRecords(int RecordToSave);

		void ZeroData(void);

		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		int						Timer_HostCheckGameExists;
		int						Timer_HostCheckGameExistsMAX;
		//Game flags
		bool					bGameCreated;
		bool					bGameDeleted;
		//Unique ID (used by host, create once)
		bool					bUniqueIdGenerated;
		//Server File Paths/Locations
		///MOTD
		char*					Server_MOTD;
		char*					Local_MOTD;
		///Feedback
		char*					Server_FEEDBACK;
		char*					Local_FEEDBACK;
		///Stats
		char*					Server_STATS;
		char*					Local_STATS;
		///Games
		char*					Server_GAME;
		char*					Local_GAME;
		//---------------------------------------------------------
		void ProcessRecords_Int(unsigned long &in_value_1,
								unsigned long &in_value_2,
								char* Local_File);
		void ProcessRecords_Float(float &in_value_1,
							      char* Local_File);
		//---------------------------------------------------------
	//-------------------------------------------------------------
};
