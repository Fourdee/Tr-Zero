#pragma once
//-----------------------------------------------------------------
class Global_Texture_Bike
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Bike
		TEXTURE2D*						Diffuse[2];
		TEXTURE2D*						Normal[2];
		TEXTURE2D*						Specular[2];
		TEXTURE2D*						Refl_Mask[2];
		TEXTURE2D*						Glow[2];
		//---------------------------------------------------------
		//Shield
		TEXTURE2D*						Shield;
		//Headlight
		TEXTURE2D*						Headlight_B;
		TEXTURE2D*						Headlight_C;
		//Trail
		TEXTURE2D*						Trail_em;
		//ENVMAP
		TEXTURECUBE*					EnvMap;
		//---------------------------------------------------------
		//constructors
		Global_Texture_Bike(void);
		~Global_Texture_Bike(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void SamplerSet(void);
		void Destroy(void);
	//-------------------------------------------------------------
};
