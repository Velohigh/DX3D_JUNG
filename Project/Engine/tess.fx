#ifndef _TESS
#define _TESS

#include "value.fx"

// ========================
// TessShader
// g_tex_0 : Color Texture
// ========================
struct VS_INOUT
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

// ==============
// Vertex Shader
// ==============
VS_INOUT VS_Tess(VS_INOUT _in)
{
    VS_INOUT output = (VS_INOUT) 0.f;
       
    output = _in;
    
    return output;
}



// ===========
// Hull Shader
// ===========
struct HS_OUT
{
       
};

HS_OUT HS_Tess(InputPatch<VS_INOUT, 3> _input
                , uint i : SV_OutputControlPointID
                , uint PatchID : SV_PrimitiveID)
{
    HS_OUT output = (HS_OUT) 0.f;
    
    // _input[i];
    
    
    return output;
}






// ============
// Pixel Shader
// ============
float4 PS_Tess(HS_OUT _in) : SV_Target
{
    float4 vObjectColor = float4(0.f, 1.f, 0.f, 1.f);
    float4 vOutColor = float4(0.f, 0.f, 0.f, 1.f);
   
    vOutColor.xyz = vObjectColor;
    return vOutColor;
}






#endif
