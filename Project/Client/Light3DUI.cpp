#include "pch.h"
#include "Light3DUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CTransform.h>
#include <Engine\CMeshRender.h>
#include <Engine\CLight3D.h>
#include <Engine\CResMgr.h>


Light3DUI::Light3DUI()
    : ComponentUI("##Light3D", COMPONENT_TYPE::LIGHT3D)
    , m_DebugShapeOn(true)
{
    SetName("Light3D");
}

Light3DUI::~Light3DUI()
{
}


int Light3DUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    float fRadius = GetTarget()->Light3D()->GetRadius();

    ImGui::Text("Radius");
    ImGui::SameLine();
    ImGui::DragFloat("##Relative Position", &fRadius);

    GetTarget()->Light3D()->SetRadius(fRadius);

    // ���� ����� ������ ������ üũ�ڽ�
    ImGui::Checkbox("##DebugShapeCheckBox", &m_DebugShapeOn);
    ImGui::SameLine();
    ImGui::Text("DebugShape");

    if (m_DebugShapeOn)
    {
        // ����Ʈ Ÿ�Կ� ����, ���̾� ���������� ǥ���� �޽� ����
        LIGHT_TYPE LightType = GetTarget()->Light3D()->GetLightType();

        if (LIGHT_TYPE::DIRECTIONAL == LightType)
        {
            GetTarget()->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"Sphere"));
        }
        else if (LIGHT_TYPE::POINT == LightType)
        {
            GetTarget()->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"Sphere"));
        }
        else if (LIGHT_TYPE::SPOT == LightType)
        {
            GetTarget()->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"ConeMesh"));
        }
    }
    else
    {
        GetTarget()->MeshRender()->SetMesh(nullptr);
    }




    return TRUE;
}