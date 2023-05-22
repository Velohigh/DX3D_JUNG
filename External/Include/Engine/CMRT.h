#pragma once
#include "CEntity.h"


#include "CTexture.h"
#include "ptr.h"

class CMRT :
    public CEntity
{
private:
    Ptr<CTexture>   m_RT[8];
    UINT            m_RTCount;

    Ptr<CTexture>   m_DSTex;


public:
    void Create(Ptr<CTexture>(&_RTArr)[8], Ptr<CTexture> _DSTex);

    void OMSet();
    void Clear(float(&Color)[4]);

    CLONE_DISABLE(CMRT);
public:
    CMRT();
    ~CMRT();
};
//assortrock