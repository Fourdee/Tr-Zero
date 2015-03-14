#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Optimiser
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Data
		bool							bStart;
		bool							bBypass;
		//Data
		bool							bOptimiseFailed;
		int								OptimiserResultScore;
		bool							bOptimiseBypass;
		//---------------------------------------------------------
		//constructors
		Game_Optimiser(void);
		~Game_Optimiser(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		//Data
		int								Timer_AutoOptimise;
		int								MissedFrames;
		int								PreAutoDelay;
		//---------------------------------------------------------
		//functions
		void ZeroData(void);
		void AutoOptimise(void);
		void StartOptimise(void);
		void StopOptimise(void);
		void ForceBypass(void);
	//-------------------------------------------------------------
};