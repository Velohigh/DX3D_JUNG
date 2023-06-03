#pragma once

#include "ComponentUI.h"

class DecalUI :
    public ComponentUI
{
private:
    bool ColorCheckBox;

public:
    virtual int render_update() override;

    void SelectTexture(DWORD_PTR _Key);


public:
    DecalUI();
    ~DecalUI();
};

