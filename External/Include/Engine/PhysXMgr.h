#pragma once
#include "CSingleton.h"
#include <PhysX/PxPhysics.h>
#include <PhysX/PxPhysicsAPI.h>
#include "CGameObject.h"

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


	using namespace physx;
class PhysXMgr :
    public CSingleton<PhysXMgr>
{
    SINGLE(PhysXMgr);

private:
    vector<CGameObject*>        m_vecDynamicObject;
    vector<PxRigidDynamic*>     m_vecDynamicActor;

    PxRigidDynamic*             m_Player;
    

public:
    void init();
    void progress();

public:
    // 동적 물체 생성 함수.
    // t : 위치, geometry : 형태, velocity : 속도
    // 생성된 물체를 반환함.
    PxRigidDynamic* CreateDynamic(const PxTransform& t, const PxGeometry& geometry, CGameObject* _Object, const PxVec3& velocity = PxVec3(0));
	
    // 평면 생성 함수
    PxRigidStatic* CreatePlane(Vec4 _Plane);

public:
    PxRigidDynamic* GetPlayer()
    {
        return m_Player;
    }
    

};

