#include "pch.h"
#include "CMeshRender.h"

#include "CCamera.h"

#include "CTransform.h"
#include "CAnimator2D.h"
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

	// 재질 업데이트
	GetMaterial(0)->UpdateData();

	// 렌더
	GetMesh()->render(0);

	// Animation 관련 정보 제거
	if (Animator2D())
		Animator2D()->Clear();
}