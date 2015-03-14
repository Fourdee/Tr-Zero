#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------

class Mesh_Bike_Engine
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//mesh
		MD5MESH*					EngineL;
		MD5MESH*					EngineL_Glow;
		MD5MESH*					EngineR;
		MD5MESH*					EngineR_Glow;
		//---------------------------------------------------------
		//constructors
		Mesh_Bike_Engine(void);
		~Mesh_Bike_Engine(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
	//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		//Offsets
		D3DXVECTOR3					Engine_Pos_OffsetL;
		D3DXVECTOR3					Engine_Pos_OffsetR;
		D3DXVECTOR2					vEngine_Rot_Offset;
		//Rotations
		float						Rotation;
		float						Rotation_Speed;
		//---------------------------------------------------------
		//functions
		void ImpostersCreate(void);
		void ImpostersDestroy(void);
		void ShaderUpdate(void);
		void Update_Engine(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1,float fTireSpin);
	//-------------------------------------------------------------
};
