#pragma once
//-----------------------------------------------------------------
class Game_Audio_Bike
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Volumes Target (eg fVolume = THIS * internal * gsoundfx)
		///Volumes - Player
		float								fVolumeTarget_sEngine_Player;
		float								fVolumeTarget_sTurbo_Player;
		float								fVolumeTarget_sBoost_Player;

		float								fVolumeTarget_sBreak_Player;
		float								fVolumeTarget_sSlip_Player;
		float								fVolumeTarget_sImpact_Player;
		float								fVolumeTarget_sBoostRelease_Player;
		float								fVolumeTarget_sShield_Player;
		///Volumes Ai
		float								fVolumeTarget_sEngine_Ai;
		//---------------------------------------------------------
		//constructors
		Game_Audio_Bike(void);
		~Game_Audio_Bike(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		//Internal Volume
		float								fInternalVol;
		///Volume Ramping
		float								fVolumeRamp;
		int									Timer_VolumeRamp;
		//Max Ranges
		float								fPlayer_MaxRange;
		float								fAi_MaxRange;
		//Player Bike Engine Layer
		///Engine
		SOUND*								sEngine_Player[3];
		float								fEngine_Player_Vol[3];
		float								fEngine_Player_Freq[3];
		float								fEngine_Player_VolMax;
		///Turbo
		SOUND*								sTurbo_Player[3];
		float								fTurbo_Player_Vol[3];
		float								fTurbo_Player_Freq[3];
		float								fTurbo_Player_VolMax;
		///Boost
		SOUND*								sBoost_Player[3];
		float								fBoost_Player_Vol[3];
		float								fBoost_Player_Freq[3];
		float								fBoost_Player_VolMax;
		///Break
		SOUND*								sBreak_Player;
		float								fBreak_Player_Vol;
		///Slip
		SOUND*								sSlip_Player;
		float								fSlip_Player_Vol;
		///Impact
		SOUND*								sImpact_Player;
		///Backfires
		SOUND*								sBoostRelease_Player;
		int									Timer_BoostRelease_Player;
		///Shield
		SOUND*								sShield_Player;
		float								fShield_Player_Vol;
		float								fShield_Player_VolMax;
		//---------------------------------------------------------
		//Ai Sounds
		SOUND*								sEngine_Ai[2];
		float								fEngine_Ai_Vol[2];
		float								fEngine_Ai_Freq[2];
		int									Engine_Ai_Closest[2];
		float								fEngine_Ai_PreviousRange[2];
		int									Timer_Ai_Tickrate;
		//---------------------------------------------------------
		//functions
		void ZeroData(void);
		void UpdateVolumeRamp(void);
		void UpdatePlayer(void);
		void UpdateAi(void);
	//-------------------------------------------------------------
};
