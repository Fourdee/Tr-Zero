// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <shellapi.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <tchar.h>
#define _USE_MATH_DEFINES
#include <time.h>
#include <math.h>
#include <string>
#include <fstream>
#include <process.h>

using namespace std;
//----------------------------------------------------------------------------------------
//oddity engine 2
#include "dllOddityEngine2.h"
//Raknet
#include "OddityEngine2_RakNet.h"
//----------------------------------------------------------------------------------------
//global data
#include "Global_Params.h"
//----------------------------------------------------------------------------------------
//memory leak detection...(comment out in final release)
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//----------------------------------------------------------------------------------------
//safe delete of pointer / array
#define SAFE_RELEASE(p)		 {if(p) {(p)->Release(); (p)=NULL;}}
#define SAFE_DELETE(p)		 {if(p) {delete(p); (p)=NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[](p);(p)=NULL;}}
//----------------------------------------------------------------------------------------