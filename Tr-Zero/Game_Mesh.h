#pragma once
//-----------------------------------------------------------------
//Mesh
#include "Mesh_Animator.h"
#include "Mesh_Bike.h"
#include "Mesh_Bike_Tire.h"
#include "Mesh_Bike_Engine.h"
#include "Mesh_Bike_Shadow.h"
#include "Mesh_Bike_Weapons.h"
#include "Mesh_Bike_Headlight.h"
#include "Mesh_Bike_Trail.h"
#include "Mesh_Track_Pickup.h"

//Culling
#include "Game_Culling_System.h"

//Lighting
#include "Game_Lighting_Directional.h"
#include "Game_PointLight.h"

//-----------------------------------------------------------------
class Game_Mesh
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Mesh Animator
		Mesh_Animator					Animator;
		//bike mesh
		Mesh_Bike						Bike;
		//bike tire mesh
		Mesh_Bike_Tire					Bike_Tire;
		//bike tire mesh
		Mesh_Bike_Engine				Bike_Engine;
		//bike shadow
		Mesh_Bike_Shadow				Bike_Shadow;
		//bike weapons
		Mesh_Bike_Weapons				Bike_Weapons;
		//bike headlight
		Mesh_Bike_Headlight				Bike_Headlight;
		//bike Trail
		Mesh_Bike_Trail					Bike_Trail;
		//Track Pickup
		Mesh_Track_Pickup				Track_Pickup;
		//Culling
		Game_Culling_System				Culling;
		//---------------------------------------------------------
		//Lighting
		Game_Lighting_Directional		Light_Direct;
		Game_PointLight					Light_Point;
		//---------------------------------------------------------
		//constructors
		Game_Mesh(void);
		~Game_Mesh(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
		void Update_Globals(void);
	//-------------------------------------------------------------
	//-------------------------------------------------------------
};
