#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Replay
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//State
		int									State;
		bool								bReplaySystemActive;
		//Thread Triggers
		bool								bThread_Record;
		bool								bThread_Play;
		//---------------------------------------------------------
		//constructors
		Game_Replay(void);
		~Game_Replay(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Record(void);
		void Playback(void);
	//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		///FileStream
		unsigned long						Seek;
		unsigned long						File_Length;
		unsigned long						CurrentFrame_Timer;
		///
		//---------------------------------------------------------
		//functions
		void ZeroData(void);
		void User_ControlsInfo(void);
	//---------------------------------------------------------
	//-------------------------------------------------------------
};
