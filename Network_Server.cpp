//-----------------------------------------------------------------
// About:
//
// name: "Network_Server.cpp:
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
#include "Network_Server.h"
//-----------------------------------------------------------------
///*****************************************************************
//NETWORK - SERVER -CONSTRUCTORS
///*****************************************************************
Network_Server::Network_Server(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Network_Server::~Network_Server(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
// NETWORK - SERVER - ZeroData
///*****************************************************************
void Network_Server::ZeroData(void)
{
	//-------------------------------------------------------------
	State = 0;
	gNumberOfClients = 0;
	gServerState = 0;

	Packet_Out = 0;

	for(int i=0;i<MAX_NETWORK_CONNECTIONS;i++)
	{
		Packet_In[i] = 0;
		bPacketRecieved[i] = false;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
// NETWORK - SERVER - CREATE
///*****************************************************************
void Network_Server::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}
///*****************************************************************
//NETWORK - SERVER - StartServer
///*****************************************************************
void Network_Server::StartServer(void)
{
	//-------------------------------------------------------------
	iNetServerStart(gNetworkPort,gNetworkPass);
	State = 2;
	//-------------------------------------------------------------
}
///*****************************************************************
/// NETWORK - SERVER - RECIEVE
///*****************************************************************
void Network_Server::Recieve(void)
{
	//-------------------------------------------------------------
	int PacketId = 0;
	//How Many Clients?
	gNumberOfClients = iNetServerConnectedClientCount();
	//-------------------------------------------------------------
	//Resend all data if new connection
	if(iNetServerNewConnectionMade() || gNumberOfClients==0)
	{
		//Reset all AI bikes
		for(int i=0;i<gAi_Max_Count;i++)
		{
			cGame_Bike[i].Networked_Ai_Type = 0;
		}
		//Reset global packet check
		ZeroData_Global_Net_Packets();
	}
	//-------------------------------------------------------------
	//Client Data
	for(int i=0;i<gNumberOfClients;i++)
	{
		//Player Names
		PacketId = i + 1; 
		iNetServerValueStringReceive(cGame_Bike[i].Name,PacketId,i);
		/////Obtain ID ready list for game
		//gNetwork_PlayerNames[i] = gNetworkStringValue[PacketId-1];


		//Packet Data (0-9)
		PacketId = i + 1; 
		bPacketRecieved[i] = false;
		iNetServerValueIntReceive(gNetworkIntValue[PacketId],PacketId,i);
		if(Packet_In[i]!=gNetworkIntValue[PacketId])
		{
			///New packet recieved
			Packet_In[i] = gNetworkIntValue[PacketId];
			bPacketRecieved[i] = true;
		}

		//1500 - Networked player Readystates
		PacketId = i + 1501; 
		iNetServerValueIntReceive(gNetPlayerReady[i],PacketId,i);

		//Speedstate 20-60
		PacketId = i + 21; 
		iNetServerValueIntReceive(cGame_Bike[i].InputSpeedState,PacketId,i);

		//Primary Weapon Fire 61-101
		PacketId = i + 62; 
		iNetServerValueIntReceive(cGame_Bike[i].Weapons.NetFirePrimary,PacketId,i);

		//NetEnergyRegen 102-142
		PacketId = i + 103; 
		iNetServerValueIntReceive(cGame_Bike[i].Energy.NetEnergyRegen,PacketId,i);

		//NetFireSecondary 143-183
		PacketId = i + 144; 
		iNetServerValueIntReceive(cGame_Bike[i].Weapons.NetFireSecondary,PacketId,i);

		//NetFireUtility 184-224
		PacketId = i + 185; 
		iNetServerValueIntReceive(cGame_Bike[i].Weapons.NetFireUtility,PacketId,i);

		//NetSecondaryLockedId 225-265
		PacketId = i + 226; 
		iNetServerValueIntReceive(cGame_Bike[i].Weapons.NetSecondaryLockedId,PacketId,i);

		//NetDrift 266-276 (PLAYERS ONLY)
		PacketId = i + 267; 
		iNetServerValueIntReceive(cGame_Bike[i].NetDrift,PacketId,i);

		//-------------------------------------------------------------
		//Recieve Tickrate Data packet
		if(bPacketRecieved[i])
		{
			//User Colours D3DXVECTOR3 61-69
			PacketId = i + 62; 
			iNetServerValueVec3Receive(&cGame_Bike[i].Colour.vBikeColourTarget,PacketId,i);

			//Energy 277-317
			PacketId = i + 278; 
			int iEnergy = 200;
			iNetServerValueIntReceive(iEnergy,PacketId,i);
			cGame_Bike[i].Energy.fEnergy = (float)iEnergy;

			//Kills 318-328
			PacketId = i + 319; 
			iNetServerValueIntReceive(cGame_Bike[i].Weapons.TotalKills,PacketId,i);
			//Deaths 329-339
			PacketId = i + 330; 
			iNetServerValueIntReceive(cGame_Bike[i].Weapons.TotalDeaths,PacketId,i);

			//Bike Data
			PacketId = i + 1; 
			D3DXVECTOR2 vData = D3DXVECTOR2(0.0f,0.0f);
			iNetServerValueVec2Receive(&vData,PacketId,i);
			cGame_Bike[i].fSteering = vData.x;
			cGame_Bike[i].Manager.fAcceleration_Speed = vData.y;

			iNetServerValueVec3Receive(&cGame_Bike[i].vNetwork_Recieve,PacketId,i);
			iNetServerValueQuatReceive(&cGame_Bike[i].qNetwork_Recieve,PacketId,i);

			cGame_Bike[i].Networked_Ai_Type = 1;
		}
		//---------------------------------------------------------
		//UPGRADES
		if(gGameState==0)
		{
			//uPrimaryDamage 340-380
			PacketId = 340 + (i + 1); 
			iNetServerValueIntReceive(cGame_Upgrades.uPrimaryDamage[i],PacketId,i);
			//uPrimaryTravel 381-421
			PacketId = 381 + (i + 1); 
			iNetServerValueIntReceive(cGame_Upgrades.uPrimaryTravel[i],PacketId,i);
			//uMissileLockTime 422-462
			PacketId = 422 + (i + 1); 
			iNetServerValueIntReceive(cGame_Upgrades.uMissileLockTime[i],PacketId,i);
			//uMissileDamage 463-503
			PacketId = 463 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uMissileDamage[i],PacketId,i);
			//uMissileRadius 504-544
			PacketId = 504 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uMissileRadius[i],PacketId,i);
			//uMissileTravel 545-585
			PacketId = 545 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uMissileTravel[i],PacketId,i);
			//uShoxwaveDamage 586-626
			PacketId = 586 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uShoxwaveDamage[i],PacketId,i);
			//uShoxwaveTravel 627-667
			PacketId = 627 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uShoxwaveTravel[i],PacketId,i);
			//uShoxwaveReduction 668-708
			PacketId = 668 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uShoxwaveReduction[i],PacketId,i);
			//uEmBurstDamage 709-749
			PacketId = 709 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uEmBurstDamage[i],PacketId,i);
			//uEmBurstRadius 750-790
			PacketId = 750 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uEmBurstRadius[i],PacketId,i);
			//uEmBurstReduction 791-831
			PacketId = 791 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uEmBurstReduction[i],PacketId,i);
			//uRailDamage 832-872
			PacketId = 832 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uRailDamage[i],PacketId,i);
			//uRailTravel 873-913
			PacketId = 873 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uRailTravel[i],PacketId,i);
			//uShieldInvTime 914-954
			PacketId = 914 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uShieldInvTime[i],PacketId,i);
			//uAutoPilotTime 955-995
			PacketId = 955 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uAutoPilotTime[i],PacketId,i);
			//uDoubleDamageTime 996-1036
			PacketId = 996 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uDoubleDamageTime[i],PacketId,i);
			//uDoubleDamageConv 1037-1077
			PacketId = 1037 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uDoubleDamageConv[i],PacketId,i);
			//uEnergyMax 1078-1118
			PacketId = 1078 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uEnergyMax[i],PacketId,i);
			//uEnergyPickup 1119-1159
			PacketId = 1119 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uEnergyPickup[i],PacketId,i);
			//uPlayerLevel 1160-1200
			PacketId = 1160 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uPlayerLevel[i],PacketId,i);
			//uEnergyTickRegen 1201-1241
			PacketId = 1201 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uEnergyTickRegen[i],PacketId,i);
			//uShieldInvConvert 1242-1282
			PacketId = 1242 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uShieldInvConvert[i],PacketId,i);
			//uWarpDamageReduce 1283-1323
			PacketId = 1283 + (i + 1);
			iNetServerValueIntReceive(cGame_Upgrades.uWarpDamageReduce[i],PacketId,i);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
