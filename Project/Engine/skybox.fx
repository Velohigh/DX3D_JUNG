#ifndef _SKYBOX
#define _SKYBOX

#include "value.fx"
#include "struct.fx"
#include "func.fx"

// =======================
// SkyBox Shader
// g_tex_0 : Output Texture
// =======================

struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

VS_OUT VS_SkyBox(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
        
    // ViewSpace ∑Œ √Î±ﬁ        
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matProj);
    output.vPosition.z = output.vPosition.w * 0.99f;
        
    output.vUV = _in.vUV;
    
    return output;
}

// Rasterizer

float4 PS_SkyBox(VS_OUT _in) : SV_Target
{
    float4 vOutColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    return vOutColor;
}



#endif
