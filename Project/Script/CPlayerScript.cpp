#include "pch.h"
#include "CPlayerScript.h"

#include <Engine\CMeshRender.h>
#include <Engine\CMaterial.h>

#include "CMissileScript.h"
#include <Engine\PhysXMgr.h>


CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, m_fSpeed(2000.f)
	, m_vForce(0.f)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fSpeed, "Speed");
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::begin()
{
	MeshRender()->GetDynamicMaterial(0);
}

void CPlayerScript::tick()
{
	Vec3 vCurPos = Transform()->GetRelativePos();
	

	if (KEY_PRESSED(KEY::R))
	{
		vCurPos.y += DT * 100.f;

	}


	if (KEY_PRESSED(KEY::UP))
	{
		for (int i = 0; i < 4; ++i)
		{
			m_vForce.z += DT * m_fSpeed;
		}
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		for (int i = 0; i < 4; ++i)
		{
			m_vForce.z -= DT * m_fSpeed;
		}
	}

	if (KEY_PRESSED(KEY::LEFT))
	{
		for (int i = 0; i < 4; ++i)
		{
			m_vForce.x -= DT * m_fSpeed;
		}
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		for (int i = 0; i < 4; ++i)
		{
			m_vForce.x += DT * m_fSpeed;
		}
	}

	if (KEY_PRESSED(KEY::Z))
	{
		Vec3 vRot = Transform()->GetRelativeRot();
		vRot.z += DT * XM_PI;
		Transform()->SetRelativeRot(vRot);
	}

	Transform()->SetRelativePos(vCurPos);	

	//// 물리월드에서 변형된 좌표값 가져오기
	//PhysXMgr::GetInst()->GetTestActor()->setGlobalPose(physx::PxTransform(vCurPos.x, vCurPos.y, vCurPos.z));
	//PxVec3 PxForce = PxVec3(m_vForce.x, m_vForce.y, m_vForce.z);
	//PhysXMgr::GetInst()->GetTestActor()->addForce(PxForce);

	//if (KEY_TAP(KEY::SPACE))
	//{
	//	DrawDebugCircle(Transform()->GetWorldPos(), 500.f, Vec4(0.f, 0.f, 1.f, 1.f), Vec3(0.f, 0.f, 0.f), 2.f);
	//
	//	Shoot();
	//}	
}

void CPlayerScript::Shoot()
{
	// 미사일 프리팹 참조
	Ptr<CPrefab> pMissilePrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"MissilePrefab");
	Vec3 vMissilePos = Transform()->GetRelativePos() + Vec3(0.f, 0.5f, 0.f) * Transform()->GetRelativeScale();
	CGameObject* pCloneMissile = pMissilePrefab->Instantiate();

	// 레벨에 추가
	SpawnGameObject(pCloneMissile, vMissilePos, L"PlayerProjectile");
}



void CPlayerScript::BeginOverlap(CCollider2D* _Other)
{
	
}





void CPlayerScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_fSpeed, sizeof(float), 1, _File);
}

void CPlayerScript::LoadFromLevelFile(FILE* _File)
{
	fread(&m_fSpeed, sizeof(float), 1, _File);
}