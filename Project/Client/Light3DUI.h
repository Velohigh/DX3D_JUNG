#pragma once

#include "ComponentUI.h"

class Light3DUI :
    public ComponentUI
{
private:
    bool    m_DebugShapeOn;

public:
    virtual int render_update() override;

public:
    Light3DUI();
    ~Light3DUI();
};

