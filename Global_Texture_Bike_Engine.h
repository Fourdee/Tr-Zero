#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Global_Texture_Bike_Engine
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		TEXTURE2D*						Diffuse;
		TEXTURE2D*						Normal;
		TEXTURE2D*						Glow_A;
		//---------------------------------------------------------
		//constructors
		Global_Texture_Bike_Engine(void);
		~Global_Texture_Bike_Engine(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void SamplerSet(void);
		void Destroy(void);
	//-------------------------------------------------------------
};
