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

    // ±¤¿ø µð¹ö±× ¼ÎÀÌÇÁ ·»´õ¸µ Ã¼Å©¹Ú½º
    bool& DecalDebugShapeOn = GetTarget()->Decal()->GetDebugShape();
    ImGui::Checkbox("##DebugShapeCheckBox", &DecalDebugShapeOn);
    ImGui::SameLine();
    ImGui::Text("DebugShapeOn");




    return TRUE;
}