#pragma once
#include "CRenderComponent.h"

class CDecal :
    public CRenderComponent
{
private:
    Ptr<CTexture>   m_DecalTex;
    int             m_Light;    // ��Į �ؽ��İ� �������� ��޵ɰ��� ����, true�� Emissive Ÿ���� ���Ÿ������ ��´�.
    bool            m_DebugShapeOn;
    float             m_Color[3];

public:
    void SetAsLight(bool _bLight) { m_Light = _bLight; }
    void SetOutputTexture(Ptr<CTexture> _Tex) { m_DecalTex = _Tex; }
    void SetDebugShape(bool _bDebugShapeOn) { m_DebugShapeOn = _bDebugShapeOn; }
    void SetColor(int _R, int _G, int _B) { m_Color[0] = _R; m_Color[1] = _G; m_Color[2] = _B; }

    const bool& GetDebugShape() { return m_DebugShapeOn; }
    const int& GetAsLight() { return m_Light; }
    Ptr<CTexture> GetOutputTexture() { return m_DecalTex; }
    float* GetColor() { return m_Color; }


    virtual void finaltick() override;
    virtual void render() override;

public:
    CLONE(CDecal);

public:
    CDecal();
    ~CDecal();
};