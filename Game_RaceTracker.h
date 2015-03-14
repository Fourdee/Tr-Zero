#pragma once
//-----------------------------------------------------------------
#define MAX_WAYPOINTS 19
//-----------------------------------------------------------------
class Game_RaceTracker
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//System
		int									ACTIVE_WAYPOINTS;
		//Total AliveBikes
		int									Total_AliveBikes;
		//Total Bikes Racing
		bool								bBikeRacing[40];
		//Lap Counter
		int									Lap_Current[40];
		//Lap times
		///Current
		float								Time_CurrentLap[40];
		///Previous
		float								Time_PrevLap[40];
		///Fastest
		float								Time_FastLap[40];
		///New Record?
		bool								bTime_FastLap_New[40];
		bool								bTime_FastLap_ThisRace[40];
		//Waypoints
		///Mater Waypoints
		D3DXVECTOR3							vWaypoint_Master[MAX_WAYPOINTS];
		float								fWaypointRadius_Master[MAX_WAYPOINTS];
		///Sorting
		int									WaypointSortedClosest[MAX_WAYPOINTS][40];
		///Bikes - relative to waypoint
		int									Waypoint_Current[40];
		float								fWaypoint_Current_Distance[40];
		//Positions
		int									Position_Current[40];
		int									Position_OrderedId[40];
		//WrongWay + Respawn System
		///Direction check
		bool								bWrongWay[40];
		float								fWrongWay_Threshold[40];
		///Bike Location Storage
		D3DXVECTOR3							vSpawn[40];
		D3DXQUATERNION						qSpawn[40];
		//---------------------------------------------------------
		//constructors
		Game_RaceTracker(void);
		~Game_RaceTracker(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
	//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		//System
		///Update Tick Rate - Waypoints
		int									TickRate;
		//Total AliveBikes
		//Lap Counter
		bool								bLap_Trigger[40];
		int									Lap_HighestReached[40];///Used to prevent laptime updates going back and forth on the start/finish line
		//Lap Times

		//Waypoints
		///Sorting
		float								fWaypointSort[MAX_WAYPOINTS][40];
		int									WaypointSort_ArraySize[MAX_WAYPOINTS];
		//Kill Death Sorting
		int									KillsSorted[40];
		int									DeathsSorted[40];
		//---------------------------------------------------------
		//functions
		void ZeroData(void);
		///Total AliveBikes
		void Update_TotalAliveBikes(void);
		///Lap System
		void Update_LapCounter(const int Index,D3DXVECTOR3* BikeLocation,D3DXQUATERNION* BikeOrientation);
		void Update_LapTimes(const int Index);
		///Waypoints
		void Update_Waypoints(const int Index,D3DXVECTOR3* BikeLocation);
		///Positions
		void Update_Positions_LapWpBased(void);
		void Update_Positions_KillBased(void);
	//-------------------------------------------------------------
};
