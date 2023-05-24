#include "pch.h"
#include "Light3DUI.h"


Light3DUI::Light3DUI()
    : ComponentUI("##Light3D", COMPONENT_TYPE::LIGHT3D)
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




    return TRUE;
}