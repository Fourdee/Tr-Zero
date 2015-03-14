#pragma once
//-----------------------------------------------------------------
#define MAX_THREADS 3
unsigned __stdcall Thread_0(void* x);
unsigned __stdcall Thread_1(void* x);
unsigned __stdcall Thread_2(void* x);
//-----------------------------------------------------------------
class System_Thread
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		bool						bActive[MAX_THREADS];
		HANDLE						Thread_Handle[MAX_THREADS];
		unsigned					Thread_Id[MAX_THREADS];
		//---------------------------------------------------------
		//constructors
		System_Thread(void);
		~System_Thread(void);
		//---------------------------------------------------------
		//functions
		void Start(int Id);
		void Stop(int Id);
	//-------------------------------------------------------------
};
