#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Mesh_Bike_Shadow
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		MD5MESH*					Shadow_A;
		//---------------------------------------------------------
		//constructors
		Mesh_Bike_Shadow(void);
		~Mesh_Bike_Shadow(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		//functions
		void Player_Update(D3DXVECTOR3* v1,D3DXQUATERNION* q1);
		void Ai_Update(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1);
		void ShaderUpdate(void);
		void ImpostersCreate(void);
		void ImpostersDestroy(void);
	//-------------------------------------------------------------
};
