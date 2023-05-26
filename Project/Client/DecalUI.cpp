#include "pch.h"
#include "DecalUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CTransform.h>
#include <Engine\CMeshRender.h>
#include <Engine\CResMgr.h>
#include <Engine\CDecal.h>
#include "TreeUI.h"
#include "ListUI.h"


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

    // 데칼 텍스쳐 미리 띄우기
    ImGui::Text("OutputTexture");
    Ptr<CTexture> TargetTex = GetTarget()->Decal()->GetOutputTexture();
    char szBuff[50] = {};

    ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
    ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
    ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white

    if (TargetTex == nullptr)
    {
        ImGui::Image((ImTextureID)0, ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);
    }
    else
    {
        ImGui::Image((ImTextureID)TargetTex->GetSRV().Get(), ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);
    }


    // 선택된 텍스쳐 키값 출력
    GetResKey(TargetTex.Get(), szBuff, 50);
    ImGui::InputText("##OutputTextureName", szBuff, 50, ImGuiInputTextFlags_ReadOnly);

    // 텍스쳐 드래그 드랍으로 선택가능.
    if (ImGui::BeginDragDropTarget())
    {
        // 해당 노드에서 마우스 뗀 경우, 지정한 PayLoad 키값이 일치한 경우
        const ImGuiPayload* pPayLoad = ImGui::AcceptDragDropPayload("Resource");
        if (pPayLoad)
        {
            TreeNode* pNode = (TreeNode*)pPayLoad->Data;
            CRes* pRes = (CRes*)pNode->GetData();
            if (RES_TYPE::TEXTURE == pRes->GetType())
            {
                GetTarget()->Decal()->SetOutputTexture((CTexture*)pRes);
                //GetTarget()->MeshRender()->SetMesh((CMesh*)pRes);
            }
        }

        ImGui::EndDragDropTarget();
    }

    ImGui::SameLine();

    // 버튼 추가, 버튼 누를시, List UI 로 텍스쳐 선택 가능
    if (ImGui::Button("##TextureSelectBtn", ImVec2(18, 18)))
    {
        const map<wstring, Ptr<CRes>>& mapTex = CResMgr::GetInst()->GetResources(RES_TYPE::TEXTURE);

        ListUI* pListUI = (ListUI*)ImGuiMgr::GetInst()->FindUI("##List");
        pListUI->Reset("Texture List", ImVec2(300.f, 500.f));
        for (const auto& pair : mapTex)
        {
            pListUI->AddItem(string(pair.first.begin(), pair.first.end()));
        }

        // 항목 선택시 호출받을 델리게이트 등록
        pListUI->AddDynamic_Select(this, (UI_DELEGATE_1)&DecalUI::SelectTexture);
    }


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

void DecalUI::SelectTexture(DWORD_PTR _Key)
{
    string strKey = (char*)_Key;
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(wstring(strKey.begin(), strKey.end()));
    GetTarget()->Decal()->SetOutputTexture(pTex);

}
