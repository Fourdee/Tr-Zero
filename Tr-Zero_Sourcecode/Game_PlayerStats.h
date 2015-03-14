#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_PlayerStats
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//bEndRace_Applied
		bool									bEndRace_Applied;
		//End race XP info
		int										Info_Xp_Kills;
		int										Info_Xp_Position;
		bool									bInfo_Xp_LevelUp;
		int										Info_Xp_Total;
		//Stats
		unsigned long							PlayTime_Total;
		unsigned long							Kill_Total;
		unsigned long							Death_Total;
		unsigned long							Win_Total;
		unsigned long							Loss_Total;
		//upgrade points
		int										Upgrade_Points_Total;
		int										Upgrade_Points_Remaining;
		int										Upgrade_Points_Used;
		//Player Level
		int										Player_Level;
		unsigned int							Player_XP;
		unsigned int							XP_Required_Next_Level;
		float									fXp_Ai_Multi;
		//Lap times
		float									LapRecord[MAX_RECORDS_CHAPTERS][MAX_RECORDS_SPEEDCLASS][MAX_RECORDS_REVERSE];
		//---------------------------------------------------------
		//ONLINE RECORDS
		///We use MAX_RECORDS+1 (extra record is a temp holder for local player data, used in final sorting)
		unsigned long							OnlineStats_Int_Value_1[MAX_RECORDS+1];
		unsigned long							OnlineStats_Int_Value_2[MAX_RECORDS+1];
		string									OnlineStats_Name[MAX_RECORDS+1];
		//LAP Times
		float									OnlineStats_Float_Value_1[MAX_RECORDS+1];
		//---------------------------------------------------------
		//constructors
		Game_PlayerStats(void);
		~Game_PlayerStats(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Destroy(void);
		void Update_New_Xp(void);
	//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		void ZeroData(void);
		void LoadSettings(void);
		void SaveSettings(void);

		void SaveSettings_LapRecords(void);
		void LoadSettings_LapRecords(void);


		int XpForNextLevel(void);
		float Ai_Difficulty_Multiplier(void);
	//-------------------------------------------------------------
};
