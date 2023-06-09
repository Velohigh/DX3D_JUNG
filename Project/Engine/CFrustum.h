#pragma once
#include "CEntity.h"

class CCamera;

enum FACE_TYPE
{
    FT_NEAR,
    FT_FAR,
    FT_LEFT,
    FT_RIGHT,
    FT_TOP,
    FT_BOT,
    FT_END,
};

class CFrustum :
    public CEntity
{
private:
    CCamera*    m_pOwner;
    Vec4        m_arrFace[FT_END];
    Vec3        m_arrProj[8];
    bool        m_DebugShape;

public:
    void finaltick();

public:
    bool FrustumCheckByPoint(Vec3 _vWorldPos);
    bool FrustumCheckBySphere(Vec3 _vWorldPos, float _fRadius);

public:
    void SetDebugShapeOn(bool _val) { m_DebugShape = _val; }

    Vec3* GetarrProj() { return m_arrProj; }
    bool& GetDebugShapeOn() { return m_DebugShape; }

public:
    CLONE(CFrustum);
    CFrustum(CCamera* _pOwner);
    ~CFrustum();
};

