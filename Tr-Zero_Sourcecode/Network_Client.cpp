//-----------------------------------------------------------------
// About:
//
// name: "Network_Client.cpp:
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
#include "Network_Client.h"
//-----------------------------------------------------------------
///*****************************************************************
// NETWORK - CLIENT - CONSTRUCTORS
///*****************************************************************
Network_Client::Network_Client(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Network_Client::~Network_Client(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
// NETWORK - CLIENT - ZeroData
///*****************************************************************
void Network_Client::ZeroData(void)
{
	//-------------------------------------------------------------
	TimeOut = 0;
	State = 0;
	Client_ID = 0;
	gNumberOfClients = 0;
	gClientState = 0;
	Packet_In = 0;
	Packet_Out = 0;
	bPacketRecieved = false;
	//-------------------------------------------------------------
}
///*****************************************************************
// NETWORK - CLIENT - CREATE
///*****************************************************************
void Network_Client::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}
///*****************************************************************
// NETWORK - CLIENT - Connect
///*****************************************************************
void Network_Client::Connect(void)
{
	//-------------------------------------------------------------
	//Connect
	if(TimeOut==0)
	{
		if(gManualNetworkGame)//Manual Game Start (use saved manual IP char)
		{
			iNetClientStart(gIpAddress,
							gNetworkPort,
							gNetworkPass,
							gClientPort,
							gPlayerName);
		}
		else//Master server game - use string obtained from FTP
		{
			iNetClientStart((char*)cGame_Ftp.IpAddressRecieved.c_str(),
							gNetworkPort,
							gNetworkPass,
							gClientPort,
							gPlayerName);
		}
	}
	//Check for Connection
	if(iNetClientConnectedToServer())
	{
		State = 2;
	}
	//Check for failure
	TimeOut++;
	if(iNetClientServerIsFull() || 
		(!iNetClientConnectedToServer() && TimeOut >= 240))
	{
		State = -1;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
/// NETWORK - CLIENT - RECIEVE
///*****************************************************************
void Network_Client::Recieve(void)
{
	//-------------------------------------------------------------
	int PacketId = 0;
	//-------------------------------------------------------------
	//Obtain Player ID
	Client_ID = iNetClientMachineId();
	//Check for Connection
	if(iNetClientServerHasClosed())
	{
		State = -1;
	}
	//-------------------------------------------------------------
	//Player Names
	PacketId = 0; 
	for(int i=0;i<gNumberOfClients;i++)
	{
		if(i==Client_ID + 1)//me
		{
			PacketId++;//Skip to next packet.
		}
		iNetClientValueStringReceive(cGame_Bike[i].Name,PacketId,Client_ID);

		PacketId++;
	}
	//-------------------------------------------------------------
	//Packet Data (0-9)
	iNetClientValueIntReceive(gNetworkIntValue[0],0,Client_ID);
	bPacketRecieved = false;
	if(Packet_In!=gNetworkIntValue[0])
	{
		///New packet recieved
		Packet_In = gNetworkIntValue[0];
		bPacketRecieved = true;
	}
	//-------------------------------------------------------------
	//Core Gamestate Data (INT 10-19)
	PacketId = 10;
	iNetClientValueIntReceive(gNetworkTickRateMax,PacketId,Client_ID);PacketId++;
	iNetClientValueIntReceive(gAi_UserChange,PacketId,Client_ID);PacketId++;
	iNetClientValueIntReceive(gAiDifficuty,PacketId,Client_ID);PacketId++;
	iNetClientValueIntReceive(gNumberOfClients,PacketId,Client_ID);PacketId++;
	iNetClientValueIntReceive(gServerState,PacketId,Client_ID);PacketId++;
	iNetClientValueIntReceive(gSpeedClass,PacketId,Client_ID);PacketId++;
	iNetClientValueIntReceive(gGameModeChange,PacketId,Client_ID);PacketId++;
	iNetClientValueIntReceive(gGameStateChange,PacketId,Client_ID);PacketId++;
	iNetClientValueIntReceive(gTrackReverse,PacketId,Client_ID);PacketId++;
	///Update Server State Changes
	ServerStatesApply();
	//-------------------------------------------------------------
	//1500 - Networked player Readystates
	PacketId = 1500; 
	for(int i=0;i<gNumberOfClients;i++)
	{
		if(i==Client_ID + 1)//me
		{
			PacketId++;//Skip to next packet.
		}
		iNetClientValueIntReceive(gNetPlayerReady[i],PacketId,Client_ID);
		PacketId++;
	}
	//-------------------------------------------------------------
	//Speedstate int 20-60
	PacketId = 20;
	for(int i=0;i<gAi_Max_Count;i++)
	{
		if(i==Client_ID + 1)//me
		{
			PacketId++;//Skip to next packet.
		}
		iNetClientValueIntReceive(cGame_Bike[i].InputSpeedState,PacketId,Client_ID);
		PacketId++;
	}
	//-------------------------------------------------------------
	//Primary Weapon Fire 61-101
	PacketId = 61; 
	for(int i=0;i<gAi_Max_Count;i++)
	{
		if(i==Client_ID + 1)//me
		{
			PacketId++;//Skip to next packet.
		}
		iNetClientValueIntReceive(cGame_Bike[i].Weapons.NetFirePrimary,PacketId,Client_ID);
		PacketId++;
	}
	//-------------------------------------------------------------
	//NetEnergyRegen 102-142
	PacketId = 102; 
	for(int i=0;i<gAi_Max_Count;i++)
	{
		if(i==Client_ID + 1)//me
		{
			PacketId++;//Skip to next packet.
		}
		iNetClientValueIntReceive(cGame_Bike[i].Energy.NetEnergyRegen,PacketId,Client_ID);
		PacketId++;
	}
	//-------------------------------------------------------------
	//NetFireSecondary 143-183
	PacketId = 143; 
	for(int i=0;i<gAi_Max_Count;i++)
	{
		if(i==Client_ID + 1)//me
		{
			PacketId++;//Skip to next packet.
		}
		iNetClientValueIntReceive(cGame_Bike[i].Weapons.NetFireSecondary,PacketId,Client_ID);
		PacketId++;
	}
	//-------------------------------------------------------------
	//NetFireUtility 184-224
	PacketId = 184; 
	for(int i=0;i<gAi_Max_Count;i++)
	{
		if(i==Client_ID + 1)//me
		{
			PacketId++;//Skip to next packet.
		}
		iNetClientValueIntReceive(cGame_Bike[i].Weapons.NetFireUtility,PacketId,Client_ID);
		PacketId++;
	}
	//-------------------------------------------------------------
	//NetSecondaryLockedId 225-265
	PacketId = 225; 
	for(int i=0;i<gAi_Max_Count;i++)
	{
		if(i==Client_ID + 1)//me
		{
			PacketId++;//Skip to next packet.
		}
		iNetClientValueIntReceive(cGame_Bike[i].Weapons.NetSecondaryLockedId,PacketId,Client_ID);
		PacketId++;
	}
	//-------------------------------------------------------------
	//NetDrift 266-276 (PLAYERS ONLY)
	PacketId = 266; 
	for(int i=0;i<gNumberOfClients;i++)
	{
		if(i==Client_ID + 1)//me
		{
			PacketId++;//Skip to next packet.
		}
		iNetClientValueIntReceive(cGame_Bike[i].NetDrift,PacketId,Client_ID);
		PacketId++;
	}
	//-------------------------------------------------------------
	//Recieve Tickrate Data packet
	if(bPacketRecieved)
	{
		//19 - Arena Timer
		PacketId = 19;
		iNetClientValueIntReceive(gRaceCountdown,PacketId,Client_ID);
		//User Colours D3DXVECTOR3 61-69
		PacketId = 61;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueVec3Receive(&cGame_Bike[i].Colour.vBikeColourTarget,PacketId,Client_ID);
			PacketId++;
		}

		//Energy 277-317
		PacketId = 277; 
		for(int i=0;i<gAi_Max_Count;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			int iEnergy = 200;
			iNetClientValueIntReceive(iEnergy,PacketId,Client_ID);
			cGame_Bike[i].Energy.fEnergy = (float)iEnergy;
			PacketId++;
		}

		//Kills 318-328
		PacketId = 318; 
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Bike[i].Weapons.TotalKills,PacketId,Client_ID);
			PacketId++;
		}
		//Deaths 329-339
		PacketId = 329; 
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Bike[i].Weapons.TotalDeaths,PacketId,Client_ID);
			PacketId++;
		}

		//Bike Data
		PacketId = 0;
		for(int i=0;i<gAi_Max_Count;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			D3DXVECTOR2 vData = D3DXVECTOR2(0.0f,0.0f);
			iNetClientValueVec2Receive(&vData,PacketId,Client_ID);
			cGame_Bike[i].fSteering = vData.x;
			cGame_Bike[i].Manager.fAcceleration_Speed = vData.y;

			iNetClientValueVec3Receive(&cGame_Bike[i].vNetwork_Recieve,PacketId,Client_ID);
			iNetClientValueQuatReceive(&cGame_Bike[i].qNetwork_Recieve,PacketId,Client_ID);

			PacketId++;

			//Active AI/Player network bikes
			if(i<gNumberOfClients)
			{
				cGame_Bike[i].Networked_Ai_Type = 1;
			}
			else
			{
				cGame_Bike[i].Networked_Ai_Type = -1;
			}
		}
	}
	//-------------------------------------------------------------
	//UPGRADES
	if(gGameState==0)
	{
		//uPrimaryDamage 340-380
		PacketId = 340; 
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uPrimaryDamage[i],PacketId,Client_ID);
			PacketId++;
		}
		//uPrimaryTravel 381-421
		PacketId = 381; 
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uPrimaryTravel[i],PacketId,Client_ID);
			PacketId++;
		}
		//uMissileLockTime 422-462
		PacketId = 422; 
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uMissileLockTime[i],PacketId,Client_ID);
			PacketId++;
		}
		//uMissileDamage 463-503
		PacketId = 463;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uMissileDamage[i],PacketId,Client_ID);
			PacketId++;
		}
		//uMissileRadius 504-544
		PacketId = 504;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uMissileRadius[i],PacketId,Client_ID);
			PacketId++;
		}
		//uMissileTravel 545-585
		PacketId = 545;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uMissileTravel[i],PacketId,Client_ID);
			PacketId++;
		}
		//uShoxwaveDamage 586-626
		PacketId = 586;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uShoxwaveDamage[i],PacketId,Client_ID);
			PacketId++;
		}
		//uShoxwaveTravel 627-667
		PacketId = 627;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uShoxwaveTravel[i],PacketId,Client_ID);
			PacketId++;
		}
		//uShoxwaveReduction 668-708
		PacketId = 668;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uShoxwaveReduction[i],PacketId,Client_ID);
			PacketId++;
		}
		//uEmBurstDamage 709-749
		PacketId = 709;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uEmBurstDamage[i],PacketId,Client_ID);
			PacketId++;
		}
		//uEmBurstRadius 750-790
		PacketId = 750;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uEmBurstRadius[i],PacketId,Client_ID);
			PacketId++;
		}
		//uEmBurstReduction 791-831
		PacketId = 791;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uEmBurstReduction[i],PacketId,Client_ID);
			PacketId++;
		}
		//uRailDamage 832-872
		PacketId = 832;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uRailDamage[i],PacketId,Client_ID);
			PacketId++;
		}
		//uRailTravel 873-913
		PacketId = 873;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uRailTravel[i],PacketId,Client_ID);
			PacketId++;
		}
		//uShieldInvTime 914-954
		PacketId = 914;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uShieldInvTime[i],PacketId,Client_ID);
			PacketId++;
		}
		//uAutoPilotTime 955-995
		PacketId = 955;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uAutoPilotTime[i],PacketId,Client_ID);
			PacketId++;
		}
		//uDoubleDamageTime 996-1036
		PacketId = 996;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uDoubleDamageTime[i],PacketId,Client_ID);
			PacketId++;
		}
		//uDoubleDamageConv 1037-1077
		PacketId = 1037;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uDoubleDamageConv[i],PacketId,Client_ID);
			PacketId++;
		}
		//uEnergyMax 1078-1118
		PacketId = 1078;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uEnergyMax[i],PacketId,Client_ID);
			PacketId++;
		}
		//uEnergyPickup 1119-1159
		PacketId = 1119;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uEnergyPickup[i],PacketId,Client_ID);
			PacketId++;
		}
		//uPlayerLevel 1160-1200
		PacketId = 1160;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uPlayerLevel[i],PacketId,Client_ID);
			PacketId++;
		}
		//uEnergyTickRegen 1201-1241
		PacketId = 1201;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uEnergyTickRegen[i],PacketId,Client_ID);
			PacketId++;
		}
		//uShieldInvConvert 1242-1282
		PacketId = 1242;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uShieldInvConvert[i],PacketId,Client_ID);
			PacketId++;
		}
		//uWarpDamageReduce 1283-1323
		PacketId = 1283;
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i==Client_ID + 1)//me
			{
				PacketId++;//Skip to next packet.
			}
			iNetClientValueIntReceive(cGame_Upgrades.uWarpDamageReduce[i],PacketId,Client_ID);
			PacketId++;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
