#pragma once
#include <Engine\CScript.h>

class CPlayerScript :
    public CScript
{
private:
    float       m_fSpeed;
    Vec3        m_vForce;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;

private:
    void Shoot();

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CPlayerScript);
public:
    CPlayerScript();
    ~CPlayerScript();
};