/// NETWORK - SERVER - SEND
///*****************************************************************
void Network_Server::Send(void)
{
	//-------------------------------------------------------------
	int PacketId = 0;
	bool bTickRateSend = false;
	gDEBUG_Net_ChangedValues	=	0;	
	//-------------------------------------------------------------
	//Player Names
	///Send me
	PacketId = 0;
	if((string)gPlayerName!=gNetworkStringValue[PacketId])
	{
		gNetworkStringValue[PacketId] = (string)gPlayerName;
		for(int i=0;i<gNumberOfClients;i++)
		{
			iNetServerValueStringSet(gNetworkStringValue[PacketId],PacketId,i);
		}
		gDEBUG_Net_ChangedValues++;
	}
	///Send other clients
	for(int i=0;i<gNumberOfClients;i++)
	{
		PacketId = i+1;
		if(cGame_Bike[i].Name!=gNetworkStringValue[PacketId])
		{
			gNetworkStringValue[PacketId] = cGame_Bike[i].Name; 
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueStringSet(gNetworkStringValue[PacketId],PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
		}
	}
	//-------------------------------------------------------------
	//Tickrate Activate
	if(gNetworkTickRate >= gNetworkTickRateMax)
	{
		//Packet Out ID
		///Send a 0-1, use on client/server for updates and predictions
		Packet_Out++;
		if(Packet_Out > 1)
		{
			Packet_Out = 0;
		}
		bTickRateSend = true;
		gNetworkTickRate = 0;
	}
	//-------------------------------------------------------------
	//Packet ID (INT 0-9)
	if(bTickRateSend)
	{
		PacketId = 0;
		for(int i=0;i<gNumberOfClients;i++)
		{
			iNetServerValueIntSet(Packet_Out,PacketId,i);
		}
	}
	//-------------------------------------------------------------
	//Core Gamestate Data (INT 10-19)
	PacketId = 10;
	///10 - gNetworkTickRateMax
	if(gNetworkTickRateMax != gNetworkIntValue[PacketId])
	{
		gNetworkIntValue[PacketId] = gNetworkTickRateMax;
		for(int i=0;i<gNumberOfClients;i++)
		{
			iNetServerValueIntSet(gNetworkIntValue[PacketId],PacketId,i);
		}
		gDEBUG_Net_ChangedValues++;
	}
	PacketId++;
	///11 - gAi_UserChange
	if(gAi_UserChange != gNetworkIntValue[PacketId])
	{
		gNetworkIntValue[PacketId] = gAi_UserChange;
		for(int i=0;i<gNumberOfClients;i++)
		{
			iNetServerValueIntSet(gNetworkIntValue[PacketId],PacketId,i);
		}
		gDEBUG_Net_ChangedValues++;
	}
	PacketId++;
	///12 - gAiDifficuty
	if(gAiDifficuty != gNetworkIntValue[PacketId])
	{
		gNetworkIntValue[PacketId] = gAiDifficuty;
		for(int i=0;i<gNumberOfClients;i++)
		{
			iNetServerValueIntSet(gNetworkIntValue[PacketId],PacketId,i);
		}
		gDEBUG_Net_ChangedValues++;
	}
	PacketId++;
	///13 - NumberOfClients
	if(gNumberOfClients != gNetworkIntValue[PacketId])
	{
		gNetworkIntValue[PacketId] = gNumberOfClients;
		for(int i=0;i<gNumberOfClients;i++)
		{
			iNetServerValueIntSet(gNetworkIntValue[PacketId],PacketId,i);
		}
		gDEBUG_Net_ChangedValues++;
	}
	PacketId++;
	///14 - gServerState
	if(gServerState != gNetworkIntValue[PacketId])
	{
		gNetworkIntValue[PacketId] = gServerState;
		for(int i=0;i<gNumberOfClients;i++)
		{
			iNetServerValueIntSet(gNetworkIntValue[PacketId],PacketId,i);
		}
		gDEBUG_Net_ChangedValues++;
	}
	PacketId++;
	///15 - gSpeedClass
	if(gSpeedClass != gNetworkIntValue[PacketId])
	{
		gNetworkIntValue[PacketId] = gSpeedClass;
		for(int i=0;i<gNumberOfClients;i++)
		{
			iNetServerValueIntSet(gNetworkIntValue[PacketId],PacketId,i);
		}
		gDEBUG_Net_ChangedValues++;
	}
	PacketId++;
	///16 - gGameModeChange
	if(gGameModeChange != gNetworkIntValue[PacketId])
	{
		gNetworkIntValue[PacketId] = gGameModeChange;
		for(int i=0;i<gNumberOfClients;i++)
		{
			iNetServerValueIntSet(gNetworkIntValue[PacketId],PacketId,i);
		}
		gDEBUG_Net_ChangedValues++;
	}
	PacketId++;
	///17 - gGameStateChange
	if(gGameStateChange != gNetworkIntValue[PacketId])
	{
		gNetworkIntValue[PacketId] = gGameStateChange;
		for(int i=0;i<gNumberOfClients;i++)
		{
			iNetServerValueIntSet(gNetworkIntValue[PacketId],PacketId,i);
		}
		gDEBUG_Net_ChangedValues++;
	}
	PacketId++;
	///18 - gTrackReverse
	if(gTrackReverse != gNetworkIntValue[PacketId])
	{
		gNetworkIntValue[PacketId] = gTrackReverse;
		for(int i=0;i<gNumberOfClients;i++)
		{
			iNetServerValueIntSet(gNetworkIntValue[PacketId],PacketId,i);
		}
		gDEBUG_Net_ChangedValues++;
	}
	PacketId++;
	///19 - Arena Timer
	if(bTickRateSend)
	{
		gNetworkIntValue[PacketId] = gRaceCountdown;
		for(int i=0;i<gNumberOfClients;i++)
		{
			iNetServerValueIntSet(gNetworkIntValue[PacketId],PacketId,i);
		}
	}
	//-------------------------------------------------------------
	//1500 - Networked player Readystates
	PacketId = 1500;
	if(gNetMeReady != gNetworkIntValue[PacketId])
	{
		for(int i=0;i<gNumberOfClients;i++)
		{
			iNetServerValueIntSet(gNetMeReady,PacketId,i);
		}
		gNetworkIntValue[PacketId] = gNetMeReady;
		gDEBUG_Net_ChangedValues++;
	}
	for(int i=0;i<gNumberOfClients;i++)
	{
		PacketId = 1501 + i;
		if(gNetPlayerReady[i] != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(gNetPlayerReady[i],PacketId,j);
			}
			gNetworkIntValue[PacketId] = gNetPlayerReady[i];
		gDEBUG_Net_ChangedValues++;
		}
	}
	//-------------------------------------------------------------
	//Speedstate 20-60
	PacketId = 20;
	if(cGame_Bike[gAi_Max_Count].InputSpeedState != gNetworkIntValue[PacketId])
	{
		for(int j=0;j<gNumberOfClients;j++)
		{
			iNetServerValueIntSet(cGame_Bike[gAi_Max_Count].InputSpeedState,PacketId,j);
		}
		gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].InputSpeedState;
		gDEBUG_Net_ChangedValues++;
	}
	for(int i=0;i<gAi_Max_Count;i++)
	{
		PacketId = i + 21;
		if(cGame_Bike[i].InputSpeedState != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Bike[i].InputSpeedState,PacketId,j);
			}
			gNetworkIntValue[PacketId] = cGame_Bike[i].InputSpeedState;
		gDEBUG_Net_ChangedValues++;
		}
	}
	//-------------------------------------------------------------
	//Primary Weapon Fire 61-101
	PacketId = 61;
	if(cGame_Bike[gAi_Max_Count].Weapons.NetFirePrimary != gNetworkIntValue[PacketId])
	{
		for(int j=0;j<gNumberOfClients;j++)
		{
			iNetServerValueIntSet(cGame_Bike[gAi_Max_Count].Weapons.NetFirePrimary,PacketId,j);
		}
		gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].Weapons.NetFirePrimary;
		gDEBUG_Net_ChangedValues++;
	}
	for(int i=0;i<gAi_Max_Count;i++)
	{
		PacketId = i + 62;
		if(cGame_Bike[i].Weapons.NetFirePrimary != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Bike[i].Weapons.NetFirePrimary,PacketId,j);
			}
			gNetworkIntValue[PacketId] = cGame_Bike[i].Weapons.NetFirePrimary;
		gDEBUG_Net_ChangedValues++;
		}
	}
	//-------------------------------------------------------------
	//NetEnergyRegen 102-142
	PacketId = 102;
	if(cGame_Bike[gAi_Max_Count].Energy.NetEnergyRegen != gNetworkIntValue[PacketId])
	{
		for(int j=0;j<gNumberOfClients;j++)
		{
			iNetServerValueIntSet(cGame_Bike[gAi_Max_Count].Energy.NetEnergyRegen,PacketId,j);
		}
		gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].Energy.NetEnergyRegen;
		gDEBUG_Net_ChangedValues++;
	}
	for(int i=0;i<gAi_Max_Count;i++)
	{
		PacketId = i + 103;
		if(cGame_Bike[i].Energy.NetEnergyRegen != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Bike[i].Energy.NetEnergyRegen,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Bike[i].Energy.NetEnergyRegen;
		}
	}
	//-------------------------------------------------------------
	//NetFireSecondary 143-183
	PacketId = 143;
	if(cGame_Bike[gAi_Max_Count].Weapons.NetFireSecondary != gNetworkIntValue[PacketId])
	{
		for(int j=0;j<gNumberOfClients;j++)
		{
			iNetServerValueIntSet(cGame_Bike[gAi_Max_Count].Weapons.NetFireSecondary,PacketId,j);
		}
		gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].Weapons.NetFireSecondary;
		gDEBUG_Net_ChangedValues++;
	}
	for(int i=0;i<gAi_Max_Count;i++)
	{
		PacketId = i + 144;
		if(cGame_Bike[i].Weapons.NetFireSecondary != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Bike[i].Weapons.NetFireSecondary,PacketId,j);
			}
			gNetworkIntValue[PacketId] = cGame_Bike[i].Weapons.NetFireSecondary;
		gDEBUG_Net_ChangedValues++;
		}
	}
	//-------------------------------------------------------------
	//NetFireUtility 184-224
	PacketId = 184;
	if(cGame_Bike[gAi_Max_Count].Weapons.NetFireUtility != gNetworkIntValue[PacketId])
	{
		for(int j=0;j<gNumberOfClients;j++)
		{
			iNetServerValueIntSet(cGame_Bike[gAi_Max_Count].Weapons.NetFireUtility,PacketId,j);
		}
		gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].Weapons.NetFireUtility;
		gDEBUG_Net_ChangedValues++;
	}
	for(int i=0;i<gAi_Max_Count;i++)
	{
		PacketId = i + 185;
		if(cGame_Bike[i].Weapons.NetFireUtility != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Bike[i].Weapons.NetFireUtility,PacketId,j);
			}
			gNetworkIntValue[PacketId] = cGame_Bike[i].Weapons.NetFireUtility;
		gDEBUG_Net_ChangedValues++;
		}
	}
	//-------------------------------------------------------------
	//NetSecondaryLockedId 225-265
	PacketId = 225;
	if(cGame_Bike[gAi_Max_Count].Weapons.NetSecondaryLockedId != gNetworkIntValue[PacketId])
	{
		for(int j=0;j<gNumberOfClients;j++)
		{
			iNetServerValueIntSet(cGame_Bike[gAi_Max_Count].Weapons.NetSecondaryLockedId,PacketId,j);
		}
		gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].Weapons.NetSecondaryLockedId;
		gDEBUG_Net_ChangedValues++;
	}
	for(int i=0;i<gAi_Max_Count;i++)
	{
		PacketId = i + 226;
		if(cGame_Bike[i].Weapons.NetSecondaryLockedId != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Bike[i].Weapons.NetSecondaryLockedId,PacketId,j);
			}
			gNetworkIntValue[PacketId] = cGame_Bike[i].Weapons.NetSecondaryLockedId;
		gDEBUG_Net_ChangedValues++;
		}
	}
	//-------------------------------------------------------------
	//NetDrift 266-276 (PLAYERS ONLY)
	PacketId = 266;
	if(cGame_Bike[gAi_Max_Count].NetDrift != gNetworkIntValue[PacketId])
	{
		for(int j=0;j<gNumberOfClients;j++)
		{
			iNetServerValueIntSet(cGame_Bike[gAi_Max_Count].NetDrift,PacketId,j);
		}
		gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].NetDrift;
		gDEBUG_Net_ChangedValues++;
	}
	for(int i=0;i<gNumberOfClients;i++)
	{
		PacketId = i + 267;
		if(cGame_Bike[i].NetDrift != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Bike[i].NetDrift,PacketId,j);
			}
			gNetworkIntValue[PacketId] = cGame_Bike[i].NetDrift;
		gDEBUG_Net_ChangedValues++;
		}
	}
	//-------------------------------------------------------------
	//TickRateSend Data Packet
	if(bTickRateSend)
	{
		//User Colours D3DXVECTOR3 61-69
		PacketId = 61;
		if(cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget != gNetworkVector3Value[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueVec3Set(&cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget,PacketId,j);
			}
			gNetworkVector3Value[PacketId] = cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget;
		gDEBUG_Net_ChangedValues++;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = i + 62;
			if(cGame_Bike[i].Colour.vBikeColourTarget != gNetworkVector3Value[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueVec3Set(&cGame_Bike[i].Colour.vBikeColourTarget,PacketId,j);
				}
				gNetworkVector3Value[PacketId] = cGame_Bike[i].Colour.vBikeColourTarget;
		gDEBUG_Net_ChangedValues++;
			}
		}

		//Energy 277-317
		PacketId = 277;
		int iEnergy = (int)cGame_Bike[gAi_Max_Count].Energy.fEnergy;
		if(iEnergy != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(iEnergy,PacketId,j);
			}
			gNetworkIntValue[PacketId] = iEnergy;
		gDEBUG_Net_ChangedValues++;
		}
		for(int i=0;i<gAi_Max_Count;i++)
		{
			PacketId = i + 278;
			iEnergy = (int)cGame_Bike[i].Energy.fEnergy;
			if(iEnergy != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(iEnergy,PacketId,j);
				}
				gNetworkIntValue[PacketId] = iEnergy;
		gDEBUG_Net_ChangedValues++;
			}
		}

		//Kills 318-328
		PacketId = 318;
		if(cGame_Bike[gAi_Max_Count].Weapons.TotalKills != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Bike[gAi_Max_Count].Weapons.TotalKills,PacketId,j);
			}
			gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].Weapons.TotalKills;
		gDEBUG_Net_ChangedValues++;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = i + 319;
			if(cGame_Bike[i].Weapons.TotalKills != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Bike[i].Weapons.TotalKills,PacketId,j);
				}
				gNetworkIntValue[PacketId] = cGame_Bike[i].Weapons.TotalKills;
		gDEBUG_Net_ChangedValues++;
			}
		}
		//Deaths 329-339
		PacketId = 329;
		if(cGame_Bike[gAi_Max_Count].Weapons.TotalDeaths != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Bike[gAi_Max_Count].Weapons.TotalDeaths,PacketId,j);
			}
			gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].Weapons.TotalDeaths;
		gDEBUG_Net_ChangedValues++;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = i + 330;
			if(cGame_Bike[i].Weapons.TotalDeaths != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Bike[i].Weapons.TotalDeaths,PacketId,j);
				}
				gNetworkIntValue[PacketId] = cGame_Bike[i].Weapons.TotalDeaths;
		gDEBUG_Net_ChangedValues++;
			}
		}

		//BIKES
		PacketId = 0;
		for(int j=0;j<gNumberOfClients;j++)
		{
			///ServerPlayer
			iNetServerValueVec2Set(&D3DXVECTOR2(cGame_Bike[gAi_Max_Count].fSteering,
									cGame_Bike[gAi_Max_Count].Manager.fAcceleration_Speed),
									PacketId,j);
			iNetServerValueVec3Set(&cGame_Bike[gAi_Max_Count].Manager.vBikeOrigin,PacketId,j);
			iNetServerValueQuatSet(&cGame_Bike[gAi_Max_Count].Manager.qBikeOrigin,PacketId,j);
		}
		for(int i=0;i<gAi_Max_Count;i++)
		{
			PacketId = i + 1;
			///ServerAi
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueVec2Set(&D3DXVECTOR2(cGame_Bike[i].fSteering,
										cGame_Bike[i].Manager.fAcceleration_Speed),
										PacketId,j);
				iNetServerValueVec3Set(&cGame_Bike[i].Manager.vBikeOrigin,PacketId,j);
				iNetServerValueQuatSet(&cGame_Bike[i].Manager.qBikeOrigin,PacketId,j);
			}
		}
	}
	//-------------------------------------------------------------
	//UPGRADES
	if(gGameState==0)
	{
		//uPrimaryDamage 340-380
		PacketId = 340;
		if(cGame_Upgrades.uPrimaryDamagePlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uPrimaryDamagePlayer,PacketId,j);
			}
			gNetworkIntValue[PacketId] = cGame_Upgrades.uPrimaryDamagePlayer;
		gDEBUG_Net_ChangedValues++;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 340 + (i + 1);
			if(cGame_Upgrades.uPrimaryDamage[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uPrimaryDamage[i],PacketId,j);
				}
				gNetworkIntValue[PacketId] = cGame_Upgrades.uPrimaryDamage[i];
		gDEBUG_Net_ChangedValues++;
			}
		}
		//uPrimaryTravel 381-421
		PacketId = 381;
		if(cGame_Upgrades.uPrimaryTravelPlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uPrimaryTravelPlayer,PacketId,j);
			}
			gNetworkIntValue[PacketId] = cGame_Upgrades.uPrimaryTravelPlayer;
		gDEBUG_Net_ChangedValues++;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 381 + (i + 1);
			if(cGame_Upgrades.uPrimaryTravel[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uPrimaryTravel[i],PacketId,j);
				}
				gNetworkIntValue[PacketId] = cGame_Upgrades.uPrimaryTravel[i];
		gDEBUG_Net_ChangedValues++;
			}
		}
		//uMissileLockTime 422-462
		PacketId = 422;
		if(cGame_Upgrades.uMissileLockTimePlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uMissileLockTimePlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uMissileLockTimePlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 422 + (i + 1);
			if(cGame_Upgrades.uMissileLockTime[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uMissileLockTime[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uMissileLockTime[i];
			}
		}
		//uMissileDamage 463-503
		PacketId = 463;
		if(cGame_Upgrades.uMissileDamagePlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uMissileDamagePlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uMissileDamagePlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 463 + (i + 1);
			if(cGame_Upgrades.uMissileDamage[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uMissileDamage[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uMissileDamage[i];
			}
		}
		//uMissileRadius 504-544
		PacketId = 504;
		if(cGame_Upgrades.uMissileRadiusPlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uMissileRadiusPlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uMissileRadiusPlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 504 + (i + 1);
			if(cGame_Upgrades.uMissileRadius[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uMissileRadius[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uMissileRadius[i];
			}
		}
		//uMissileTravel 545-585
		PacketId = 545;
		if(cGame_Upgrades.uMissileTravelPlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uMissileTravelPlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uMissileTravelPlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 545 + (i + 1);
			if(cGame_Upgrades.uMissileTravel[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uMissileTravel[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uMissileTravel[i];
			}
		}
		//uShoxwaveDamage 586-626
		PacketId = 586;
		if(cGame_Upgrades.uShoxwaveDamagePlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uShoxwaveDamagePlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uShoxwaveDamagePlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 586 + (i + 1);
			if(cGame_Upgrades.uShoxwaveDamage[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uShoxwaveDamage[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uShoxwaveDamage[i];
			}
		}
		//uShoxwaveTravel 627-667
		PacketId = 627;
		if(cGame_Upgrades.uShoxwaveTravelPlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uShoxwaveTravelPlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uShoxwaveTravelPlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 627 + (i + 1);
			if(cGame_Upgrades.uShoxwaveTravel[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uShoxwaveTravel[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uShoxwaveTravel[i];
			}
		}
		//uShoxwaveReduction 668-708
		PacketId = 668;
		if(cGame_Upgrades.uShoxwaveReductionPlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uShoxwaveReductionPlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uShoxwaveReductionPlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 668 + (i + 1);
			if(cGame_Upgrades.uShoxwaveReduction[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uShoxwaveReduction[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uShoxwaveReduction[i];
			}
		}
		//uEmBurstDamage 709-749
		PacketId = 709;
		if(cGame_Upgrades.uEmBurstDamagePlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uEmBurstDamagePlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uEmBurstDamagePlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 709 + (i + 1);
			if(cGame_Upgrades.uEmBurstDamage[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uEmBurstDamage[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uEmBurstDamage[i];
			}
		}
		//uEmBurstRadius 750-790
		PacketId = 750;
		if(cGame_Upgrades.uEmBurstRadiusPlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uEmBurstRadiusPlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uEmBurstRadiusPlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 750 + (i + 1);
			if(cGame_Upgrades.uEmBurstRadius[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uEmBurstRadius[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uEmBurstRadius[i];
			}
		}
		//uEmBurstReduction 791-831
		PacketId = 791;
		if(cGame_Upgrades.uEmBurstReductionPlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uEmBurstReductionPlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uEmBurstReductionPlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 791 + (i + 1);
			if(cGame_Upgrades.uEmBurstReduction[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uEmBurstReduction[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uEmBurstReduction[i];
			}
		}
		//uRailDamage 832-872
		PacketId = 832;
		if(cGame_Upgrades.uRailDamagePlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uRailDamagePlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uRailDamagePlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 832 + (i + 1);
			if(cGame_Upgrades.uRailDamage[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uRailDamage[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uRailDamage[i];
			}
		}
		//uRailTravel 873-913
		PacketId = 873;
		if(cGame_Upgrades.uRailTravelPlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uRailTravelPlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uRailTravelPlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 873 + (i + 1);
			if(cGame_Upgrades.uRailTravel[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uRailTravel[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uRailTravel[i];
			}
		}
		//uShieldInvTime 914-954
		PacketId = 914;
		if(cGame_Upgrades.uShieldInvTimePlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uShieldInvTimePlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uShieldInvTimePlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 914 + (i + 1);
			if(cGame_Upgrades.uShieldInvTime[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uShieldInvTime[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uShieldInvTime[i];
			}
		}
		//uAutoPilotTime 955-995
		PacketId = 955;
		if(cGame_Upgrades.uAutoPilotTimePlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uAutoPilotTimePlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uAutoPilotTimePlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 955 + (i + 1);
			if(cGame_Upgrades.uAutoPilotTime[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uAutoPilotTime[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uAutoPilotTime[i];
			}
		}
		//uDoubleDamageTime 996-1036
		PacketId = 996;
		if(cGame_Upgrades.uDoubleDamageTimePlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uDoubleDamageTimePlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uDoubleDamageTimePlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 996 + (i + 1);
			if(cGame_Upgrades.uDoubleDamageTime[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uDoubleDamageTime[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uDoubleDamageTime[i];
			}
		}
		//uDoubleDamageConv 1037-1077
		PacketId = 1037;
		if(cGame_Upgrades.uDoubleDamageConvPlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uDoubleDamageConvPlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uDoubleDamageConvPlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 1037 + (i + 1);
			if(cGame_Upgrades.uDoubleDamageConv[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uDoubleDamageConv[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uDoubleDamageConv[i];
			}
		}
		//uEnergyMax 1078-1118
		PacketId = 1078;
		if(cGame_Upgrades.uEnergyMaxPlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uEnergyMaxPlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uEnergyMaxPlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 1078 + (i + 1);
			if(cGame_Upgrades.uEnergyMax[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uEnergyMax[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uEnergyMax[i];
			}
		}
		//uEnergyPickup 1119-1159
		PacketId = 1119;
		if(cGame_Upgrades.uEnergyPickupPlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uEnergyPickupPlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uEnergyPickupPlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 1119 + (i + 1);
			if(cGame_Upgrades.uEnergyPickup[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uEnergyPickup[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uEnergyPickup[i];
			}
		}
		//uPlayerLevel 1160-1200
		PacketId = 1160;
		if(cGame_PlayerStats.Player_Level != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_PlayerStats.Player_Level,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_PlayerStats.Player_Level;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 1160 + (i + 1);
			if(cGame_Upgrades.uPlayerLevel[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uPlayerLevel[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uPlayerLevel[i];
			}
		}
		//uEnergyTickRegen 1201-1241
		PacketId = 1201;
		if(cGame_Upgrades.uEnergyTickRegenPlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uEnergyTickRegenPlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uEnergyTickRegenPlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 1201 + (i + 1);
			if(cGame_Upgrades.uEnergyTickRegen[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uEnergyTickRegen[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uEnergyTickRegen[i];
			}
		}
		//uShieldInvConvert 1242-1282
		PacketId = 1242;
		if(cGame_Upgrades.uShieldInvConvertPlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uShieldInvConvertPlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uShieldInvConvertPlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 1242 + (i + 1);
			if(cGame_Upgrades.uShieldInvConvert[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uShieldInvConvert[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uShieldInvConvert[i];
			}
		}
		//uWarpDamageReduce 1283-1323
		PacketId = 1283;
		if(cGame_Upgrades.uWarpDamageReducePlayer != gNetworkIntValue[PacketId])
		{
			for(int j=0;j<gNumberOfClients;j++)
			{
				iNetServerValueIntSet(cGame_Upgrades.uWarpDamageReducePlayer,PacketId,j);
			}
		gDEBUG_Net_ChangedValues++;
			gNetworkIntValue[PacketId] = cGame_Upgrades.uWarpDamageReducePlayer;
		}
		for(int i=0;i<gNumberOfClients;i++)
		{
			PacketId = 1283 + (i + 1);
			if(cGame_Upgrades.uWarpDamageReduce[i] != gNetworkIntValue[PacketId])
			{
				for(int j=0;j<gNumberOfClients;j++)
				{
					iNetServerValueIntSet(cGame_Upgrades.uWarpDamageReduce[i],PacketId,j);
				}
		gDEBUG_Net_ChangedValues++;
				gNetworkIntValue[PacketId] = cGame_Upgrades.uWarpDamageReduce[i];
			}
		}
	}
	//-------------------------------------------------------------
	//Send Packet
	iNetServerValuesToClientsBroadcast();
	//-------------------------------------------------------------
}
///*****************************************************************
//NETWORK - SERVER - DESTROY
///*****************************************************************
void Network_Server::Destroy(void)
{
	//-------------------------------------------------------------
	iNetStop();
	ZeroData();
	//Reset all AI bikes
	for(int i=0;i<gAi_Max_Count;i++)
	{
		cGame_Bike[i].Networked_Ai_Type = 0;
	}
	//-------------------------------------------------------------
}