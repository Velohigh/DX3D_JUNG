#pragma once
#include "CRenderComponent.h"

class CSkyBox :
    public CRenderComponent
{
public:
    virtual void finaltick() override;
    virtual void render() override;

    CLONE(CSkyBox);
public:
    CSkyBox();
    ~CSkyBox();
};

