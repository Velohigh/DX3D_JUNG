#include "pch.h"
#include "PhysXMgr.h"
#include <Engine\\CTimeMgr.h>

using namespace physx;

// 변수 선언
physx::PxDefaultErrorCallback   mDefaultErrorCallback;
physx::PxDefaultAllocator       mDefaultAllocatorCallback;
physx::PxDefaultCpuDispatcher*  mDispatcher = nullptr;
physx::PxTolerancesScale        mToleranceScale;

physx::PxFoundation*            mFoundation = nullptr;
physx::PxPhysics*               mPhysics = nullptr;

physx::PxScene*                 mScene = nullptr;
physx::PxMaterial*              mMaterial = nullptr;

physx::PxPvd*                   mPvd = nullptr;


PhysXMgr::PhysXMgr()
{
}

PhysXMgr::~PhysXMgr()
{
    // Cleanup
    mScene->release();
    mMaterial->release();
    mPhysics->release();
    mFoundation->release();

    if (nullptr != mDispatcher)
		mDispatcher->release();

    if (mPvd)
    {
        physx::PxPvdTransport* transport = mPvd->getTransport();
        mPvd->release(); mPvd = nullptr;
        if (transport)
        {
            transport->release();
            transport = nullptr;
        }
    }
}

void PhysXMgr::init()
{
	// Init PhysX
    // Foundation init (메모리 할당, 오류 보고, 디버그 출력 등의 기능을 제공)
    mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);
    if (!mFoundation)
        MessageBoxA(nullptr, "Error", "PxCreateFoundation failed!", MB_OK);

    // PhysX Visual Debugger init
    mPvd = PxCreatePvd(*mFoundation);
    physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
    mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

    // Physics init (PhysX 주요 기능을 제공하는 객체로, 물리 장면, 물체, 물질 등을 생성하는 기능을 제공)
    mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale, true, mPvd);
    if (!mPhysics)
        MessageBoxA(nullptr, "Error", "PxCreatePhysics failed!", MB_OK);

    // Create scene
    physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    //mDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
    mScene = mPhysics->createScene(sceneDesc);

    physx::PxPvdSceneClient* pvdClient = mScene->getScenePvdClient();
    if (pvdClient)
    {
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
        pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
    }

    // Create material (물리 객체 표면의 마찰력, 반탄력 등 설정)
    mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);

    ////////////////
    // Create actor

    // PxCreatePlane
    // 지면 평면 생성, PxPlane(0, 1, 0, 0)는 평면의 방정식을 나타내는데, 이 경우 y축을 따라 위쪽을 향하는 수평 평면을 나타냄
    // *mMaterial는 이 평면의 물리적 속성(마찰력, 반발력 등)을 정의하는 물질을 나타냄.
    //physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*mPhysics, physx::PxPlane(0, 1, 0, 0), *mMaterial);
    //mScene->addActor(*groundPlane);

    // 동적 물체 생성, #1 위치, #2 물체 모양, #3 속도(기본값 0)
    CreateDynamic(PxTransform(PxVec3(0, 40, 100)), PxSphereGeometry(10), PxVec3(0, -50, -100));
}

void PhysXMgr::progress()
{
	// Run simulation
    //mScene->simulate(DT);
    mScene->simulate(1.f/60.f);
    mScene->fetchResults(true);

}

PxRigidStatic* PhysXMgr::CreatePlane(Vec4 _Plane)
{
    physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*mPhysics, physx::PxPlane(_Plane.x, _Plane.y, _Plane.z, _Plane.w), *mMaterial);
    mScene->addActor(*groundPlane);
    return groundPlane;
}

PxRigidDynamic* PhysXMgr::CreateDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity)
{
    PxRigidDynamic* dynamic = PxCreateDynamic(*mPhysics, t, geometry, *mMaterial, 10.0f);
    dynamic->setAngularDamping(0.5f);   // 물체가 회전할 때 얼마나 빨리 속도가 줄어드는지를 결정
    dynamic->setLinearVelocity(velocity);   // 물체의 선속도, 물체가 얼마나 빨리 이동하는지를 결정
    mScene->addActor(*dynamic);             // 씬에 해당 액터 추가
    return dynamic;
}
