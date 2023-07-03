#include "pch.h"
#include "CMeshRender.h"

#include "CCamera.h"

#include "CTransform.h"
#include "CAnimator2D.h"
#include "CAnimator3D.h"

#include "CLevelMgr.h"
#include "CLevel.h"

CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)		
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::finaltick()
{
	Vec3 MyWorldPos = Transform()->GetWorldPos();
	Vec3 LookCamDir;
	Matrix CamViewInv;

	CGameObject* MainCamObj = CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"MainCamera");

	if (nullptr != MainCamObj)
	{
		Vec3 CamWorldPos = MainCamObj->Transform()->GetWorldPos();

		LookCamDir = CamWorldPos - MyWorldPos;
		//LookCamDir.Normalize();

		CamViewInv = MainCamObj->Camera()->GetViewMat();
	//Transform()->SetRelativeRot(CamViewInv);
	}

	// Sphere 디버그 렌더
	if (IsUseBoundDebug())
	{
		DrawDebugCircle(MyWorldPos, GetBounding(), Vec4(0,0,1,1), LookCamDir);
	}
}

void CMeshRender::render()
{
	if (nullptr == GetMesh() || nullptr == GetMaterial(0))
		return;

	// Transform 에 UpdateData 요청
	Transform()->UpdateData();

	// Animator2D 컴포넌트가 있다면
	if (Animator2D())
	{
		Animator2D()->UpdateData();
	}

	// Animator3D 업데이트
	if (Animator3D())
	{
		Animator3D()->UpdateData();

		for (UINT i = 0; i < GetMtrlCount(); ++i)
		{
			if (nullptr == GetMaterial(i))
				continue;

			GetMaterial(i)->SetAnim3D(true); // Animation Mesh 알리기
			GetMaterial(i)->SetBoneCount(Animator3D()->GetBoneCount());
		}
	}


	// 렌더
	UINT iSubsetCount = GetMesh()->GetSubsetCount();

	for (UINT i = 0; i < iSubsetCount; ++i)
	{
		if (nullptr != GetMaterial(i))
		{
			// 사용할 재질 업데이트
			GetMaterial(i)->UpdateData();

			// 사용할 메쉬 업데이트 및 렌더링
			GetMesh()->render(i);
		}
	}

	// Animation 관련 정보 제거
	if (Animator2D())
		Animator2D()->Clear();

	if (Animator3D())
		Animator3D()->ClearData();
}