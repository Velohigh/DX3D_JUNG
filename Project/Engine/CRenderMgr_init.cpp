#include "pch.h"
#include "CRenderMgr.h"

#include "CResMgr.h"
#include "CDevice.h"
#include "CStructuredBuffer.h"

#include "CMRT.h"



void CRenderMgr::init()
{
    // Light2DBuffer ����ȭ ���� ����
    m_Light2DBuffer = new CStructuredBuffer;
    m_Light2DBuffer->Create(sizeof(tLightInfo), 10, SB_TYPE::READ_ONLY, true);

    // Light3DBuffer ����ȭ ���� ����
    m_Light3DBuffer = new CStructuredBuffer;
    m_Light3DBuffer->Create(sizeof(tLightInfo), 10, SB_TYPE::READ_ONLY, true);


    // ==================
    // SwapChain MRT ����
    // ==================
    {
        Ptr<CTexture> arrRTTex[8] = { CResMgr::GetInst()->FindRes<CTexture>(L"RenderTargetTex"), };
        Ptr<CTexture> DSTex = CResMgr::GetInst()->FindRes<CTexture>(L"DepthStencilTex");

        m_MRT[(UINT)MRT_TYPE::SWAPCHAIN] = new CMRT;
        m_MRT[(UINT)MRT_TYPE::SWAPCHAIN]->Create(arrRTTex, DSTex);
    }

    // ============
    // Deferred MRT
    // ============
    {
        Vec2 vRenderResolotion = CDevice::GetInst()->GetRenderResolution();

        Ptr<CTexture> arrRTTex[8] = {
              CResMgr::GetInst()->CreateTexture(L"ColorTargetTex"
                , vRenderResolotion.x, vRenderResolotion.y
                , DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE
                , D3D11_USAGE_DEFAULT),

              CResMgr::GetInst()->CreateTexture(L"NormalTargetTex"
                , vRenderResolotion.x, vRenderResolotion.y
                , DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE
                , D3D11_USAGE_DEFAULT),

             CResMgr::GetInst()->CreateTexture(L"PositionTargetTex"
                , vRenderResolotion.x, vRenderResolotion.y
                , DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE
                , D3D11_USAGE_DEFAULT),

             CResMgr::GetInst()->CreateTexture(L"DataTargetTex"
                , vRenderResolotion.x, vRenderResolotion.y
                , DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE
                , D3D11_USAGE_DEFAULT),
        };

        Ptr<CTexture> DSTex = CResMgr::GetInst()->FindRes<CTexture>(L"DepthStencilTex");

        m_MRT[(UINT)MRT_TYPE::DEFERRED] = new CMRT;
        m_MRT[(UINT)MRT_TYPE::DEFERRED]->Create(arrRTTex, DSTex);
    }


    // =========
    // Light MRT
    // =========
    {
        Vec2 vRenderResolotion = CDevice::GetInst()->GetRenderResolution();

        Ptr<CTexture> arrRTTex[8] = {
              CResMgr::GetInst()->CreateTexture(L"DiffuseTargetTex"
                , vRenderResolotion.x, vRenderResolotion.y
                , DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE
                , D3D11_USAGE_DEFAULT),

              CResMgr::GetInst()->CreateTexture(L"SpecularTargetTex"
                , vRenderResolotion.x, vRenderResolotion.y
                , DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE
                , D3D11_USAGE_DEFAULT),
        };

        m_MRT[(UINT)MRT_TYPE::LIGHT] = new CMRT;
        m_MRT[(UINT)MRT_TYPE::LIGHT]->Create(arrRTTex, nullptr);
    }
}