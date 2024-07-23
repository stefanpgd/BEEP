struct VertexPosColor
{
    float3 Position : POSITION;
    float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
};

struct VertexOutput
{
    float2 TexCoord : TexCoord;
    float3 Normal : Normal;
    float4 Position : SV_POSITION;
};

struct TransformData
{
    matrix MVP;
};
ConstantBuffer<TransformData> Transform : register(b0);

VertexOutput main(VertexPosColor IN)
{
    VertexOutput OUT;
    OUT.Position = mul(Transform.MVP, float4(IN.Position, 1.0f));
    OUT.Normal = normalize(mul(Transform.MVP, float4(IN.Normal, 0.0f)).xyz);
    OUT.TexCoord = IN.TexCoord;
    
    return OUT;
}