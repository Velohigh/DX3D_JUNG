#pragma once
#include "CComponent.h"


#include "CMesh.h"
#include "CMaterial.h"
#include "ptr.h"


struct tMtrlSet
{
    Ptr<CMaterial>  pSharedMtrl;    // 공유 메테리얼
    Ptr<CMaterial>  pDynamicMtrl;   // 공유 메테리얼의 복사본    
    Ptr<CMaterial>  pCurMtrl;       // 현재 사용 할 메테리얼
};

class CRenderComponent :
    public CComponent
{
private:
    Ptr<CMesh>              m_pMesh;
    vector<tMtrlSet>        m_vecMtrls;     // 재질    

    Ptr<CMaterial>          m_pSharedMtrl;      // 원본 메테리얼
    Ptr<CMaterial>          m_pDynamicMtrl;     // SharedMaterial 복사본
    Ptr<CMaterial>          m_pCurrentMtrl;     // 현재 사용 중인 재질
    float                   m_fBounding;        // FrustumCheck 용도 경계범위
    bool                    m_bFrustumCheck;    // 절두체 컬링 체크 유무
    bool                    m_bDynamicShadow;

    bool                    m_bBoundDebugRender;    // 바운딩 경계 디버그 렌더 온오프


public:
    virtual void render() = 0;
    virtual void render_depthmap();

public:
    void SetMesh(Ptr<CMesh> _Mesh);
    void SetMaterial(Ptr<CMaterial> _Mtrl, UINT _idx);

    Ptr<CMesh> GetMesh() { return m_pMesh; }

    Ptr<CMaterial> GetMaterial(UINT _idx);
    Ptr<CMaterial> GetSharedMaterial(UINT _idx);
    Ptr<CMaterial> GetDynamicMaterial(UINT _idx);

    UINT GetMtrlCount() { return (UINT)m_vecMtrls.size(); }

    void SetFrustumCheck(bool _bUse) { m_bFrustumCheck = _bUse; }
    bool IsUseFrustumCheck() { return m_bFrustumCheck; }
    void SetBounding(float _fBounding) { m_fBounding = _fBounding; }
    float GetBounding() { return m_fBounding; }
    void SetDynamicShadow(bool _bSet) { m_bDynamicShadow = _bSet; }
    bool IsDynamicShadow() { return m_bDynamicShadow; }
    void SetBoundDebug(bool _bound) { m_bBoundDebugRender = _bound; }
    bool IsUseBoundDebug() { return m_bBoundDebugRender; }

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;


public:
    CRenderComponent(COMPONENT_TYPE _type);
    ~CRenderComponent();
};

