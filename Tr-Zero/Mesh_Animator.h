#pragma once
//-----------------------------------------------------------------
#define MAX_SEGMENTS 20
//-----------------------------------------------------------------
class Mesh_Animator
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Animator System
		D3DXVECTOR3					vBike[40];
		D3DXVECTOR3					vBike_Offset[40];
		D3DXVECTOR3					vTarget[40];
		D3DXVECTOR3					vTarget_Previous[40];

		D3DXQUATERNION				qBike[40];
		D3DXVECTOR3					qBike_Offset[40];
		D3DXVECTOR3					qTarget[40];
		D3DXVECTOR3					qTarget_Previous[40];

		int							Mode[40];
		int							Mode_Segment[40];
		int							Timer[40];
		int							Timer_MAX[40];
		//Creator
		D3DXVECTOR3					vTarget_Creator[MAX_SEGMENTS];
		D3DXVECTOR3					qTarget_Creator[MAX_SEGMENTS];
		int							Timer_Creator_MAX[MAX_SEGMENTS];
		bool						bPlay;

		//---------------------------------------------------------
		//constructors
		Mesh_Animator(void);
		~Mesh_Animator(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
		//CREATORSAVE
		void Save(void);
		void Load(void);
	//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		void UpdateSegments(const int index);
		void NextSegment(const int index);
		void LastSegment(const int index);


		//Preset Animation Pools
		void Animate_DaytonaFlip(const int index);
		void Animate_HighSpeedDeath(const int index);
	//-------------------------------------------------------------
};
