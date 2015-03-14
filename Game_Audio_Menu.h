#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Audio_Menu
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//---------------------------------------------------------
		//constructors
		Game_Audio_Menu(void);
		~Game_Audio_Menu(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void MenuFx(int index);
		void Stop(void);
		void Destroy(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		//Menu Sounds
		SOUND*								Menu_Up;
		float								Menu_Up_Volume;

		SOUND*								Menu_Down;
		float								Menu_Down_Volume;

		SOUND*								Menu_ValueChange;
		float								Menu_ValueChange_Volume;

		SOUND*								Start_Select;
		float								Start_Select_Volume;

		SOUND*								MenuBack;
		float								MenuBack_Volume;

		SOUND*								MenuSelect;
		float								MenuSelect_Volume;

		SOUND*								ChatRecieve;
		float								ChatRecieve_Volume;

		void Volume(void);
	//-------------------------------------------------------------
};
