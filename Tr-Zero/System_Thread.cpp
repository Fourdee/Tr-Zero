//-----------------------------------------------------------------
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "System_Thread.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - THREAD - CONSTRUCTORS
///*****************************************************************
System_Thread::System_Thread(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<MAX_THREADS;i++)
	{
		bActive[i] = false;
		Thread_Handle[i] = NULL;
		Thread_Id[i] = i+1;
	}
	//-------------------------------------------------------------
}

System_Thread::~System_Thread(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
//*****************************************************************
//START
//*****************************************************************
void System_Thread::Start(int Id)
{
	//-------------------------------------------------------------
	if(!bActive[Id])
	{
		//Mesh/Audio systems
		if(Id==0)
		{
			Thread_Handle[Id] = (HANDLE)_beginthreadex(NULL,0,&Thread_0,NULL,0,&Thread_Id[Id]);
			SetPriorityClass(Thread_Handle[Id], ABOVE_NORMAL_PRIORITY_CLASS);
		}
		//Replay File Stream
		else if(Id==1)
		{
			Thread_Handle[Id] = (HANDLE)_beginthreadex(NULL,0,&Thread_1,NULL,0,&Thread_Id[Id]);
			SetPriorityClass(Thread_Handle[Id],NORMAL_PRIORITY_CLASS);
		}
		//Raknet Networking
		else if(Id==2)
		{
			Thread_Handle[Id] = (HANDLE)_beginthreadex(NULL,0,&Thread_2,NULL,0,&Thread_Id[Id]);
			SetPriorityClass(Thread_Handle[Id],NORMAL_PRIORITY_CLASS);
		}
		bActive[Id] = true;
	}
	//-------------------------------------------------------------
}
//*****************************************************************
//STOP
//*****************************************************************
void System_Thread::Stop(int Id)
{
	//-------------------------------------------------------------
	if(bActive[Id])
	{
		WaitForSingleObject(Thread_Handle[Id],3000);
		//WaitForSingleObject(Thread_Handle[Id],INFINITE);
		CloseHandle(Thread_Handle[Id]);
		bActive[Id] = false;
	}
	//-------------------------------------------------------------
}
//*****************************************************************
///Thread 0 - Mesh/Audio systems
//*****************************************************************
unsigned __stdcall Thread_0(void* x)
{
	//-------------------------------------------------------------
	while(cThread.bActive[0])
	{
		cGame_Mesh.Update();
		cGame_Track.Update();
		cGame_Audio.Update();
		cGame_Mesh.Culling.Update();
		cGame_Particle.Update();
		cGame_PostProcessing.Update();
		cGame_Controls.Update_Feedback();
		cThread.bActive[0] = false;
	}
	return 0;
	//-------------------------------------------------------------
}
//*****************************************************************
///Thread 1 - Replay Filestream
//*****************************************************************
unsigned __stdcall Thread_1(void* x)
{
	//-------------------------------------------------------------
	while(cThread.bActive[1])
	{
		if(cGame_Replay.State==1)
		{
			cGame_Replay.Record();
		}
		else if(cGame_Replay.State==2)
		{
			cGame_Replay.Playback();
		}
		cThread.bActive[1] = false;
	}
	return 0;
	//-------------------------------------------------------------
}
//*****************************************************************
///Thread 2 - Network
//*****************************************************************
unsigned __stdcall Thread_2(void* x)
{
	//-------------------------------------------------------------
	while(cThread.bActive[2])
	{
		if(cGame_Network.bThread_Send)
		{
			cGame_Network.Update_Send();
			cGame_Network.bThread_Send = false;
		}
		else
		{
			cGame_Network.Update_Recieve();
		}
		iOddityEngine2_Raknet_Update();
		cThread.bActive[2] = false;
	}
	return 0;
	//-------------------------------------------------------------
}