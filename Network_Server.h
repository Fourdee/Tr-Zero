#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Network_Server
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Connection Data
		int								State;
		bool							bPacketRecieved[8];
		int								Packet_In[8];
		//---------------------------------------------------------
		//constructors
		Network_Server(void);
		~Network_Server(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Destroy(void);

		void StartServer(void);
		void Recieve(void);
		void Send(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		//functions
		void ZeroData(void);
		//---------------------------------------------------------
		int								Packet_Out;
		//---------------------------------------------------------
	//-------------------------------------------------------------
};
