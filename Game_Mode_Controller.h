#pragma once
//-----------------------------------------------------------------
#include "Game_Mode_WeaponsEnabler.h"
#include "Game_Mode_WeaponsPickup.h"
#include "Game_Mode_UtilityPickup.h"
#include "Game_Mode_BoostEnabler.h"
#include "Game_Mode_EnergyPickup.h"
#include "Game_Mode_Intro.h"
#include "Game_Mode_EndRace.h"
#include "Game_Mode_Elimination.h"
#include "Game_Mode_Annihilation.h"
#include "Game_Mode_Arena.h"
//-----------------------------------------------------------------
class Game_Mode_Controller
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Weapons Enabler
		Game_Mode_WeaponsEnabler				WeaponsEnabler;
		//Weapons Pickup
		Game_Mode_WeaponsPickup					WeaponsPickup;
		//Boost Enabler
		Game_Mode_BoostEnabler					BoostEnabler;
		//Weapons Pickup
		Game_Mode_EnergyPickup					EnergyPickup;
		//Utility Pickup
		Game_Mode_UtilityPickup					UtilityPickup;
		//Intro
		Game_Mode_Intro							Intro;
		//End Race
		Game_Mode_EndRace						EndRace;
		//Elimination Mode
		Game_Mode_Elimination					Elimination;
		//Annihilation Mode
		Game_Mode_Annihilation					Annihilation;
		//Net Arena Mode
		Game_Mode_Arena						Arena;
		//---------------------------------------------------------
		//constructors
		Game_Mode_Controller(void);
		~Game_Mode_Controller(void);
		//---------------------------------------------------------
		//functions
		void ApplyNewGlobalFlags(void);
		void Create(void);
		void Update(void);
		void Destroy(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		//functions
		void GlobalMonitor(void);
		void NetworkMonitor(void);
		int TotalLaps(void);
	//-------------------------------------------------------------
};
