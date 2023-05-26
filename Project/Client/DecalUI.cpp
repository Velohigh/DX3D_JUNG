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

    // 데칼 디버그 셰이프 렌더링 체크박스
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


    // 데칼 광원으로 취급할건지 체크박스
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