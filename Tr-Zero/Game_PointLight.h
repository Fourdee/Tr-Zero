#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_PointLight
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Headlights
		float								PointLight_HeadLight_Alpha;
		float								PointLight_HeadLight_Range;
		float								PointLight_HeadLight_Falloff;
		float								PointLight_HeadLight_Multi;
		D3DXVECTOR3							PointLight_HeadLight_Offset;
		//Shield
		float								PointLight_Shield_Alpha;
		float								PointLight_Shield_Range;
		float								PointLight_Shield_Falloff;
		float								PointLight_Shield_Multi;
		D3DXVECTOR3							PointLight_Shield_Offset;
		//---------------------------------------------------------
		//constructors
		Game_PointLight(void);
		~Game_PointLight(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		int									MAX_POINTLIGHT;
		//---------------------------------------------------------
	//-------------------------------------------------------------
};
