#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Global_Text_Description
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		//---------------------------------------------------------
		//constructors
		Game_Global_Text_Description(void);
		~Game_Global_Text_Description(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		string PositionReadout(int position);
		string Weapon_Secondary_Name(int Value);
		string Weapon_Utility_Name(int Value);

		string Weapon_KilledBy_Name(int Value);

	//-------------------------------------------------------------
};