/// NETWORK - CLIENT - SEND
///*****************************************************************
void Network_Client::Send(void)
{
	//-------------------------------------------------------------
	int PacketId = 0;
	//-------------------------------------------------------------
	//Player Names
	PacketId = 0 + (Client_ID + 1);
	if((string)gPlayerName!=gNetworkStringValue[PacketId])
	{
		gNetworkStringValue[PacketId] = (string)gPlayerName;
		iNetClientValueStringSet(gNetworkStringValue[PacketId],PacketId);
	}


	//Packet Out ID (0-9)
	bool bTickRateSend = false;
	PacketId = Client_ID + 1;
	if(gNetworkTickRate >= gNetworkTickRateMax)
	{
		///Send a 0-1, use on client/server for updates and predictions
		Packet_Out++;
		if(Packet_Out > 1)
		{
			Packet_Out = 0;
		}
		iNetClientValueIntSet(Packet_Out,PacketId);
		bTickRateSend = true;
		gNetworkTickRate = 0;
	}
	//-------------------------------------------------------------
	//1500 - Networked player Readystates
	PacketId = 1500 + (Client_ID + 1);
	if(gNetMeReady!=gNetworkIntValue[PacketId])
	{
		iNetClientValueIntSet(gNetMeReady,PacketId);
		gNetworkIntValue[PacketId] = gNetMeReady;
	}
	//-------------------------------------------------------------
	//Speedstate 20-60
	PacketId = 20 + (Client_ID + 1);
	if(cGame_Bike[gAi_Max_Count].InputSpeedState!=gNetworkIntValue[PacketId])
	{
		iNetClientValueIntSet(cGame_Bike[gAi_Max_Count].InputSpeedState,PacketId);
		gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].InputSpeedState;
	}
	//-------------------------------------------------------------
	//Primary Weapon Fire 61-101
	PacketId = 61 + (Client_ID + 1);
	if(cGame_Bike[gAi_Max_Count].Weapons.NetFirePrimary!=gNetworkIntValue[PacketId])
	{
		iNetClientValueIntSet(cGame_Bike[gAi_Max_Count].Weapons.NetFirePrimary,PacketId);
		gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].Weapons.NetFirePrimary;
	}
	//-------------------------------------------------------------
	//NetEnergyRegen 102-142
	PacketId = 102 + (Client_ID + 1);
	if(cGame_Bike[gAi_Max_Count].Energy.NetEnergyRegen!=gNetworkIntValue[PacketId])
	{
		iNetClientValueIntSet(cGame_Bike[gAi_Max_Count].Energy.NetEnergyRegen,PacketId);
		gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].Energy.NetEnergyRegen;
	}
	//-------------------------------------------------------------
	//NetFireSecondary 143-183
	PacketId = 143 + (Client_ID + 1);
	if(cGame_Bike[gAi_Max_Count].Weapons.NetFireSecondary!=gNetworkIntValue[PacketId])
	{
		iNetClientValueIntSet(cGame_Bike[gAi_Max_Count].Weapons.NetFireSecondary,PacketId);
		gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].Weapons.NetFireSecondary;
	}
	//-------------------------------------------------------------
	//NetFireUtility 184-224
	PacketId = 184 + (Client_ID + 1);
	if(cGame_Bike[gAi_Max_Count].Weapons.NetFireUtility!=gNetworkIntValue[PacketId])
	{
		iNetClientValueIntSet(cGame_Bike[gAi_Max_Count].Weapons.NetFireUtility,PacketId);
		gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].Weapons.NetFireUtility;
	}
	//-------------------------------------------------------------
	//NetSecondaryLockedId 225-265
	PacketId = 225 + (Client_ID + 1);
	if(cGame_Bike[gAi_Max_Count].Weapons.NetSecondaryLockedId!=gNetworkIntValue[PacketId])
	{
		iNetClientValueIntSet(cGame_Bike[gAi_Max_Count].Weapons.NetSecondaryLockedId,PacketId);
		gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].Weapons.NetSecondaryLockedId;
	}
	//-------------------------------------------------------------
	//Drift 266-276 (PLAYERS ONLY)
	PacketId = 266 + (Client_ID + 1);
	if(cGame_Bike[gAi_Max_Count].NetDrift!=gNetworkIntValue[PacketId])
	{
		iNetClientValueIntSet(cGame_Bike[gAi_Max_Count].NetDrift,PacketId);
		gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].NetDrift;
	}
	//-------------------------------------------------------------
	//TickRateSend Data Packet
	if(bTickRateSend)
	{
		//User Colours D3DXVECTOR3 61-69
		PacketId = 61 + (Client_ID + 1);
		if(cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget!=gNetworkVector3Value[PacketId])
		{
			iNetClientValueVec3Set(&cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget,PacketId);
			gNetworkVector3Value[PacketId] = cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget;
		}

		//Energy 277-317
		PacketId = 277 + (Client_ID + 1);
		int iEnergy = (int)cGame_Bike[gAi_Max_Count].Energy.fEnergy;
		if(iEnergy != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(iEnergy,PacketId);
			gNetworkIntValue[PacketId] = iEnergy;
		}

		//Kills 318-328
		PacketId = 318 + (Client_ID + 1);
		if(cGame_Bike[gAi_Max_Count].Weapons.TotalKills != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Bike[gAi_Max_Count].Weapons.TotalKills,PacketId);
			gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].Weapons.TotalKills;
		}
		//Deaths 329-339
		PacketId = 329 + (Client_ID + 1);
		if(cGame_Bike[gAi_Max_Count].Weapons.TotalDeaths != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Bike[gAi_Max_Count].Weapons.TotalDeaths,PacketId);
			gNetworkIntValue[PacketId] = cGame_Bike[gAi_Max_Count].Weapons.TotalDeaths;
		}

		//Bikes
		PacketId = Client_ID + 1;
		iNetClientValueVec2Set(&D3DXVECTOR2(cGame_Bike[gAi_Max_Count].fSteering,
											cGame_Bike[gAi_Max_Count].Manager.fAcceleration_Speed),
											PacketId);
		iNetClientValueVec3Set(&cGame_Bike[gAi_Max_Count].Manager.vBikeOrigin,PacketId);
		iNetClientValueQuatSet(&cGame_Bike[gAi_Max_Count].Manager.qBikeOrigin,PacketId);
	}
	//-------------------------------------------------------------
	//UPGRADES
	if(gGameState==0)
	{
		//uPrimaryDamagePlayer 340-380
		PacketId = 340 + (Client_ID + 1);
		if(cGame_Upgrades.uPrimaryDamagePlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uPrimaryDamagePlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uPrimaryDamagePlayer;
		}
		//uPrimaryTravelPlayer 381-421
		PacketId = 381 + (Client_ID + 1);
		if(cGame_Upgrades.uPrimaryTravelPlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uPrimaryTravelPlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uPrimaryTravelPlayer;
		}
		//uMissileLockTime 422-462
		PacketId = 422 + (Client_ID + 1);
		if(cGame_Upgrades.uMissileLockTimePlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uMissileLockTimePlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uMissileLockTimePlayer;
		}
		//uMissileDamagePlayer 463-503
		PacketId = 463 + (Client_ID + 1);
		if(cGame_Upgrades.uMissileDamagePlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uMissileDamagePlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uMissileDamagePlayer;
		}
		//uMissileRadius 504-544
		PacketId = 504 + (Client_ID + 1);
		if(cGame_Upgrades.uMissileRadiusPlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uMissileRadiusPlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uMissileRadiusPlayer;
		}
		//uMissileTravel 545-585
		PacketId = 545 + (Client_ID + 1);
		if(cGame_Upgrades.uMissileTravelPlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uMissileTravelPlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uMissileTravelPlayer;
		}
		//uShoxwaveDamage 586-626
		PacketId = 586 + (Client_ID + 1);
		if(cGame_Upgrades.uShoxwaveDamagePlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uShoxwaveDamagePlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uShoxwaveDamagePlayer;
		}
		//uShoxwaveTravelPlayer 627-667
		PacketId = 627 + (Client_ID + 1);
		if(cGame_Upgrades.uShoxwaveTravelPlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uShoxwaveTravelPlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uShoxwaveTravelPlayer;
		}
		//uShoxwaveReductionPlayer 668-708
		PacketId = 668 + (Client_ID + 1);
		if(cGame_Upgrades.uShoxwaveReductionPlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uShoxwaveReductionPlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uShoxwaveReductionPlayer;
		}
		//uEmBurstDamagePlayer 709-749
		PacketId = 709 + (Client_ID + 1);
		if(cGame_Upgrades.uEmBurstDamagePlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uEmBurstDamagePlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uEmBurstDamagePlayer;
		}
		//uEmBurstRadiusPlayer 750-790
		PacketId = 750 + (Client_ID + 1);
		if(cGame_Upgrades.uEmBurstRadiusPlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uEmBurstRadiusPlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uEmBurstRadiusPlayer;
		}
		//uEmBurstReductionPlayer 791-831
		PacketId = 791 + (Client_ID + 1);
		if(cGame_Upgrades.uEmBurstReductionPlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uEmBurstReductionPlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uEmBurstReductionPlayer;
		}
		//uRailDamagePlayer 832-872
		PacketId = 832 + (Client_ID + 1);
		if(cGame_Upgrades.uRailDamagePlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uRailDamagePlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uRailDamagePlayer;
		}
		//uRailTravelPlayer 873-913
		PacketId = 873 + (Client_ID + 1);
		if(cGame_Upgrades.uRailTravelPlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uRailTravelPlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uRailTravelPlayer;
		}
		//uShieldInvTimePlayer 914-954
		PacketId = 914 + (Client_ID + 1);
		if(cGame_Upgrades.uShieldInvTimePlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uShieldInvTimePlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uShieldInvTimePlayer;
		}
		//uAutoPilotTimePlayer 955-995
		PacketId = 955 + (Client_ID + 1);
		if(cGame_Upgrades.uAutoPilotTimePlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uAutoPilotTimePlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uAutoPilotTimePlayer;
		}
		//uDoubleDamageTimePlayer 996-1036
		PacketId = 996 + (Client_ID + 1);
		if(cGame_Upgrades.uDoubleDamageTimePlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uDoubleDamageTimePlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uDoubleDamageTimePlayer;
		}
		//uDoubleDamageConvPlayer 1037-1077
		PacketId = 1037 + (Client_ID + 1);
		if(cGame_Upgrades.uDoubleDamageConvPlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uDoubleDamageConvPlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uDoubleDamageConvPlayer;
		}
		//uEnergyMaxPlayer 1078-1118
		PacketId = 1078 + (Client_ID + 1);
		if(cGame_Upgrades.uEnergyMaxPlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uEnergyMaxPlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uEnergyMaxPlayer;
		}
		//uEnergyPickupPlayer 1119-1159
		PacketId = 1119 + (Client_ID + 1);
		if(cGame_Upgrades.uEnergyPickupPlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uEnergyPickupPlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uEnergyPickupPlayer;
		}
		//uPlayerLevelPlayer 1160-1200
		PacketId = 1160 + (Client_ID + 1);
		if(cGame_PlayerStats.Player_Level != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_PlayerStats.Player_Level,PacketId);
			gNetworkIntValue[PacketId] = cGame_PlayerStats.Player_Level;
		}
		//uEnergyTickRegen 1201-1241
		PacketId = 1201 + (Client_ID + 1);
		if(cGame_Upgrades.uEnergyTickRegenPlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uEnergyTickRegenPlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uEnergyTickRegenPlayer;
		}
		//uShieldInvConvert 1242-1282
		PacketId = 1242 + (Client_ID + 1);
		if(cGame_Upgrades.uShieldInvConvertPlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uShieldInvConvertPlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uShieldInvConvertPlayer;
		}
		//uWarpDamageReduce 1283-1323
		PacketId = 1283 + (Client_ID + 1);
		if(cGame_Upgrades.uWarpDamageReducePlayer != gNetworkIntValue[PacketId])
		{
			iNetClientValueIntSet(cGame_Upgrades.uWarpDamageReducePlayer,PacketId);
			gNetworkIntValue[PacketId] = cGame_Upgrades.uWarpDamageReducePlayer;
		}
	}
	//-------------------------------------------------------------
	//Send Packet
	iNetClientValuesToServerSend();
	//-------------------------------------------------------------
}
///*****************************************************************
/// NETWORK - CLIENT - ServerStatesApply
///*****************************************************************
void Network_Client::ServerStatesApply(void)
{
	//-------------------------------------------------------------
	//Applys gServerState to Client, from Server (eg: tells us what the server is doing, and, how to apply it)
	// -1 = Destroy/load
	//  0 = NULL
	//  1 = Intro Started
	// 
	//-------------------------------------------------------------
	//Check clientstate with serverstate
	if(gClientState != gServerState)
	{
		//-------------------------------------------------------------
		//Host has Started to Destroy Game
		if(gServerState==-1)
		{
			if(gGameState==0)///Menu - lobby
			{
				gMenu_Active = false;
			}
			else
			{
				cGame_Gamma_Fade.bFadeOut = true;
			}
		}
		//-------------------------------------------------------------
		//Host has Started Race Countdown
		if(gServerState==1)
		{
			cGame_Mode_Controller.Intro.bBeginTimer = true;
		}
		//-------------------------------------------------------------
		//Match client flag to server
		gClientState = gServerState;
		//-------------------------------------------------------------
	}
	//-------------------------------------------------------------
}
///*****************************************************************
// NETWORK - CLIENT - DESTROY
///*****************************************************************
void Network_Client::Destroy(void)
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