#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Upgrades
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Primary Weapon Upgrades
		///Primary Damage
		int								uPrimaryDamage[40];
		int								uPrimaryDamagePlayer;
		float							fPrimaryDamageMin[40];
		float							fPrimaryDamageMax[40];
		int								Info_PrimaryDamage[4];
		///Primary Travel Speed
		int								uPrimaryTravel[40];
		int								uPrimaryTravelPlayer;
		float							fPrimaryTravel[40];
		int								Info_PrimaryTravel[4];
		//Secondary Weapon Upgrades
		///Missile Lock Time
		int								uMissileLockTime[40];
		int								uMissileLockTimePlayer;
		int								MissileLockTime[40];
		int								Info_MissileLockTime[4];
		///Missile Damage
		int								uMissileDamage[40];
		int								uMissileDamagePlayer;
		float							fMissileDamage[40];
		int								Info_MissileDamage[4];
		///Missile Radius
		int								uMissileRadius[40];
		int								uMissileRadiusPlayer;
		float							fMissileRadius[40];
		int								Info_MissileRadius[4];
		///Missile Travel Speed
		int								uMissileTravel[40];
		int								uMissileTravelPlayer;
		float							fMissileTravel[40];
		int								Info_MissileTravel[4];
		///Shoxwave Damage
		int								uShoxwaveDamage[40];
		int								uShoxwaveDamagePlayer;
		float							fShoxwaveDamage[40];
		int								Info_ShoxwaveDamage[4];
		///Shoxwave Travel Speed
		int								uShoxwaveTravel[40];
		int								uShoxwaveTravelPlayer;
		float							fShoxwaveTravel[40];
		int								Info_ShoxwaveTravel[4];
		///Shoxwave Speed Reduction
		int								uShoxwaveReduction[40];
		int								uShoxwaveReductionPlayer;
		float							fShoxwaveReduction[40];
		int								Info_ShoxwaveReduction[4];
		///Em Burst Damage
		int								uEmBurstDamage[40];
		int								uEmBurstDamagePlayer;
		float							fEmBurstDamageMin[40];
		float							fEmBurstDamageMax[40];
		int								Info_EmBurstDamage[4];
		///Em Burst Radius
		int								uEmBurstRadius[40];
		int								uEmBurstRadiusPlayer;
		float							fEmBurstRadius[40];
		int								Info_EmBurstRadius[4];
		///Em Burst Speed Reduction
		int								uEmBurstReduction[40];
		int								uEmBurstReductionPlayer;
		float							fEmBurstReduction[40];
		int								Info_EmBurstReduction[4];
		///Rail Damage
		int								uRailDamage[40];
		int								uRailDamagePlayer;
		float							fRailDamageMin[40];
		float							fRailDamageMax[40];
		int								Info_RailDamage[4];
		///Rail Travel Speed
		int								uRailTravel[40];
		int								uRailTravelPlayer;
		float							fRailTravel[40];
		int								Info_RailTravel[4];
		//Utility Weapon Upgrades
		///ShieldInv Time
		int								uShieldInvTime[40];
		int								uShieldInvTimePlayer;
		int								ShieldInvTime[40];
		int								Info_ShieldInvTime[4];
		///ShieldInv Convert
		int								uShieldInvConvert[40];
		int								uShieldInvConvertPlayer;
		float							fShieldInvConvert[40];
		int								Info_ShieldInvConvert[4];
		///AutoPilot Time
		int								uAutoPilotTime[40];
		int								uAutoPilotTimePlayer;
		int								AutoPilotTime[40];
		int								Info_AutoPilotTime[4];
		///DoubleDamage Time
		int								uDoubleDamageTime[40];
		int								uDoubleDamageTimePlayer;
		int								DoubleDamageTime[40];
		int								Info_DoubleDamageTime[4];
		///DoubleDamage Conv
		int								uDoubleDamageConv[40];
		int								uDoubleDamageConvPlayer;
		float							fDoubleDamageConv[40];
		int								Info_DoubleDamageConv[4];
		///Warp Damage Reduce
		int								uWarpDamageReduce[40];
		int								uWarpDamageReducePlayer;
		float							fWarpDamageReduce[40];
		int								Info_WarpDamageReduce[4];
		//Energy Upgrades
		///EnergyMax
		int								uEnergyMax[40];
		int								uEnergyMaxPlayer;
		float							fEnergyMax[40];
		int								Info_EnergyMax[4];
		///EnergyPickup
		int								uEnergyPickup[40];
		int								uEnergyPickupPlayer;
		float							fEnergyPickup[40];
		int								Info_EnergyPickup[4];
		///EnergyTickRegen
		int								uEnergyTickRegen[40];
		int								uEnergyTickRegenPlayer;
		float							fEnergyTickRegen[40];
		int								Info_EnergyTickRegen[4];
		///Player Levels
		int								uPlayerLevel[40];
		///Speed class unlocks
		int								uSpeedClassUnlockPlayer;
		int								Info_SpeedClassUnlock[4];
		//---------------------------------------------------------
		//constructors
		Game_Upgrades(void);
		~Game_Upgrades(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void LoadSettings(void);
		void SaveSettings(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		void ZeroData(void);
		//---------------------------------------------------------
	//-------------------------------------------------------------
};
