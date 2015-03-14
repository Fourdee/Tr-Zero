#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Global_Texture_Bike_Shadow
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		TEXTURE2D*						Bike_Shadow;
		//TEXTURE2D*						Bike_Shadow_TP;
		//---------------------------------------------------------
		//constructors
		Global_Texture_Bike_Shadow(void);
		~Global_Texture_Bike_Shadow(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void SamplerSet(void);
		void Destroy(void);
	//-------------------------------------------------------------
};
