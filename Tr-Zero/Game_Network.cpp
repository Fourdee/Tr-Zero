//-----------------------------------------------------------------
// About:
//
// name: "Game_Network.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
//
// device input: none.
//
// todo:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Network.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - NETWORK - CONSTRUCTORS
///*****************************************************************
Game_Network::Game_Network(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Network::~Game_Network(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - NETWORK - CREATE
///*****************************************************************
void Game_Network::Create(void)
{
	//-------------------------------------------------------------
	Server.Create();
	Client.Create();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - NETWORK - ZeroData
///*****************************************************************
void Game_Network::ZeroData(void)
{
	//-------------------------------------------------------------
	ZeroData_Global_Net_Packets();
	//-------------------------------------------------------------
	//Chat
	for(int i=0;i<MAX_CHAT_DISPLAY;i++)
	{
		ChatMessageDisplay[i] = "";
		ChatMessageUser[i] = "";
		ChatDisplayTimer[i] = 0;
	}
	ChatDisplayTimerMax = 1200;
	bRemoveT = true;
	//-------------------------------------------------------------
	//Thread Send Trigger
	bThread_Send = false;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - NETWORK - Update_Chat
///*****************************************************************
void Game_Network::Update_Chat(void)
{
	//-------------------------------------------------------------
	//Recieve
	char name[1024] = "";
	char recieve[1024] = "";
	//Server Recieve
	if(iNetMachineIsServer())
	{ 
		if(iNetServerChatReceive(name,recieve))
		{
			cGame_Audio.Menu.MenuFx(4);
			ChatMessageDisplay[3] = ChatMessageDisplay[2];
			ChatMessageDisplay[2] = ChatMessageDisplay[1];
			ChatMessageDisplay[1] = ChatMessageDisplay[0];
			ChatMessageDisplay[0] = recieve;

			ChatMessageUser[3] = ChatMessageUser[2];
			ChatMessageUser[2] = ChatMessageUser[1];
			ChatMessageUser[1] = ChatMessageUser[0];
			ChatMessageUser[0] = name;

			ChatDisplayTimer[3] = ChatDisplayTimer[2];
			ChatDisplayTimer[2] = ChatDisplayTimer[1];
			ChatDisplayTimer[1] = ChatDisplayTimer[0];
			ChatDisplayTimer[0] = 0;
		}
	}
	//Client
	else if(iNetMachineIsClient())
	{
		if(iNetClientChatReceive(name,recieve))
		{
			cGame_Audio.Menu.MenuFx(4);
			ChatMessageDisplay[3] = ChatMessageDisplay[2];
			ChatMessageDisplay[2] = ChatMessageDisplay[1];
			ChatMessageDisplay[1] = ChatMessageDisplay[0];
			ChatMessageDisplay[0] = recieve;

			ChatMessageUser[3] = ChatMessageUser[2];
			ChatMessageUser[2] = ChatMessageUser[1];
			ChatMessageUser[1] = ChatMessageUser[0];
			ChatMessageUser[0] = name;

			ChatDisplayTimer[3] = ChatDisplayTimer[2];
			ChatDisplayTimer[2] = ChatDisplayTimer[1];
			ChatDisplayTimer[1] = ChatDisplayTimer[0];
			ChatDisplayTimer[0] = 0;
		}
	}
	//-------------------------------------------------------------
	//Text Input
	static bool bChatType = false;
	static string input = "";
	D3DXVECTOR2 vPrint = D3DXVECTOR2(-14.0f,0.0f);
	if(gMenu_Active)
	{
		vPrint = D3DXVECTOR2(-2.0f,-10.0f);
	}


	//Activate Chat
	if(!gTextInputLock)
	{
		if(iKeyDown(DIK_T))
		{
			gTextInputLock = true;
			bChatType = true;
			bRemoveT = true;///prevent T passing to input string
		}
	}
	else if(gTextInputLock && !bChatType)//exit
	{
		gTextInputLock = false;
	}
	else if(bChatType)//update
	{
		int c = iTypedChar(true);
		//Enter Key
		if(c==-1)
		{
			//cGame_Audio.Menu.MenuFx(2);
			bChatType = false;
			//send gCharBuffer
			if(iNetMachineIsServer() && input!="")
			{
				iNetServerChatSend((char*)input.c_str(),-1);
			}
			else if(input!="")
			{
				iNetClientChatSend((char*)input.c_str());
			}
			input = "";
		}
		//Character Input
		if(c > 0 && input.length() < 70)
		{
			cGame_Audio.Menu.MenuFx(0);
			input += " ";
			input[input.length()-1] = c;
		}
		//back-space
		if(iKeyClickAutoRepeat(VK_BACK,gMenu_Input_Init_Delay,2.0f))
		{
			if(input.length() >= 1)
			{
				cGame_Audio.Menu.MenuFx(5);
				input.resize(input.length()-1);
			}
		}
		//Print Input Text
		if(input=="")
		{
			iPrint3((char*)"Chat......",cGame_Font.f26pt,
				   &vPrint,
				   &D3DXVECTOR4(gMenuFontColour.x,gMenuFontColour.y,gMenuFontColour.z,1.0f),
				   gFont,false);
		}
		else
		{
			iPrint3((char*)input.c_str(),cGame_Font.f22pt,
				   &vPrint,
				   &D3DXVECTOR4(gMenuFontColour.x,gMenuFontColour.y,gMenuFontColour.z,1.0f),
				   gFont,false);
		}
		//Remove the T from the iKeyClick follow over........
		if(bRemoveT)
		{
			input = "";
			bRemoveT = false;
		}
	}
	vPrint.y += 1.0f;
	//-------------------------------------------------------------
	//Print Chat
	for(int i=0;i<MAX_CHAT_DISPLAY;i++)
	{
		if(ChatDisplayTimer[i] < ChatDisplayTimerMax)
		{
			ChatDisplayTimer[i]++;
			float alpha = iFloatInterpolateSmooth((float)ChatDisplayTimer[i],(float)(ChatDisplayTimerMax - 300),(float)ChatDisplayTimerMax,1.0f,0.0f);
			iPrint3((char*)ChatMessageDisplay[i].c_str(),cGame_Font.f20pt,
				   &vPrint,
				   &D3DXVECTOR4(1.0f,1.0f,1.0f,alpha),
				   gFont,false);
			vPrint.y += 0.5f;

			iPrint3((char*)ChatMessageUser[i].c_str(),cGame_Font.f20pt,
				   &vPrint,
				   &D3DXVECTOR4(gMenuFontColour.x,gMenuFontColour.y,gMenuFontColour.z,alpha),
				   gFont,false);
			vPrint.y += 0.75f;
		}
	}
	//-------------------------------------------------------------
	//Network lobby info etc
	if(iNetworkIsActive() && 
		gMenu_Active)
	{
		//Print Total Clients
		D3DXVECTOR2 vPrint = D3DXVECTOR2(6.0f,11.0f);
		sprintf_s(gCharBuffer,"Total Connected Players : %d/%d",gNumberOfClients,iNetServerMaxClientCount());
		iPrint(gCharBuffer,cGame_Font.f18pt,&vPrint,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
		//Status
		vPrint = D3DXVECTOR2(10.0f,-5.0f);
		D3DXVECTOR4 vColour = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
		for(int i=0;i<iNetServerMaxClientCount()-1;i++)
		{
			if(i<gNumberOfClients)
			{
				vColour = D3DXVECTOR4(cGame_Bike[i].Colour.vBikeColourTarget.x,cGame_Bike[i].Colour.vBikeColourTarget.y,cGame_Bike[i].Colour.vBikeColourTarget.z,1.0f);
			}
			else///empty slot
			{
				vColour = D3DXVECTOR4(0.6f,0.6f,0.6f,1.0f);
			}
			iPrint3((char*)cGame_Bike[i].Name.c_str(),cGame_Font.f18pt,&vPrint,&vColour,gFont,false);

			vPrint.y -= 0.75f;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - NETWORK - Update_ConnectionManager
///*****************************************************************
void Game_Network::Update_ConnectionManager(void)
{
	//-------------------------------------------------------------
	//Monitor Connection States
	// -1=kill
	//	0=inactive,
	//	1=create
	//	2=active
	//-------------------------------------------------------------
	//Connect Disconnect
	//string iNetExternalIp(void);
	//bool iNetMasterServerGet(string &targetIp);
	//void iNetMasterServerPost(void);	
	if(Server.State==-1)
	{
		Server.Destroy();
		ZeroData();
	}
	else if(Server.State==1)
	{
		Server.StartServer();
	}

	if(Client.State==-1)
	{
		Client.Destroy();
		ZeroData();
	}
	else if(Client.State==1)
	{
		Client.Connect();
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - NETWORK - Update_Recieve
///*****************************************************************
void Game_Network::Update_Recieve(void)
{
	//-------------------------------------------------------------
	//Update_Recieve
	// - Runs before the bike updates
	//-------------------------------------------------------------
	//Update Active Connections
	///Update Active Server
	if(Server.State==2)
	{
		Server.Recieve();
		Update_Chat();
	}
	///Update Active Client
	else if(Client.State==2)
	{
		Client.Recieve();
		Update_Chat();
	}
	//-------------------------------------------------------------
	//Conection Manager
	Update_ConnectionManager();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - NETWORK - Update_Send
///*****************************************************************
void Game_Network::Update_Send(void)
{
	//-------------------------------------------------------------
	//Update_Send
	// - Runs at the end of bike updates
	//-------------------------------------------------------------
	//Update Active Connections
	///Update Tick rate
	gNetworkTickRate++;
	///Update Active Server
	if(Server.State==2)
	{
		Server.Send();
	}
	///Update Active Client
	else if(Client.State==2)
	{
		Client.Send();
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - NETWORK - DESTROY
///*****************************************************************
void Game_Network::Destroy(void)
{
	//-------------------------------------------------------------
	Server.Destroy();
	Client.Destroy();
	//-------------------------------------------------------------
}