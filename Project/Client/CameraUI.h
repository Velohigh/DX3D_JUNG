#pragma once
#include "ComponentUI.h"
class CameraUI :
    public ComponentUI
{
private:

public:
    virtual int render_update() override;

public:
    CameraUI();
    ~CameraUI();
};

