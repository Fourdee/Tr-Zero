#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Global_Texture_Bike_Tire
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		TEXTURE2D*						Diffuse[2];
		TEXTURE2D*						Normal[2];
		TEXTURE2D*						Specular[2];
		TEXTURE2D*						DiffuseBlur[2];
		TEXTURE2D*						NormalBlur[2];
		TEXTURE2D*						SpecularBlur[2];
		TEXTURE2D*						Glow_A[2];
		TEXTURE2D*						Glow_A_Blur[2];

		TEXTURE2D*						Glow_B;
		//---------------------------------------------------------
		//constructors
		Global_Texture_Bike_Tire(void);
		~Global_Texture_Bike_Tire(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void SamplerSet(void);
		void Destroy(void);
	//-------------------------------------------------------------
};
