#include "pch.h"
#include "CameraUI.h"
#include <Engine\CGameObject.h>
#include <Engine\CCamera.h>
#include <Engine\CFrustum.h>


CameraUI::CameraUI()
    : ComponentUI("##Camera", COMPONENT_TYPE::CAMERA)
{
    SetName("Camera");
}

CameraUI::~CameraUI()
{
}

int CameraUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;
    
    // ī�޶� �þ� ����� ������ ������ üũ�ڽ�
    bool& FrustumDebugShape = GetTarget()->Camera()->GetFrustum().GetDebugShapeOn();
    ImGui::Checkbox("##FrustumDebugShapeBox", &FrustumDebugShape);
    ImGui::SameLine();
    ImGui::Text("FrustumDebugShape");

    if (FrustumDebugShape)
    {
        CFrustum _Frustum = GetTarget()->Camera()->GetFrustum();
        _Frustum.SetDebugShapeOn(true);

    }
    else
    {
        CFrustum _Frustum = GetTarget()->Camera()->GetFrustum();
        _Frustum.SetDebugShapeOn(false);

        //GetTarget()->Decal()->SetDebugShape(false);
    }

    // Far �� ����

    float fFar = GetTarget()->Camera()->GetFar();

    ImGui::Text("Far");
    ImGui::SameLine();
    ImGui::DragFloat("##Far", &fFar);
    GetTarget()->Camera()->SetFar(fFar);





    return TRUE;
}
