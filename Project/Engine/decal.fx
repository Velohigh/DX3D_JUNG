#pragma once
#ifndef _DECAL
#define _DECAL


#include "value.fx"

// =================
// Decal Shader
// RS_TYPE  : CULL_FRONT
// DS_TYPE  : NO_TEST_NO_WRITE
// BS_TYPE  : ONE_ONE

// g_tex_0  : Output Texture
// g_tex_1  : Position Target
// ==================
struct VS_DECAL_IN
{
    float3 vPos : POSITION;
};

struct VS_DECAL_OUT
{
    float4 vPosition : SV_Position;
};

VS_DECAL_OUT VS_Decal(VS_DECAL_IN _in)
{
    VS_DECAL_OUT output = (VS_DECAL_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    
    return output;
}

float4 PS_DebugShape(VS_DECAL_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    return vOutColor;
}




#endif
