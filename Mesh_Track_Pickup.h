#pragma once
//-----------------------------------------------------------------
#define MAX_WEAPON_PICKUPS 10
#define MAX_ENERGY_PICKUPS 10
#define MAX_UTILITY_PICKUPS 5
//-----------------------------------------------------------------
class Mesh_Track_Pickup
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Mesh Data
		MD5MESH*					Pickup_Weapon;
		MD5MESH*					Pickup_Energy;
		MD5MESH*					Pickup_Utility;
		//---------------------------------------------------------
		//constructors
		Mesh_Track_Pickup(void);
		~Mesh_Track_Pickup(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
		void ImpostersCreate_Weapon(void);
		void ImpostersDestroy_Weapon(void);
		void ImpostersCreate_Energy(void);
		void ImpostersDestroy_Energy(void);
		void ImpostersCreate_Utility(void);
		void ImpostersDestroy_Utility(void);
		//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		//functions
		void ShaderUpdate(void);
		void Update_TexturePan(void);
		void Update_MeshSpin(void);
		//---------------------------------------------------------
};
