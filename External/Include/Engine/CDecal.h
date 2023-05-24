#pragma once
#include "CRenderComponent.h"

class CDecal :
    public CRenderComponent
{
private:
    Ptr<CTexture>   m_DecalTex;

public:
    virtual void finaltick() override;
    virtual void render() override;

public:
    CLONE(CDecal);

public:
    CDecal();
    ~CDecal();
};