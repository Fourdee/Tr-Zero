#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Audio_Voices
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		int									PlayTimer;
		//---------------------------------------------------------
		//constructors
		Game_Audio_Voices(void);
		~Game_Audio_Voices(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
	private:
		//---------------------------------------------------------
		//Data
		float								fVoiceVolume;
		int									PlayTimerMax;
		//---------------------------------------------------------
		//Utility
		SOUND*								ShieldInv;
		bool								bShieldInv;
		SOUND*								AutoPilot;
		bool								bAutoPilot;
		SOUND*								DoubleDamage;
		bool								bDoubleDamage;
		SOUND*								Warp;
		bool								bWarp;
		//---------------------------------------------------------
		//Weapons
		SOUND*								WeaponsOnline;
		bool								bWeaponsOnline;
		SOUND*								Shockwave;
		bool								bShockwave;
		SOUND*								EMBurst;
		bool								bEMBurst;
		SOUND*								FusionMissile;
		bool								bFusionMissile;
		SOUND*								LancerRail;
		bool								bLancerRail;
		//BoostEnabled
		SOUND*								BoostEnabled;
		bool								bBoostEnabled;
		//Energy
		SOUND*								EnergyCrit;
		bool								bEnergyCrit;
		//CountDown
		SOUND*								Countdown;
		bool								bCountdown;
		//End Game Alerts
		SOUND*								GameComplete;
		SOUND*								GameOver;
		bool								bGameComplete;
		//Final Lap
		SOUND*								FinalLap;
		bool								bFinalLap;
		//---------------------------------------------------------
		//Position Placed
		SOUND*								PositionPlaced;
		bool								bPositionPlaced;
		//Position Human
		SOUND*								PositionHuman;
		bool								bPositionHuman;
		//---------------------------------------------------------
		//functions
		void ZeroData(void);
		//---------------------------------------------------------
	//-------------------------------------------------------------
};
