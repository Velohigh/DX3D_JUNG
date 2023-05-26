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

    // ��Į �ؽ��� �̸� ����
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


    // ���õ� �ؽ��� Ű�� ���
    GetResKey(TargetTex.Get(), szBuff, 50);
    ImGui::InputText("##OutputTextureName", szBuff, 50, ImGuiInputTextFlags_ReadOnly);

    // �ؽ��� �巡�� ������� ���ð���.
    if (ImGui::BeginDragDropTarget())
    {
        // �ش� ��忡�� ���콺 �� ���, ������ PayLoad Ű���� ��ġ�� ���
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

    // ��ư �߰�, ��ư ������, List UI �� �ؽ��� ���� ����
    if (ImGui::Button("##TextureSelectBtn", ImVec2(18, 18)))
    {
        const map<wstring, Ptr<CRes>>& mapTex = CResMgr::GetInst()->GetResources(RES_TYPE::TEXTURE);

        ListUI* pListUI = (ListUI*)ImGuiMgr::GetInst()->FindUI("##List");
        pListUI->Reset("Texture List", ImVec2(300.f, 500.f));
        for (const auto& pair : mapTex)
        {
            pListUI->AddItem(string(pair.first.begin(), pair.first.end()));
        }

        // �׸� ���ý� ȣ����� ��������Ʈ ���
        pListUI->AddDynamic_Select(this, (UI_DELEGATE_1)&DecalUI::SelectTexture);
    }


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

void DecalUI::SelectTexture(DWORD_PTR _Key)
{
    string strKey = (char*)_Key;
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(wstring(strKey.begin(), strKey.end()));
    GetTarget()->Decal()->SetOutputTexture(pTex);

}
