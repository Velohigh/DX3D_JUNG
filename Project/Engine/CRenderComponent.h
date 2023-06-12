#pragma once
#include "CComponent.h"


#include "CMesh.h"
#include "CMaterial.h"
#include "ptr.h"

class CRenderComponent :
    public CComponent
{
private:
    Ptr<CMesh>              m_pMesh;

    Ptr<CMaterial>          m_pSharedMtrl;      // 원본 메테리얼
    Ptr<CMaterial>          m_pDynamicMtrl;     // SharedMaterial 복사본
    Ptr<CMaterial>          m_pCurrentMtrl;     // 현재 사용 중인 재질
    float                   m_fBounding;        // FrustumCheck 용도 경계범위
    bool                    m_bFrustumCheck;    // 절두체 컬링 체크 유무

    bool                    m_bBoundDebugRender;    // 바운딩 경계 디버그 렌더 온오프


public:
    virtual void render() = 0;

public:
    void SetMesh(Ptr<CMesh> _Mesh) { m_pMesh = _Mesh; }
    void SetMaterial(Ptr<CMaterial> _Mtrl);

    Ptr<CMesh> GetMesh() { return m_pMesh; }
    Ptr<CMaterial> GetMaterial() { return m_pCurrentMtrl; }
    Ptr<CMaterial> GetSharedMaterial() { return m_pSharedMtrl; }
    Ptr<CMaterial> GetDynamicMaterial();

    void SetFrustumCheck(bool _bUse) { m_bFrustumCheck = _bUse; }
    bool IsUseFrustumCheck() { return m_bFrustumCheck; }
    void SetBounding(float _fBounding) { m_fBounding = _fBounding; }
    float GetBounding() { return m_fBounding; }
    void SetBoundDebug(bool _bound) { m_bBoundDebugRender = _bound; }
    bool IsUseBoundDebug() { return m_bBoundDebugRender; }

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;


public:
    CRenderComponent(COMPONENT_TYPE _type);
    ~CRenderComponent();
};

