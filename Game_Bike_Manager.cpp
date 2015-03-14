//-----------------------------------------------------------------
// bike manager class
//
// Scan based system. fires a ray from a origin vector
// and generates the offset from which to place meshes.
// 
//
// 
// TODO:
// 
// - Setup intercollision system for all bikes (using vectors, or, psyx?)
// - 
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Bike_Manager.h"
//-----------------------------------------------------------------
Game_Bike_Manager::Game_Bike_Manager(void)
{
	//-------------------------------------------------------------
	ResetData(0);
	//-------------------------------------------------------------
}

Game_Bike_Manager::~Game_Bike_Manager(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - MANAGER - PLAYER - CREATE - sets up our start vectors
///*****************************************************************
void Game_Bike_Manager::Player_Create(D3DXVECTOR3* SpawnLocation, D3DXQUATERNION* SpawnOrientation,int inPlayerID)
{
	//-------------------------------------------------------------
	ResetData(inPlayerID);
	//set the spawn values 
	vBikeOrigin = *SpawnLocation;
	qBikeOrigin = *SpawnOrientation;
	//-------------------------------------------------------------
	//Define Speedclass settings
	if(gSpeedClass==0){fAcceleration_Max = 2.6f;}//2.3
	else if(gSpeedClass==1){fAcceleration_Max = 3.6f;}//3.0
	else if(gSpeedClass==2){fAcceleration_Max = 4.3f;}//3.6
	else if(gSpeedClass==3){fAcceleration_Max = 5.0f;}//4.2
	///Cap Menu speed
	if(gGameState==0){fAcceleration_Max = 1.3f;}

	//Define boost Multi
	fBoost_Max = fAcceleration_Max * 1.9f;

	iFloatDecimalCap(fAcceleration_Max);
	iFloatDecimalCap(fBoost_Max);
	//-------------------------------------------------------------
	//settings
	fScanLengthWall = 9.0f;
	fScanLeft_DistanceCp = fScanLengthWall;
	fScanRight_DistanceCp = fScanLengthWall;
	//Smooth Wall Return (when no scan hit)
	fTendToWalls = 1.5f;
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - MANAGER - AI - CREATE - sets up our start vectors
///*****************************************************************
void Game_Bike_Manager::Ai_Create(D3DXVECTOR3* SpawnLocation, D3DXQUATERNION* SpawnOrientation,int inPlayerID)
{
	//-------------------------------------------------------------
	ResetData(inPlayerID);
	//set the spawn values 
	vBikeOrigin = *SpawnLocation;
	qBikeOrigin = *SpawnOrientation;
	//-------------------------------------------------------------
	//Define Speedclass settings
	if(gSpeedClass==0){fAcceleration_Max = 2.6f;}//2.3
	else if(gSpeedClass==1){fAcceleration_Max = 3.6f;}//3.0
	else if(gSpeedClass==2){fAcceleration_Max = 4.3f;}//3.6
	else if(gSpeedClass==3){fAcceleration_Max = 5.0f;}//4.2
	///Cap Menu speed
	if(gGameState==0){fAcceleration_Max = 1.3f;}

	//Define boost Multi
	fBoost_Max = fAcceleration_Max * iFloatInterpolate((float)gAiDifficuty,0.0f,4.0f,1.7f,1.9f);
	//fBoost_Max = fAcceleration_Max * cGame_Upgrades.fBoostMulti[PlayerID];
	
	
	///Apply Difficulty Multi to base speed (standard speed, higher than player 1.1f)
	fAcceleration_Max = fAcceleration_Max * gAiDifficutyMulti;
	///Seperate the pack
	float fSeperation_Multi = iFloatInterpolate((float)inPlayerID,(float)gAi_Max_Count / 2.0f,(float)gAi_Max_Count,1.2f,0.9f);
	fAcceleration_Max = fAcceleration_Max * fSeperation_Multi;

	iFloatDecimalCap(fAcceleration_Max);
	iFloatDecimalCap(fBoost_Max);

	//-------------------------------------------------------------
	//settings
	fScanLengthWall = 85.0f;
	fScanLeft_DistanceCp = fScanLengthWall;
	fScanRight_DistanceCp = fScanLengthWall;
	//Smooth Wall Return (when no scan hit)
	fTendToWalls = 25.0f;

	fAcceleration_TendTo_Break				= 30.0f;
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - MANAGER - UPDATE
///*****************************************************************
void Game_Bike_Manager::Update(int* In_SpeedState,
							   float in_TurnAngle,
							   bool bDrift,
							   bool bCollisionUpdate)
{
	//-------------------------------------------------------------
	bHardCollision = false;
	bGoingBackwards = false;
	vBikeMove = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//-------------------------------------------------------------
	//Scan Walls (COLLISIONS)
	//-------------------------------------------------------------
	if(fAcceleration_Speed >= 0.0f)//forwards
	{
		iQuaternionFromEulerAngles(&qScanLeft,-10.0f,-25.0f,0.0f);
		iQuaternionFromEulerAngles(&qScanRight,-10.0f,25.0f,0.0f);
	}
	else//backwards
	{
		bGoingBackwards = true;
		iQuaternionFromEulerAngles(&qScanLeft,-10.0f,-155.0f,0.0f);
		iQuaternionFromEulerAngles(&qScanRight,-10.0f,155.0f,0.0f);
	}
	iQuaternionMultiply(&qScanLeft,&qScanLeft,&qBikeOrigin);
	iQuaternionMultiply(&qScanRight,&qScanRight,&qBikeOrigin);

	D3DXVECTOR3 vScanFrontOffset = iVectorLocationOffset(&vBikeOrigin,&qBikeOrigin,&D3DXVECTOR3(0.0f,0.0f,-3.0f));

	if(iPhysxActorRaycastClosestStaticShape(cGame_Track.Physx.PhysxActor_Wall,
											&vScanFrontOffset,
											&qScanLeft,
											fScanLengthWall,
											&vScanLeftCp,
											&vScanLeftCn,
											fScanLeft_DistanceCp,
											true))
	{
	}
	else{iFloatTendTo2(fScanLeft_DistanceCp,fScanLengthWall,fTendToWalls);}
	if(iPhysxActorRaycastClosestStaticShape(cGame_Track.Physx.PhysxActor_Wall,
											&vScanFrontOffset,
											&qScanRight,
											fScanLengthWall,
											&vScanRightCp,
											&vScanRightCn,
											fScanRight_DistanceCp,
											true))
	{
	}
	else{iFloatTendTo2(fScanRight_DistanceCp,fScanLengthWall,fTendToWalls);}

	///Create a collision float based on scanner results
	///This is only active when front scanners are within threshold (9.0f)
	fCollision_px = 0.0f;
	if(fScanLeft_DistanceCp <= 9.0f || fScanRight_DistanceCp <= 9.0f)
	{
		fCollision_px = iFloatInterpolate(fScanRight_DistanceCp - fScanLeft_DistanceCp,-fScanLengthWall,fScanLengthWall,-9.0f,9.0f);
	}
	///AI additional Steering results from scanners
	fAiSteering = fScanRight_DistanceCp - fScanLeft_DistanceCp;
	//-------------------------------------------------------------
	// Speed Controller
	//-------------------------------------------------------------
	//Check for full frontal collision
	///This is only active when front scanners are within threshold (8.0f)
	fCollision_pz = 0.0f;
	if(fScanLeft_DistanceCp < 8.0f && 
		fScanRight_DistanceCp < 8.0f)
	{
		///Front & rear head on Collision Damage
		if(!bFrontCollision)
		{
			bFrontCollision = true;
			fCollision_pz = iFloatInterpolateSmooth(abs(fAcceleration_Speed),0.0f,7.5f,0.0f,400.0f);
		}
		///Define Speed/Xcollision
		fAcceleration_Speed = -8.0f + ((fScanLeft_DistanceCp + fScanRight_DistanceCp) / 2.0f);
		if(bGoingBackwards)
		{
			fAcceleration_Speed = 8.05f - ((fScanLeft_DistanceCp + fScanRight_DistanceCp) / 2.0f);
		}
		vBikeMove = D3DXVECTOR3(fCollision_px,0.0f,fAcceleration_Speed);
	}
	//No front collision, resume normal speed math
	else if(gBikesGo)
	{
		///Reset Front Collision Damage
		bFrontCollision = false;
		///Gravity
		iVectorRotate(&vGravity,&D3DXVECTOR3(0.0f,0.0f,1.0f),&qBikeOutput);//qBikeOrigin??
		float GravityScaleIn = (abs(fAcceleration_Speed) + 1.0f);
		float GravityScaleOut = ((abs(fAcceleration_Speed) * fAcceleration_Max) / 450.0f);
		
		if(vGravity.y <= -0.0f)
		{
			float GravDown = iFloatInterpolateSmooth(-vGravity.y,-GravityScaleIn,GravityScaleIn,-0.04f,0.04f);
			iFloatTendTo2(fGravity,GravDown,2.0f);
		}
		else
		{
			float GravUp = iFloatInterpolateSmooth(-vGravity.y,-GravityScaleIn,GravityScaleIn,-GravityScaleOut,GravityScaleOut);
			iFloatTendTo2(fGravity,GravUp,2.0f);
		}
		///Update speed with Gravity
		fAcceleration_Speed += fGravity;
		///Update speed with Wall Collision adjustments
		if(abs(fAcceleration_Speed) > 1.0f)
		{
			fAcceleration_Speed -= (abs(fCollision_px) * 0.125f);
		}
		///Update speed with bike Xrotations
		if(vRotations.x >= 0.0f)
		{
			fAcceleration_Speed -= (vRotations.x / 350.0f);
		}
		///Process new speed with inputs
		if(*In_SpeedState==2)//Boost
		{
			iFloatTendTo2(fAcceleration_Speed,fBoost_Max,fAcceleration_TendTo_Forward);
		}
		else if(*In_SpeedState==1)//acceleration
		{
			if(bDrift)
			{
				float fAcceleration_Max_DriftMulti = iFloatInterpolate(abs(in_TurnAngle),0.3f,2.0f,1.2f,1.6f);
				iFloatTendTo2(fAcceleration_Speed,fAcceleration_Max * fAcceleration_Max_DriftMulti,fAcceleration_TendTo_Forward / 3.0f);
			}
			else
			{
				iFloatTendTo2(fAcceleration_Speed,fAcceleration_Max,fAcceleration_TendTo_Forward);
			}
		}
		else if(*In_SpeedState==-1)//breaks
		{
			//if(fAcceleration_Speed > 0.2f)
			//{
				iFloatTendTo2(fAcceleration_Speed,0.0f,fAcceleration_TendTo_Break);
			//}
			//else//reverse
			//{
			//	iFloatTendTo2(fAcceleration_Speed,-2.0f,fAcceleration_TendTo_Forward);
			//	if(fAcceleration_Speed<=-0.0f)
			//	{
			//		in_TurnAngle = -in_TurnAngle;
			//	}
			//}
		}
		else//Idle
		{
			iFloatTendTo2(fAcceleration_Speed,0.0f,fAcceleration_TendTo_Idle);
		}
		//-------------------------------------------------------------
		// Steering/Strafe - APPLY
		//-------------------------------------------------------------
		///vBikeMove - Assign movement data
		vBikeMove = D3DXVECTOR3(fCollision_px,0.0f,fAcceleration_Speed);
		///Add strafe to X vector when theres no side collision
		if(abs(fCollision_px) <= 0.01f)
		{
			if(bDrift)
			{
				float fDriftSpeedDivide = iFloatInterpolate(abs(fAcceleration_Speed),0.0f,8.0f,4.0f,1.5f);
				float fDriftSteeringMulti = iFloatInterpolateSmooth(abs(in_TurnAngle),0.0f,1.8f,1.4f,2.0f);
				vBikeMove.x -= (in_TurnAngle / fDriftSpeedDivide) * fDriftSteeringMulti;//75.0f
			}
			else
			{
				vBikeMove.x -= in_TurnAngle / 50.0f;//200.0f 75.0f
			}
			
			//Update Ai Bike Collision System
			if(bCollisionUpdate)
			{
				Update_Collision();
			}
		}

		//Steering
		if(bDrift)
		{
			float fDriftSteering = iFloatInterpolate(abs(in_TurnAngle),0.3f,2.5f,1.05f,1.35f);
			in_TurnAngle = in_TurnAngle * fDriftSteering;
		}
		///Output
		iFloatTendTo2(fSteeringAdjust,(fCollision_px * 1.8f),8.0f);
		iQuaternionFromEulerAngles(&qBikeSteer,0.0f,(in_TurnAngle + fSteeringAdjust),0.0f);
		iQuaternionMultiply(&qBikeOrigin,&qBikeSteer,&qBikeOrigin);
	}
	//-------------------------------------------------------------
	// Scan Floor (Rotation + Height) Controller
	//-------------------------------------------------------------
	///Reset Items (incase of no scandown)
	vUp	= D3DXVECTOR3(0.0f,0.0f,1.0f);
	fScanDown_DistanceCp = 4.0f;///2
	vRotations = D3DXVECTOR3(0.0f,0.0f,0.0f);
	///Point Scanner down
	iQuaternionFromEulerAngles(&qScanDown,90.0f,0.0f,0.0f);
	iQuaternionMultiply(&qScanDown,&qScanDown,&qBikeOrigin);
	D3DXQUATERNION qPrevious = qBikeOrigin;

	//Sample Scan at output location
	D3DXVECTOR3 vScanOrigin = iVectorLocationOffset(&vBikeOrigin,&qBikeOrigin,&vBikeMove);

	if(iPhysxActorRaycastClosestStaticShape(cGame_Track.Physx.PhysxActor_Floor,
											&vScanOrigin,
											&qScanDown,
											fScanLength,
											&vScanDownCp,
											&vScanDownCn,
											fScanDown_DistanceCp,
											true))
	{
		//-------------------------------------------------------------
		// METHOD 3
		///Rotate
		D3DXQUATERNION qBikeRotation;
		iVectorRotate(&vUp,&vUp,&qBikeOrigin);
		iQuaternionLookAt(&qBikeRotation,&vScanDownCp,&(vScanDownCp+vScanDownCn),&vUp);
		D3DXQUATERNION qForward;
		iQuaternionFromEulerAngles(&qForward,-90.0f,180.0f,0.0f);
		iQuaternionMultiply(&qBikeRotation,&qForward,&qBikeRotation);
		///Smooth new height
		float fTargetHeight = 4.0f - fScanDown_DistanceCp;
		float fHeightTendTo = iFloatInterpolate(abs(fSmoothHeight - fTargetHeight),0.0f,0.15f,20.0f,4.0f);
		iFloatTendTo2(fSmoothHeight,fTargetHeight,fHeightTendTo);

		//Apply new vector
		vBikeMove.y = fSmoothHeight;
		if(!gBikesGo)///Stop movement
		{
			vBikeMove.x = 0.0f;
			vBikeMove.y = fTargetHeight;
			vBikeMove.z = 0.0f;
		}
		iVectorRotate(&vBikeMove,&vBikeMove,&qBikeRotation);
		vBikeOrigin += vBikeMove;

		///Grab Delta
		D3DXQUATERNION qDelta;
		iQuaternionDelta(&qDelta,&qPrevious,&qBikeRotation);
		iQuaternionToEulerAngles(&qDelta,&vRotations);

		///Smooth rotation for mesh/nextloop
		iQuaternionInterpolate(&qBikeOrigin,&qPrevious,&qBikeRotation,0.85f);
	}
	//No scan - temp fix, "just keep on moving, yeah, keep on moving, along!"
	// Add jump mechanic, you know you want to.
	else
	{
		iFloatTendTo2(fSmoothHeight,0.0f,4.0f);
		if(gBikesGo)
		{
			vBikeOrigin = iVectorLocationOffset(&vBikeOrigin,&qBikeOrigin,&D3DXVECTOR3(vBikeMove.x,fSmoothHeight,vBikeMove.z));
		}
	}

	//-------------------------------------------------------------
	// Output Vector/quat (for camera/skinmesh)
	//-------------------------------------------------------------
	//Create Smooth output for camera/mesh
	iQuaternionInterpolate(&qBikeOutput,&qBikeOutput,&qBikeOrigin,0.5f);//0.25f
	///vBikeOutput
	D3DXVECTOR3 vBikeOutputOffset = D3DXVECTOR3(0.0f,-2.0f,0.0f);
	iVectorRotate(&vBikeOutputOffset,&vBikeOutputOffset,&qBikeOutput);
	vBikeOutput = vBikeOrigin + vBikeOutputOffset;
	///vTargetMesh
	vTargetMesh = iVectorLocationOffset(&vBikeOutput,&qBikeOutput,&D3DXVECTOR3(0.0f,-0.24f,0.0f));
	//-------------------------------------------------------------
	//Mesh Output
	///Drift y axis mesh rotation
	if(bDrift)
	{
		float fDriftTarget = iFloatInterpolateSmooth(abs(in_TurnAngle),0.0f,2.5f,5.0f,7.0f);
		iFloatTendTo2(fDriftMeshMulti,fDriftTarget,18.0f);
	}
	else
	{
		iFloatTendTo2(fDriftMeshMulti,1.0f,18.0f);
	}
	///Work out lean
	fLean = iFloatInterpolate(in_TurnAngle,-2.5f,2.5f,-30.0f,30.0f);
	fLean += fCollision_px / 2.0f;
	fLean += fSteeringAdjust * 6.0f;
	///Apply New Rotations
	iFloatTendTo2(vRotationsMesh.x,vRotations.x * 1.25f,3.0f);
	iFloatTendTo2(vRotationsMesh.y,(in_TurnAngle * fDriftMeshMulti) + (fSteeringAdjust * 3.0f),2.0f);
	iFloatTendTo2(vRotationsMesh.z,fLean - (vRotations.z * 2.0f),4.5f);
	D3DXQUATERNION q1;
	iQuaternionFromEulerAngles(&q1,vRotationsMesh.x,vRotationsMesh.y,vRotationsMesh.z);
	iQuaternionMultiply(&qBikeOutputLean,&q1,&qBikeOutput);
	//-------------------------------------------------------------
}
///*****************************************************************
///BIKE - MANAGER - UPDATE_COLLISION
///*****************************************************************
void Game_Bike_Manager::Update_Collision(void)
{
	//-------------------------------------------------------------
	const float LRoffset = 0.5f;
	const float limit = 6.0f;
	float PXAdjustment = 0.0f;

	D3DXVECTOR3 vTargetCol = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXQUATERNION qTargetCol = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	float Distance = 0.0f;

	for(int i=0;i<=gAi_Max_Count;i++)
	{
		PXAdjustment = 0.0f;

		vTargetCol = cGame_Bike[i].Manager.vBikeOutput;
		qTargetCol = qBikeOutput;
		Distance = iVectorLength(&(vBikeOrigin - vTargetCol));

		if(PlayerID!=i)
		{
			//HARD
			if(Distance < 12.0f)
			{
				D3DXVECTOR3 vFrontL = iVectorLocationOffset(&vTargetCol,&qTargetCol,&D3DXVECTOR3(-LRoffset,0.0f,3.0f));
				D3DXVECTOR3 vFrontR = iVectorLocationOffset(&vTargetCol,&qTargetCol,&D3DXVECTOR3(LRoffset,0.0f,3.0f));
				D3DXVECTOR3 vRearL = iVectorLocationOffset(&vTargetCol,&qTargetCol,&D3DXVECTOR3(-LRoffset,0.0f,-6.0f));
				D3DXVECTOR3 vRearR = iVectorLocationOffset(&vTargetCol,&qTargetCol,&D3DXVECTOR3(LRoffset,0.0f,-6.0f));
				if((iVectorLength(&(vBikeOrigin - vFrontL)) < (iVectorLength(&(vBikeOrigin - vRearL)))))
				{
					///Front Check
					if((iVectorLength(&(vBikeOrigin - vFrontL))) < (iVectorLength(&(vBikeOrigin - vFrontR))) && (iVectorLength(&(vBikeOrigin - vFrontL)) <= limit))
					{
						if((iVectorLength(&(vBikeOrigin - vFrontL))) <= (limit / 1.15f))
						{
							bHardCollision = true;
						}
						PXAdjustment += ((limit - iVectorLength(&(vBikeOrigin - vFrontL))) / 1.75f);			
						vBikeMove.x -= PXAdjustment;
						fSteeringAdjust -= (PXAdjustment / 2.0f);
						vRotationsMesh.z -= (PXAdjustment * 5.0f);
					}
					else if((iVectorLength(&(vBikeOrigin - vFrontL))) >= (iVectorLength(&(vBikeOrigin - vFrontR))) && (iVectorLength(&(vBikeOrigin - vFrontR)) <= limit))
					{
						if((iVectorLength(&(vBikeOrigin - vFrontL))) <= (limit / 1.15f))
						{
							bHardCollision = true;
						}
						PXAdjustment += ((limit - iVectorLength(&(vBikeOrigin - vFrontR))) / 1.75f);			
						vBikeMove.x += PXAdjustment;
						fSteeringAdjust += (PXAdjustment / 2.0f);
						vRotationsMesh.z += (PXAdjustment * 5.0f);
					}
					fAcceleration_Speed += (PXAdjustment / 15.0f);
				}
				else 
				{
					///Rear Check
					if((iVectorLength(&(vBikeOrigin - vRearL))) < (iVectorLength(&(vBikeOrigin - vRearR))) && (iVectorLength(&(vBikeOrigin - vRearL)) <= limit))
					{
						if((iVectorLength(&(vBikeOrigin - vRearL))) <= (limit / 1.2f))
						{
							bHardCollision = true;
						}
						PXAdjustment += ((limit - iVectorLength(&(vBikeOrigin - vRearL))) / 1.75f);			
						vBikeMove.x -= PXAdjustment;
						fSteeringAdjust -= (PXAdjustment / 2.0f);
						vRotationsMesh.z -= (PXAdjustment * 5.0f);
					}
					else if((iVectorLength(&(vBikeOrigin - vRearL))) >= (iVectorLength(&(vBikeOrigin - vRearR))) && (iVectorLength(&(vBikeOrigin - vRearR)) <= limit))
					{
						if((iVectorLength(&(vBikeOrigin - vRearR))) <= (limit / 1.2f))
						{
							bHardCollision = true;
						}
						PXAdjustment += ((limit - iVectorLength(&(vBikeOrigin - vRearR))) / 1.75f);			
						vBikeMove.x += PXAdjustment;
						fSteeringAdjust += (PXAdjustment / 2.0f);
						vRotationsMesh.z += (PXAdjustment * 5.0f);
					}
					if(fAcceleration_Speed > 0.5f)
					{
						fAcceleration_Speed -= (PXAdjustment / 12.0f);
					}
				}
				//break; //?
			}
			//Soft Avoidance
			else if(!bHardCollision &&
				Distance < 40.0f)
			{
				D3DXVECTOR3 vFrontL = iVectorLocationOffset(&vTargetCol,&qTargetCol,&D3DXVECTOR3(-LRoffset,0.0f,0.0f));
				D3DXVECTOR3 vFrontR = iVectorLocationOffset(&vTargetCol,&qTargetCol,&D3DXVECTOR3(LRoffset,0.0f,0.0f));
				if((iVectorLength(&(vBikeOrigin - vFrontL)) < (iVectorLength(&(vBikeOrigin - vFrontR)))))
				{
					vBikeMove.x -= 0.03f;
					fSteeringAdjust -= 0.02f;
				}
				else if((iVectorLength(&(vBikeOrigin - vFrontL)) >= (iVectorLength(&(vBikeOrigin - vFrontR)))))
				{
					vBikeMove.x += 0.03f;
					fSteeringAdjust += 0.02f;
				}
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - MANAGER - Update_Replay
///*****************************************************************
void Game_Bike_Manager::Update_Replay(int* In_SpeedState,
										float in_TurnAngle,
										bool bDrift)
{
	//-------------------------------------------------------------
	bHardCollision = false;
	bGoingBackwards = false;
	vBikeMove = D3DXVECTOR3(0.0f,0.0f,0.0f);
	fScanLengthWall = 9.0f;
	//-------------------------------------------------------------
	//Scan Walls (COLLISIONS)
	//-------------------------------------------------------------
	if(fAcceleration_Speed >= 0.0f)//forwards
	{
		iQuaternionFromEulerAngles(&qScanLeft,-10.0f,-25.0f,0.0f);
		iQuaternionFromEulerAngles(&qScanRight,-10.0f,25.0f,0.0f);
	}
	else//backwards
	{
		bGoingBackwards = true;
		iQuaternionFromEulerAngles(&qScanLeft,-10.0f,-155.0f,0.0f);
		iQuaternionFromEulerAngles(&qScanRight,-10.0f,155.0f,0.0f);
	}
	iQuaternionMultiply(&qScanLeft,&qScanLeft,&qBikeOrigin);
	iQuaternionMultiply(&qScanRight,&qScanRight,&qBikeOrigin);

	D3DXVECTOR3 vScanFrontOffset = iVectorLocationOffset(&vBikeOrigin,&qBikeOrigin,&D3DXVECTOR3(0.0f,0.0f,-3.0f));

	if(iPhysxActorRaycastClosestStaticShape(cGame_Track.Physx.PhysxActor_Wall,
											&vScanFrontOffset,
											&qScanLeft,
											fScanLengthWall,
											&vScanLeftCp,
											&vScanLeftCn,
											fScanLeft_DistanceCp,
											true))
	{
	}
	else
	{
		fScanLeft_DistanceCp = fScanLengthWall;
	}

	if(iPhysxActorRaycastClosestStaticShape(cGame_Track.Physx.PhysxActor_Wall,
											&vScanFrontOffset,
											&qScanRight,
											fScanLengthWall,
											&vScanRightCp,
											&vScanRightCn,
											fScanRight_DistanceCp,
											true))
	{
	}
	else
	{
		fScanRight_DistanceCp = fScanLengthWall;
	}

	//Create a collision float based on scanner results
	///This is only active when front scanners are within threshold (9.0f)
	fCollision_px = 0.0f;
	if(fScanLeft_DistanceCp <= 9.0f || fScanRight_DistanceCp <= 9.0f)
	{
		fCollision_px = iFloatInterpolate(fScanRight_DistanceCp - fScanLeft_DistanceCp,-fScanLengthWall,fScanLengthWall,-9.0f,9.0f);
	}
	//-------------------------------------------------------------
	// Speed Controller
	//-------------------------------------------------------------
	//Check for full frontal collision
	///This is only active when front scanners are within threshold (8.0f)
	fCollision_pz = 0.0f;
	if(fScanLeft_DistanceCp < 8.0f && 
		fScanRight_DistanceCp < 8.0f)
	{
		///Front & rear head on Collision Damage
		bFrontCollision = true;
	}
	//No front collision, resume normal speed math
	else if(gBikesGo)
	{
		///Reset Front Collision Damage
		bFrontCollision = false;
		///Steering/Strafe - APPLY
		if(bDrift)
		{
			float fDriftSteering = iFloatInterpolate(abs(in_TurnAngle),0.3f,2.5f,1.05f,1.35f);
			in_TurnAngle = in_TurnAngle * fDriftSteering;
		}
		iFloatTendTo2(fSteeringAdjust,(fCollision_px * 1.8f),8.0f);
	}
	//-------------------------------------------------------------
	// Output Vector/quat (for camera/skinmesh)
	//-------------------------------------------------------------
	//Create Smooth output for camera/mesh
	iQuaternionInterpolate(&qBikeOutput,&qBikeOutput,&qBikeOrigin,0.5f);//0.25f

	///vBikeOutput
	D3DXVECTOR3 vBikeOutputOffset = D3DXVECTOR3(0.0f,-2.0f,0.0f);
	iVectorRotate(&vBikeOutputOffset,&vBikeOutputOffset,&qBikeOutput);
	vBikeOutput = vBikeOrigin + vBikeOutputOffset;
	///vTargetMesh
	vTargetMesh = iVectorLocationOffset(&vBikeOutput,&qBikeOutput,&D3DXVECTOR3(0.0f,-0.24f,0.0f));
	//-------------------------------------------------------------
	//Mesh Output
	///Drift y axis mesh rotation
	if(bDrift)
	{
		float fDriftTarget = iFloatInterpolateSmooth(abs(in_TurnAngle),0.0f,2.5f,5.0f,7.0f);
		iFloatTendTo2(fDriftMeshMulti,fDriftTarget,18.0f);
	}
	else
	{
		iFloatTendTo2(fDriftMeshMulti,1.0f,18.0f);
	}
	///Work out lean
	fLean = iFloatInterpolate(in_TurnAngle,-2.5f,2.5f,-30.0f,30.0f);
	fLean += fCollision_px / 2.0f;
	fLean += fSteeringAdjust * 6.0f;
	///Apply New Rotations
	vRotationsMesh.x = 0.0f;
	iFloatTendTo2(vRotationsMesh.y,(in_TurnAngle * fDriftMeshMulti) + (fSteeringAdjust * 3.0f),2.0f);
	iFloatTendTo2(vRotationsMesh.z,fLean,4.5f);
	D3DXQUATERNION q1;
	iQuaternionFromEulerAngles(&q1,vRotationsMesh.x,vRotationsMesh.y,vRotationsMesh.z);
	iQuaternionMultiply(&qBikeOutputLean,&q1,&qBikeOutput);
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - MANAGER - DESTROY
///*****************************************************************
void Game_Bike_Manager::Destroy(void)
{
	//-------------------------------------------------------------
	ResetData(0);
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - MANAGER - RESET DATA
///*****************************************************************
void Game_Bike_Manager::ResetData(int inPlayerID)
{
	//-------------------------------------------------------------
	PlayerID								= inPlayerID;
	bGoingBackwards							= false;
	//post-data
	vBikeOutput								= D3DXVECTOR3(0.0f,0.0f,0.0f);

	qBikeOutput								= D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);

	qBikeOutputLean							= D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);

	vTargetMesh								= D3DXVECTOR3(0.0f,0.0f,0.0f);
	//Scan data
	vScanDownCp								= D3DXVECTOR3(0.0f,0.0f,0.0f);
	vScanDownCn								= D3DXVECTOR3(0.0f,0.0f,0.0f);
	vScanLeftCp								= D3DXVECTOR3(0.0f,0.0f,0.0f);
	vScanLeftCn								= D3DXVECTOR3(0.0f,0.0f,0.0f);
	vScanRightCp							= D3DXVECTOR3(0.0f,0.0f,0.0f);
	vScanRightCn							= D3DXVECTOR3(0.0f,0.0f,0.0f);
	vRotations								= D3DXVECTOR3(0.0f,0.0f,0.0f);
	vRotationsMesh							= D3DXVECTOR3(0.0f,0.0f,0.0f);
	fScanLength								= 20.0f;
	fScanLengthWall							= 9.0f;
	fScanDown_DistanceCp					= 2.13f;
	fScanDown_DistanceCn					= 0.0f;
	fScanLeft_DistanceCp					= 0.0f;
	fScanLeft_DistanceCn					= 0.0f;
	fScanRight_DistanceCp					= 0.0f;
	fScanRight_DistanceCn					= 0.0f;
	// AI Additional Data
	fAiSteering								= 0.0f;
	//Collision data
	fCollision_px							= 0.0f;
	fSteeringAdjust							= 0.0f;
	bHardCollision							= false;
	fCollision_pz							= 0.0f;
	//Speed Controller Updates
	fGravity								= 0.0f;
	fAcceleration_Max						= 0.0f;
	fBoost_Max								= 0.0f;
	fAcceleration_TendTo_Forward			= 140.0f;
	fAcceleration_TendTo_Break				= 45.0f;
	fAcceleration_TendTo_Idle				= 110.0f;
	fAcceleration_Speed						= 0.0f;
	//pre-data
	vBikeOrigin								 = D3DXVECTOR3(0.0f,0.0f,0.0f);

	qBikeOrigin								 = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);

	vBikeMove								 = D3DXVECTOR3(0.0f,0.0f,0.0f);
	vUp										 = D3DXVECTOR3(0.0f,0.0f,1.0f);
	qBikeSteer								 = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	fSmoothHeight							 = 0.0f;
	//Scan data
	qScanDown								 = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	qScanLeft								 = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	qScanRight								 = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	//Speed Controller Updates
	vGravity								 = D3DXVECTOR3(0.0f,0.0f,0.0f);
	vAcceleration							 = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//Skinmesh Lean
	fLean									 = 0.0f;
	//Smooth Wall Return (when no scan hit)
	fTendToWalls							 = 1.0f;
	//Drift (RidgeRacer Style)
	fDriftMeshMulti							 = 1.0f;
	//Front Collision Applied
	bFrontCollision							= false;
	//-------------------------------------------------------------
}