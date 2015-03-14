#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Controls
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		//---------------------------------------------------------
		//constructors
		Game_Controls(void);
		~Game_Controls(void);
		//---------------------------------------------------------
		//functions
		void Update(void);
		void Update_Feedback(void);
		///bike
		bool Input_Bike_Acceleration(void);
		bool Input_Bike_Break(void);
		bool Input_Bike_Boost(void);
		bool Input_Bike_PrimaryWeapon(void);
		bool Input_Bike_SecondaryWeapon(void);
		bool Input_Bike_UtilityWeapon(void);
		float Input_Bike_Steering(void);
		float Input_Bike_Axis_Y(void);
		///camera
		bool Input_Camera_Mode_Change(void);
		float Input_Camera_Axis_X(void);
		float Input_Camera_Axis_Y(void);
		bool Input_Camera_LookBack(void);
		///action
		bool Input_Action_Start(void);
		void Input_Action_Pause(void);
		bool Input_Action_DevMode(void);
		bool Input_Action_Colour(void);
		bool Input_Action_ScoreBoard(void);
		///menu
		bool Input_Menu_Action_Up(void);
		bool Input_Menu_Action_Down(void);
		bool Input_Menu_Action_Left(void);
		bool Input_Menu_Action_Right(void);
		bool Input_Menu_Action_Select(void);
		bool Input_Menu_Action_Back(void);		
	//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		//data
		//---------------------------------------------------------
		//functions
		//---------------------------------------------------------
	//-------------------------------------------------------------
};
