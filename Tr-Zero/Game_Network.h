#pragma once
//-----------------------------------------------------------------
#include "Network_Client.h"
#include "Network_Server.h"
//-----------------------------------------------------------------
#define MAX_CHAT_DISPLAY 4
//-----------------------------------------------------------------
class Game_Network
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Classes
		Network_Client						Client;
		Network_Server						Server;
		//Chat
		string								ChatMessageDisplay[MAX_CHAT_DISPLAY];
		string								ChatMessageUser[MAX_CHAT_DISPLAY];
		int									ChatDisplayTimer[MAX_CHAT_DISPLAY];
		int									ChatDisplayTimerMax;
		//Thread Send Trigger
		bool								bThread_Send;
		//---------------------------------------------------------
		//constructors
		Game_Network(void);
		~Game_Network(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update_Recieve(void);
		void Update_Send(void);
		void Destroy(void);
		void ZeroData(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		void Update_ConnectionManager(void);
		void Update_Chat(void);
		//---------------------------------------------------------
		bool									bRemoveT;
	//-------------------------------------------------------------
};
