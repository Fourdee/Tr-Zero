//-----------------------------------------------------------------
// About:
//
// name: "Game_Mode_EnergyPickup.cpp:
//
// usage: Enables/Updates Track Weapon Pickups
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Mode_EnergyPickup.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - MODE - ENERGYPICKUP - CONSTRUCTORS
///*****************************************************************
Game_Mode_EnergyPickup::Game_Mode_EnergyPickup(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Mode_EnergyPickup::~Game_Mode_EnergyPickup(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - MODE - ENERGYPICKUP - ZERODATA
///*****************************************************************
void Game_Mode_EnergyPickup::ZeroData(void)
{
	//-------------------------------------------------------------
	bPickupsEnable = false;
	for(int i=0;i<MAX_ENERGY_PICKUPS;i++)
	{
		PickupResetTimer[i] = 0;
		PickupReady[i] = false;
		vPickup[i] = D3DXVECTOR3(0.0f,-5000.0f,0.0f);
		qPickup[i] = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - MODE - ENERGYPICKUP - PICKUPTRACKLOCATIONS
///*****************************************************************
void Game_Mode_EnergyPickup::PickupTrackLocations(void)
{
	//-------------------------------------------------------------
	if(gGameState==1) //VOLEX
	{
		vPickup[0] = D3DXVECTOR3(-259.9f,-100.0f,117.0f);//
		//iQuaternionFromEulerAngles(&qPickup[0],0.0f,0.0f,0.0f);//forward
		vPickup[1] = D3DXVECTOR3(-240.0f,-305.7f,116.7f);//
		//iQuaternionFromEulerAngles(&qPickup[1],0.0f,0.0f,0.0f);//forward
		vPickup[2] = D3DXVECTOR3(-225.0f,-460.0f,116.5f);//
		//iQuaternionFromEulerAngles(&qPickup[2],0.0f,0.0f,0.0f);//forward
		vPickup[3] = D3DXVECTOR3(-240.0f,-300.0f,-36.6f);//
		iQuaternionFromEulerAngles(&qPickup[3],-180.0f,0.0f,0.0f);//back
		vPickup[4] = D3DXVECTOR3(-240.0f,-86.6f,-36.8f);//
		iQuaternionFromEulerAngles(&qPickup[4],-180.0f,0.0f,0.0f);//back
		vPickup[5] = D3DXVECTOR3(-468.6f,-22.4f,97.4f);//
		iQuaternionFromEulerAngles(&qPickup[5],90.0f,0.0f,0.0f);//down
		vPickup[6] = D3DXVECTOR3(-501.2f,-40.0f,112.5f);//
		iQuaternionFromEulerAngles(&qPickup[6],90.0f,0.0f,0.0f);//down
		vPickup[7] = D3DXVECTOR3(-428.3f,-357.9f,-832.7f);//
		iQuaternionFromEulerAngles(&qPickup[7],90.0f,0.0f,0.0f);//down
		vPickup[8] = D3DXVECTOR3(-300.7f,-357.6f,-356.8f);//
		iQuaternionFromEulerAngles(&qPickup[8],90.0f,0.0f,0.0f);//down
		vPickup[9] = D3DXVECTOR3(333.5f,245.1f,-353.1f);//
		iQuaternionFromEulerAngles(&qPickup[9],0.0f,90.0f,0.0f);//right
	}
	else if(gGameState==2)//Silence
	{
		vPickup[0] = D3DXVECTOR3(0.0f,-13.0f,709.6f);
		iQuaternionFromEulerAngles(&qPickup[0],0.0f,-90.0f,0.0f);///right

		vPickup[1] = D3DXVECTOR3(-20.0f,2.0f,210.0f);
		iQuaternionFromEulerAngles(&qPickup[1],90.0f,0.0f,0.0f);///down
		vPickup[2] = D3DXVECTOR3(18.9f,-24.9f,1147.9f);
		iQuaternionFromEulerAngles(&qPickup[2],180.0f,0.0f,0.0f);///Up
		vPickup[3] = D3DXVECTOR3(14.8f,461.6f,1701.0f);
		vPickup[4] = D3DXVECTOR3(-18.2f,32.0f,1762.8f);
		vPickup[5] = D3DXVECTOR3(12.3f,-210.4f,1210.9f);
		vPickup[6] = D3DXVECTOR3(-19.4f,-379.2f,-171.4f);
		iQuaternionFromEulerAngles(&qPickup[6],180.0f,0.0f,0.0f);///Up
		vPickup[7] = D3DXVECTOR3(18.0f,-529.9f,-417.6f);
		iQuaternionFromEulerAngles(&qPickup[7],180.0f,0.0f,0.0f);///Up
		vPickup[8] = D3DXVECTOR3(-18.0f,-529.9f,-417.6f);
		iQuaternionFromEulerAngles(&qPickup[8],180.0f,0.0f,0.0f);///Up
		vPickup[9] = D3DXVECTOR3(20.0f,2.0f,210.0f);
		iQuaternionFromEulerAngles(&qPickup[9],90.0f,0.0f,0.0f);///down
	}
	else if(gGameState==3)//Phantom
	{
		vPickup[0] = D3DXVECTOR3(259.5f,-49.3f,849.0f);//
		vPickup[1] = D3DXVECTOR3(-498.2f,-209.4f,337.2f);//
		vPickup[2] = D3DXVECTOR3(-219.0f,-92.4f,867.2f);//
		vPickup[3] = D3DXVECTOR3(-260.9f,182.1f,868.3f);//
		iQuaternionFromEulerAngles(&qPickup[3],180.0f,0.0f,0.0f);///Up
		vPickup[4] = D3DXVECTOR3(-83.5f,921.1f,426.2f);
		vPickup[5] = D3DXVECTOR3(240.0f,270.4f,477.0f);
		vPickup[6] = D3DXVECTOR3(531.3f,-97.4f,-804.7f);
		vPickup[7] = D3DXVECTOR3(187.5f,-112.9f,-895.1f);
		iQuaternionFromEulerAngles(&qPickup[7],90.0f,0.0f,0.0f);//down
		vPickup[8] = D3DXVECTOR3(144.5f,-64.5f,-693.2f);
		vPickup[9] = D3DXVECTOR3(-239.f,379.8f,481.8f);
	}
	else if(gGameState==10)//Rez
	{
		vPickup[0] = D3DXVECTOR3(135.0f,0.05f,90.0f);//
		vPickup[1] = D3DXVECTOR3(-135.0f,0.05f,-90.0f);//
		vPickup[2] = D3DXVECTOR3(0.0f,48.0f,539.0f);//
		vPickup[3] = D3DXVECTOR3(0.0f,48.0f,-539.0f);//
		iQuaternionFromEulerAngles(&qPickup[3],-180.0f,0.0f,0.0f);//back

		vPickup[4] = D3DXVECTOR3(90.0f,0.05f,-192.0f);//
		vPickup[5] = D3DXVECTOR3(-90.0f,0.05f,192.0f);//

		vPickup[6] = D3DXVECTOR3(454.0f,311.0f,394.0f);//
		vPickup[7] = D3DXVECTOR3(-454.0f,391.0f,394.0f);//

		vPickup[8] = D3DXVECTOR3(454.0f,311.0f,-394.0f);//
		vPickup[9] = D3DXVECTOR3(-454.0f,391.0f,-394.0f);//

		iQuaternionFromEulerAngles(&qPickup[6],0.0f,90.0f,0.0f);///front right
		iQuaternionFromEulerAngles(&qPickup[7],0.0f,-90.0f,0.0f);///front left
		iQuaternionFromEulerAngles(&qPickup[8],0.0f,-180.0f,0.0f);///back right
		iQuaternionFromEulerAngles(&qPickup[9],0.0f,-180.0f,0.0f);///back left
	}
	//-------------------------------------------------------------
	//Scan rotate
	for(int i=0;i<MAX_ENERGY_PICKUPS;i++)
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
//GAME - MODE - ENERGYPICKUP - CREATE
///*****************************************************************
void Game_Mode_EnergyPickup::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	PickupTrackLocations();
	//Set Locations
	for(int i=0;i<MAX_ENERGY_PICKUPS;i++)
	{
		iMeshImposterLocationSet(cGame_Mesh.Track_Pickup.Pickup_Energy,i,&vPickup[i],true);
		iMeshImposterOrientationSet(cGame_Mesh.Track_Pickup.Pickup_Energy,i,&qPickup[i],true);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - ENERGYPICKUP - UPDATE
///*****************************************************************
void Game_Mode_EnergyPickup::Update(void)
{
	//-------------------------------------------------------------
	//Start Pickups when Game Is running
	if(!bPickupsEnable)
	{
		for(int i=0;i<MAX_ENERGY_PICKUPS;i++)
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
		for(int i=0;i<MAX_ENERGY_PICKUPS;i++)
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
				iMeshImposterShow(cGame_Mesh.Track_Pickup.Pickup_Energy,i,false);

				for(int a=0;a<=gAi_Max_Count;a++)
				{
					//Define all active bikes
					D3DXVECTOR3 vBikeTarget = D3DXVECTOR3(0.0f,0.0f,0.0f);
					float EnergyCheck = 0.0f;
					float EnergyMax = 0.0f;
					bool bAlive = false;
					vBikeTarget = cGame_Bike[a].Manager.vBikeOutput;
					EnergyCheck = cGame_Bike[a].Energy.fEnergy;
					EnergyMax = cGame_Upgrades.fEnergyMax[a];
					bAlive = cGame_Bike[a].Energy.bAlive;
					//Check Range
					if(bAlive &&
						EnergyCheck < EnergyMax &&
						iVectorLength(&(vPickup[i] - vBikeTarget)) <= gPickupRadius)
					{
						//Give player Energy Regen
						if(a==gAi_Max_Count)
						{
							cGame_Bike[gAi_Max_Count].Energy.fEnergy += cGame_Upgrades.fEnergyPickup[a];
							cGame_Bike[gAi_Max_Count].Energy.bEnergyPickedUp = true;
							///Reset Weapon heat?
							if(gEnergyPickup_ZeroHeat)
							{
								cGame_Bike[gAi_Max_Count].Weapons.PrimaryHeat = 0;
							}
						}
						else
						{
							cGame_Bike[a].Energy.fEnergy += cGame_Upgrades.fEnergyPickup[a];
							cGame_Bike[a].Energy.bEnergyPickedUp = true;
							///Reset Weapon heat?
							if(gEnergyPickup_ZeroHeat)
							{
								cGame_Bike[a].Weapons.PrimaryHeat = 0;
							}
						}
						PickupReady[i] = false;
						break;
					}
				}
			}
			//Pickups Not Ready
			else if(PickupResetTimer[i] < gPickupTimerReset)
			{
				iMeshImposterHide(cGame_Mesh.Track_Pickup.Pickup_Energy,i,false);
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
//GAME - MODE - ENERGYPICKUP - DESTROY
///*****************************************************************
void Game_Mode_EnergyPickup::Destroy(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}