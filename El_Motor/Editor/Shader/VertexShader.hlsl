struct VSIn
{
    float4 position : POSITION;
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

    output.pos = vs.position;
    output.normal = vs.normal;
    output.uv = vs.uv;

    return output;
}