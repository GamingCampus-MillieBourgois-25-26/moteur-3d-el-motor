cbuffer ObjectColor : register(b0)
{
    float3 objColor;
    int useTexture; // 0 = pas de texture, 1 = utiliser texture
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

struct PS_INPUT
{
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_Target
{
    if (useTexture != 0)
        return tex.Sample(samp, input.uv);
    else
        return float4(objColor, 1.0f);
}