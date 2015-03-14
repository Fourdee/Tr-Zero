#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Mode_EndRace
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Data
		bool							bExit;
		int								ScoreTimer;
		int								ExitTimer;
		bool							bHideResults;
		//---------------------------------------------------------
		//constructors
		Game_Mode_EndRace(void);
		~Game_Mode_EndRace(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		//Data
		bool							bPlayerUseAiControls;
		string							sHuman_Position;
		//---------------------------------------------------------
		//functions
		void ZeroData(void);
		void PrintResults(void);
	//-------------------------------------------------------------
};