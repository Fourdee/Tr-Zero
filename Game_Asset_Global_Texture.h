#pragma once
//-----------------------------------------------------------------
#include "Global_Texture_Menu_Main.h"
#include "Global_Texture_Bike.h"
#include "Global_Texture_Bike_Tire.h"
#include "Global_Texture_Bike_Engine.h"
#include "Global_Texture_Bike_Shadow.h"
#include "Global_Texture_Bike_Weapons.h"
#include "Global_Texture_Track_Pickups.h"
//-----------------------------------------------------------------
class Game_Asset_Global_Texture
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//menu
		Global_Texture_Menu_Main		Menu_Main;
		//---------------------------------------------------------
		//bike
		Global_Texture_Bike				Bike;
		//---------------------------------------------------------
		//bike tire
		Global_Texture_Bike_Tire		Bike_Tire;
		//---------------------------------------------------------
		//bike tire
		Global_Texture_Bike_Engine		Bike_Engine;
		//---------------------------------------------------------
		//bike shadow
		Global_Texture_Bike_Weapons		Bike_Weapons;
		//---------------------------------------------------------
		//bike weapons
		Global_Texture_Bike_Shadow		Bike_Shadow;
		//---------------------------------------------------------
		//Track Pickups
		Global_Texture_Track_Pickups	Track_Pickup;
		//---------------------------------------------------------
		//constructors
		Game_Asset_Global_Texture(void);
		~Game_Asset_Global_Texture(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void SamplerUpdate(void);
		void Destroy(void);
	//-------------------------------------------------------------
};
