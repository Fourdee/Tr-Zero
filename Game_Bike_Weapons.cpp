//-----------------------------------------------------------------
// About:
//
// name: "Game_Bike_Weapons.cpp:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Bike_Weapons.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - BIKE - WEAPONS - CONSTRUCTORS
///*****************************************************************
Game_Bike_Weapons::Game_Bike_Weapons(void)
{
	//-------------------------------------------------------------
	//Zero
	ZeroData(0);
	//-------------------------------------------------------------
}

Game_Bike_Weapons::~Game_Bike_Weapons(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - ZERODATA
///*****************************************************************
void Game_Bike_Weapons::ZeroData(int in_PlayerID)
{
	//-------------------------------------------------------------
	//Setup Player
	PlayerID							= in_PlayerID;
	TotalDamageOutput					= 0;
	TotalDamageDoneLoop					= 0;
	TotalDamageReceived					= 0;
	TotalKills							= 0;
	TotalDeaths							= 0;
	bKilledBySend						= false;
	KilledByID							= 0;
	//---------------------------------------------------------
	//MultiKill Tracking System
	MultiKillTotal						= 0;
	MultiKillName						= "";
	MultiKillTimer						= 0;
	MultiKillType						= -1;
	//-------------------------------------------------------------
	//Crosshair
	vPlayerCrosshair					= D3DXVECTOR2(0.0f,0.0f);
	vCrosshairOrigin					= D3DXVECTOR3(0.0f,0.0f,0.0f);
	vHelmetLookAt						= D3DXVECTOR3(0.0f,0.0f,0.0f);
	//-------------------------------------------------------------
	//Primary Weapon
	bPrimaryFired						= false;
	PrimarySpeed						= 0;
	PrimaryHeat							= 0;
	//Primary Weapon Projectile
	for(int i=0;i<MAX_PRIMARY_PROJECTILES_PER_BIKE;i++)
	{
		fPrimaryDamage[i]				= 0.0f;
		fPrimarySpeed[i]				= 0.0f;
		bPrimaryProjectileSetup[i]		= false;
		bPrimaryProjectileInUse[i]		= false;
		vPrimaryProjectile[i]			= D3DXVECTOR3(0.0f,0.0f,0.0f);
		qPrimaryProjectile[i]			= D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
		PrimaryProjectileAliveTime[i]	= 0;
	}
	//---------------------------------------------------------
	//Utility
	UtilityType							= -1;
	bUtilityFired						= false;
	bUtilityInUse						= false;
	UtilityAliveTime					= 0;
	UtilityAliveTimeMax					= 240;
	bUtilityProjectileSetup				= false;
	vUtilityWarpTo						= D3DXVECTOR3(0.0f,0.0f,0.0f);
	qUtilityWarpTo						= D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	UtilityWarpToTarget					= -1;
	fUtilityWarpToSpeed					= 0.0f;
	//-------------------------------------------------------------
	//Secondary Weapons
	fSecondaryDamage					= 50.0f;
	SecondaryWeaponType					= -1;
	bSecondaryWeaponCharging			= false;
	SecondaryWeaponChargeTime			= 0;
	SecondaryWeaponChargeTimeMax		= 180;
	bSecondaryFired						= false;
	bSecondaryInUse						= false;
	//Tracking System
	bTrackingEnabled					= false;
	bTrackingInProgress					= false;
	bTargetLocked						= false;
	CurrentTarget						= -1;
	PreviousTarget						= -1;
	Tracking_Timer						= 0;
	//Secondary Weapon Projectile
	bSecondaryProjectileSetup			= false;
	vSecondaryProjectile				= D3DXVECTOR3(0.0f,0.0f,0.0f);
	qSecondaryProjectile				= D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	SecondaryProjectileAliveTime		= 0;
	SecondaryProjectileAliveTimeMax		= 360;
	fSecondaryProjectileTravelSpeed		= 0.0f;
	//-------------------------------------------------------------
	//Incomming Weapon Data
	bBeingHit							= false;
	BeingHitTimer						= 60;
	InDamagePlayerID					= 0;
	fInDamage							= 0.0f;
	//Incomming Weapon ID type
	WeaponId_In							= -1;
	WeaponId_Out						= WeaponId_In;
	WeaponId_KilledBy					= WeaponId_In;
	//Incomming Tracking Data
	bBeingTracked						= false;
	vTrackingMeshColour					= D3DXVECTOR3(0.0f,0.0f,0.0f);
	//-------------------------------------------------------------
	//Ai Primary Fireing State Math
	Ai_FireTime							= 0;
	Ai_Rand								= 0;
	Ai_RandTimer						= 0;
	//-------------------------------------------------------------
	//Net
	NetFirePrimary						= 0;
	NetFireSecondary					= -2;
	NetSecondaryLockedId				= 0;
	NetFireUtility						= -1;
	Networked_Ai_Type					= 0;
	//---------------------------------------------------------
	//Tagged Target ID
	TaggedTargetId						= -1;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - WEAPONS - CREATE
///*****************************************************************
void Game_Bike_Weapons::Create(int in_PlayerID)
{
	//-------------------------------------------------------------
	ZeroData(in_PlayerID);
	//-------------------------------------------------------------
	//Setup Ai Difficulty Damage Modifiers (global flags, apply only on 1st bike)
	if(in_PlayerID==0)
	{
		gAiWeaponsDamageMulti	= 1.0f;
		gPrimaryAiFireTimeMax	= 250;
		gPrimaryAiRandMax		= 10;

		if(gGameMode<4)///Not Arena/Ahniliation
		{
			gAiWeaponsDamageMulti = iFloatInterpolate((float)gAiDifficuty,0.0f,4.0f,0.3f,1.0f);
			gPrimaryAiFireTimeMax = (int)(iFloatInterpolate((float)gAiDifficuty,0.0f,4.0f,150.0f,250.0f));
			gPrimaryAiRandMax = (int)(iFloatInterpolate((float)gAiDifficuty,0.0f,4.0f,14.0f,10.0f));
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - Player_InputControls
///*****************************************************************
void Game_Bike_Weapons::Player_InputControls(void)
{
	//-------------------------------------------------------------
	//Primary
	NetFirePrimary = 0;
	if(cGame_Controls.Input_Bike_PrimaryWeapon())
	{
		NetFirePrimary = 1;
		bPrimaryFired = true;
	}
	//-------------------------------------------------------------
	//Secondary
	if(cGame_Controls.Input_Bike_SecondaryWeapon() && 
		SecondaryWeaponType > -1)
	{
		bSecondaryFired = true;
	}
	//-------------------------------------------------------------
	//Utility Math
	if(cGame_Controls.Input_Bike_UtilityWeapon() && 
		UtilityType > -1)
	{
		bUtilityFired = true;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - Ai_InputControls
///*****************************************************************
void Game_Bike_Weapons::Ai_InputControls(void)
{
	//-------------------------------------------------------------
	//Offline
	if(Networked_Ai_Type==0)
	{
		//Primary Fire
		NetFirePrimary = 0;
		if(Ai_Rand==1 && 
			Ai_FireTime < gPrimaryAiFireTimeMax)
		{
			bPrimaryFired = true;
			NetFirePrimary = 1;
			Ai_FireTime++;
		}
		//Primary Reset
		else
		{
			Ai_FireTime = 0;
		}
		//Primary Generate number
		if(Ai_RandTimer < 60)
		{
			Ai_RandTimer++;
		}
		else if(!bPrimaryFired)
		{
			Ai_Rand = iIntRand(0,gPrimaryAiRandMax);
			Ai_RandTimer = 0;
		}
		//-------------------------------------------------------------
		//Secondary Weapon Math
		///Just fire if they have that weapon boom
		if(SecondaryWeaponType > -1)
		{
			bSecondaryFired = true;
		}
		//-------------------------------------------------------------
		//Utility Math
		///Just fire if they have a utility, awesome
		if(UtilityType > -1)
		{
			bUtilityFired = true;
		}
	}
	//-------------------------------------------------------------
	//online
	else
	{
		//Primary Fire
		if(NetFirePrimary==1)
		{
			bPrimaryFired = true;
		}
		//Secondary
		if(NetFireSecondary==-1)///Charging
		{
			SecondaryWeaponChargeTimeMax = 180;
			SecondaryWeaponChargeTime++;
			bSecondaryWeaponCharging = true;
		}
		else if(NetFireSecondary>=0)
		{
			SecondaryWeaponType = NetFireSecondary;
			bSecondaryInUse = true;
		}
		//Utility
		if(NetFireUtility>=0)
		{
			UtilityType = NetFireUtility;
			bUtilityInUse = true;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - WEAPONS - Crosshair
///*****************************************************************
void Game_Bike_Weapons::Crosshair(void)
{
	//-------------------------------------------------------------
	//Ai Crosshairlocation from bike origin
	vCrosshairOrigin = iVectorLocationOffset(&cGame_Bike[PlayerID].Manager.vBikeOutput,&cGame_Bike[PlayerID].Manager.qBikeOutput,&D3DXVECTOR3(cGame_Bike[PlayerID].fSteering * 7.0f,2.0f,50.0f));
	//Helmet Lookat target (crosshair + a bit extra)
	vHelmetLookAt = iVectorLocationOffset(&vCrosshairOrigin,&cGame_Bike[PlayerID].Manager.qBikeOutput,&D3DXVECTOR3(cGame_Bike[PlayerID].fSteering,-cGame_Bike[PlayerID].Manager.vRotations.x,-30.0f));
	//3D to screen location for sprite
	i3DLocationToScreen(&vPlayerCrosshair,&vCrosshairOrigin,gCamera);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - Player_MissleTracking
///*****************************************************************
void Game_Bike_Weapons::Player_MissleTracking(void)
{
	//-------------------------------------------------------------
	bTrackingEnabled = false;
	bTrackingInProgress = false;
	bTargetLocked = false;
	float maxrange = 400.0f;
	CurrentTarget = -1;
	//-------------------------------------------------------------
	//Define weapons which use tracking system here
	if(SecondaryWeaponType==0)
	{
		bTrackingEnabled = true;
	}
	//-------------------------------------------------------------
	if(bTrackingEnabled)
	{
		//Projectile Fired, keep last target active
		if(bSecondaryInUse)
		{
			CurrentTarget = PreviousTarget;
			bTrackingInProgress = true;
			Tracking_Timer = cGame_Upgrades.MissileLockTime[PlayerID];
			bTargetLocked = true;
		}
		//Track Ai Locking
		else
		{
			for(int i=0;i<gAi_Max_Count;i++)
			{
				D3DXVECTOR2 Screen;
				if(cGame_Bike[i].Energy.bAlive &&
					i3DLocationToScreen(&Screen,&cGame_Bike[i].Manager.vBikeOutput,gCamera))
				{
					if(cGame_Bike[i].fDistanceToCam < maxrange)
					{
						float ScaleRange = iFloatInterpolate(cGame_Bike[i].fDistanceToCam,15.0f,maxrange,3.0f,1.0f);
						float left = Screen.x - ScaleRange;
						float right = Screen.x + ScaleRange;
						float bottom = Screen.y - 5.0f;
						float top = Screen.y + 12.0f;

						if((cGame_Bike[gAi_Max_Count].Weapons.vPlayerCrosshair.x >= left && cGame_Bike[gAi_Max_Count].Weapons.vPlayerCrosshair.x <= right) &&
							(cGame_Bike[gAi_Max_Count].Weapons.vPlayerCrosshair.y >= bottom && cGame_Bike[gAi_Max_Count].Weapons.vPlayerCrosshair.y <= top))
						{
							if(i==PreviousTarget)
							{
								bTrackingInProgress = true;
								CurrentTarget = i;
							}
							else if(Tracking_Timer < cGame_Upgrades.MissileLockTime[PlayerID] / 2)
							{
								bTrackingInProgress = true;
								PreviousTarget = i;
								CurrentTarget = i;
							}
						}
					}
				}
			}
		}
		//-------------------------------------------------------------
		//Update LockState + Tracking Timer
		if(bTrackingInProgress)
		{
			//Tracking Timer
			if(Tracking_Timer < cGame_Upgrades.MissileLockTime[PlayerID])
			{
				Tracking_Timer++;
				cGame_Bike[CurrentTarget].Weapons.vTrackingMeshColour = D3DXVECTOR3(1.5f,1.0f,0.0f);
			}
			else
			{
				bTargetLocked = true;
				cGame_Bike[CurrentTarget].Weapons.vTrackingMeshColour = D3DXVECTOR3(3.0f,0.3f,0.0f);
			}
			//Inform other player of lock
			cGame_Bike[CurrentTarget].Weapons.bBeingTracked = true;
		}
		else if(Tracking_Timer > 0)
		{
			//Tracking Timer
			Tracking_Timer--;	
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - Ai_MissleTracking
///*****************************************************************
void Game_Bike_Weapons::Ai_MissleTracking(void)
{
	//-------------------------------------------------------------
	bTrackingEnabled = false;
	bTrackingInProgress = false;
	bTargetLocked = false;
	float maxrange = 400.0f;
	CurrentTarget = -1;
	//-------------------------------------------------------------
	//Define weapons which use tracking system here
	if(SecondaryWeaponType==0)
	{
		bTrackingEnabled = true;
	}
	//-------------------------------------------------------------
	//Find a target Near crosshair
	if(bTrackingEnabled)
	{
		//Projectile Fired, keep last target active
		if(bSecondaryInUse)
		{
			CurrentTarget = PreviousTarget;
			bTrackingInProgress = true;
			Tracking_Timer = cGame_Upgrades.MissileLockTime[PlayerID];
			bTargetLocked = true;
		}
		//Find a Target
		else
		{
			D3DXVECTOR3 vBikeTarget = D3DXVECTOR3(0.0f,0.0f,0.0f);
			for(int i=0;i<=gAi_Max_Count;i++)
			{
				//Prevent Lock on Targets allready locked, or, dead.
				bool bAllreadyLocked = false;
				vBikeTarget = cGame_Bike[i].Manager.vBikeOutput;
				if(cGame_Bike[i].Weapons.bBeingTracked ||
					!cGame_Bike[i].Energy.bAlive ||
					!iVectorInFront(cGame_Bike[PlayerID].Manager.qBikeOutput,cGame_Bike[PlayerID].Manager.vBikeOutput,vBikeTarget))

				{
					bAllreadyLocked = true;
				}
				//Apply lock on available targets				
				if(i!=PlayerID &&
					!bAllreadyLocked &&
					iVectorLength(&(vCrosshairOrigin - vBikeTarget)) < maxrange)
				{
					if(i==PreviousTarget)
					{
						bTrackingInProgress = true;
						CurrentTarget = i;
					}
					else if(Tracking_Timer < cGame_Upgrades.MissileLockTime[PlayerID] / 2)
					{
						bTrackingInProgress = true;
						PreviousTarget = i;
						CurrentTarget = i;
					}
				}
			}
		}
		//-------------------------------------------------------------
		//Update LockState + Tracking Timer
		if(bTrackingInProgress)
		{
			if(Tracking_Timer < cGame_Upgrades.MissileLockTime[PlayerID])
			{
				Tracking_Timer++;
				cGame_Bike[CurrentTarget].Weapons.vTrackingMeshColour = D3DXVECTOR3(1.5f,1.0f,0.0f);
				cGame_Bike[CurrentTarget].Weapons.bBeingTracked = true;
			}
			else
			{
				cGame_Bike[CurrentTarget].Weapons.vTrackingMeshColour = D3DXVECTOR3(3.0f,0.3f,0.0f);
				cGame_Bike[CurrentTarget].Weapons.bBeingTracked = true;
				bTargetLocked = true;
			}
		}
		else if(Tracking_Timer > 0)
		{
			Tracking_Timer--;	
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - Network_MissleTracking
///*****************************************************************
void Game_Bike_Weapons::Network_MissleTracking(void)
{
	//-------------------------------------------------------------
	bTrackingEnabled = false;
	bTargetLocked = false;

	//CurrentTarget = NetSecondaryLockedId;

	if(bSecondaryInUse && SecondaryWeaponType==0) //User has fired
	{
		if(cGame_Network.Server.State==2)
		{
			PreviousTarget = NetSecondaryLockedId;
			if(NetSecondaryLockedId==0)
			{
				PreviousTarget = gAi_Max_Count;
			}
		}
		else if(cGame_Network.Client.State==2)
		{
			PreviousTarget = NetSecondaryLockedId;
			if(NetSecondaryLockedId==cGame_Network.Client.Client_ID)
			{
				PreviousTarget = gAi_Max_Count;
			}
		}
		CurrentTarget = PreviousTarget;
		//-------------------------------------------------------------
		//Update LockState
		cGame_Bike[CurrentTarget].Weapons.vTrackingMeshColour = D3DXVECTOR3(3.0f,0.3f,0.0f);
		cGame_Bike[CurrentTarget].Weapons.bBeingTracked = true;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - PlayerDamageDoneReadout
///*****************************************************************
void Game_Bike_Weapons::PlayerDamageDoneReadout(void)
{
	//-------------------------------------------------------------
	static float fPrintDamage = 0.0f;
	static bool bPrint = false;
	D3DXVECTOR2 Screen = D3DXVECTOR2(0.0f,0.0f);
	//-------------------------------------------------------------
	//Setup
	if(!bPrint &&
		bBeingHit &&
		InDamagePlayerID==gAi_Max_Count)
	{
		BeingHitTimer = 0;
		fPrintDamage = fInDamage;
		bPrint = true;
	}
	//-------------------------------------------------------------
	//Update
	if(BeingHitTimer < 60 &&
		i3DLocationToScreen(&Screen,&cGame_Bike[PlayerID].Manager.vBikeOutput,gCamera))
	{
		BeingHitTimer++;
		Screen.y += 0.2f + ((float)BeingHitTimer / 30.0f);
		Screen.x += 0.1f + ((float)BeingHitTimer / 60.0f);
		//Output iprint
		float AlphaScale = iFloatInterpolateSmooth((float)BeingHitTimer,30.0f,60.0f,0.8f,0.0f);
		sprintf_s(gCharBuffer,"%0.0f",fPrintDamage);
		iPrint3(gCharBuffer,cGame_Font.f16pt,&Screen,&D3DXVECTOR4(1.0f,1.0f,1.0f,AlphaScale),gFont2,false);
	}
	else
	{
		BeingHitTimer = 60;
		bPrint = false;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - PrimaryGun_Projectile
///*****************************************************************
void Game_Bike_Weapons::PrimaryGun_Projectile(D3DXVECTOR3 *v1,D3DXQUATERNION *q1,float *in_speed)
{
	//-------------------------------------------------------------
	bool bProjectileSent = false;
	const int WeaponIdUsed = 0;
	//-------------------------------------------------------------
	//Define and pick when projectile is starting
	if(bPrimaryFired)
	{
		for(int i=0;i<MAX_PRIMARY_PROJECTILES_PER_BIKE;i++)
		{
			//Find a projectile to use
			if(!bProjectileSent && 
				!bPrimaryProjectileInUse[i])
			{
				bPrimaryProjectileInUse[i] = true;
				bProjectileSent = true;
				break;
			}
		}
		//Reset longest alive projectile for use
		if(!bProjectileSent)
		{
			int Reset = iIntHighestValueInArrayIndex(PrimaryProjectileAliveTime,MAX_PRIMARY_PROJECTILES_PER_BIKE);
			//Close-reset
			Reset_Primary(Reset);
			bPrimaryProjectileInUse[Reset] = true;
			bProjectileSent = true;
		}
	}
	//-------------------------------------------------------------
	//Update Active projectiles
	for(int i=0;i<MAX_PRIMARY_PROJECTILES_PER_BIKE;i++)
	{
		if(bPrimaryProjectileInUse[i])
		{
			//Setup the projectile
			if(!bPrimaryProjectileSetup[i])
			{
				//Init Data
				///Damage
				fPrimaryDamage[i] = iFloatInterpolate((float)PrimaryHeat,50.0f,100.0f,cGame_Upgrades.fPrimaryDamageMax[PlayerID],cGame_Upgrades.fPrimaryDamageMin[PlayerID]);
				///Check for Double Damage
				if(bUtilityInUse && UtilityType==2)
				{
					fPrimaryDamage[i] = fPrimaryDamage[i] * 2.0f;
				}
				///Check for AI/Net Output Damage
				if(PlayerID < gAi_Max_Count && 
					Networked_Ai_Type <= 0)
				{
					fPrimaryDamage[i] = fPrimaryDamage[i] * gAiWeaponsDamageMulti;
				}
				fPrimarySpeed[i] = abs(*in_speed) + cGame_Upgrades.fPrimaryTravel[PlayerID];
				//Location
				///Set Location/orientation to match bike
				D3DXQUATERNION qLookAt;
				D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
				iVectorRotate(&vUp,&vUp,q1);
				vPrimaryProjectile[i] = *v1;
				qPrimaryProjectile[i] = *q1;//qLookAt
				///scan+place
				if(iProjectile_Floor(vPrimaryProjectile[i],qPrimaryProjectile[i],5.0f,2.5f))
				{
				}
				iQuaternionLookAt(&qLookAt,&vPrimaryProjectile[i],&vCrosshairOrigin,&vUp);
				qPrimaryProjectile[i] = qLookAt;//qLookAt
				bPrimaryProjectileSetup[i] = true;
			}
			//Update location for active projectiles
			else
			{
				///Follow Track Floor
				if(iProjectile_Floor(vPrimaryProjectile[i],qPrimaryProjectile[i],fPrimarySpeed[i],2.5f))
				{
					///Update alive time
					PrimaryProjectileAliveTime[i]++;
					if(PrimaryProjectileAliveTime[i] >= gPrimaryAliveTimeMax)
					{
						//Close-reset - (Alive Timer Reached)
						Reset_Primary(i);
					}
					///---------------------
				}
				else
				{
					//Close-reset - (Wall , no track surface)
					Reset_Primary(i);
				}
				//Check for hit
				for(int a=0;a<=gAi_Max_Count;a++)
				{
					D3DXVECTOR3 vBikeTarget = cGame_Bike[a].Manager.vBikeOutput;

					if(PlayerID!=a &&
						iVectorLength(&(vPrimaryProjectile[i] - vBikeTarget)) < gPrimaryRadius)
					{
						DamageSend(a,&fPrimaryDamage[i],0.0f,WeaponIdUsed);
						TotalDamageDoneLoop += (int)fPrimaryDamage[i];
						//Close-reset - (Hit Bike)
						Reset_Primary(i);
						///Tagged Target ID
						TaggedTargetId = a;
						break;
					}
				}
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - PrimaryGun_Trigger
///*****************************************************************
void Game_Bike_Weapons::PrimaryGun_Trigger(void)
{
	//-------------------------------------------------------------
	//Heat - Cancel Fire
	if(PrimaryHeat > gPrimaryHeatMax)
	{
		bPrimaryFired = false;
		PrimaryHeat--;
	}
	else if(PrimaryHeat>0)
	{
		PrimaryHeat--;
	}
	//-------------------------------------------------------------
	//Cancel fire, wait for spinup
	if(PrimarySpeed > 0)
	{
		bPrimaryFired = false;
		PrimarySpeed--;
	}
	//Fire 
	else if(bPrimaryFired)
	{
		PrimarySpeed += 5 + (PrimaryHeat / 25);
		PrimaryHeat += 16;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - SecondaryGun_Trigger
///*****************************************************************
void Game_Bike_Weapons::SecondaryGun_Trigger(void)
{
	//-------------------------------------------------------------
	if(!bSecondaryInUse)
	{
		if(bSecondaryFired && SecondaryWeaponType==0 && bTargetLocked)//Missile
		{
			//Fire Missile
			bSecondaryInUse = true;
		}
		else if(bSecondaryFired && SecondaryWeaponType==1)//Shockwave
		{
			//Fire Shockwave
			bSecondaryInUse = true;
		}
		else if(SecondaryWeaponType==2)//Aoe Burst
		{
			//Fire Charged AOE burst
			SecondaryWeaponChargeTimeMax = 180;
			if(bSecondaryFired && SecondaryWeaponChargeTime < SecondaryWeaponChargeTimeMax)
			{
				//Show charging mesh
				bSecondaryWeaponCharging = true;
				SecondaryWeaponChargeTime++;
			}
			else if(SecondaryWeaponChargeTime > 1)
			{
				bSecondaryInUse = true;
			}
		}
		else if(SecondaryWeaponType==3)//Rail
		{
			//Fire Charged Rail
			SecondaryWeaponChargeTimeMax = 60;
			if(bSecondaryFired && SecondaryWeaponChargeTime < SecondaryWeaponChargeTimeMax)
			{
				//Show charging mesh
				bSecondaryWeaponCharging = true;
				SecondaryWeaponChargeTime++;
			}
			else if(SecondaryWeaponChargeTime > 1)
			{
				bSecondaryInUse = true;
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - Utility_Trigger
///*****************************************************************
void Game_Bike_Weapons::Utility_Trigger(void)
{
	//-------------------------------------------------------------
	if(!bUtilityInUse && 
		bUtilityFired)
	{
		bUtilityInUse = true;
		//Cancel for warp with no targets.
		if(UtilityType==3 && TaggedTargetId<0)
		{
			bUtilityInUse = false;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - Utility_Projectile
///*****************************************************************
void Game_Bike_Weapons::Utility_Projectile(void)
{
	//-------------------------------------------------------------
	if(bUtilityInUse)
	{
		//-------------------------------------------------------------
		//Utility Type 0 (SHIELD INV)
		//-------------------------------------------------------------
		if(UtilityType==0)
		{
			//-------------------------------------------------------------
			//Setup meshes etc
			if(!bUtilityProjectileSetup)
			{
				UtilityAliveTimeMax = cGame_Upgrades.ShieldInvTime[PlayerID];
				bUtilityProjectileSetup = true;
			}
			//Update location for active projectiles
			else if(UtilityAliveTime < UtilityAliveTimeMax)
			{
				//Update Mesh location
				UtilityAliveTime++;
			}
			//Close-reset
			else
			{
				Reset_Utility();
			}
		}
		//-------------------------------------------------------------
		//END - Utility Type 0 (SHIELD INV)
		//-------------------------------------------------------------
		//-------------------------------------------------------------
		//Utility Type 1 (AUTO PILOT PLAYER)
		//-------------------------------------------------------------
		else if(UtilityType==1)
		{
			//-------------------------------------------------------------
			bool ApplyStats = false;
			//Prevent applying to network
			if(PlayerID==gAi_Max_Count)
			{
				ApplyStats = true;
			}
			//-------------------------------------------------------------
			//Setup meshes etc
			if(!bUtilityProjectileSetup)
			{
				UtilityAliveTimeMax = cGame_Upgrades.AutoPilotTime[PlayerID];
				if(ApplyStats)
				{
					//Reset Manager - AI Spec
					cGame_Bike[gAi_Max_Count].bAiTakeover = true;
					bUtilityProjectileSetup = true;
				}
			}
			//Update location for active projectiles
			else if(UtilityAliveTime < UtilityAliveTimeMax)
			{
				//Update Mesh location
				UtilityAliveTime++;
				//if(ApplyStats)
				//{
				//	cGame_Bike[gAi_Max_Count].Manager.fAcceleration_Speed += 0.02f;
				//}
			}
			//Close-reset
			else
			{
				//Reset Manager - Player Spec
				if(ApplyStats)
				{
					cGame_Bike[gAi_Max_Count].bAiTakeover = true;
				}
				Reset_Utility();
			}
		}
		//-------------------------------------------------------------
		//END - Utility Type 1 (AUTO PILOT PLAYER)
		//-------------------------------------------------------------
		//-------------------------------------------------------------
		//Utility Type 2 (DOUBLE DAMAGE)
		//-------------------------------------------------------------
		else if(UtilityType==2)
		{
			//-------------------------------------------------------------
			//Setup meshes etc
			if(!bUtilityProjectileSetup)
			{
				UtilityAliveTimeMax = cGame_Upgrades.DoubleDamageTime[PlayerID];
				bUtilityProjectileSetup = true;
			}
			//Update location for active projectiles
			else if(UtilityAliveTime < UtilityAliveTimeMax)
			{
				//Update Mesh location
				UtilityAliveTime++;
			}
			//Close-reset
			else
			{
				Reset_Utility();
			}
		}
		//-------------------------------------------------------------
		//END - Utility Type 2 (DOUBLE DAMAGE)
		//-------------------------------------------------------------
		//-------------------------------------------------------------
		//Utility Type 3 (WARP)
		//-------------------------------------------------------------
		else if(UtilityType==3)
		{
			//-------------------------------------------------------------
			//Setup
			if(!bUtilityProjectileSetup)
			{
				UtilityAliveTimeMax = 120;//cGame_Upgrades.ShieldInvTime[PlayerID];
				///Grab current target/location/orientation used for warp
				UtilityWarpToTarget = TaggedTargetId;
				vUtilityWarpTo = cGame_Bike[UtilityWarpToTarget].Manager.vBikeOrigin;
				qUtilityWarpTo = cGame_Bike[UtilityWarpToTarget].Manager.qBikeOrigin;
				fUtilityWarpToSpeed = cGame_Bike[UtilityWarpToTarget].Manager.fAcceleration_Speed;
				bUtilityProjectileSetup = true;
			}
			//Update location for active projectiles
			else if(UtilityAliveTime<=UtilityAliveTimeMax)
			{
				//Update Mesh location
				UtilityAliveTime++;
				//Apply warp
				if(UtilityAliveTime==25)
				{
					if(cGame_Network.Client.State==0)///Disable AI warping on NetClients (server does this)
					{
						///warp ai to player
						cGame_Bike[PlayerID].Manager.vBikeOrigin = vUtilityWarpTo;
						cGame_Bike[PlayerID].Manager.qBikeOrigin = qUtilityWarpTo;
						cGame_Bike[PlayerID].Manager.fAcceleration_Speed = fUtilityWarpToSpeed;
						cGame_Bike[PlayerID].fSteering = 0.0f;
					}
				}
			}
			else
			{
				Reset_Utility();
			}
		}
		//-------------------------------------------------------------
		//END  Utility Type 3 (WARP)
		//-------------------------------------------------------------
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - SecondaryGun_Projectile
///*****************************************************************
void Game_Bike_Weapons::SecondaryGun_Projectile(D3DXVECTOR3 *v1,D3DXQUATERNION *q1,float *in_speed)
{
	//-------------------------------------------------------------
	if(bSecondaryInUse)
	{
		//-------------------------------------------------------------
		//Weapon Id sent to target
		int WeaponIdUsed = SecondaryWeaponType + 1;
		//-------------------------------------------------------------
		//Secondary Weapon 0 (MISSILE)
		//-------------------------------------------------------------
		if(SecondaryWeaponType==0)
		{
			//-------------------------------------------------------------
			//Define Special Missile targets
			D3DXVECTOR3 vBikeTarget = cGame_Bike[CurrentTarget].Manager.vBikeOutput;
			//-------------------------------------------------------------
			//Setup the projectile
			if(!bSecondaryProjectileSetup)
			{
				//Init Data
				SecondaryProjectileAliveTimeMax = 360;
				fSecondaryDamage = cGame_Upgrades.fMissileDamage[PlayerID];
				///Check for AI Output Damage
				if(PlayerID < gAi_Max_Count && 
					Networked_Ai_Type <= 0)
				{
					fSecondaryDamage = fSecondaryDamage * gAiWeaponsDamageMulti;
				}
				///Check for Double Damage
				if(bUtilityInUse && UtilityType==2)
				{
					fSecondaryDamage = fSecondaryDamage * 2.0f;
				}
				//Location Updates
				///Set Location/orientation to match bike
				D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
				iVectorRotate(&vUp,&vUp,q1);
				vSecondaryProjectile = *v1;
				qSecondaryProjectile = *q1;//qLookAt
				///scan+place
				iProjectile_Floor(vSecondaryProjectile,qSecondaryProjectile,5.0f,2.5f);
				D3DXQUATERNION qLookAt;
				iQuaternionLookAt(&qLookAt,&vSecondaryProjectile,&vCrosshairOrigin,&vUp);
				qSecondaryProjectile = qLookAt;
				fSecondaryProjectileTravelSpeed = *in_speed + 0.1f;
				bSecondaryProjectileSetup = true;
			}
			//Update location for active projectiles
			else if(SecondaryProjectileAliveTime < SecondaryProjectileAliveTimeMax)
			{
				//---------------------
				///Travel Speed Update
				fSecondaryProjectileTravelSpeed += cGame_Upgrades.fMissileTravel[PlayerID];
				if(fSecondaryProjectileTravelSpeed>9.0f)
				{
					fSecondaryProjectileTravelSpeed = 9.0f;
				}
				///Steer to target
				D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
				D3DXVECTOR3 vRotations = D3DXVECTOR3(0.0f,0.0f,0.0f);
				D3DXQUATERNION qSteer;
				iVectorRotate(&vUp,&vUp,&qSecondaryProjectile);
				iQuaternionLookAt(&qSteer,&vSecondaryProjectile,&vBikeTarget,&vUp);
				iQuaternionDelta(&qSteer,&qSecondaryProjectile,&qSteer);
				iQuaternionToEulerAngles(&qSteer,&vRotations);
				///Steering Control linked to distance
				float SmoothSteer = 0.0f;
				float fSteeringTendTo = 0.0f;//iFloatInterpolate((float)SecondaryProjectileAliveTime,0.0f,(float)SecondaryProjectileAliveTimeMax,10.0f,2.0f);
				fSteeringTendTo = iFloatInterpolate(iVectorLength(&(vSecondaryProjectile - vBikeTarget)),100.0f,15.0f,15.0f,1.0f);
				iFloatTendTo2(SmoothSteer,vRotations.y,fSteeringTendTo);
				iQuaternionFromEulerAngles(&qSteer,0.0f,SmoothSteer,0.0f);
				iQuaternionMultiply(&qSecondaryProjectile,&qSteer,&qSecondaryProjectile);
				///Follow track
				if(iProjectile_Floor(vSecondaryProjectile,qSecondaryProjectile,fSecondaryProjectileTravelSpeed,3.5f))
				{
					///Update Alive time
					SecondaryProjectileAliveTime++;
				}
				else
				{
					SecondaryProjectileAliveTime = SecondaryProjectileAliveTimeMax;
				}
				//Check for hit
				bool bApplyRadiusDamage = false;
				if(iVectorLength(&(vSecondaryProjectile - vBikeTarget)) < 4.5f)
				{
					DamageSend(CurrentTarget,&fSecondaryDamage,0.0f,WeaponIdUsed);
					bApplyRadiusDamage = true;
					///Send explosion data for mesh.
					cGame_Mesh.Bike_Weapons.bExplosionInUse[CurrentTarget] = true;
					cGame_Mesh.Bike_Weapons.ExplosionUpgradeScale[CurrentTarget] = cGame_Upgrades.fMissileRadius[PlayerID];
					cGame_Mesh.Bike_Weapons.ExplosionTimer[CurrentTarget] = 0;
					cGame_Mesh.Bike_Weapons.vExplosionColour[CurrentTarget] = cGame_Bike[PlayerID].Colour.vBikeColourTarget;
					TotalDamageDoneLoop += (int)fSecondaryDamage;
				}

				if(bApplyRadiusDamage)
				{
					//Apply Radius Damage to all in area
					D3DXVECTOR3 vBikeTargetSecondPass = D3DXVECTOR3(0.0f,0.0f,0.0f);
					float Distance = 0.0f;
					for(int i=0;i<=gAi_Max_Count;i++)
					{
						vBikeTargetSecondPass = cGame_Bike[i].Manager.vBikeOutput;
						Distance = iVectorLength(&(vBikeTarget - vBikeTargetSecondPass));
						if(i!=CurrentTarget &&
							i!=PlayerID &&
							Distance < cGame_Upgrades.fMissileRadius[PlayerID])
						{
							///Update new damage
							fSecondaryDamage = iFloatInterpolate(Distance,0.0f,cGame_Upgrades.fMissileRadius[PlayerID],fSecondaryDamage,fSecondaryDamage / 5.0f);
							DamageSend(i,&fSecondaryDamage,0.0f,WeaponIdUsed);
							TotalDamageDoneLoop += (int)fSecondaryDamage;
						}
					}
					SecondaryProjectileAliveTime = SecondaryProjectileAliveTimeMax;
				}
			}
			//Close-reset
			else
			{
				Reset_Secondary();
			}
		}
		//-------------------------------------------------------------
		//END - Secondary Weapon 0 (MISSILE)
		//-------------------------------------------------------------
		//-------------------------------------------------------------
		//Secondary Weapon 1 (ShockWave)
		//-------------------------------------------------------------
		else if(SecondaryWeaponType==1)
		{
			//-------------------------------------------------------------
			//Setup the projectile
			if(!bSecondaryProjectileSetup)
			{
				//Init Data
				SecondaryProjectileAliveTimeMax = 360;
				fSecondaryDamage = cGame_Upgrades.fShoxwaveDamage[PlayerID];
				///Check for AI Output Damage
				if(PlayerID < gAi_Max_Count && 
					Networked_Ai_Type <= 0)
				{
					fSecondaryDamage = fSecondaryDamage * gAiWeaponsDamageMulti;
				}
				///Check for Double Damage
				if(bUtilityInUse && UtilityType==2)
				{
					fSecondaryDamage = fSecondaryDamage * 2.0f;
				}
				//Location
				///Set Location/orientation to match bike
				D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
				iVectorRotate(&vUp,&vUp,q1);
				vSecondaryProjectile = *v1;
				qSecondaryProjectile = *q1;//qLookAt
				///scan+place
				if(iProjectile_Floor(vSecondaryProjectile,qSecondaryProjectile,5.0f,3.5f))
				{
				}
				D3DXQUATERNION qLookAt;
				iQuaternionLookAt(&qLookAt,&vSecondaryProjectile,&vCrosshairOrigin,&vUp);
				qSecondaryProjectile = qLookAt;
				fSecondaryProjectileTravelSpeed = *in_speed + 0.5f;
				bSecondaryProjectileSetup = true;
			}
			//Update location for active projectiles
			else if(SecondaryProjectileAliveTime < SecondaryProjectileAliveTimeMax)
			{
				//---------------------
				//Travel Speed Update
				fSecondaryProjectileTravelSpeed += cGame_Upgrades.fShoxwaveTravel[PlayerID];
				//Steer to target
				D3DXVECTOR3 vScanSteerCp = D3DXVECTOR3(0.0f,0.0f,0.0f);
				D3DXVECTOR3 vScanSteerCn = D3DXVECTOR3(0.0f,0.0f,0.0f);
				D3DXQUATERNION qScanLeft;
				D3DXQUATERNION qScanRight;
				float fScanLeft_DistanceCp = 90.0f;
				float fScanRight_DistanceCp = 90.0f;
				iQuaternionFromEulerAngles(&qScanLeft,-10.0f,-25.0f,0.0f);
				iQuaternionFromEulerAngles(&qScanRight,-10.0f,25.0f,0.0f);
				iQuaternionMultiply(&qScanLeft,&qScanLeft,&qSecondaryProjectile);
				iQuaternionMultiply(&qScanRight,&qScanRight,&qSecondaryProjectile);

				if(iPhysxActorRaycastClosestStaticShape(cGame_Track.Physx.PhysxActor_Wall,
														&vSecondaryProjectile,
														&qScanLeft,
														90.0f,
														&vScanSteerCp,
														&vScanSteerCn,
														fScanLeft_DistanceCp,
														true))
				{
				}
				if(iPhysxActorRaycastClosestStaticShape(cGame_Track.Physx.PhysxActor_Wall,
														&vSecondaryProjectile,
														&qScanRight,
														90.0f,
														&vScanSteerCp,
														&vScanSteerCn,
														fScanRight_DistanceCp,
														true))
				{
				}
				float Steering = 0.0f;
				iFloatTendTo2(Steering,fScanRight_DistanceCp - fScanLeft_DistanceCp,12.0f);
				D3DXQUATERNION qSteer;
				iQuaternionFromEulerAngles(&qSteer,0.0f,Steering,0.0f);
				iQuaternionMultiply(&qSecondaryProjectile,&qSteer,&qSecondaryProjectile);
				//Follow track
				if(iProjectile_Floor(vSecondaryProjectile,qSecondaryProjectile,fSecondaryProjectileTravelSpeed,3.5f))
				{
					///Update Alive time
					SecondaryProjectileAliveTime++;
				}
				else
				{
					SecondaryProjectileAliveTime = SecondaryProjectileAliveTimeMax;
				}
				//Check for hit
				for(int i=0;i<=gAi_Max_Count;i++)
				{
					D3DXVECTOR3 vBikeTarget = cGame_Bike[i].Manager.vBikeOutput;
					if(i!=PlayerID &&
						iVectorLength(&(vSecondaryProjectile - vBikeTarget)) < 20.0f)
					{
						DamageSend(i,&fSecondaryDamage,cGame_Upgrades.fShoxwaveReduction[PlayerID],WeaponIdUsed);
						TotalDamageDoneLoop += (int)(fSecondaryDamage);
					}
				}
			}
			//Close-reset
			else
			{
				Reset_Secondary();
			}
		}
		//-------------------------------------------------------------
		//END - Secondary Weapon 1 (SHOCKWAVE)
		//-------------------------------------------------------------
		//-------------------------------------------------------------
		//Secondary Weapon 2 (AOE BURST)
		//-------------------------------------------------------------
		else if(SecondaryWeaponType==2)
		{
			//-------------------------------------------------------------
			//Setup the projectile
			if(!bSecondaryProjectileSetup)
			{
				//Init Data
				SecondaryProjectileAliveTimeMax = 45;
				fSecondaryDamage = iFloatInterpolate((float)SecondaryWeaponChargeTime,0.0f,(float)SecondaryWeaponChargeTimeMax,cGame_Upgrades.fEmBurstDamageMin[PlayerID],cGame_Upgrades.fEmBurstDamageMax[PlayerID]);
				///Check for AI Output Damage
				if(PlayerID < gAi_Max_Count && 
					Networked_Ai_Type <= 0)
				{
					fSecondaryDamage = fSecondaryDamage * gAiWeaponsDamageMulti;
				}
				///Check for Double Damage
				if(bUtilityInUse && UtilityType==2)
				{
					fSecondaryDamage = fSecondaryDamage * 2.0f;
				}
				//Location
				///Set Location/orientation
				vSecondaryProjectile = iVectorLocationOffset(v1,q1,&D3DXVECTOR3(0.0f,-1.0f,0.0f));
				qSecondaryProjectile = *q1;
				bSecondaryProjectileSetup = true;
			}
			//Update location for active projectiles
			else if(SecondaryProjectileAliveTime < SecondaryProjectileAliveTimeMax)
			{
				///---------------------
				///Set Location/orientation
				qSecondaryProjectile = *q1;
				vSecondaryProjectile = iVectorLocationOffset(v1,q1,&D3DXVECTOR3(0.0f,-0.5f,0.0f));
				///Update alive time
				SecondaryProjectileAliveTime++;
				//---------------------
				//Check for hit
				for(int i=0;i<=gAi_Max_Count;i++)
				{
					D3DXVECTOR3 vBikeTarget = vBikeTarget = cGame_Bike[i].Manager.vBikeOutput;

					if(i!=PlayerID &&
						iVectorLength(&(vSecondaryProjectile - vBikeTarget)) < cGame_Upgrades.fEmBurstRadius[PlayerID])
					{
						DamageSend(i,&fSecondaryDamage,cGame_Upgrades.fEmBurstReduction[PlayerID],WeaponIdUsed);
						TotalDamageDoneLoop += (int)(fSecondaryDamage);
						//break;
					}
				}
			}
			//Close-reset
			else
			{
				Reset_Secondary();
			}
		}
		//-------------------------------------------------------------
		//END - Secondary Weapon 2 (EM BURST)
		//-------------------------------------------------------------
		//-------------------------------------------------------------
		//Secondary Weapon 3 (RAIL)
		//-------------------------------------------------------------
		else if(SecondaryWeaponType==3)
		{
			//-------------------------------------------------------------
			//Setup the projectile
			if(!bSecondaryProjectileSetup)
			{
				//Init Data
				SecondaryProjectileAliveTimeMax = 60;
				fSecondaryProjectileTravelSpeed = cGame_Upgrades.fRailTravel[PlayerID];
				fSecondaryDamage = iFloatInterpolate((float)SecondaryWeaponChargeTime,1.0f,(float)SecondaryWeaponChargeTimeMax,cGame_Upgrades.fRailDamageMin[PlayerID],cGame_Upgrades.fRailDamageMax[PlayerID]);
				///Check for AI Output Damage
				if(PlayerID < gAi_Max_Count && 
					Networked_Ai_Type <= 0)
				{
					fSecondaryDamage = fSecondaryDamage * gAiWeaponsDamageMulti;
				}
				///Check for Double Damage
				if(bUtilityInUse && UtilityType==2)
				{
					fSecondaryDamage = fSecondaryDamage * 2.0f;
				}
				//Location
				///Set Location/orientation to match bike
				D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
				iVectorRotate(&vUp,&vUp,q1);
				vSecondaryProjectile = *v1;
				qSecondaryProjectile = *q1;//qLookAt
				///scan+place
				if(iProjectile_Floor(vSecondaryProjectile,qSecondaryProjectile,5.0f,2.5f))
				{
				}
				D3DXQUATERNION qLookAt;
				iQuaternionLookAt(&qLookAt,&vSecondaryProjectile,&vCrosshairOrigin,&vUp);
				qSecondaryProjectile = qLookAt;
				bSecondaryProjectileSetup = true;
			}
			//Update location for active projectiles
			else if(SecondaryProjectileAliveTime < SecondaryProjectileAliveTimeMax)
			{
				//D3DXVECTOR3 vBikeTarget = D3DXVECTOR3(0.0f,0.0f,0.0f);
				//float MaxDistance = 25.0f;
				//bool bSteerToTarget = false;
				//for(int i=0;i<=gAi_Max_Count;i++)
				//{

				//	D3DXVECTOR3 vNewTarget = D3DXVECTOR3(0.0f,0.0f,0.0f);
				//	float Distance = MaxDistance;
				//	if(i!=PlayerID && i==gAi_Max_Count)
				//	{
				//		Distance = iVectorLength(&(cGame_Bike[gAi_Max_Count].Manager.vBikeOutput-vSecondaryProjectile));
				//		if(Distance<MaxDistance)
				//		{
				//			D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
				//			D3DXVECTOR3 vRotations = D3DXVECTOR3(0.0f,0.0f,0.0f);
				//			D3DXQUATERNION qInfront;
				//			iVectorRotate(&vUp,&vUp,&qSecondaryProjectile);
				//			iQuaternionLookAt(&qInfront,&vSecondaryProjectile,&cGame_Bike[gAi_Max_Count].Manager.vBikeOutput,&vUp);
				//			iQuaternionDelta(&qInfront,&qSecondaryProjectile,&qInfront);
				//			iQuaternionToEulerAngles(&qInfront,&vRotations);
				//			if(abs(vRotations.y) < 45.0f)
				//			{
				//				vBikeTarget = cGame_Bike[gAi_Max_Count].Manager.vBikeOutput;
				//				MaxDistance = Distance;
				//				bSteerToTarget = true;
				//			}
				//		}
				//	}
				//	else if(i!=PlayerID)
				//	{
				//		Distance = iVectorLength(&(cGame_Bike[i].Manager.vBikeOutput-vSecondaryProjectile));
				//		if(Distance<MaxDistance)
				//		{
				//			D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
				//			D3DXVECTOR3 vRotations = D3DXVECTOR3(0.0f,0.0f,0.0f);
				//			D3DXQUATERNION qInfront;
				//			iVectorRotate(&vUp,&vUp,&qSecondaryProjectile);
				//			iQuaternionLookAt(&qInfront,&vSecondaryProjectile,&cGame_Bike[i].Manager.vBikeOutput,&vUp);
				//			iQuaternionDelta(&qInfront,&qSecondaryProjectile,&qInfront);
				//			iQuaternionToEulerAngles(&qInfront,&vRotations);
				//			if(abs(vRotations.y) < 45.0f)
				//			{
				//				vBikeTarget = cGame_Bike[i].Manager.vBikeOutput;
				//				MaxDistance = Distance;
				//				bSteerToTarget = true;
				//			}
				//		}
				//	}
				//}
				//if(bSteerToTarget)
				//{
				////Steer to target
					//D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
					//D3DXVECTOR3 vRotations = D3DXVECTOR3(0.0f,0.0f,0.0f);
					//D3DXQUATERNION qSteer;
					//iVectorRotate(&vUp,&vUp,&qSecondaryProjectile);
					//iQuaternionLookAt(&qSteer,&vSecondaryProjectile,&vBikeTarget,&vUp);
					//iQuaternionDelta(&qSteer,&qSecondaryProjectile,&qSteer);
					//iQuaternionToEulerAngles(&qSteer,&vRotations);
					//iQuaternionFromEulerAngles(&qSteer,0.0f,vRotations.y,0.0f);
					//iQuaternionMultiply(&qSecondaryProjectile,&qSteer,&qSecondaryProjectile);
				//}


				///Follow Track Floor
				if(iProjectile_Floor(vSecondaryProjectile,qSecondaryProjectile,fSecondaryProjectileTravelSpeed,2.5f))
				{
					///Update Alive time
					SecondaryProjectileAliveTime++;
				}
				else
				{
					SecondaryProjectileAliveTime = SecondaryProjectileAliveTimeMax;
				}
				//---------------------
				//Check for hit
				D3DXVECTOR3 vBikeTarget = D3DXVECTOR3(0.0f,0.0f,0.0f);
				for(int i=0;i<=gAi_Max_Count;i++)
				{
					vBikeTarget = cGame_Bike[i].Manager.vBikeOutput;

					if(i!=PlayerID &&
						iVectorLength(&(vSecondaryProjectile - vBikeTarget)) < gSecondaryRadiusRail)
					{
						DamageSend(i,&fSecondaryDamage,0.0f,WeaponIdUsed);
						TotalDamageDoneLoop += (int)fSecondaryDamage;
						break;
					}
				}
			}
			//Close-reset
			else
			{
				Reset_Secondary();
			}
		}
		//-------------------------------------------------------------
		//END - Secondary Weapon 3 (RAIL)
		//-------------------------------------------------------------
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - DamageRecieve
///*****************************************************************
void Game_Bike_Weapons::DamageRecieve(void)
{
	//-------------------------------------------------------------
	if(fInDamage > 0.0f)
	{
		//-------------------------------------------------------------
		//Apply incomming weapon damage ID's
		WeaponId_Out = WeaponId_In;
		bBeingHit = true;
		//-------------------------------------------------------------
		//Hitsound for Active Player
		if(InDamagePlayerID==cGame_Camera.SpectateId)
		{
			cGame_Audio.Weapons.Play_Hitsound(fInDamage);
		}
		//-------------------------------------------------------------
		//Incomming Damage for Player
		const float BikeColourDivide = 2.5f;
		float ShieldTarget = iFloatInterpolate(cGame_Bike[PlayerID].Energy.fEnergy,gEnergyWarningLimit,cGame_Upgrades.fEnergyMax[PlayerID],0.02f,1.5f);
		///Utility Damage Checks
		if(bUtilityInUse)
		{
			if(UtilityType==0)///Shield
			{
				cGame_Bike[PlayerID].Energy.fEnergy += (fInDamage * cGame_Upgrades.fShieldInvConvert[PlayerID]);
				fInDamage = 0.0f;
			}
			else if(UtilityType==3)///Warp
			{
				fInDamage *= cGame_Upgrades.fWarpDamageReduce[PlayerID];
			}
		}
		///Apply damage
		cGame_Bike[PlayerID].Energy.fEnergy -= fInDamage;
		cGame_Bike[PlayerID].Colour.vBikeColour /= BikeColourDivide;
		cGame_Bike[PlayerID].Colour.vShieldColour = D3DXVECTOR3(2.0f,ShieldTarget,ShieldTarget / 4.0f);
		///Check for death - Apply kill count
		if(cGame_Bike[PlayerID].Energy.fEnergy < 0.0f)
		{
			if(cGame_Replay.State!=2)///Playback
			{
				cGame_Bike[InDamagePlayerID].Weapons.TotalKills++;
				TotalDeaths++;
			}
			cGame_Bike[InDamagePlayerID].Weapons.MultiKillTotal++;
			cGame_Bike[InDamagePlayerID].Weapons.MultiKillTimer = 0;
			cGame_Particle.Explosion_Intensity[PlayerID] = (int)gParticle_Explosion_WeaponHitMaxEmit;
			KilledByID = InDamagePlayerID;
			WeaponId_KilledBy = WeaponId_In;
			bKilledBySend = true;
		}
		//-------------------------------------------------------------
		//Update Particle Send
		cGame_Particle.bExplosion_InUse[PlayerID] = true;
		cGame_Particle.Explosion_Intensity[PlayerID] += (int)iFloatInterpolate(fInDamage,1.0f,100.0f,5.0f,gParticle_Explosion_WeaponHitMaxEmit);
		if(cGame_Particle.Explosion_Intensity[PlayerID] > gParticle_Explosion_MaxCreate)
		{
			cGame_Particle.Explosion_Intensity[PlayerID] = gParticle_Explosion_MaxCreate;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - WEAPONS - UPDATE PLAYER
///*****************************************************************
void Game_Bike_Weapons::Update_Player(D3DXVECTOR3 *v1, D3DXQUATERNION *q1, float *in_speed)
{
	//-------------------------------------------------------------
	//Reset any flags
	bBeingHit = false;
	bPrimaryFired = false;
	bSecondaryWeaponCharging = false;
	bSecondaryFired = false;
	bUtilityFired = false;
	bKilledBySend = false;
	TotalDamageDoneLoop = 0;
	WeaponId_Out = -1;
	//-------------------------------------------------------------
	//Inputs and Damage updates (ALIVE - GAME RUNNING - WEAPONS ON)
	if(cGame_Bike[gAi_Max_Count].Energy.bAlive && 
		gRaceState>=1 &&
		cGame_RaceTracker.bBikeRacing[gAi_Max_Count])
	{
		//-------------------------------------------------------------
		//Player Input
		Player_InputControls();
		//-------------------------------------------------------------
		//Utility Trigger
		Utility_Trigger();
		//Utility Projectile
		Utility_Projectile();
		//-------------------------------------------------------------
		//Update Incomming Damage
		DamageRecieve();
		//-------------------------------------------------------------
		//Update Triggers
		///Primary Weapon Trigger
		PrimaryGun_Trigger();
		///Secondary Weapon Trigger
		SecondaryGun_Trigger();
		///Tracking
		Player_MissleTracking();
	}
	else
	{
		Reset_Secondary();
		Reset_Utility();
	}
	//-------------------------------------------------------------
	//Update Projectiles
	///Primary Weapon Projectile
	PrimaryGun_Projectile(v1,q1,in_speed);
	///Secondary Weapon Projectile
	SecondaryGun_Projectile(v1,q1,in_speed);
	//-------------------------------------------------------------
	//Update damage output score
	TotalDamageOutput += TotalDamageDoneLoop;
	///Check for Double damage upgrade
	if(bUtilityInUse && 
		UtilityType==2)
	{
		cGame_Bike[gAi_Max_Count].Energy.fEnergy += ((float)TotalDamageDoneLoop * cGame_Upgrades.fDoubleDamageConv[PlayerID]);
	}
	//-------------------------------------------------------------
	//MultiKill update
	MultiKillSystem();
	//-------------------------------------------------------------
	//Reset states
	TotalDamageReceived += (int)fInDamage;
	fInDamage = 0.0f;
	WeaponId_In = -1;
	//-------------------------------------------------------------
	//Net Send
	Net_CheckAndSend();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - WEAPONS - UPDATE AI
///*****************************************************************
void Game_Bike_Weapons::Update_Ai(D3DXVECTOR3 *v1, D3DXQUATERNION *q1, float *in_speed, int *NetAiType)
{
	//-------------------------------------------------------------
	//Reset any flags
	bBeingHit = false;
	Networked_Ai_Type = *NetAiType;
	bPrimaryFired = false;
	bSecondaryWeaponCharging = false;
	bSecondaryFired = false;
	bUtilityFired = false;
	bKilledBySend = false;
	TotalDamageDoneLoop = 0;
	WeaponId_Out = -1;
	//-------------------------------------------------------------
	//Inputs and Damage updates
	if(cGame_Bike[PlayerID].Energy.bAlive && 
		gRaceState>=1 &&
		cGame_RaceTracker.bBikeRacing[PlayerID])
	{
		//-------------------------------------------------------------
		//Player Input
		Ai_InputControls();
		//-------------------------------------------------------------
		//Utility Trigger
		Utility_Trigger();
		//Utility Projectile (must be before damageupdatecontroller)
		Utility_Projectile();
		//-------------------------------------------------------------
		//Update Incomming Damage
		DamageRecieve();
		//Print Player Damage Readout
		PlayerDamageDoneReadout();
		//-------------------------------------------------------------
		//Triggers
		///Primary Weapon Trigger
		PrimaryGun_Trigger();
		///Secondary Weapon Trigger
		SecondaryGun_Trigger();
		if(Networked_Ai_Type==0)
		{
			///Secondary Weapon Tracking
			Ai_MissleTracking();
		}
		else
		{
			///Secondary Weapon Tracking
			Network_MissleTracking();
		}
	}
	else
	{
		Reset_Secondary();
		Reset_Utility();
	}
	//-------------------------------------------------------------
	//Projectiles
	///Primary Weapon Projectile
	PrimaryGun_Projectile(v1,q1,in_speed);
	///Secondary Weapon Projectile
	SecondaryGun_Projectile(v1,q1,in_speed);
	//-------------------------------------------------------------
	//Update damage output score
	TotalDamageOutput += TotalDamageDoneLoop;
	///Check for Double damage upgrade
	if(bUtilityInUse && 
		UtilityType==2)
	{
		cGame_Bike[PlayerID].Energy.fEnergy += ((float)TotalDamageDoneLoop * cGame_Upgrades.fDoubleDamageConv[PlayerID]);
	}
	//-------------------------------------------------------------
	//MultiKill update
	MultiKillSystem();
	//-------------------------------------------------------------
	//Reset states
	TotalDamageReceived += (int)fInDamage;
	fInDamage = 0.0f;
	WeaponId_In = -1;
	//-------------------------------------------------------------
	//Net Send
	Net_CheckAndSend();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - WEAPONS - Update_Replay
///*****************************************************************
void Game_Bike_Weapons::Update_Replay(D3DXVECTOR3 *v1, D3DXQUATERNION *q1, float *in_speed)
{
	//-------------------------------------------------------------
	//Reset any flags
	bBeingHit = false;
	Networked_Ai_Type = 1;
	bPrimaryFired = false;
	bSecondaryWeaponCharging = false;
	bSecondaryFired = false;
	bUtilityFired = false;
	bKilledBySend = false;
	TotalDamageDoneLoop = 0;
	WeaponId_Out = -1;
	//-------------------------------------------------------------
	//Inputs and Damage updates
	if(cGame_Bike[PlayerID].Energy.bAlive &&
		gWeaponsEnable)
	{
		//-------------------------------------------------------------
		//Net Input (uses NetType = 1)
		Ai_InputControls();
		//-------------------------------------------------------------
		//Utility Trigger
		Utility_Trigger();
		//Utility Projectile (must be before damageupdatecontroller)
		Utility_Projectile();
		//-------------------------------------------------------------
		//Update Incomming Damage
		DamageRecieve();
		//Print Player Damage Readout
		//PlayerDamageDoneReadout();
		//-------------------------------------------------------------
		//Triggers
		///Primary Weapon Trigger
		PrimaryGun_Trigger();
		///Secondary Weapon Trigger
		SecondaryGun_Trigger();
		///Secondary Weapon Tracking
		Network_MissleTracking();
	}
	else
	{
		Reset_Secondary();
		Reset_Utility();
	}
	//-------------------------------------------------------------
	//Projectiles
	///Primary Weapon Projectile
	PrimaryGun_Projectile(v1,q1,in_speed);
	///Secondary Weapon Projectile
	SecondaryGun_Projectile(v1,q1,in_speed);
	//-------------------------------------------------------------
	//Update damage output score
	//TotalDamageOutput += TotalDamageDoneLoop;
	//-------------------------------------------------------------
	//MultiKill update
	MultiKillSystem();
	//-------------------------------------------------------------
	//Reset states
	fInDamage = 0.0f;
	WeaponId_In = -1;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - MultiKillSystem
///*****************************************************************
void Game_Bike_Weapons::MultiKillSystem(void)
{
	//-------------------------------------------------------------
	MultiKillName = "";
	MultiKillType = -1;
	//-------------------------------------------------------------
	if(MultiKillTotal>=1)
	{
		if(MultiKillTotal==2)
		{
			MultiKillName = "Double Kill";
			MultiKillType = 0;
		}
		else if(MultiKillTotal==3)
		{
			MultiKillName = "Multi Kill";
			MultiKillType = 1;
		}
		else if(MultiKillTotal==4)
		{
			MultiKillName = "Connect -Four";
			MultiKillType = 2;
		}
		else if(MultiKillTotal==5)
		{
			MultiKillName = "Rub a Jack!";
			MultiKillType = 3;
		}
		///Holy Shit!
		else if(MultiKillTotal>5)
		{
			MultiKillName = "Holy Shit Batma... " + (string)gPlayerName;
			MultiKillType = 4;
		}

		//Update Timer
		MultiKillTimer++;
		if(MultiKillTimer>=gMaxMultiKillTimer)
		{
			///Reset
			MultiKillTotal = 0;
			MultiKillTimer = gMaxMultiKillTimer;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - Net_CheckAndSend
///*****************************************************************
void Game_Bike_Weapons::Net_CheckAndSend(void)
{
	//-------------------------------------------------------------
	//Primary done via activation (key press)
	//NetFirePrimary = 0;
	//if(bPrimaryFired)
	//{
	//	NetFirePrimary = 1;
	//}

	//Secondary
	NetFireSecondary = -2;
	if(bSecondaryWeaponCharging)///Charging
	{
		NetFireSecondary = -1;
	}
	else if(bSecondaryInUse)
	{
		NetFireSecondary = SecondaryWeaponType;
		NetSecondaryLockedId = CurrentTarget;
	}

	NetFireUtility = -1;
	if(bUtilityInUse)
	{
		NetFireUtility = UtilityType;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - Reset_Utility
///*****************************************************************
void Game_Bike_Weapons::Reset_Utility(void)
{
	//-------------------------------------------------------------
	//Close-reset
	bUtilityInUse = false;
	UtilityType = -1;
	bUtilityProjectileSetup = false;
	UtilityAliveTime = 0;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - Reset_Secondary
///*****************************************************************
void Game_Bike_Weapons::Reset_Secondary(void)
{
	//-------------------------------------------------------------
	fSecondaryProjectileTravelSpeed = 0.0f;
	Tracking_Timer = 0;
	bSecondaryInUse = false;
	SecondaryWeaponType = -1;
	bSecondaryProjectileSetup = false;
	SecondaryProjectileAliveTime = 0;
	SecondaryWeaponChargeTime = 0;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - Reset_Primary
///*****************************************************************
void Game_Bike_Weapons::Reset_Primary(int Index)
{
	//-------------------------------------------------------------
	bPrimaryProjectileSetup[Index] = false;
	PrimaryProjectileAliveTime[Index] = 0;
	bPrimaryProjectileInUse[Index] = false;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - WEAPONS - Reset_Replay
///*****************************************************************
void Game_Bike_Weapons::Reset_Replay(void)
{
	//-------------------------------------------------------------
	//Flush Weapons
	for(int i=0;i<MAX_PRIMARY_PROJECTILES_PER_BIKE;i++)
	{
		Reset_Primary(i);
	}
	Reset_Utility();
	Reset_Secondary();
	//Flush incomming damage
	fInDamage = 0.0f;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - WEAPONS - DamageApply
///*****************************************************************
void Game_Bike_Weapons::DamageSend(int index, float *fDamage, float fSpeedReduction, int WeaponId)
{
	//-------------------------------------------------------------
	///Slow Bike Speed
	if(cGame_Bike[index].Manager.fAcceleration_Speed > 0.5f)
	{
		cGame_Bike[index].Manager.fAcceleration_Speed -= fSpeedReduction;
	}
	///Apply Damage to AI Bikes
	cGame_Bike[index].Weapons.InDamagePlayerID = PlayerID;
	cGame_Bike[index].Weapons.fInDamage += *fDamage;
	cGame_Bike[index].Weapons.WeaponId_In = WeaponId;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - WEAPONS - ShieldRespawnActivator
///*****************************************************************
void Game_Bike_Weapons::ShieldRespawnActivator(void)
{
	//-------------------------------------------------------------
	//Activate shield for respawn
	if(gWeaponsEnable)
	{
		bUtilityInUse = true;
		UtilityType = 0;
		UtilityAliveTime = 0;
		UtilityAliveTimeMax = gRespawnShieldTimeMax;
		bUtilityProjectileSetup = true;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - WEAPONS - DESTROY
///*****************************************************************
void Game_Bike_Weapons::Destroy(void)
{
	//-------------------------------------------------------------
	ZeroData(0);
	//-------------------------------------------------------------
}