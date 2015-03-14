#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Mesh_Bike_Tire
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//mesh
		MD5MESH*					Back[2];
		MD5MESH*					Back_Glow[2];
		MD5MESH*					Back_Glow_In[2];
		MD5MESH*					Front[2];
		MD5MESH*					Front_Glow[2];
		MD5MESH*					Front_Glow_In[2];
		//data
		D3DXVECTOR3					Back_Pos_Offset[2];
		D3DXVECTOR3					Front_Pos_Offset[2];
		int							ActiveModel_Ai;
		int							ActiveModel_Player;
		//---------------------------------------------------------
		//constructors
		Mesh_Bike_Tire(void);
		~Mesh_Bike_Tire(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
	//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		//functions
		void ImpostersCreate(void);
		void ImpostersDestroy(void);
		void ShaderUpdate(void);
		void Player_Update(D3DXVECTOR3* v1,D3DXQUATERNION* q1,float* fTireSpin);
		void Ai_Update(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1,float* fTireSpin);
	//-------------------------------------------------------------
};