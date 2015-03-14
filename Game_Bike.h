#pragma once
//-----------------------------------------------------------------
#include "Game_Bike_Manager.h"
#include "Game_Bike_Colour.h"
#include "Game_Bike_Energy.h"
#include "Game_Bike_Weapons.h"
//-----------------------------------------------------------------
class Game_Bike
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Sub Classes
		Game_Bike_Manager					Manager;
		Game_Bike_Colour					Colour;
		Game_Bike_Energy					Energy;
		Game_Bike_Weapons					Weapons;
		//---------------------------------------------------------
		///PlayerName
		string								Name;
		///PlayerID (imposter index number)
		int									PlayerID;
		///Convert to Network Bike?
		int									Networked_Ai_Type;
		D3DXVECTOR3							vNetwork_Recieve;
		D3DXQUATERNION						qNetwork_Recieve;
		///Speed states - sent to bikemanager
		int									InputSpeedState;
		///Steering
		float								fSteering;
		float								fSteering_Target;
		///Tire Spin
		float								fTireSpin;
		///Culling Distance
		float								fDistanceToCam;
		///Drift (RidgeRacer Style)
		bool								bDrift;
		int									NetDrift;
		int									DriftTimer;
		int									DriftTimerDisable;
		///Respawn
		int									RespawnTimer;
		bool								bRespawning;
		///PLAYER - (AI Control takeover switch)
		bool								bAiTakeover;
		//---------------------------------------------------------
		//constructors
		Game_Bike(void);
		~Game_Bike(void);
		//---------------------------------------------------------
		//functions
		void Create(int ImposterIndex);
		void Update(void);
		void Destroy(void);
	private:
		//---------------------------------------------------------
		//functions
		void ResetData(void);
		//AI
		void Update_AI_InputSpeedState(void);
		void Update_Ai_SteeringControl(void);
		void Update_Ai_Offline(void);
		void Update_Ai_Networked(void);
		void Apply_Ai_Steering_Limits_Per_Track(void);
		//PLAYER
		void Update_Player(void);
		void Update_Player_AiTakeOver(void);
		void Update_Player_InputSpeedState(void);
		void Update_Player_SteeringControl(void);
		void Update_Player_DriftControl(void);
		void Apply_Player_Steering_Limits_Per_Track(void);
		//Replay
		void Update_Replay(void);
	//-------------------------------------------------------------
};
