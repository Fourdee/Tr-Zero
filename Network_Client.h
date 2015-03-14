#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Network_Client
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Connection Data
		int								State;
		int								TimeOut;
		int								Client_ID;
		bool							bPacketRecieved;
		int								Packet_In;
		//---------------------------------------------------------
		//constructors
		Network_Client(void);
		~Network_Client(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Destroy(void);
		void ZeroData(void);

		void Connect(void);
		void Recieve(void);
		void Send(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		void ServerStatesApply(void);
		//---------------------------------------------------------
		int								Packet_Out;
		//---------------------------------------------------------
	//-------------------------------------------------------------
};
