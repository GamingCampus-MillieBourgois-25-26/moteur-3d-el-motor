cbuffer ObjectColor : register(b0)
{
    float3 objColor;
};

float4 main() : SV_Target
{
    return float4(objColor, 1.0f);
}