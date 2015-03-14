#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Mesh_Bike_Headlight
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		MD5MESH*					Headlight[2];
		int							ActiveModel_Ai;
		int							ActiveModel_Player;
		//---------------------------------------------------------
		//constructors
		Mesh_Bike_Headlight(void);
		~Mesh_Bike_Headlight(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
	//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		//functions
		void Player_Update(D3DXVECTOR3* v1,D3DXQUATERNION* q1);
		void Ai_Update_Headlight(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1);
		void ShaderUpdate(void);
		void ImpostersCreate(void);
		void ImpostersDestroy(void);
	//-------------------------------------------------------------
};
