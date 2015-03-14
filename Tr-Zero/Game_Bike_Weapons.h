#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Bike_Weapons
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Player Data
		int										PlayerID;
		unsigned int							TotalDamageOutput;
		unsigned int							TotalDamageReceived;
		int										TotalKills;
		int										TotalDeaths;
		int										KilledByID; 
		bool									bKilledBySend; ///Trigger sent to killboard
		//---------------------------------------------------------
		//MultiKill Tracking System
		int										MultiKillTotal;
		string									MultiKillName;
		int										MultiKillTimer;
		int										MultiKillType;///eg: -1 = nothing, 0 = double kill etc etc
		//---------------------------------------------------------
		//Crosshair Data
		D3DXVECTOR2								vPlayerCrosshair;
		D3DXVECTOR3								vCrosshairOrigin;
		D3DXVECTOR3								vHelmetLookAt;
		//---------------------------------------------------------
		//Primary Weapon
		bool									bPrimaryFired;
		int										PrimarySpeed;
		int										PrimaryHeat;
		float									fPrimaryDamage[10];
		float									fPrimarySpeed[10];
		//Primary Weapon Projectile
		bool									bPrimaryProjectileSetup[10];//MAX_PRIMARY_PROJECTILES_PER_BIKE
		bool									bPrimaryProjectileInUse[10];
		D3DXVECTOR3								vPrimaryProjectile[10];
		D3DXQUATERNION							qPrimaryProjectile[10];
		int										PrimaryProjectileAliveTime[10];
		//---------------------------------------------------------
		//Utility
		int										UtilityType;
		bool									bUtilityFired;
		bool									bUtilityInUse;
		int										UtilityAliveTime;
		int										UtilityAliveTimeMax;
		bool									bUtilityProjectileSetup;
		D3DXVECTOR3								vUtilityWarpTo;
		D3DXQUATERNION							qUtilityWarpTo;
		int										UtilityWarpToTarget;
		float									fUtilityWarpToSpeed;
		//---------------------------------------------------------
		//Secondary Weapons
		int										SecondaryWeaponType;//0 = Missle,1=EM etc...
		bool									bSecondaryWeaponCharging;
		int										SecondaryWeaponChargeTime;
		int										SecondaryWeaponChargeTimeMax;
		bool									bSecondaryFired;
		bool									bSecondaryInUse;
		float									fSecondaryDamage;
		//Tracking System
		bool									bTrackingEnabled;
		bool									bTrackingInProgress;
		bool									bTargetLocked;
		int										CurrentTarget;
		int										PreviousTarget;
		int										Tracking_Timer;
		//Secondary Weapon Projectile
		bool									bSecondaryProjectileSetup;
		D3DXVECTOR3								vSecondaryProjectile;
		D3DXQUATERNION							qSecondaryProjectile;
		int										SecondaryProjectileAliveTime;
		int										SecondaryProjectileAliveTimeMax;
		float									fSecondaryProjectileTravelSpeed;
		//---------------------------------------------------------
		//Incomming Weapon Data
		bool									bBeingHit;
		int										BeingHitTimer;
		int										InDamagePlayerID;
		float									fInDamage;
		//Weapon Type incomming
		int										WeaponId_In;
		int										WeaponId_Out;
		int										WeaponId_KilledBy;
		//Incomming Tracking Data
		bool									bBeingTracked;
		D3DXVECTOR3								vTrackingMeshColour;
		//---------------------------------------------------------
		//Network Extras
		int										NetFirePrimary;
		int										NetFireSecondary;
		int										NetSecondaryLockedId;
		int										NetFireUtility;
		//---------------------------------------------------------
		//Tagged Target ID
		int										TaggedTargetId;
		//---------------------------------------------------------
		//constructors
		Game_Bike_Weapons(void);
		~Game_Bike_Weapons(void);
		//---------------------------------------------------------
		//functions
		void Create(int in_PlayerID);
		void Update_Player(D3DXVECTOR3 *v1, D3DXQUATERNION *q1, float *in_speed);
		void Update_Ai(D3DXVECTOR3 *v1, D3DXQUATERNION *q1, float *in_speed, int *NetAiType);
		void Update_Replay(D3DXVECTOR3 *v1, D3DXQUATERNION *q1, float *in_speed);

		void Crosshair(void);
		void Destroy(void);
		///Shield Respawn Activator
		void ShieldRespawnActivator(void);
		///Replay Reset
		void Reset_Replay(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		int										TotalDamageDoneLoop;
		//Network Extras
		int										Networked_Ai_Type;
		//---------------------------------------------------------
		//Ai Primary Math
		int										Ai_FireTime;
		int										Ai_Rand;
		int										Ai_RandTimer;
		//---------------------------------------------------------
		void ZeroData(int in_PlayerID);
		void Player_InputControls(void);
		void Ai_InputControls(void);
		void PlayerDamageDoneReadout(void);
		void PrimaryGun_Trigger(void);
		void PrimaryGun_Projectile(D3DXVECTOR3 *v1,D3DXQUATERNION *q1,float *in_speed);
		void SecondaryGun_Trigger(void);
		void SecondaryGun_Projectile(D3DXVECTOR3 *v1,D3DXQUATERNION *q1,float *in_speed);
		void Utility_Trigger(void);
		void Utility_Projectile(void);
		void Player_MissleTracking(void);
		void Ai_MissleTracking(void);
		void Network_MissleTracking(void);

		void MultiKillSystem(void);
		void DamageRecieve(void);
		void DamageSend(int index, float *fDamage, float fSpeedReduction, int WeaponId);

		void Net_CheckAndSend(void);

		//Reset
		void Reset_Primary(int Index);
		void Reset_Secondary(void);
		void Reset_Utility(void);
	//-------------------------------------------------------------
};
