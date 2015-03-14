#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Settings
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//display data
		DEVICERESOLUTIONS*					DeviceRes;
		char								DeviceName[1024];
		int									DeviceResolutionsCount;
		int*								DisplayWidth;
		int*								DisplayHeight;
		int									ResIndex;
		//---------------------------------------------------------
		//post process effects
		//---------------------------------------------------------
		//texture filter
		bool								bUse_Anisotrpic_Filter;
		int									Anisotropic_Level;
		int									Anisotropic_Max_Level;
		//---------------------------------------------------------
		//constructors
		Game_Settings(void);
		~Game_Settings(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void ResolutionApply(void);
		void LoadSettings(void);
		void SaveSettings(void);
		void Destroy(void);
		void ScaleFixer(void);
	//-------------------------------------------------------------
};
