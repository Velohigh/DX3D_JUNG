#pragma once
#include <Engine\CSingleton.h>
#include <PhysX/PxPhysics.h>
#include <PhysX/PxPhysicsAPI.h>

	using namespace physx;
class PhysXMgr :
    public CSingleton<PhysXMgr>
{
    SINGLE(PhysXMgr);

public:


public:
    void init();
    void progress();

public:
    // 동적 물체 생성 함수.
    // t : 위치, geometry : 형태, velocity : 속도
    // 생성된 물체를 반환함.
    PxRigidDynamic* CreateDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity = PxVec3(0));
	
    // 평면 생성 함수
    PxRigidStatic* CreatePlane(Vec4 _Plane);
    

};

