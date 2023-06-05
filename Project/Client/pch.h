#pragma once


#include "framework.h"

#include <Engine\global.h>
#include <Engine\CEngine.h>


// Engine Library
#ifdef _DEBUG
#pragma comment(lib, "Engine//Engine_d")
#else
#pragma comment(lib, "Engine//Engine")
#endif


// Script Library
#ifdef _DEBUG
#pragma comment(lib, "Script//Script_d")
#else
#pragma comment(lib, "Script//Script")
#endif

// PhysX Library
#pragma comment(lib, "PhysX//PhysX_64")
#pragma comment(lib, "PhysX//PhysXCommon_64")
#pragma comment(lib, "PhysX//PhysXFoundation_64")

#pragma comment(lib, "PhysX//LowLevel_static_64")
#pragma comment(lib, "PhysX//LowLevelAABB_static_64")
#pragma comment(lib, "PhysX//LowLevelDynamics_static_64")
#pragma comment(lib, "PhysX//PhysXCharacterKinematic_static_64")
#pragma comment(lib, "PhysX//PhysXCooking_64")
#pragma comment(lib, "PhysX//PhysXExtensions_static_64")
#pragma comment(lib, "PhysX//PhysXPvdSDK_static_64")
#pragma comment(lib, "PhysX//PhysXTask_static_64")
#pragma comment(lib, "PhysX//PhysXVehicle_static_64")
#pragma comment(lib, "PhysX//SceneQuery_static_64")
