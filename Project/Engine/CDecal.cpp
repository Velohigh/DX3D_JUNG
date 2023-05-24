#include "pch.h"
#include "CDecal.h"

#include "CTransform.h"
#include "CResMgr.h"

CDecal::CDecal()
	: CRenderComponent(COMPONENT_TYPE::DECAL)
{
	SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CubeMesh"));

}

CDecal::~CDecal()
{
}

void CDecal::finaltick()
{
	const Matrix& matWorld = Transform()->GetWorldMat();
	DrawDebugCube(matWorld, Vec4(0.f, 1.f, 0.f, 1.f), 0.f);
}

void CDecal::render()
{

}
