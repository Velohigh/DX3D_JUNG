#include "pch.h"
#include "DecalUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CTransform.h>
#include <Engine\CMeshRender.h>
#include <Engine\CResMgr.h>
#include <Engine\CDecal.h>


DecalUI::DecalUI()
    : ComponentUI("##DecalUI", COMPONENT_TYPE::DECAL)
{
    SetName("Decal");
}

DecalUI::~DecalUI()
{
}


int DecalUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    // ��Į ����� ������ ������ üũ�ڽ�
    bool DecalDebugShapeOn = GetTarget()->Decal()->GetDebugShape();
    ImGui::Checkbox("##DebugShapeCheckBox", &DecalDebugShapeOn);
    ImGui::SameLine();
    ImGui::Text("DebugShapeOn");

    if (DecalDebugShapeOn)
    {
        GetTarget()->Decal()->SetDebugShape(true);
    }
    else
    {
        GetTarget()->Decal()->SetDebugShape(false);
    }


    // ��Į �������� ����Ұ��� üũ�ڽ�
    bool DecalAsLightOn = GetTarget()->Decal()->GetAsLight();
    ImGui::Checkbox("##AsLightCheckBox", &DecalAsLightOn);
    ImGui::SameLine();
    ImGui::Text("AsLightOn");

    if (DecalAsLightOn)
    {
        GetTarget()->Decal()->SetAsLight(true);
    }
    else
    {
        GetTarget()->Decal()->SetAsLight(false);
    }




    return TRUE;
}