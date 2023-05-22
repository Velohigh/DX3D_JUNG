#include "pch.h"
#include "CLight3D.h"

#include "CTransform.h"
#include "CRenderMgr.h"
#include "CResMgr.h"


CLight3D::CLight3D()
	: CComponent(COMPONENT_TYPE::LIGHT3D)
	, m_LightInfo{}
{
	SetLightType(LIGHT_TYPE::POINT);
}

CLight3D::~CLight3D()
{
}


void CLight3D::SetLightType(LIGHT_TYPE _Type)
{
	m_LightInfo.LightType = (UINT)_Type;

	if (LIGHT_TYPE::DIRECTIONAL == _Type)
	{
		m_VolumeMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
		//m_LightMtrl = 
	}

	else if (LIGHT_TYPE::POINT == _Type)
	{
		m_VolumeMesh = CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh");
		//m_LightMtrl = 
	}

	else
	{
		m_VolumeMesh = CResMgr::GetInst()->FindRes<CMesh>(L"ConeMesh");
		//m_LightMtrl = 
	}
}

void CLight3D::finaltick()
{
	m_LightInfo.vWorldPos = Transform()->GetWorldPos();
	m_LightInfo.vWorldDir = Transform()->GetWorldDir(DIR_TYPE::FRONT);

	CRenderMgr::GetInst()->RegisterLight3D(this);
}

void CLight3D::render()
{
	m_LightMtrl->UpdateData();
	m_VolumeMesh->render();
}

void CLight3D::SaveToLevelFile(FILE* _File)
{
}

void CLight3D::LoadFromLevelFile(FILE* _File)
{
}

