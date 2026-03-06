cbuffer MatrixBuffer : register(b0)
{
    matrix view;
    matrix projection;
    matrix vp;
};

struct VSIn
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
};

struct VSOut
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
};

VSOut main(VSIn vs)
{
    VSOut output;

    float4 worldPos = float4(vs.position, 1.0f);

    // transformation complète
    output.pos = mul(worldPos, vp);

    output.normal = vs.normal;
    output.uv = vs.uv;

    return output;
}