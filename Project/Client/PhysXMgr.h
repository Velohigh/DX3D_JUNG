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
    // ���� ��ü ���� �Լ�.
    // t : ��ġ, geometry : ����, velocity : �ӵ�
    // ������ ��ü�� ��ȯ��.
    PxRigidDynamic* CreateDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity = PxVec3(0));
	
    // ��� ���� �Լ�
    PxRigidStatic* CreatePlane(Vec4 _Plane);
    

};

