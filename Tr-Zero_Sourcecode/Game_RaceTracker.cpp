//-----------------------------------------------------------------
// About:
//
// name: "Game_RaceTracker.cpp:
//
// Tracks all bike positions
// Tracks all bike laps
// Tracks all bike laptimes
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_RaceTracker.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - RACETRACKER - CONSTRUCTORS
///*****************************************************************
Game_RaceTracker::Game_RaceTracker(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_RaceTracker::~Game_RaceTracker(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - RACETRACKER - ZeroData
///*****************************************************************
void Game_RaceTracker::ZeroData(void)
{
	//-------------------------------------------------------------
	//System
	///Update Tick Rate - Waypoints
	TickRate							= 0;
	ACTIVE_WAYPOINTS					= 0;//Applied per track basis
	//-------------------------------------------------------------
	//Total AliveBikes
	Total_AliveBikes					= gAi_Max_Count + 1;
	//Total Bikes Racing
	for(int i=0;i<40;i++)
	{
		bBikeRacing[i]					= true;
	}
	//Lap Systems
	for(int i=0;i<40;i++)
	{
		//Lap Counter
		Lap_Current[i]					= 0;
		bLap_Trigger[i]					= false;
		Lap_HighestReached[i]			= 1;
		//Lap times
		///Current
		Time_CurrentLap[i]				= 0.0f;
		///Previous
		Time_PrevLap[i]					= 0.0f;
		///Fastest
		Time_FastLap[i]					= 817.0f;
		///New Record?
		bTime_FastLap_New[i]			= false;
		bTime_FastLap_ThisRace[i]		= false;
		///Fastest - Grab from saved file
		if(i==gAi_Max_Count &&///Only load players fastest lap record
			gGameState<MAX_RECORDS_CHAPTERS)///skip arena etc
		{
			Time_FastLap[i]	= cGame_PlayerStats.LapRecord[gGameState][gSpeedClass][gTrackReverse];
		}
	}
	//-------------------------------------------------------------
	//Waypoints
	///Mater Waypoints
	for(int i=0;i<MAX_WAYPOINTS;i++)
	{
		vWaypoint_Master[i]					= D3DXVECTOR3(0.0f,0.0f,0.0f);
		fWaypointRadius_Master[i]			= 100.0f; ///default
		///Sorting
		WaypointSort_ArraySize[i] = 0;
		for(int j=0;j<40;j++)
		{
			fWaypointSort[i][j]				= -1.0f;
			WaypointSortedClosest[i][j]		= -1;
		}
	}
	///Bikes - relative to waypoint
	for(int i=0;i<40;i++)
	{
		Waypoint_Current[i]				= 0;
		fWaypoint_Current_Distance[i]	= 1000.0f;
	}
	//-------------------------------------------------------------
	//Positions
	for(int i=0;i<40;i++)
	{
		Position_Current[i] = i + 1;
		Position_OrderedId[i] = i + 1;
	}
	//-------------------------------------------------------------
	//Kill Death Sorting
	for(int i=0;i<40;i++)
	{
		KillsSorted[i]		= 0;
		DeathsSorted[i]		= 0;
	}
	//-------------------------------------------------------------
	//Track - Master Waypoints
	///Reverse the points?
	int WpIndex = 0;
	int WpIndex_Step = 1;
	///Volex
	if(gGameState==1)
	{
		ACTIVE_WAYPOINTS = 19;
		if(gTrackReverse)
		{
			WpIndex = ACTIVE_WAYPOINTS - 2;///last ID is always 1st ID
			WpIndex_Step = -1;
		}
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,10.0f,280.0f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-112.4f,128.5f,418.6f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-236.4f,-22.3f,150.1f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-239.1f,-868.3f,33.4f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-239.0f,120.5f,-222.0f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-428.8f,120.5f,-469.7f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-676.1f,120.5f,-147.6f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-991.0f,174.4f,58.5f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-649.1f,99.6f,301.9f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-556.0f,-52.3f,38.8f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-724.2f,-91.4f,156.5f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-518.8f,-169.8f,156.5f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-337.9f,-355.6f,-882.1f);
		fWaypointRadius_Master[WpIndex] = 150.0f;WpIndex+=WpIndex_Step;

		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-341.5f,-356.7f,-386.9f);
		fWaypointRadius_Master[WpIndex] = 125.0f;WpIndex+=WpIndex_Step;

		vWaypoint_Master[WpIndex] = D3DXVECTOR3(309.5f,-295.0f,-256.6f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(336.8f,224.1f,-291.4f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(230.0f,215.0f,-483.7f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,6.5f,-401.3f);WpIndex+=WpIndex_Step;
		///LAST WP MUST BE SAME AS WP0
		vWaypoint_Master[ACTIVE_WAYPOINTS - 1] = vWaypoint_Master[0];
	}
	///Silence
	else if(gGameState==2)
	{
		ACTIVE_WAYPOINTS = 17;
		if(gTrackReverse)
		{
			WpIndex = ACTIVE_WAYPOINTS - 2;///last ID is always 1st ID
			WpIndex_Step = -1;
		}
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,2.5f,149.3f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,2.5f,801.3f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,26.0f,1181.2f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,148.7f,1308.9f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,428.1f,1239.2f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,550.8f,1555.5f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,271.2f,1791.2f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,-47.7f,1702.6f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,-197.3f,1322.8f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,-207.6f,114.8f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,-421.9f,-203.4f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,-533.2f,-423.9f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,-397.4f,-642.9f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,-211.8f,-664.1f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,-50.0f,-521.4f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,2.4f,-281.2f);WpIndex+=WpIndex_Step;
		///LAST WP MUST BE SAME AS WP0
		vWaypoint_Master[ACTIVE_WAYPOINTS - 1] = vWaypoint_Master[0];
	}
	///PHantom
	else if(gGameState==3)
	{
		ACTIVE_WAYPOINTS = 18;
		if(gTrackReverse)
		{
			WpIndex = ACTIVE_WAYPOINTS - 2;///last ID is always 1st ID
			WpIndex_Step = -1;
		}
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(0.0f,1.3f,283.0f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(31.2f,-7.0f,691.7f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(336.5f,-71.6f,799.4f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(336.0f,-159.2f,461.1f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-232.1f,-165.2f,151.8f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-522.5f,-204.5f,333.2f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-238.5f,-90.1f,828.3f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-239.4f,53.2f,1165.5f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-239.4f,408.0f,477.8f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(104.6f,973.4f,393.5f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(241.1f,216.4f,463.6f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(243.9f,-206.8f,-245.1f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(538.9f,-70.6f,-958.8f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-49.7f,-171.4f,-707.5f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-235.2f,-154.2f,-892.7f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(-60.9f,-104.0f,-1058.8f);WpIndex+=WpIndex_Step;
		vWaypoint_Master[WpIndex] = D3DXVECTOR3(140.3f,-47.9f,-606.6f);WpIndex+=WpIndex_Step;
		///LAST WP MUST BE SAME AS WP0
		vWaypoint_Master[ACTIVE_WAYPOINTS - 1] = vWaypoint_Master[0];
	}
	//-------------------------------------------------------------
	//WrongWay + Respawn System
	for(int i=0;i<40;i++)
	{
		///Bike Location Storage
		vSpawn[i]						= cGame_Spawn.vSpawnLocation[i];
		qSpawn[i]						= cGame_Spawn.qSpawnLocation;
		///Direction check
		bWrongWay[i]					= false;
		fWrongWay_Threshold[i]			= iVectorLength(&(cGame_Spawn.vSpawnLocation[i]-vWaypoint_Master[0])) + 100.0f;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - RACETRACKER - Create
///*****************************************************************
void Game_RaceTracker::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - RACETRACKER - UPDATE
///*****************************************************************
void Game_RaceTracker::Update(void)
{
	//-------------------------------------------------------------
	if(cGame_Replay.State!=2 &&		///Not playing Replay
		gGameState>0)				///Not the menu level
	{
		//System Tickrate
		TickRate++;
		if(TickRate==10)
		{
			TickRate = 0; ///Apply any updates
		}
		//-------------------------------------------------------------
		//Define when each bike has finished Racing (eg: stop everything when their not)
		///TimerBased
		if(gRaceCountdown==0)
		{
			for(int i=0;i<=gAi_Max_Count;i++)
			{
				bBikeRacing[i] = false;
			}
		}
		///Ahnilation Based
		else if(gGameMode==4)
		{
			for(int i=0;i<=gAi_Max_Count;i++)
			{
				if(KillsSorted[i]>=cGame_Mode_Controller.Annihilation.KillsRequired)
				{
					bBikeRacing[i] = false;
				}
			}
		}
		///Laps based
		else
		{
			for(int i=0;i<=gAi_Max_Count;i++)
			{
				if(Lap_Current[i]>gLapMax)
				{
					bBikeRacing[i] = false;
				}
			}
		}
		///Death Based (Elimination)
		if(!gRespawnEnable)
		{
			for(int i=0;i<=gAi_Max_Count;i++)
			{
				if(!cGame_Bike[i].Energy.bAlive)
				{
					bBikeRacing[i] = false;
				}
			}
		}
		//-------------------------------------------------------------
		//All modes requiring Lap/Wp updates
		if(gLapsUpdate)
		{
			///Lap Times - Update everyones current seconds
			if(gBikesGo)
			{
				for(int i=0;i<=gAi_Max_Count;i++)
				{
					Time_CurrentLap[i] += gET_DeltaTime;
				}
			}
			///Lap Counters
			for(int i=0;i<=gAi_Max_Count;i++)
			{
				Update_LapCounter(i,&cGame_Bike[i].Manager.vBikeOutput,&cGame_Bike[i].Manager.qBikeOutput);
			}
			///Waypoints
			for(int i=0;i<=gAi_Max_Count;i++)
			{
				if(cGame_Bike[i].Energy.bAlive)
				{
					Update_Waypoints(i,&cGame_Bike[i].Manager.vTargetMesh);
				}
			}
		}
		//-------------------------------------------------------------
		//Update Positions based on Type (eg: kills or waypoint based)
		if(TickRate==0)
		{
			if(gKillBasedPositions)
			{
				///Positions relative to kills/deaths
				Update_Positions_KillBased();
			}
			else
			{
				///Positions relative to Waypoint/Lap
				Update_Positions_LapWpBased();
			}
			///Obtain total alive players in the game
			if(gGameMode==3)
			{
				Update_TotalAliveBikes();
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - RACETRACKER - Update_TotalAliveBikes
///*****************************************************************
void Game_RaceTracker::Update_TotalAliveBikes(void)
{
	//-------------------------------------------------------------
	//Reset
	Total_AliveBikes = 0;
	//-------------------------------------------------------------
	//Update Totals
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		if(cGame_Bike[i].Energy.bAlive)
		{
			Total_AliveBikes++;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - RACETRACKER - Update_LapCounter
///*****************************************************************
void Game_RaceTracker::Update_LapCounter(const int Index,D3DXVECTOR3* BikeLocation, D3DXQUATERNION* BikeOrientation)
{
	//-------------------------------------------------------------
	bTime_FastLap_New[Index] = false;
	//-------------------------------------------------------------
	//lap counter
	if ((BikeLocation->x >= -60.0f && BikeLocation->x <= 60.0f) &&
		(BikeLocation->y >= -15.0f && BikeLocation->y <= 15.0f) &&
		(BikeLocation->z >= -5.0f && BikeLocation->z <= 5.0f))//3.0f
	{
		//in the zone
		if(bLap_Trigger[Index])
		{
			D3DXVECTOR3 LapDirectionCheck = D3DXVECTOR3(0.0f,0.0f,0.0f);
			iQuaternionToEulerAngles(BikeOrientation,&LapDirectionCheck);

			//Check Direction
			if(LapDirectionCheck.y > -90.0f && 
					LapDirectionCheck.y < 90.0f)
			{
				//Facing Wrong Way
				if(gTrackReverse==1)
				{
					Lap_Current[Index]--;
				}
				//Facing Correct Way
				else
				{
					Lap_Current[Index]++;
				}
			}
			else
			{
				//Facing Correct Way
				if(gTrackReverse==1)
				{
					Lap_Current[Index]++;
				}
				//Facing Wrong Way
				else
				{
					Lap_Current[Index]--;
				}
			}
			///Reset
			bLap_Trigger[Index] = false;
			///-------------------------------------------------------------
			//Cap laps to 0-MAX
			iIntCap(Lap_Current[Index],0,gLapMax + 1);
			//Reset WP index
			Waypoint_Current[Index] = 0;
			//Apply new lap
			///Checks the players highest obtained lap number against current
			///If its below the current lap, apply new lap data.
			if(Lap_HighestReached[Index] < Lap_Current[Index])
			{
				///Record lap times
				if(bBikeRacing[Index])
				{
					Update_LapTimes(Index);
				}
				///Match highestreached to lap current
				Lap_HighestReached[Index] = Lap_Current[Index];
			}
		}
	}
	else
	{
		//reset trigger state again
		bLap_Trigger[Index] = true;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - RACETRACKER - Update_LapTimes
///*****************************************************************
void Game_RaceTracker::Update_LapTimes(const int Index)
{
	//-------------------------------------------------------------
	if(Lap_Current[Index]>=2)
	{
		//New lap, check/update values
		///Delta Time

		///Previous
		Time_PrevLap[Index] = Time_CurrentLap[Index];
		///Fastest
		if(Time_CurrentLap[Index] <= Time_FastLap[Index])///New fastest lap
		{
			Time_FastLap[Index] = Time_CurrentLap[Index];
			bTime_FastLap_New[Index] = true;
			bTime_FastLap_ThisRace[Index] = true;///Doesnt get reset until reload
			//-------------------------------------------------------------
			//Update Lap Record for player
			if(Index==gAi_Max_Count)
			{
				/// Player new lap record
				cGame_PlayerStats.LapRecord[gGameState][gSpeedClass][gTrackReverse] = Time_FastLap[gAi_Max_Count];
			}
		}
		///Reset Current
		Time_CurrentLap[Index] = 0.0f;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - RACETRACKER - Update_Waypoints
///*****************************************************************
void Game_RaceTracker::Update_Waypoints(const int Index,D3DXVECTOR3* BikeLocation)
{
	//-------------------------------------------------------------
	//Inside raidus of waypoint, move to next
	if(fWaypoint_Current_Distance[Index] <= fWaypointRadius_Master[Waypoint_Current[Index]])
	{
		Waypoint_Current[Index]++;
		fWaypoint_Current_Distance[Index] = iVectorLength(&(*BikeLocation-vWaypoint_Master[Waypoint_Current[Index]]));

		///WrongWay System - Obtain new data for respawning
		fWrongWay_Threshold[Index] = fWaypoint_Current_Distance[Index] + 175.0f;
		vSpawn[Index] = cGame_Bike[Index].Manager.vBikeOrigin;
		qSpawn[Index] = cGame_Bike[Index].Manager.qBikeOrigin;
	}
	else
	{
		//Distance to current waypoint
		fWaypoint_Current_Distance[Index] = iVectorLength(&(*BikeLocation-vWaypoint_Master[Waypoint_Current[Index]]));
	}
	//-------------------------------------------------------------
	//Wrong Direction Check (Distrance Threshold Method)
	bWrongWay[Index] = false;
	if(fWaypoint_Current_Distance[Index]>fWrongWay_Threshold[Index])
	{
		bWrongWay[Index] = true;
		///Reset bikes
		if(cGame_Network.Client.State==0)///Dont apply on clients
		{
			cGame_Bike[Index].Energy.fEnergy = -1.0f;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - RACETRACKER - Update_Positions_LapWpBased
///*****************************************************************
void Game_RaceTracker::Update_Positions_LapWpBased(void)
{
	//-------------------------------------------------------------
	//Get range and waypoint data for all bikes
	for(int i=0;i<ACTIVE_WAYPOINTS;i++)
	{
		///Reset all Data
		WaypointSort_ArraySize[i] = 0;
		for(int j=0;j<=gAi_Max_Count;j++)
		{
			fWaypointSort[i][j] = -1.0f;
			WaypointSortedClosest[i][j] = -1;
			///Match bike current waypoints to sorting arrays
			if(Waypoint_Current[j]==i &&
				bBikeRacing[j])///exclude finished bikes
			{
				///Add range to bottom of array, count how many are used for sorting.
				fWaypointSort[i][WaypointSort_ArraySize[i]] = fWaypoint_Current_Distance[j];
				WaypointSort_ArraySize[i]++;
			}
		}
	}
	//Sort Waypoint range arrays
	for(int i=0;i<ACTIVE_WAYPOINTS;i++)
	{
		///Sort data, against total bikes stored in each waypoint array
		///Optimised, and you know it!
		if(WaypointSort_ArraySize[i]>1)///No need to sort one value...
		{
			iFloatQsort(fWaypointSort[i],WaypointSort_ArraySize[i]);
		}
	}
	//Match up sorted waypoint ranges to bike ID's
	for(int i=0;i<ACTIVE_WAYPOINTS;i++)
	{
		for(int j=0;j<=gAi_Max_Count;j++)
		{
			///Match current waypoint to Bike waypoints
			if(i==Waypoint_Current[j])
			{
				///For total bikes in their sorted array, match them up to find the closest ID's
				///Optimised, and you know it!
				for(int k=0;k<WaypointSort_ArraySize[i];k++)
				{
					if(fWaypointSort[i][k]==fWaypoint_Current_Distance[j])
					{
						WaypointSortedClosest[i][k] = j;
						break;
					}
				}
			}
		}
	}
	//-------------------------------------------------------------
	//Positions
	///reset active
	int Total_Finished_Bikes = 1;
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		if(!bBikeRacing[i])
		{
			///Obtain a total of bikes finished, for later position calculations
			Total_Finished_Bikes++;
		}
	}

	if(gGameMode==3)///Elmination doesnt require this method - Cancel above
	{
		Total_Finished_Bikes = 1;
	}

	//Hand out using waypoint data against current laps
	int Position = Total_Finished_Bikes;
	int LapId = 0;
	int WaypointId = 0;
	int BikesActiveOnThisLap = 0;
	for(int i=0;i<=gLapMax;i++)
	{
		///Sort from MaxLaps to 0
		LapId = gLapMax - i;
		BikesActiveOnThisLap = 0;
		for(int j=0;j<=gAi_Max_Count;j++)
		{
			if(Lap_Current[j]==LapId)
			{
				BikesActiveOnThisLap++;
			}
		}

		if(BikesActiveOnThisLap>0)
		{
			for(int j=0;j<ACTIVE_WAYPOINTS;j++)
			{
				///Now Sort from 18 to 0
				WaypointId = (ACTIVE_WAYPOINTS - 1) - j;
				
				if(WaypointSort_ArraySize[WaypointId]>0)
				{
					for(int k=0;k<WaypointSort_ArraySize[WaypointId];k++)
					{
						if(Lap_Current[WaypointSortedClosest[WaypointId][k]]==LapId)
						{
							Position_Current[WaypointSortedClosest[WaypointId][k]] = Position;
							Position_OrderedId[Position-1] = WaypointSortedClosest[WaypointId][k];
							Position++;
						}
					}
				}
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - RACETRACKER - Update_Positions_KillBased
///*****************************************************************
void Game_RaceTracker::Update_Positions_KillBased(void)
{
	//-------------------------------------------------------------
	//Get Data / Reset!
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		KillsSorted[i] = cGame_Bike[i].Weapons.TotalKills;
		DeathsSorted[i] = cGame_Bike[i].Weapons.TotalDeaths;
		///reset positions
		Position_Current[i] = -1;
	}
	//-------------------------------------------------------------
	//find Highest Kills / Lowest Deaths
	int HighestKillsIndex = iIntHighestValueInArrayIndex(KillsSorted,gAi_Max_Count+1);
	int HighestKills = KillsSorted[HighestKillsIndex];

	int LowestKillsIndex = iIntLowestValueInArrayIndex(KillsSorted,gAi_Max_Count+1);
	int LowestKills = KillsSorted[LowestKillsIndex];

	int HighestDeathsIndex = iIntHighestValueInArrayIndex(DeathsSorted,gAi_Max_Count+1);
	int HighestDeaths = DeathsSorted[HighestDeathsIndex];

	int LowestDeathsIndex = iIntLowestValueInArrayIndex(DeathsSorted,gAi_Max_Count+1);
	int LowestDeaths = DeathsSorted[LowestDeathsIndex];

	int Position = 1;
	//-------------------------------------------------------------
	//Sort the data - Apply positions
	for(int i=HighestKills;i>=LowestKills;i--)
	{
		for(int j=0;j<=gAi_Max_Count;j++)
		{
			///obtain highest score in the set
			if(KillsSorted[j]==i &&
				DeathsSorted[j]==LowestDeaths)
			{
				Position_Current[j] = Position;
				Position_OrderedId[Position-1] = j;
				Position++;
			}
			///Anyone with same kills?
			else if(KillsSorted[j]==i)
			{
				///Who has the least deaths?
				for(int k=LowestDeaths;k<=HighestDeaths;k++)
				{
					if(DeathsSorted[j]==k)
					{
						Position_Current[j] = Position;
						Position_OrderedId[Position-1] = j;
						Position++;
						break;
					}
				}
			}
		}
	}
	//-------------------------------------------------------------
}