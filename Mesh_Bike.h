#pragma once
//-----------------------------------------------------------------
#define MAX_BIKE_MODELS 4
//-----------------------------------------------------------------
class Mesh_Bike
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Player Models
		MD5MESH*					Shell[MAX_BIKE_MODELS];
		MD5MESH*					Glow[MAX_BIKE_MODELS];
		MD5MESH*					Shield[MAX_BIKE_MODELS];
		MD5MESH*					Rider[MAX_BIKE_MODELS];
		MD5MESH*					RiderGlow[MAX_BIKE_MODELS];
		MD5MESH*					Helmet[MAX_BIKE_MODELS];
		MD5MESH*					HelmetGlow[MAX_BIKE_MODELS];
		int							ActiveModel_Ai;
		int							ActiveModel_Player;
		//---------------------------------------------------------
		//constructors
		Mesh_Bike(void);
		~Mesh_Bike(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
	//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		//imposter data
		D3DXVECTOR3					vHelmetOffset;
		//Spawn
		D3DXVECTOR3					SpawnLocation_Menu;
		//---------------------------------------------------------
		//functions
		void Player_Update(D3DXVECTOR3* v1,D3DXQUATERNION* q1);
		void Ai_Update_Rider(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1);
		void Ai_Update_Shell(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1);
		void Ai_Update_ShellGlow(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1);
		void Ai_Update_Shield(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1);
		void ShaderUpdate(void);
		void ImpostersCreate(void);
		void ImpostersDestroy(void);
	//-------------------------------------------------------------
};
