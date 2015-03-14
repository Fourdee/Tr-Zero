#pragma once
//-----------------------------------------------------------------
#define MAX_TRAILS 40 //1Max = 2 trail objects
//-----------------------------------------------------------------
class Mesh_Bike_Trail
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		int							ActiveModel_Ai;
		int							ActiveModel_Player;
		//---------------------------------------------------------
		//constructors
		Mesh_Bike_Trail(void);
		~Mesh_Bike_Trail(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		//Rear Trails
		TRAIL*							TrailR[MAX_TRAILS];
		TRAIL*							TrailL[MAX_TRAILS];
		D3DXVECTOR3						vTrailOffsetR[2];
		D3DXVECTOR3						vTrailOffsetL[2];
		float							fAngle;
		float							fWidth;
		//---------------------------------------------------------
		//functions
		void Update(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1,D3DXVECTOR3* vColour,bool bEnable);
	//-------------------------------------------------------------
};
