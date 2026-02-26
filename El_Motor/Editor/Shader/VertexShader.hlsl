struct VSOut
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
};

VSOut main(float3 position : POSITION,
           float3 normal : NORMAL,
           float2 uv : TEXCOORD0)
{
    VSOut output;

    output.pos = float4(position, 1.0f);
    output.normal = normal;
    output.uv = uv;

    return output;
}