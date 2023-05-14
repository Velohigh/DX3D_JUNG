#ifndef _STD3D
#define _STD3D

#include "value.fx"
#include "struct.fx"
#include "func.fx"


// ========================
// Std3D Shader
//
// g_tex_0 : Color Texture
// g_tex_1 : Normal Texture
// ========================


struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
   
    float3 vTangent : TANGENT;
    float3 vNormal : NORMAL;
    float3 vBinormal : BINORMAL;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    
    float3 vViewPos : POSITION;
    
    float3 vViewTangent : TANGENT;
    float3 vViewNormal : NORMAL;
    float3 vViewBinormal : BINORMAL;
};

VS_OUT VS_Std3D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
        
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
    output.vViewTangent = normalize(mul(float4(_in.vTangent, 0.f), g_matWV));
    output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV));
    output.vViewBinormal = normalize(mul(float4(_in.vBinormal, 0.f), g_matWV));
    
    return output;
}

// Rasterizer

float4 PS_Std3D(VS_OUT _in) : SV_Target
{
    float4 vObjectColor = float4(0.4f, 0.4f, 0.4f, 1.f);
    float4 vOutColor = float4(0.f, 0.f, 0.f, 1.f);
    
    float3 vViewNormal = _in.vViewNormal;
     
    // 텍스쳐가 있으면, 해당 색상을 사용한다.
    if (g_btex_0)
    {
        vObjectColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    }
       
    // NomalMap 이 있다면
    if (g_btex_1 && g_int_0 == 1)
    {
        float3x3 matRot =
        {
            _in.vViewTangent,
            -_in.vViewBinormal,
            _in.vViewNormal,
        };

        float3 vNormal = g_tex_1.Sample(g_sam_0, _in.vUV);
        vNormal = (vNormal * 2.f) - 1.f;
        vViewNormal = mul(vNormal, matRot);
    }
    
    // Light 의 ViewSpace 에서의 방향
    float3 vLightDir = mul(float4(g_Light3DBuffer[0].vWorldDir.xyz, 0.f), g_matView);
    
    // Diffuse Power
    float fPow = saturate(dot(-vLightDir, vViewNormal));
            
    // Specular 계산
    float3 vViewReflect = normalize(vLightDir + 2.f * (dot(-vLightDir, vViewNormal)) * vViewNormal);
    
    // 카메라에서 픽셀 지점을 바라보는 시선 벡터
    float3 vEye = -normalize(_in.vViewPos);
    
    // 반사광 세기          
    float fRelfectPow = pow(saturate(dot(vViewReflect, vEye)), 10);
        
    // 광원 적용
    vOutColor.xyz = vObjectColor.xyz * g_Light3DBuffer[0].Color.vDiffuse.xyz * fPow
                    + g_Light3DBuffer[0].Color.vSpecular.xyz * fRelfectPow
                    + g_Light3DBuffer[0].Color.vAmbient.xyz * vObjectColor.xyz;
    
    return vOutColor;
}

#endif
