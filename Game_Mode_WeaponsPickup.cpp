//-----------------------------------------------------------------
// About:
//
// name: "Game_Mode_WeaponsPickup.cpp:
//
// usage: Enables/Updates Track Weapon Pickups
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Mode_WeaponsPickup.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - MODE - WEAPONSPICKUP - CONSTRUCTORS
///*****************************************************************
Game_Mode_WeaponsPickup::Game_Mode_WeaponsPickup(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Mode_WeaponsPickup::~Game_Mode_WeaponsPickup(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - MODE - WEAPONSPICKUP - ZERODATA
///*****************************************************************
void Game_Mode_WeaponsPickup::ZeroData(void)
{
	//-------------------------------------------------------------
	bPickupsEnable = false;
	for(int i=0;i<MAX_WEAPON_PICKUPS;i++)
	{
		PickupResetTimer[i] = 0;
		PickupReady[i] = false;
		vPickup[i] = D3DXVECTOR3(0.0f,-5000.0f,0.0f);
		qPickup[i] = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - MODE - WEAPONSPICKUP - PICKUPTRACKLOCATIONS
///*****************************************************************
void Game_Mode_WeaponsPickup::PickupTrackLocations(void)
{
	//-------------------------------------------------------------
	if(gGameState==1) //VOLEX
	{
		vPickup[0] = D3DXVECTOR3(-120.0f,159.3f,430.1f);
		vPickup[1] = D3DXVECTOR3(-120.0f,133.2f,425.1f);
		vPickup[2] = D3DXVECTOR3(-225.0f,-870.1f,43.9f);
		iQuaternionFromEulerAngles(&qPickup[2],90.0f,0.0f,0.0f);//down
		vPickup[3] = D3DXVECTOR3(-255.0f,-870.1f,43.9f);
		iQuaternionFromEulerAngles(&qPickup[3],90.0f,0.0f,0.0f);//down
		vPickup[4] = D3DXVECTOR3(-678.2f,119.0f,-174.5f);
		//iQuaternionFromEulerAngles(&qPickup[4],90.0f,0.0f,0.0f);//down
		vPickup[5] = D3DXVECTOR3(-734.0f,-70.0f,138.5f);
		iQuaternionFromEulerAngles(&qPickup[5],90.0f,0.0f,0.0f);//down
		vPickup[6] = D3DXVECTOR3(-715.2f,-80.3f,128.8f);
		iQuaternionFromEulerAngles(&qPickup[6],90.0f,0.0f,0.0f);//down
		vPickup[7] = D3DXVECTOR3(-471.9f,-357.9f,-872.3f);
		iQuaternionFromEulerAngles(&qPickup[7],90.0f,0.0f,0.0f);//down
		vPickup[8] = D3DXVECTOR3(-341.6f,-357.6f,-322.3f);
		iQuaternionFromEulerAngles(&qPickup[8],90.0f,0.0f,0.0f);//down
		vPickup[9] = D3DXVECTOR3(332.3f,278.6f,-341.6f);
		iQuaternionFromEulerAngles(&qPickup[9],0.0f,90.0f,0.0f);//right
		//iQuaternionFromEulerAngles(&qPickup[0],-180.0f,0.0f,0.0f);//back
		//iQuaternionFromEulerAngles(&qPickup[0],90.0f,0.0f,0.0f);//down
		//iQuaternionFromEulerAngles(&qPickup[0],0.0f,90.0f,0.0f);//right
	}
	else if(gGameState==2)//Silence
	{
		vPickup[0] = D3DXVECTOR3(0.0f,12.2f,709.9f);
		iQuaternionFromEulerAngles(&qPickup[0],0.0f,-90.0f,0.0f);///right

		vPickup[1] = D3DXVECTOR3(-19.4f,-29.1f,1148.2f);
		iQuaternionFromEulerAngles(&qPickup[1],180.0f,0.0f,0.0f);///Up
		vPickup[2] = D3DXVECTOR3(17.3f,429.8f,1237.8f);
		iQuaternionFromEulerAngles(&qPickup[2],-180.0f,0.0f,0.0f);//back
		vPickup[3] = D3DXVECTOR3(-17.3f,429.8f,1237.8f);
		iQuaternionFromEulerAngles(&qPickup[3],-180.0f,0.0f,0.0f);//back
		vPickup[4] = D3DXVECTOR3(0.0f,305.6f,1788.2f);
		vPickup[5] = D3DXVECTOR3(-14.2f,-192.0f,1210.9f);
		vPickup[6] = D3DXVECTOR3(-1.0f,-200.0f,791.1f);
		iQuaternionFromEulerAngles(&qPickup[6],0.0f,-90.0f,0.0f);///right
		vPickup[7] = D3DXVECTOR3(19.4f,-379.2f,-171.4f);
		iQuaternionFromEulerAngles(&qPickup[7],180.0f,0.0f,0.0f);///Up
		vPickup[8] = D3DXVECTOR3(-17.9f,-38.1f,-484.7f);
		iQuaternionFromEulerAngles(&qPickup[8],90.0f,0.0f,0.0f);///down
		vPickup[9] = D3DXVECTOR3(17.9f,-38.1f,-484.7f);
		iQuaternionFromEulerAngles(&qPickup[9],90.0f,0.0f,0.0f);///down
	}
	else if(gGameState==3)//Phantom
	{
		vPickup[0] = D3DXVECTOR3(251.5f,-61.7f,816.1f);
		vPickup[1] = D3DXVECTOR3(-544.7f,-209.5f,342.6f);
		vPickup[2] = D3DXVECTOR3(-239.9f,46.6f,1168.6f);
		vPickup[3] = D3DXVECTOR3(-61.1f,896.2f,439.5f);
		vPickup[4] = D3DXVECTOR3(221.9f,-71.8f,326.2f);
		vPickup[5] = D3DXVECTOR3(258.0f,-71.7f,326.1f);
		vPickup[6] = D3DXVECTOR3(565.8f,-88.7f,-782.5f);
		vPickup[7] = D3DXVECTOR3(216.4f,-127.0f,-869.6f);
		vPickup[8] = D3DXVECTOR3(11.2f,-14.8f,-375.9f);
		vPickup[9] = D3DXVECTOR3(-229.9f,-164.6f,-857.6f);
	}
	else if(gGameState==10)//Rez
	{
		vPickup[0] = D3DXVECTOR3(-135.0f,0.05f,90.0f);
		vPickup[1] = D3DXVECTOR3(135.0f,0.05f,-90.0f);

		vPickup[2] = D3DXVECTOR3(-539.0f,48.0f,0.0f);
		vPickup[3] = D3DXVECTOR3(539.0f,48.0f,0.0f);//
		//iQuaternionFromEulerAngles(&qPickup[2],-90.0f,0.0f,0.0f);
		//iQuaternionFromEulerAngles(&qPickup[3],-90.0f,0.0f,0.0f);

		vPickup[4] = D3DXVECTOR3(-90.0f,0.05f,-192.0f);//
		vPickup[5] = D3DXVECTOR3(90.0f,0.05f,192.0f);//

		vPickup[6] = D3DXVECTOR3(454.0f,391.0f,394.0f);//
		vPickup[7] = D3DXVECTOR3(-454.0f,311.0f,394.0f);//

		vPickup[8] = D3DXVECTOR3(454.0f,391.0f,-394.0f);//
		vPickup[9] = D3DXVECTOR3(-454.0f,311.0f,-394.0f);//

		iQuaternionFromEulerAngles(&qPickup[6],0.0f,90.0f,0.0f);///front right
		iQuaternionFromEulerAngles(&qPickup[7],0.0f,-90.0f,0.0f);///front left
		iQuaternionFromEulerAngles(&qPickup[8],0.0f,-180.0f,0.0f);///back right
		iQuaternionFromEulerAngles(&qPickup[9],0.0f,-180.0f,0.0f);///back left
	}
	//-------------------------------------------------------------
	//Scan rotate
	for(int i=0;i<MAX_WEAPON_PICKUPS;i++)
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
//GAME - MODE - WEAPONSPICKUP - CREATE
///*****************************************************************
void Game_Mode_WeaponsPickup::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	PickupTrackLocations();
	//Set Locations
	for(int i=0;i<MAX_WEAPON_PICKUPS;i++)
	{
		iMeshImposterLocationSet(cGame_Mesh.Track_Pickup.Pickup_Weapon,i,&vPickup[i],true);
		iMeshImposterOrientationSet(cGame_Mesh.Track_Pickup.Pickup_Weapon,i,&qPickup[i],true);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - MODE - WEAPONSPICKUP - UPDATE
///*****************************************************************
void Game_Mode_WeaponsPickup::Update(void)
{
	//-------------------------------------------------------------
	//Start Pickups when Game Weapons are enabled
	if(!bPickupsEnable && gWeaponsEnable)
	{
		for(int i=0;i<MAX_WEAPON_PICKUPS;i++)
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
		for(int i=0;i<MAX_WEAPON_PICKUPS;i++)
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
				iMeshImposterShow(cGame_Mesh.Track_Pickup.Pickup_Weapon,i,false);

				for(int a=0;a<=gAi_Max_Count;a++)
				{
					//Define all active bikes
					D3DXVECTOR3 vBikeTarget = D3DXVECTOR3(0.0f,0.0f,0.0f);
					int WeaponCheck = -1;
					bool bAlive = false;
					vBikeTarget = cGame_Bike[a].Manager.vBikeOutput;
					WeaponCheck = cGame_Bike[a].Weapons.SecondaryWeaponType;
					bAlive = cGame_Bike[a].Energy.bAlive;
					//Check Range
					if(bAlive &&
						WeaponCheck==-1 &&
						iVectorLength(&(vPickup[i] - vBikeTarget)) <= gPickupRadius)
					{
						//Give secondary weapon
						WeaponCheck = iIntRand(0,MAX_SECONDARY_TYPES);
						cGame_Bike[a].Weapons.SecondaryWeaponType = WeaponCheck;
						PickupReady[i] = false;
						break;
					}
				}
			}
			//Pickups Not Ready
			else if(PickupResetTimer[i] < gPickupTimerReset)
			{
				iMeshImposterHide(cGame_Mesh.Track_Pickup.Pickup_Weapon,i,false);
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
//GAME - MODE - WEAPONSPICKUP - DESTROY
///*****************************************************************
void Game_Mode_WeaponsPickup::Destroy(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}