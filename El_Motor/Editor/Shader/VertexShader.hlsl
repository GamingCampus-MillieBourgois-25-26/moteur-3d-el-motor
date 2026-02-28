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
    
    // Fausse 3d
    output.pos = float4(vs.position.x, vs.position.y, vs.position.z, 1.0f);
    
    output.normal = vs.normal;
    output.uv = vs.uv;

    return output;
}