#include "pch.h"
#include "CMRT.h"

#include "CDevice.h"

CMRT::CMRT()
	: m_RT{}
	, m_RTCount(0)
{
}

CMRT::~CMRT()
{
}

void CMRT::Create(Ptr<CTexture>(&_RTArr)[8], Ptr<CTexture> _DSTex)
{
	for (UINT i = 0; i < 8; ++i)
	{
		if (nullptr == _RTArr[i])
		{
			m_RTCount = i;
			break;
		}

		m_RT[i] = _RTArr[i];
	}

	m_DSTex = _DSTex;
}

void CMRT::OMSet()
{
	ID3D11RenderTargetView* RTView[8] = {};
	for (UINT i = 0; i < m_RTCount; ++i)
	{
		RTView[i] = m_RT[i]->GetRTV().Get();
	}

	CONTEXT->OMSetRenderTargets(m_RTCount, RTView, m_DSTex->GetDSV().Get());
}

void CMRT::Clear(float(&Color)[4])
{
	for (UINT i = 0; i < m_RTCount; ++i)
	{
		CONTEXT->ClearRenderTargetView(m_RT[i]->GetRTV().Get(), Color);
	}

	CONTEXT->ClearDepthStencilView(m_DSTex->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}