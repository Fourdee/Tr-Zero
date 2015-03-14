#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Input_xbox360controller
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		GAMEPAD_XBOX360_CONTROLLER* Gamepad;
		int GamepadsConnected;
		//Buttons
		bool							bAcell;
		bool							bBreak;
		bool							bBoost;
		bool							bCamera;
		bool							bColour;
		bool							bStart;
		bool							bSelect;
		bool							bPrimary;
		bool							bSecondary;
		bool							bUtility;
		//---------------------------------------------------------
		//constructors
		Game_Input_xbox360controller(void);
		~Game_Input_xbox360controller(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
	//-------------------------------------------------------------
};
