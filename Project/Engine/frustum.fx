#ifndef _STD3D
#define _STD3D

#include "value.fx"
#include "struct.fx"
#include "func.fx"


// ========================
// Frustum Shader
// 
// ========================


#define CameraPos g_int_0;


struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    
    float3 vViewPos : POSITION;
};

VS_OUT VS_Frustum(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
        
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
    
    return output;
}

// Rasterizer

float4 PS_Frustum(VS_OUT _in) : SV_Target
{
    float4 vOutColor = float4(0.f, 1.f, 0.f, 1.f);

    return vOutColor;
}



#endif
