#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Physx_Collision_Mask
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		PHYSXCOLLISIONMASK*				Default;
		//---------------------------------------------------------
		//constructors
		Game_Physx_Collision_Mask(void);
		~Game_Physx_Collision_Mask(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Destroy(void);
	//-------------------------------------------------------------
};
