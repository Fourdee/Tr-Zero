#pragma once
//-----------------------------------------------------------------
class Game_Audio_Weapons
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Volumes Target (eg fVolume = THIS * internal * gsoundfx)
		///Volumes - Player
		float								fVolumeTarget_sPrimaryGun;
		float								fVolumeTarget_sEm_Charge;
		float								fVolumeTarget_sEm_Fire;
		float								fVolumeTarget_sRail_Charge;
		float								fVolumeTarget_sRail_Fire;
		float								fVolumeTarget_sShoxwave_Fire;
		float								fVolumeTarget_sMissile_Fire;
		float								fVolumeTarget_sShield;
		float								fVolumeTarget_sDoubleDamage;
		float								fVolumeTarget_sWarp;
		///Volumes - Ai
		float								fVolumeTarget_sEm_Charge_Ai;
		float								fVolumeTarget_sEm_Fire_Ai;
		float								fVolumeTarget_sRail_Charge_Ai;
		float								fVolumeTarget_sRail_Fire_Ai;
		float								fVolumeTarget_sShoxwave_Fire_Ai;
		float								fVolumeTarget_sMissile_Fire_Ai;
		float								fVolumeTarget_sShield_Ai;
		float								fVolumeTarget_sDoubleDamage_Ai;
		float								fVolumeTarget_sWarp_Ai;
		///Volumes - Travel
		float								fVolumeTarget_sPrimaryTravel;
		float								fVolumeTarget_sMissile_Travel;
		float								fVolumeTarget_sMissile_Explosion;
		float								fVolumeTarget_sShoxwave_Travel;
		float								fVolumeTarget_sRail_Travel;
		///Volumes - Impact
		float								fVolumeTarget_sPrimary_Impact;
		float								fVolumeTarget_sShield_Impact;
		//---------------------------------------------------------
		//constructors
		Game_Audio_Weapons(void);
		~Game_Audio_Weapons(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
		void Play_Hitsound(float in_damage);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		///Master Volumes
		float								fInternalVol;
		///Master Ranges
		float								fImpact_MaxRange;
		float								fTravel_MaxRange;
		float								fAi_MaxRange;
		///Volumes - Player
		float								fVolume_sPrimaryGun;
		float								fVolume_sEm_Charge;
		float								fVolume_sEm_Fire;
		float								fVolume_sRail_Charge;
		float								fVolume_sRail_Fire;
		float								fVolume_sShoxwave_Fire;
		float								fVolume_sMissile_Fire;
		float								fVolume_sShield;
		float								fVolume_sDoubleDamage;
		float								fVolume_sWarp;
		///Volumes - Ai
		float								fVolume_sEm_Charge_Ai;
		float								fVolume_sEm_Fire_Ai;
		float								fVolume_sRail_Charge_Ai;
		float								fVolume_sRail_Fire_Ai;
		float								fVolume_sShoxwave_Fire_Ai;
		float								fVolume_sMissile_Fire_Ai;
		float								fVolume_sShield_Ai;
		float								fVolume_sDoubleDamage_Ai;
		float								fVolume_sWarp_Ai;
		///Volumes - Travel
		float								fVolume_sPrimaryTravel;
		float								fVolume_sMissile_Travel;
		float								fVolume_sMissile_Explosion;
		float								fVolume_sShoxwave_Travel;
		float								fVolume_sRail_Travel;
		///Impacts
		float								fVolume_sPrimary_Impact;
		float								fVolume_sShield_Impact;
		//---------------------------------------------------------
		//HITSOUND
		SOUND*								sHitSound;
		//Player
		///primary
		SOUND*								sPrimaryGun;
		///Em_Charge
		SOUND*								sEm_Charge;
		///Em_Fire
		SOUND*								sEm_Fire;
		///Rail_Charge
		SOUND*								sRail_Charge;
		///Rail_Fire
		SOUND*								sRail_Fire;
		///Shoxwave_Fire
		SOUND*								sShoxwave_Fire;
		///sMissile_Fire
		SOUND*								sMissile_Fire;
		///sShield
		SOUND*								sShield;
		///sDoubleDamage
		SOUND*								sDoubleDamage;
		///sWarp
		SOUND*								sWarp[2];
		//Ai
		///Em_Charge
		SOUND*								sEm_Charge_Ai;
		///Em_Fire
		SOUND*								sEm_Fire_Ai;
		///Rail_Charge
		SOUND*								sRail_Charge_Ai;
		///Rail_Fire
		SOUND*								sRail_Fire_Ai;
		///Shoxwave_Fire
		SOUND*								sShoxwave_Fire_Ai;
		///sMissile_Fire_Ai
		SOUND*								sMissile_Fire_Ai;
		///sShield_Ai
		SOUND*								sShield_Ai;
		///sDoubleDamage_Ai
		SOUND*								sDoubleDamage_Ai;
		///sWarp_Ai
		SOUND*								sWarp_Ai[2];
		//---------------------------------------------------------
		//Globals Travel/Explosion Sounds
		///Primary Travel
		SOUND*								sPrimaryTravel;
		///Fusion Missile Travel
		SOUND*								sMissile_Travel;
		///Fusion Missile Explosion
		SOUND*								sMissile_Explosion;
		///ShoxWave Travel
		SOUND*								sShoxwave_Travel;
		///Rail Travel
		SOUND*								sRail_Travel;
		//---------------------------------------------------------
		//Global Impacts
		SOUND*								sPrimary_Impact[3];
		SOUND*								sShield_Impact[3];
		//---------------------------------------------------------
		//functions
		void ZeroData(void);
		///player
		void Player_Update(void);
		///ai
		void Ai_Update(void);
		//Travel
		void Travel_Update(void);
		//Impact
		void Impact_Update(void);
		//Global SFX Math
		float Freq_Charge(float input,float max);
	//-------------------------------------------------------------
};