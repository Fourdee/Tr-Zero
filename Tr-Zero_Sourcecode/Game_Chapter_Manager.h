#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Chapter_Manager
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Threaded Load/Destroy States
		int										tLoadState;
		int										tDestroyState;
		//---------------------------------------------------------
		//constructors
		Game_Chapter_Manager(void);
		~Game_Chapter_Manager(void);
		//---------------------------------------------------------
		//functions
		void Load(void);
		void Update(void);
		void Destroy(void);
		//---------------------------------------------------------
	//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		void LoadBoot(void);
		void Update_CoreGame(void);
		//---------------------------------------------------------
	//-------------------------------------------------------------
};
