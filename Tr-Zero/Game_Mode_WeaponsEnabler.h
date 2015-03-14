#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Mode_WeaponsEnabler
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Activate Timer
		int									EnableTimer;
		int									EnableTimerMax;
		//---------------------------------------------------------
		//constructors
		Game_Mode_WeaponsEnabler(void);
		~Game_Mode_WeaponsEnabler(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
	//-------------------------------------------------------------
};
