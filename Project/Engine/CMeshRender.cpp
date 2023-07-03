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

	// Sphere ����� ����
	if (IsUseBoundDebug())
	{
		DrawDebugCircle(MyWorldPos, GetBounding(), Vec4(0,0,1,1), LookCamDir);
	}
}

void CMeshRender::render()
{	
	if (nullptr == GetMesh() || nullptr == GetMaterial(0))
		return;

	// Transform �� UpdateData ��û
	Transform()->UpdateData();

	// Animator2D ������Ʈ�� �ִٸ�
	if (Animator2D())
	{
		Animator2D()->UpdateData();
	}

	// ���� ������Ʈ
	GetMaterial(0)->UpdateData();

	// ����
	GetMesh()->render(0);

	// Animation ���� ���� ����
	if (Animator2D())
		Animator2D()->Clear();
}