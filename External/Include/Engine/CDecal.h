#pragma once
#include "CRenderComponent.h"

class CDecal :
    public CRenderComponent
{
private:
    Ptr<CTexture>   m_DecalTex;
    int             m_Light;    // ��Į �ؽ��İ� �������� ��޵ɰ��� ����, true�� Emissive Ÿ���� ���Ÿ������ ��´�.
    bool            m_DebugShapeOn;

public:
    void SetAsLight(bool _bLight) { m_Light = _bLight; }
    void SetOutputTexture(Ptr<CTexture> _Tex) { m_DecalTex = _Tex; }
    void SetDebugShape(bool _bDebugShapeOn) { m_DebugShapeOn = _bDebugShapeOn; }

    const bool& GetDebugShape() { return m_DebugShapeOn; }
    const int& GetAsLight() { return m_Light; }
    Ptr<CTexture> GetOutputTexture() { return m_DecalTex; }
    


    virtual void finaltick() override;
    virtual void render() override;

public:
    CLONE(CDecal);

public:
    CDecal();
    ~CDecal();
};