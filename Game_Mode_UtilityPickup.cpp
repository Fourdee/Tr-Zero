//-----------------------------------------------------------------
// About:
//
// name: "Game_Mode_UtilityPickup.cpp:
//
// usage: Enables/Updates Track Utility Pickups
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Mode_UtilityPickup.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - MODE - UTILITYPICKUP - CONSTRUCTORS
///*****************************************************************
Game_Mode_UtilityPickup::Game_Mode_UtilityPickup(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Mode_UtilityPickup::~Game_Mode_UtilityPickup(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - MODE - UTILITYPICKUP - ZERODATA
///*****************************************************************
void Game_Mode_UtilityPickup::ZeroData(void)
{
	//-------------------------------------------------------------
	bPickupsEnable = false;
	for(int i=0;i<MAX_UTILITY_PICKUPS;i++)
	{
		PickupResetTimer[i] = 0;
		PickupReady[i] = false;
		vPickup[i] = D3DXVECTOR3(0.0f,-5000.0f,0.0f);
		qPickup[i] = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - MODE - UTILITYPICKUP - PICKUPTRACKLOCATIONS
///*****************************************************************
void Game_Mode_UtilityPickup::PickupTrackLocations(void)
{
	//-------------------------------------------------------------
	if(gGameState==1) //VOLEX
	{
		vPickup[0] = D3DXVECTOR3(69.9f,-357.0f,-260.0f);
		iQuaternionFromEulerAngles(&qPickup[0],90.0f,0.0f,0.0f);//down
		vPickup[1] = D3DXVECTOR3(-654.1f,119.0f,-142.5f);
		//iQuaternionFromEulerAngles(&qPickup[1],90.0f,0.0f,0.0f);//down
		vPickup[2] = D3DXVECTOR3(-240.0f,-870.0f,43.9f);
		iQuaternionFromEulerAngles(&qPickup[2],90.0f,0.0f,0.0f);//down
		//vPickup[3] = D3DXVECTOR3(-255.0f,-870.1f,43.9f);
		//iQuaternionFromEulerAngles(&qPickup[3],90.0f,0.0f,0.0f);//down
		//vPickup[4] = D3DXVECTOR3(-678.2f,118.0f,-174.5f);
		///iQuaternionFromEulerAngles(&qPickup[0],-180.0f,0.0f,0.0f);//back
		///iQuaternionFromEulerAngles(&qPickup[0],90.0f,0.0f,0.0f);//down
		///iQuaternionFromEulerAngles(&qPickup[0],0.0f,90.0f,0.0f);//right
	}
	else if(gGameState==2)//Silence
	{
		vPickup[0] = D3DXVECTOR3(0.0f,573.4f,1450.8f);
		iQuaternionFromEulerAngles(&qPickup[0],180.0f,0.0f,0.0f);///Up
		vPickup[1] = D3DXVECTOR3(0.0f,-220.0f,14.5f);
		iQuaternionFromEulerAngles(&qPickup[1],180.0f,0.0f,0.0f);///Up
		vPickup[2] = D3DXVECTOR3(0.0f,-181.5f,1509.6f);
	}
	else if(gGameState==3)//Phantom
	{
		vPickup[0] = D3DXVECTOR3(12.5f,-180.0f,247.9f);
		vPickup[1] = D3DXVECTOR3(261.7f,917.3f,396.4f);
		vPickup[2] = D3DXVECTOR3(510.8f,-74.5f,-979.6f);
	}
	else if(gGameState==10)//Rez
	{
		vPickup[0] = D3DXVECTOR3(0.0f,0.05f,0.0f);
		vPickup[1] = D3DXVECTOR3(0.0f,350.0f,569.0f);
		iQuaternionFromEulerAngles(&qPickup[1],-90.0f,0.0f,0.0f);///forward
		vPickup[2] = D3DXVECTOR3(0.0f,350.0f,-569.0f);
		iQuaternionFromEulerAngles(&qPickup[2],90.0f,0.0f,0.0f);///Back
	}
	//-------------------------------------------------------------
	//Scan rotate
	for(int i=0;i<MAX_UTILITY_PICKUPS;i++)
	{
		float fScanLength = 25.0f;
		float fScanDown_DistanceCp = 0.0f;
		D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,0.0f,1.0f);
		D3DXVECTOR3 vScanDownCp = D3DXVECTOR3(0.0f,0.0f,0.0f);
		D3DXVECTOR3 vScanDownCn = D3DXVECTOR3(0.0f,0.0f,0.0f);
		D3DXQUATERNION q1 = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
		if(iPhysxActorRaycastClosestStaticShape(cGame_Track.Physx.PhysxActor_Floor,
											&vPickup[i],
											&qPickup[i],
											fScanLength,
											&vScanDownCp,
											&vScanDownCn,
											fScanDown_DistanceCp,
											true))
		{
			iVectorRotate(&vUp,&vUp,&qPickup[i]);
			iQuaternionLookAt(&qPickup[i],&vScanDownCp,&(vScanDownCp+vScanDownCn),&vUp);
			vPickup[i] = iVectorLocationOffset(&vScanDownCp,&qPickup[i],&D3DXVECTOR3(0.0f,0.0f,0.1f));
			iQuaternionFromEulerAngles(&q1,90.0f,0.0f,0.0f);
			iQuaternionMultiply(&qPickup[i],&q1,&qPickup[i]);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - UTILITYPICKUP - CREATE
///*****************************************************************
void Game_Mode_UtilityPickup::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	PickupTrackLocations();
	//Set Locations
	for(int i=0;i<MAX_UTILITY_PICKUPS;i++)
	{
		iMeshImposterLocationSet(cGame_Mesh.Track_Pickup.Pickup_Utility,i,&vPickup[i],true);
		iMeshImposterOrientationSet(cGame_Mesh.Track_Pickup.Pickup_Utility,i,&qPickup[i],true);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - UTILITYPICKUP - UPDATE
///*****************************************************************
void Game_Mode_UtilityPickup::Update(void)
{
	//-------------------------------------------------------------
	//Start Pickups when Game Weapons are enabled
	if(!bPickupsEnable && gWeaponsEnable)
	{
		for(int i=0;i<MAX_UTILITY_PICKUPS;i++)
		{
			PickupReady[i] = true;
		}
		bPickupsEnable = true;
	}
	//-------------------------------------------------------------
	//Update Pickup System
	else if(bPickupsEnable)
	{
		//---------------------------------------------------------
		for(int i=0;i<MAX_UTILITY_PICKUPS;i++)
		{
			//Pickups Ready
			if(PickupReady[i])
			{
				////DEBUG
				//D3DXVECTOR2 v2D;
				//if(i3DLocationToScreen(&v2D,&vPickup[i],gCamera))
				//{
				//	iPrint((char*)"X",cGame_Font.f32pt,&v2D,&D3DXVECTOR4(1.0f,0.5f,0.0f,1.0f),gFont,false);
				//}
				//Show Mesh
				iMeshImposterShow(cGame_Mesh.Track_Pickup.Pickup_Utility,i,false);

				for(int a=0;a<=gAi_Max_Count;a++)
				{
					//Define all active bikes
					D3DXVECTOR3 vBikeTarget = D3DXVECTOR3(0.0f,0.0f,0.0f);
					int UtilityCheck = -1;
					bool bAlive = false;
					vBikeTarget = cGame_Bike[a].Manager.vBikeOutput;
					UtilityCheck = cGame_Bike[a].Weapons.UtilityType;
					bAlive = cGame_Bike[a].Energy.bAlive;
					//Check Range
					if(iVectorLength(&(vPickup[i] - vBikeTarget)) <= gPickupRadius &&
						bAlive &&
						UtilityCheck==-1)
					{
						//Give player utility
						UtilityCheck = iIntRand(0,MAX_UTILITY_TYPES);
						///Arena Swap auto pilot to warp
						if(gGameMode==5 && UtilityCheck==1)
						{
							UtilityCheck = 3;
						}
						///Non-arena, swap warp for auto pilot
						else if(gGameMode<5 && UtilityCheck==3)
						{
							UtilityCheck = 1;
						}

						if(a==gAi_Max_Count)
						{
							cGame_Bike[gAi_Max_Count].Weapons.UtilityType = UtilityCheck;
						}
						else
						{
							if(UtilityCheck==1)///AutoPilot - Cancel for AI
							{
								UtilityCheck = -1;
							}
							cGame_Bike[a].Weapons.UtilityType = UtilityCheck;
						}
						PickupReady[i] = false;
						break;
					}
				}
			}
			//Pickups Not Ready
			else if(PickupResetTimer[i] < gPickupTimerReset)
			{
				iMeshImposterHide(cGame_Mesh.Track_Pickup.Pickup_Utility,i,false);
				PickupResetTimer[i]++;
			}
			//Reset
			else
			{
				PickupReady[i] = true;
				PickupResetTimer[i] = 0;
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - UTILITYPICKUP - DESTROY
///*****************************************************************
void Game_Mode_UtilityPickup::Destroy(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}