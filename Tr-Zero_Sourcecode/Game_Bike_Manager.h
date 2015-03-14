#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Bike_Manager
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		bool				bGoingBackwards;

		D3DXVECTOR3			vBikeOrigin;

		D3DXQUATERNION		qBikeOrigin;

		//post-data
		D3DXVECTOR3			vBikeOutput;

		D3DXQUATERNION		qBikeOutput;

		D3DXQUATERNION		qBikeOutputLean;


		D3DXVECTOR3			vTargetMesh;
		//Scan data
		D3DXQUATERNION		qScanDown;
		D3DXVECTOR3			vScanDownCp;
		D3DXVECTOR3			vScanDownCn;
		D3DXVECTOR3			vScanLeftCp;
		D3DXVECTOR3			vScanLeftCn;
		D3DXVECTOR3			vScanRightCp;
		D3DXVECTOR3			vScanRightCn;
		D3DXVECTOR3			vRotations;
		D3DXVECTOR3			vRotationsMesh;
		float				fSmoothHeight;
		float				fScanLength;
		float				fScanLengthWall;
		float				fScanDown_DistanceCp;
		float				fScanDown_DistanceCn;
		float				fScanLeft_DistanceCp;
		float				fScanLeft_DistanceCn;
		float				fScanRight_DistanceCp;
		float				fScanRight_DistanceCn;
		// AI Additional Data
		float				fAiSteering;
		//Collision data
		float				fCollision_px;
		float				fSteeringAdjust;
		bool				bHardCollision;
		float				fCollision_pz;
		//Smooth Wall Return (when no scan hit)
		float				fTendToWalls;
		//---------------------------------------------------------
		//Speed Controller Updates
		float							fBoost_Max;
		float							fAcceleration_Max;
		float							fAcceleration_TendTo_Forward;
		float							fAcceleration_TendTo_Break;
		float							fAcceleration_TendTo_Idle;
		float							fAcceleration_Speed;
		float							fLean;
		//---------------------------------------------------------
		//Front Collision Applied
		bool							bFrontCollision;
		//---------------------------------------------------------
		//constructors
		Game_Bike_Manager(void);
		~Game_Bike_Manager(void);
		//---------------------------------------------------------
		//Functions
		void Player_Create(D3DXVECTOR3* SpawnLocation, D3DXQUATERNION* SpawnOrientation,int inPlayerID);
		void Ai_Create(D3DXVECTOR3* SpawnLocation, D3DXQUATERNION* SpawnOrientation,int inPlayerID);
		void Update(int* In_SpeedState,
					float in_TurnAngle,
					bool bDrift,
					bool bCollisionUpdate);
		void Update_Replay(int* In_SpeedState,
							float in_TurnAngle,
							bool bDrift);
		void Destroy(void);
		//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		int								PlayerID;
		//pre-data
		D3DXVECTOR3						vBikeMove;
		D3DXVECTOR3						vUp;
		D3DXQUATERNION					qBikeSteer;
		//Scan data
		D3DXQUATERNION					qScanLeft;
		D3DXQUATERNION					qScanRight;
		//Speed Controller Updates
		D3DXVECTOR3						vGravity;
		float							fGravity;
		D3DXVECTOR3						vAcceleration;
		//Drift (RidgeRacer Style)
		float							fDriftMeshMulti;
		//---------------------------------------------------------
		//Functions
		void Update_Collision(void);
		void ResetData(int inPlayerID);
		//---------------------------------------------------------
};
